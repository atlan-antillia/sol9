/******************************************************************************
 *
 * Copyright (c) 2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer.
 *  
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *  ZipFileParser.h
 *
 *****************************************************************************/

// SOL9
// 2008/09/04


#pragma once

#include <sol\Thread.h>
#include <sol/String.h>

namespace SOL {

#define WM_THREAD_CANCEL  (WM_USER + 2008)


#define ERR_ZS_NULL_POINTER  -5000
#define ERR_ZS_NOT_FOUND  -5001
#define ERR_ZS_OPEN    -5002
#define ERR_ZS_SIGNATURE  -5003
#define ERR_ZS_SIZE    -5004


/* For zip file format, see the following:
 * http://www.pkware.com/documents/casestudies/APPNOTE.TXT 
 */

/**
 * ZipFileParser class is a thread class to parse a zip file and
 * extrace each entry of the file.
 */
class ZipFileParser: public Thread {

  static struct LocalFileHeader {
   // unsigned int signature;
        unsigned short versionNeededToExtract; // Version needed to extract: 2 bytes 
        unsigned short flags; // General purpose bit flag: 2 bytes 
        unsigned short compressionMethod; // Compression method: 2 bytes 
        unsigned short lastModifiedTime; // Last modified time: 2 bytes 
        unsigned short lastModifiedDate; // Last modified date: 2 bytes 
        unsigned int crc32;     // CRC-32: 4 bytes 
        unsigned int compressedSize;   // Compressed size: 4 bytes 
        unsigned int uncompressedSize;   // Uncompressed size: 4 bytes 
        unsigned short fileNameLength;   // File name length: 2 bytes 
        unsigned short extraFieldLength; // Extra field length: 2 bytes 
        // File name (variable size) 
        // Extra field (variable size) 
  };

  static struct FileHeader
  {
   // unsigned int signature;
        unsigned short versionMadeBy;     // Version made by :2 bytes 
        unsigned short versionNeededToExtract;   // Version needed to extract: 2 bytes 
        unsigned short flags;       // General purpose bit flag: 2 bytes 
        unsigned short compressionMethod;   // Compression method: 2 bytes 
        unsigned short lastModifiedTime;   // Last modified time: 2 bytes 
        unsigned short lastModifiedDate;   // Last modified date: 2 bytes 
        unsigned int crc32;       // CRC-32: 4 bytes 
        unsigned int compressedSize;     // Compressed size: 4 bytes 
        unsigned int uncompressedSize;     // Uncompressed size: 4 bytes 
        unsigned short fileNameLength;     // File name length: 2 bytes 
        unsigned short extraFieldLength;   // Extra field length: 2 bytes 
        unsigned short fileCommentLength;   // File comment length: 2 bytes 
        unsigned short diskNumberStart;   // Disk number start: 2 bytes 
        unsigned short internalFileAttribs;   // Internal file attributes: 2 bytes 
        unsigned int externalFileAttribs;   // External file attributes: 4 bytes 
        unsigned int relativeOffsetOfLocalHeader; // Relative offset of local header: 4 bytes 
        // File name (variable size) 
        // Extra field (variable size) 
        // File comment (variable size) 
  };

  static struct ExtendedHeader {
    //unsigned int signature;  // Local file header signature: 4 bytes  (0x08074b50)
  unsigned int crc32;    // CRC-32: 4 bytes
  unsigned int compressedSize;  // Compressed size: 4 bytes
  unsigned int uncompressedSize;  // Uncompressed size:4 bytes
  };

  static struct EndOfCentralDir
  {
        //unsigned int signature;     // 4 bytes (0x06054b50)
        unsigned short numberOfThisDisk;    // 2 bytes
        unsigned short numberOfTheDiskWithStartOfCentralDirectory; // 2 bytes
        unsigned short nCentralDirectoryEntries_ThisDisk;       // 2 bytes
        unsigned short nCentralDirectoryEntries_Total;  // 2 bytes
        unsigned int centralDirectorySize;   // 4 bytes
        unsigned int startOfCentralDirOffset;   // 4 bytes
        unsigned short commentLength;     // 2 bytes
        // Zip file comment follows
  };

private:

  unsigned char* startPos;

  unsigned char* currentPos;

