/******************************************************************************
 *
 * Copyright (c) 1999-2008 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  LogWriter.h
 *
 *****************************************************************************/

// SOL++2000

// 2008/07/16 Added a method 
// public: static LogWriter& getInstance()
// 2008/09/30 Added hex output methods(traceHex, debugHex, errorHex).


#pragma once

#include <sol\Object.h>

#include <sol\String.h>
#include <sol\Directory.h>
#include <sol\InvalidArgumentException.h>
#include <sol\FileFindData.h>
#include <sol\Folder.h>
#include <sol\Profile.h>
#include <sol\Mutex.h>

/**
 */
namespace SOL {

class LogWriter :public Object{
private:
  //Bytes
  static const int BUFF_SIZE =1024*10;


private:
  TCHAR fullpath[_MAX_PATH];
  
  int level;

  int  logHistory;
  int  logFileSize;

  char* buffer;

public:

  static const int LOG_NONE  = 0;
  static const int LOG_ERROR  = 1;
  static const int LOG_DEBUG  = 2;
  static const int LOG_TRACE  = 3;

public:
  /**
   * Constructor. Ooutput dir, name, level are set from a default setting.
   * dir   = UserProfile
   * name  = Module.exe
   * level = LOG_ERROR
   */
  LogWriter() 
  :level(LOG_ERROR), buffer(NULL) {
    this->fullpath[0] = '\0';
    this->buffer = new char[BUFF_SIZE];

    String logdir;
    String logname;
    getDefaultDir(logdir);    //%UserProfile%\sollog
    getDefaultName(logname);  //Module.exe

    _stprintf_s(this->fullpath, CountOf(this->fullpath), _T("%s\\%s.log"),
      (const TCHAR*)logdir,
      (const TCHAR*)logname);

    //fullpath will be something like "c:\Users\someone\sollog\foo.exe.log"
    // or "c:\Users\someone\foo.exe.log"
    
    getDefaultLevel(this->level);

    this->logHistory = 10;
    this->logFileSize = 1024*10;  //Max file size of each log file is 10MB
    //printf("LogWriter#LogWriter,OK\n");
  }

public:
  /**
   * Constructor
   */
  LogWriter(const TCHAR* dir, const TCHAR* fname, int lv=LOG_ERROR)
    :level(lv), buffer(NULL) 
  {
    //Default output file.
    strcpy_s(this->fullpath, CountOf(this->fullpath), _T(".\\sol.log")); //2012/06/21
    
    setProperties(dir, fname, lv);

    this->buffer = new char[BUFF_SIZE];
    
    this->logHistory = 10;      //Leave 10 log files.
    this->logFileSize = 1024*10;  //Max file size of each log file is 10MB
  }

public:
  /**
   *
   */
  ~LogWriter() {
    if (this->buffer) {
      delete [] this->buffer;
      this->buffer = NULL;
    }
  }

private:
  void getDefaultDir(String& logdir)
  {
    logdir = ".\\";
    TCHAR user[_MAX_PATH];
    if(GetEnvironmentVariable(_T("UserProfile"), user, CountOf(user))) { //2012/06/21
      TCHAR soldir[_MAX_PATH];
      _stprintf_s(soldir, CountOf(soldir), _T("%s\\sollog"), user);
      if (GetFileAttributes(soldir) == 0xffffffff) {
        if (CreateDirectory(soldir, NULL)) {
          logdir = soldir;
        } else {
          logdir = user;
        }
      } else {
        logdir = soldir;
      }
    }
  }

public:
  /**
   * Return a default LogWriter object constructed based on LogWriter::LogWriter
   * and, default output profiles defined on Profile(Current User Registry).
   *
   * Return a reference to LogWriter of static variable of this method.
   */
  static LogWriter& getInstance() {

    static LogWriter logWriter;

    //printf("LogWriter#getInstance,fullpath=[%s], level=[%d]\n",
    //  logWriter.getFullPath(), logWriter.getLevel());

    return logWriter;

  }

private:
  void getDefaultName(String& logname)
  {
    logname = _T("sol.log");
    wchar_t wmodule[_MAX_PATH];
  
    GetModuleFileNameW(NULL, wmodule, _MAX_PATH);
    
    Folder folder(wmodule);
    folder.getFileName(logname);
  }

private:
  void getDefaultLevel(int& level)
  {
    level = LOG_ERROR;

    //Profile is really a CurrentUserRegistry.
    //Refer the key "HKEY_CURRENT_USER\Software\Antillia^Application\Solapp\Log"
    // and the name "Level" of REG_DWORD type.
    Profile profile;
    int lv = 0;
    if (profile.getLogLevel(lv)) {
      level = lv;
    }
  }

public:
  /**
   *
   */
  void setProperties(const TCHAR* dir, const TCHAR* fname, int lv) {
    
    if (dir != NULL && fname != NULL) {
      
      TCHAR tdir[_MAX_PATH];
      strcpy_s(tdir, CountOf(tdir), dir);

      size_t len = strlen(tdir);
      //If dir were something like "c:\windows\foo\", convert tdir= "c:\windows\foo"
      //Bu dir = "c:\", leave it.
      if (len >= 2 && tdir[len - 2] != ':' && tdir[len - 1] == '\\') {
         tdir[len - 1] = '\0';
      }
    
      Directory direct;
      if (direct.exists(tdir) == false) {
        if (direct.make(tdir) == false){
          throw InvalidArgumentException(
            "Logger#Logger,1,Failed to create folder", GetLastError());      
        }
      }
      _stprintf_s(this->fullpath, CountOf(fullpath), _T("%s\\%s"), dir, fname);
      //printf("LogWriter,fullpaht=%s\n", fullpath);
    }
    this->level = lv;
  }


private:
  /**
   *
   */
  BOOL rename(TCHAR* fullpath)
  {
    BOOL rc = FALSE;
    try {    
      FileFindData ffdata(fullpath);

      ULONGLONG fsize = ffdata.getFileSize()/SIZE_1KB;

      if (fsize > this->logFileSize) {
        rc = TRUE;
        renameFiles(fullpath);
      }
    } catch (...) {
      ;
    }
    return rc;
  }

public:
  /**
   */
  BOOL renameFiles(TCHAR* fullpath) {
    BOOL rc = TRUE;

    TCHAR filePath[MAX_PATH];

    _stprintf_s(filePath, CountOf(filePath), _T("%s.%d"), 
      fullpath, this->logHistory);

    if (::GetFileAttributes(filePath) != 0xFFFFFFFF) {
      DeleteFile(filePath);    
    }

    for (int i = logHistory-1; i>=1; i--) {
      TCHAR source[MAX_PATH];
      TCHAR destination[MAX_PATH];
      _stprintf_s(source, CountOf(source), _T("%s.%d"), fullpath, i);

      _stprintf_s(destination, CountOf(destination), _T("%s.%d"), 
        fullpath, (i+1));

      if (::GetFileAttributes(source) != 0xFFFFFFFF) {
        rc = MoveFile(source, destination);    
      }
    }

    TCHAR first[MAX_PATH];
    _stprintf_s(first, CountOf(first), _T("%s.1"), fullpath);
    rc = MoveFile(fullpath, first);
    return rc;  
  }

public:
  /**
   */
  void trace(const char* format,...) {

    if (this->level <=LOG_NONE || fullpath[0] == '\0') {
      return;
    }

    if (LOG_TRACE >this->level) {
      return;
    }

    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(this->buffer, BUFF_SIZE, _TRUNCATE, format, pos);


    va_end(pos);
  
    write(this->buffer, "TRACE");
  }



public:

