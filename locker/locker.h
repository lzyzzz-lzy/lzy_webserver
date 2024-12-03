#ifdef _LOCKER_H_
#define _LOCKER_H_

#include <pthread.h>
#include <exception>
#include <semaphore.h>

//对mutex 简单封装
class locker
{
private:
    pthread_mutex_t m_mutex;

public:
    locker()
    {
        if (pthread_mutex_init(&m_mutex, NULL) != 0)
        {
            throw std::runtime_error("mutex init error!");
        }
    }

    ~locker()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }

    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

    pthread_mutex_t *get()
    {
        return &m_mutex;
    }
};

//对cond 简单封装
class cond
{
private:
    pthread_cond_t m_cond;

public:
    cond()
    {
        if (pthread_cond_init(&m_cond, NULL) != 0)
        {
            throw std::runtime_error("cond init error!");
        }
    }
    ~cond()
    {
        pthread_cond_destroy(&m_cond);
    }

    bool wait(pthread_mutex_t *m_mutex)
    {
        return pthread_cond_wait(&m_cond, m_mutex) == 0;
    }

    bool timewait(pthread_mutex_t *m_mutex, struct timespec time)
    {
        return pthread_cond_timewait(&m_cond, m_mutex, &time) == 0;
    }

    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }

    bool broadcast()
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }
};

//对sem 简单封装
class sem
{
private:
    sem_t m_sem;

public:
    sem()
    {
        if (sem_init(&m_sem, 0, 0) != 0)
        {
            throw std::runtime_error("sem init error!");
        }
    }
    sem(int num)
    {
        if (sem_init(&m_sem, 0, num) != 0)
        {
            throw std::runtime_error("sem init error!");
        }
    }
    ~sem()
    {
        sem_destroy(&m_sem);
    }
    bool wait()
    {
        return sem_wait(&m_sem, 0) == 0;
    }
    bool post()
    {
        return sem_post(&m_sem) == 0;
    }
};

#endif