  unsigned char* endPos;

private:
  int  files;
  int  encryptedFiles;
  int  unencryptedFiles;

  bool  encrypted;

private:
  bool  looping;

private:
  static  const unsigned int SIG_LOCAL_FILE_HEADER = 0x04034b50;
  static  const unsigned int SIG_FILE_HEADER       = 0x02014b50;
  static  const unsigned int SIG_EXTENDED_HEADER   = 0x08074b50;
  static  const unsigned int SIG_END_OF_CENTRAL_DIR= 0x06054b50;


public:
  /**
   * Constructor
   */
  ZipFileParser()
    :Thread(),
    startPos(NULL),
    currentPos(NULL),
    endPos(NULL),
    files(0),
    encryptedFiles(0),
    unencryptedFiles(0),
    encrypted(false),
    looping(false)
  {

  }


public:
  /**
   * Destructor
   */
  ~ZipFileParser() {
    close();
  }


public:
  void close() {
    if (startPos) {
      delete [] startPos;
      startPos = NULL;
    }
    currentPos = NULL;
    endPos     = NULL;
  }


public:
  /**
   *
   */
  int open(const TCHAR* filePath)
  {
    int rc = -1;  
    if (filePath == NULL) {
      throw ERR_ZS_NULL_POINTER;
    }

    if (GetFileAttributes(filePath) == 0xffffffff) {
      throw ERR_ZS_NOT_FOUND;
    }

    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, filePath, _T("rb"));
  