  void error(const char* format,...) {

    if (this->level <=LOG_NONE || fullpath[0] == '\0') {
      return;
    }
    if (LOG_ERROR >this->level) {
      return;
    }

    va_list pos;
    va_start(pos, format);
    //_vsntprintf(this->buffer, BUFF_SIZE, format, pos);
    _vsnprintf_s(this->buffer, BUFF_SIZE, _TRUNCATE ,format, pos);

    va_end(pos);
    
    write(this->buffer, "ERROR");

  }

public:
  void debug(const char* format,...) {

    if (this->level <=LOG_NONE || fullpath[0] == '\0') {

      return;
    }

    if (LOG_DEBUG >this->level) {

      return;
    }
    
    va_list pos;
    va_start(pos, format);
    _vsnprintf_s(this->buffer, BUFF_SIZE, _TRUNCATE, format, pos);
//    inline int _vsnprintf(wchar_t *a, size_t b, const wchar_t *c, va_list d) 

    va_end(pos);

    write(this->buffer, "DEBUG");
  }

private:
  void write(const char* buffer, const char* name)
  {
    Mutex mutex(fullpath);
    mutex.lock();

    //If needed, rename the logfiles.
    rename(fullpath);
    
    //Open the file fullpath by append mode!
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, this->fullpath, _T("a+"));
    if (err == 0 && fp != NULL) {
    
      time_t ptime;
      time(&ptime);
      struct tm tm;
      //errno_t err = 
      localtime_s(&tm, &ptime);
      char now[128];
      //errno_t err = 
      asctime_s(now, CountOf(now), &tm);
      
      //char* now = asctime(localtime(&ptime));
      now[strlen(now)-1]= ' ';
              
      fprintf(fp, "%s %s: %s\n", now, name, buffer);

      fclose(fp);    
    }
    mutex.unlock();
  }

public:
  const TCHAR* getFullPath() const {
    return this->fullpath;
  }

public:
  int getLevel() const {
    return this->level;
  }

