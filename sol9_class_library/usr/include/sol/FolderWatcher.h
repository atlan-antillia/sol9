/******************************************************************************
 *
 * Copyright (c) 2008-2012 Antillia.com TOSHIYUKI ARAI. ALL RIGHTS RESERVED.
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
 *  FolderWatcher.h
 *
 *****************************************************************************/

// SOL9
// 2008/09/17
// 2008/12/10
// Added an optional 'flags' parameter to specify filters for
// ReadDirectoryChangesW API to the contructor 'FolderWatcher'.
// 2012/06/22

#include <sol\Thread.h>
#include <sol\String.h>

namespace SOL {

/**
 * FolderWatcher is a thread class to watch changes of a directory (including all 
 * subdirectories). In thread procedure 'run' method, we use Windows API ReadDirectoryChangesW()
 * 
 */

class FolderWatcher: public Thread {

private:
  String directory;

private:
  HANDLE hFolder;
private:
  bool  looping;

private:
  HANDLE terminateEvent;

private:
  //2008/12/10
  DWORD filters;

public:
  FolderWatcher(const TCHAR* dir=_T("C:\\"),
    DWORD flags=FILE_NOTIFY_CHANGE_DIR_NAME | 
          FILE_NOTIFY_CHANGE_FILE_NAME | 
          FILE_NOTIFY_CHANGE_LAST_ACCESS |
          FILE_NOTIFY_CHANGE_ATTRIBUTES | 
          FILE_NOTIFY_CHANGE_SIZE  | 
          FILE_NOTIFY_CHANGE_LAST_WRITE|
          FILE_NOTIFY_CHANGE_CREATION | 
          FILE_NOTIFY_CHANGE_SECURITY )
  :Thread(),
   directory(dir),
   hFolder(INVALID_HANDLE_VALUE),
   looping(false),
   terminateEvent(NULL),
   filters(flags) {
    //
    terminateEvent = CreateEvent(0,FALSE,FALSE,0);

  }

public:
  ~FolderWatcher() {
    close();
  }

private:
  bool close()
  {
    bool rc = false;
    if (this->hFolder != INVALID_HANDLE_VALUE) {
      //To stop this thread, close handle hFolder;
      //It will cause an error in ReadDirectoryChangesW()
      CloseHandle(this->hFolder);
      this->hFolder = INVALID_HANDLE_VALUE;
      rc = true;
    }
    if (terminateEvent) {
      CloseHandle(terminateEvent);
      terminateEvent = NULL;
    }
    return rc;
  }

public:
  // Set terminateEvent to stop run loop.
  void stop() {
    SetEvent(terminateEvent);
    looping  = false;
  }

public:
  //Added on 2008/12/10
  const TCHAR* getDirectory()
  {
    return (const TCHAR*)directory;
  }

public:
  //Print out action and filename to console.In order to customize or change output,
  //define your own subclass and redfine this mehtod in that class.
  virtual void changedFileName(const wchar_t* action, const wchar_t* filename)
  {
    wprintf(L"%s: %s\n", action,  filename);
  }


public:
  /**
   * Thread procedure
   */
  void run()
  {
    looping = true;

    const TCHAR* dir = (const TCHAR*)directory;
    if (GetFileAttributes(dir) == 0xffffffff) {
      //2008/09/24 Should be changed to be able to make multiple subdirectories
      if (CreateDirectory(dir, NULL)) {
        _tprintf(_T("Create a new directory %s\n"), dir); //2012/06/22
      }
    }

    this->hFolder = CreateFile(dir,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ|FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        // Specify FILE_FLAG_OVERLAPPED flags
      FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED, 
        NULL);

    if(this->hFolder == INVALID_HANDLE_VALUE){
      _tprintf(_T("Failed to open dir %s\n"), dir); //2012/06/22
      return;
    }

    OVERLAPPED ol; 
    ol.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL); 
    HANDLE waitEvents[2];
    waitEvents[0] = terminateEvent;
    waitEvents[1] = ol.hEvent;

    //Start a loop of call ReadDirectoryChangesW().
    while(looping) {

      DWORD dwBytes = 0;
      TCHAR buf[1024];

      BOOL rc = ReadDirectoryChangesW(hFolder, buf, 1022,1,
        this->filters,
/*
//2008/12/10
        FILE_NOTIFY_CHANGE_DIR_NAME | 
        FILE_NOTIFY_CHANGE_FILE_NAME | 
        FILE_NOTIFY_CHANGE_LAST_ACCESS |
        FILE_NOTIFY_CHANGE_ATTRIBUTES | 
        FILE_NOTIFY_CHANGE_SIZE  | 
        FILE_NOTIFY_CHANGE_LAST_WRITE|
        FILE_NOTIFY_CHANGE_CREATION | 
        FILE_NOTIFY_CHANGE_SECURITY,
*/      
        &dwBytes, &ol, NULL);

      if (rc == FALSE) {
        printf("Failed:ReadDirectoryChanges()\n");
        break;
      }
      if (looping == false) {
        printf("looping ends\n");
        break;
      }
      
      int r = WaitForMultipleObjects(2, waitEvents, FALSE, INFINITE ); 
      if (r == WAIT_OBJECT_0 ) {
        //printf("Stopped 0\n"); 
        printf("\nTerminateEvent has been set, so break this thread loop\n");
        break;
      }

      BOOL b = GetOverlappedResult(hFolder, &ol, &dwBytes, TRUE ); 
      if (b == FALSE) {
        continue;
      }

      //printf("buf ReadSize=%d\n",dwBytes);

      FILE_NOTIFY_INFORMATION *fn = (FILE_NOTIFY_INFORMATION *)buf;

      while (fn) {
        //FileName will be "NULL" terminated 
        fn->FileName[fn->FileNameLength/2] = 0;

        wchar_t * action = L"";

        switch(fn->Action){

        case FILE_ACTION_ADDED:
          action = L"Added";
          break;
        case FILE_ACTION_REMOVED:
          action = L"Removed";
          break;
        case FILE_ACTION_MODIFIED:
          action = L"Accessed/Modified";
          break;
        case FILE_ACTION_RENAMED_OLD_NAME:
          action = L"Renamed(Old name)";
          break;
        case FILE_ACTION_RENAMED_NEW_NAME:
          action = L"Renamed(New name)";
          break;
        default:
          action = L"(Unknown)";
        }

          changedFileName(action,  fn->FileName);

          if (fn->NextEntryOffset == NULL) {
          break;
        } else {
              fn = (FILE_NOTIFY_INFORMATION *)(((char *)fn) + fn->NextEntryOffset);
          }
      } //while

    }

    CloseHandle(ol.hEvent);

    close();

  }
};

}