    if (err == 0 && fp) {
      int size = _filelength(_fileno(fp));
      
      if (size >= sizeof(int)) {
        //
        unsigned char* buffer = new unsigned char[size];
        fread(buffer, 1, size, fp);
        startPos = buffer;
        currentPos = buffer;
        endPos = startPos + size;
        unsigned int sig = 0;
      
        memcpy(&sig, buffer, sizeof(sig));
        if (sig != SIG_LOCAL_FILE_HEADER) {
          fclose(fp);
          fp = NULL;
          throw ERR_ZS_SIGNATURE;
        }
      } else {
        fclose(fp);
        fp = NULL;
        throw ERR_ZS_SIZE;
      }

      if (fp) {
        fclose(fp);
        fp = NULL;
      }
      rc = 0;  //NO_ERROR
    } else {
      throw ERR_ZS_OPEN;
    } 
    return rc;
  }

public:
  virtual void displayFilename(const TCHAR* filename, bool enc, const TCHAR* dateTime, 
        int originalFileSize, int packedFileSize)
  {
    //printf("%s%s %s %d/%d\n", 
    //  filename, enc, dateTime, unsize, cmsize);
    TCHAR* encoded = _T("");
    if (enc) {
      encoded = _T("+");
    }
    
    _tprintf(_T("%s%s %s %d(Bytes)\n"), 
      filename, encoded, dateTime, originalFileSize);

  }

public:
  virtual void displayFoldername(const TCHAR* filename, const TCHAR* dateTime)
  {
    _tprintf(_T("%s %s\n"), 
        filename, dateTime);

  }

private:
  bool doMessageLoop()
  {
    MSG msg;
    bool rc = true;
    while (PeekMessage (&msg,NULL,0,0,PM_REMOVE)) {
      Sleep(10);

      if (msg.message == WM_THREAD_CANCEL) {
        rc = false;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    return rc;
  }

public:
  bool isLooping() {
    return   looping;
  }


public:
  // Thread procedure
  void run()
  {
    this-> files = 0;

    looping = true;
 
    while (looping) {
    
      if (doMessageLoop()==false) {
        break;
      }

      unsigned int sig;
      
      int r = read(&sig);

      if (r ==0) {
        break;
      }
      //printf("Signature =%x\n", sig);
      switch(sig) {

      case SIG_LOCAL_FILE_HEADER: 
      {      
        LocalFileHeader header;
        read(header, sizeof(header));

        char* filename = new char[header.fileNameLength+1];
        read(filename, header.fileNameLength);
        filename[header.fileNameLength] = '\0';
        //printf("Filename=[%s]\n", filename);
        delete [] filename;

        seekCurrent(header.extraFieldLength); 
        seekCurrent(header.compressedSize);
    
        if (header.flags & 8) {
          //printf("1 Extended header\n");
          int pos = search(SIG_EXTENDED_HEADER, sizeof(SIG_EXTENDED_HEADER));
          if (pos>0) {
            //printf("Found SIG_EXTENDED_HEADER \n");
            seekCurrent(pos);
          }
        }
      }

      break;

      case SIG_FILE_HEADER:
      {
        FileHeader header;
        read(header, sizeof(header));
      
        char* filename = new char[header.fileNameLength+1];
        read(filename, header.fileNameLength);
        filename[header.fileNameLength] = '\0';

        int cmsize = header.compressedSize;
        int unsize = header.uncompressedSize;  
        unsigned short ltime = header.lastModifiedTime; 
        unsigned short ldate = header.lastModifiedDate; 

        char dateTime[128];
        memset(&dateTime, 0, sizeof(dateTime));
        getLastModifiedDateTime(ldate, ltime, dateTime, CountOf(dateTime) ); //2015/12/23

        //If filename doesn't end with '/', it's a filename
        // 
        if (filename[strlen(filename)-1] != '/') {
          //char* enc = "";
          bool enc = false;

          this->files++;
          if (header.flags & 1) {
            enc = true;
            this->encryptedFiles++;
          } else {
            this->unencryptedFiles++;
          }

          displayFilename(String(filename),
            enc, String(dateTime), unsize, cmsize);

        } else {
          displayFoldername(String(filename), String(dateTime));
        }

        delete [] filename;
  
        seekCurrent(header.extraFieldLength); 

        seekCurrent(header.fileCommentLength);
        if (header.flags & 8) {
          //printf("2 Extended header\n");
        }
      }
      break;

      case SIG_EXTENDED_HEADER:
      {
        ExtendedHeader header;
        read(header, sizeof(header));
      }
      break;

      case SIG_END_OF_CENTRAL_DIR:
      {
        EndOfCentralDir header;
        read(header, sizeof(header));
        seekCurrent(header.commentLength);

        printf("Completed\n");
        looping = false;
      }
      break;

      default:
        break;
      }
    }
    if (this->files>0 && this->files == this->encryptedFiles) {
      this->encrypted = true;
    }

    delete this;
  }

public:
  bool isEncrypted() {
    return encrypted;
  }
  
private:
  int read(unsigned int* integer) {
    int rc = 0;
    size_t size = sizeof(int);
    if ((currentPos-size)<endPos) {
      memcpy(integer, currentPos, size);
      currentPos += size;
      rc = size;
    }
    else {
      rc =  0;
    }
    return rc;
  }

private:
  int read(void* data, size_t size) {
    int rc = 0;
    if ((currentPos-size)<endPos) {
      memcpy(data, currentPos, size);
      currentPos += size;
      rc = size;
    }
    else {
      rc =  0;
    }
    return rc;
  }

private:
  int seekCurrent(size_t size) {
    int rc = 0;
    if (size >0 && (currentPos-size)<endPos) {  
      currentPos += size;
      rc = size;
    }
    else {
      rc =  0;
    }
    return rc;

  }
  
private:
  int read(LocalFileHeader& h, size_t size) {
    int rc = 0;
    memset(&h, 0, sizeof(h));
    if ((currentPos-size)<endPos) {
            read(&h.versionNeededToExtract, sizeof(h.versionNeededToExtract)); 

      read(&h.flags,  sizeof(h.flags)); 

            read(&h.compressionMethod, sizeof(h.compressionMethod));

            read(&h.lastModifiedTime, sizeof(h.lastModifiedTime));

            read(&h.lastModifiedDate, sizeof(h.lastModifiedDate));

            read(&h.crc32, sizeof(h.crc32));

            read(&h.compressedSize, sizeof(h.compressedSize));

      read(&h.uncompressedSize, sizeof(h.uncompressedSize)); 

      read(&h.fileNameLength, sizeof(h.fileNameLength));

      read(&h.extraFieldLength, sizeof(h.extraFieldLength));
      
      rc = size;
    }
    else {
      rc =  0;
    }
    return rc;
  }  

private:
  int read(FileHeader& h, size_t size) {
    int rc = 0;
    memset(&h, 0, sizeof(h));
    if ((currentPos-size)<endPos) {
       read(&h.versionMadeBy, sizeof(h.versionMadeBy));

      read(&h.versionNeededToExtract,  sizeof(h.versionNeededToExtract));

      read(&h.flags, sizeof(h.flags)); 

      read(&h.compressionMethod, sizeof(h.compressionMethod));

      read(&h.lastModifiedTime, sizeof(h.lastModifiedTime));

      read(&h.lastModifiedDate, sizeof(h.lastModifiedDate));

      read(&h.crc32, sizeof(h.crc32)); 

      read(&h.compressedSize, sizeof(h.compressedSize)); 

      read(&h.uncompressedSize, sizeof(h.uncompressedSize));

      read(&h.fileNameLength, sizeof(h.fileNameLength));

      read(&h.extraFieldLength, sizeof(h.extraFieldLength));

      read(&h.fileCommentLength, sizeof(h.fileCommentLength));

      read(&h.diskNumberStart, sizeof(h.diskNumberStart)); 

      read(&h.internalFileAttribs, sizeof(h.internalFileAttribs));

      read(&h.externalFileAttribs, sizeof(h.externalFileAttribs)); 

      read(&h.relativeOffsetOfLocalHeader, sizeof(h.relativeOffsetOfLocalHeader));
      rc = size;

    }
    return rc;
  }
private:
  int read(ExtendedHeader& h, size_t size) {
    int rc = 0;
    memset(&h, 0, sizeof(h));
    if ((currentPos-size)<endPos) {
      read(&h.crc32, sizeof(h.crc32));
      read(&h.compressedSize,  sizeof(h.compressedSize));
            read(&h.uncompressedSize, sizeof(h.uncompressedSize)); 
       rc = size;
    }
    else {
      rc =  0;
    }
    return rc;
  }  

private:
  int read(EndOfCentralDir& h, size_t size) {
    int rc = 0;
    memset(&h, 0, sizeof(h));
    if ((currentPos-size)<endPos) {
      read(&h.numberOfThisDisk, sizeof(h.numberOfThisDisk)); 

      read(&h.numberOfTheDiskWithStartOfCentralDirectory, sizeof(h.numberOfTheDiskWithStartOfCentralDirectory));

      read(&h.nCentralDirectoryEntries_ThisDisk, sizeof(h.nCentralDirectoryEntries_ThisDisk));

      read(&h.nCentralDirectoryEntries_Total, sizeof(h.nCentralDirectoryEntries_Total));

      read(&h.centralDirectorySize, sizeof(h.centralDirectorySize));

      read(&h.startOfCentralDirOffset, sizeof(h.startOfCentralDirOffset));

      read(&h.commentLength, sizeof(h.commentLength)); 
      rc = size;
    }
    else {
      rc =  0;
    }
    return rc;
  }  

private:
  int search(int integer, size_t size)
  {
    int pos = 0;
    unsigned char* found = NULL;
    if ((currentPos-size) <endPos) {
  
      unsigned char* ptr = currentPos;
      while (ptr <endPos) {
        int in =0;
        memcpy(&in, ptr, sizeof(int));
        if (in == integer) {
          found = ptr;
          pos = found - currentPos;
          break;
        }
        ptr++;  
      }
    }
    return pos;
  }

private:
  //  date and time fields: (2 bytes each)
  //  The date and time are encoded in standard MS-DOS format.
  // 2015/12/23 Added size_ bsize parameter. 
  void getLastModifiedDateTime(unsigned short _date, unsigned short _time, 
    char* string, size_t bsize)
  {
    unsigned char date[2];
    unsigned char time[2];

    date[0] = LOBYTE(_date);
    date[1] = HIBYTE(_date);

    time[0] = LOBYTE(_time);
    time[1] = HIBYTE(_time);

    unsigned short year   = (date[1] >> 1) & 127;
    unsigned short month = ((date[1] << 3) & 14) | ((date[0] >> 5) & 7);
    unsigned short day   = date[0] & 31;
 
    unsigned short hour    = (time[1] >> 3) & 31;
    unsigned short minutes = ((time[1] << 3) & 56) | ((time[0] >> 5) & 7);
    //unsigned short seconds = (time[0] & 31) * 2;

    sprintf_s(string, bsize, "%04d/%02d/%02d %d:%d",    
       (1980 + year), month, day,
      hour, minutes);
  }


};

}

