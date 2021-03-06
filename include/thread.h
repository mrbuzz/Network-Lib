#ifndef _thread_h
#define _thread_h

#include "lib_base.h"

class thread
{
  public:
    thread();
    ~thread();

    int start();
    int join();
    int detach();
    pthread_t self();

    virtual void* run() = 0;

  private:
    pthread_t  m_tid;
    int        m_running;
    int        m_detached;
};

#endif /* _thread_h */