  ////////////////////////////////////////////////
  // 2008/09/30 Added hex output methods. 
  // 
public:
  void errorHex(const char* message, const unsigned char* data, size_t len) {
    writeHex(LOG_ERROR, "ERROR:", message, data, len);
  }

public:
  void debugHex(const char* message, const unsigned char* data, size_t len) {
    writeHex(LOG_DEBUG, "DEBUG:", message, data, len);
  }

public:
  void traceHex(const char* message, const unsigned char* data, size_t len) {
    writeHex(LOG_TRACE, "TRACE:", message, data, len);
  }

private:
  void writeHex(int outlevel, const char* levels, const char* message, const unsigned char* data, size_t len) {
    if (this == NULL) {
      return;
    }

    if (level == 0 || fullpath[0] == '\0') {
      return;
    }

    if (outlevel >level) {
      return;
    }
    if (message == NULL) {
      message = "";
    }

    Mutex mutex(fullpath);
    mutex.lock();

    rename(fullpath);

    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, fullpath, _T("a+"));
    if (err == 0 && fp != NULL) {

      time_t ptime;
      time(&ptime);
      
      struct tm tm;
      //errno_t err = 
      localtime_s(&tm, &ptime);
      char now[128];
      //errno_t err = 
      asctime_s(now, CountOf(now), &tm);
      
      now[strlen(now)-1]= ' ';

      fprintf(fp, "%s %s %s size=%d\n", now, levels, message, len);
      const int SIXTEEN = 16;
      int lines = len / SIXTEEN;
      int remainder = len % SIXTEEN;
      if (remainder) {
        lines++;
      }
     
      int s     =0;
      for (int i = 0; i<lines; i++) {
        int MAX = SIXTEEN;
        if (remainder>0 && i == (lines-1)) {
          MAX = remainder;
        }
        for (s = 0; s<MAX; s++) {
          fprintf(fp, "%02X ", data[i*16+s]);
        }
        for(int j = 0; j<SIXTEEN-MAX; j++) {
          fprintf(fp, "   ");
        }
        fprintf(fp, "    ");
        for (s = 0; s<MAX; s++) {
          char c = (char)data[i*16+s];
          if (c <' ') {
            c = '.';
          }
          fprintf(fp, "%c", c);
        }
        fprintf(fp, "\n");
      }
      fprintf(fp, "\n");
      fclose(fp);
    }
    mutex.unlock();
  }
};

}



