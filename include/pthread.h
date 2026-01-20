#pragma once

#ifndef _WIN32
    #if defined(__GNUC__) || defined(__clang__)
        #include_next <pthread.h>
    #else
        #include <pthread.h>
    #endif
#else
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SRWLOCK pthread_mutex_t;
typedef CONDITION_VARIABLE pthread_cond_t;
typedef INIT_ONCE pthread_once_t;
typedef DWORD pthread_t;

#ifndef PTHREAD_MUTEX_INITIALIZER
#define PTHREAD_MUTEX_INITIALIZER SRWLOCK_INIT
#endif

#ifndef PTHREAD_COND_INITIALIZER
#define PTHREAD_COND_INITIALIZER CONDITION_VARIABLE_INIT
#endif

#ifndef PTHREAD_ONCE_INIT
#define PTHREAD_ONCE_INIT INIT_ONCE_STATIC_INIT
#endif

static inline int pthread_mutex_init(pthread_mutex_t *m, void *attr) {
    (void)attr;
    InitializeSRWLock(m);
    return 0;
}

static inline int pthread_mutex_destroy(pthread_mutex_t *m) {
    (void)m;
    return 0;
}

static inline int pthread_mutex_lock(pthread_mutex_t *m) {
    AcquireSRWLockExclusive(m);
    return 0;
}

static inline int pthread_mutex_unlock(pthread_mutex_t *m) {
    ReleaseSRWLockExclusive(m);
    return 0;
}

static inline int pthread_cond_init(pthread_cond_t *c, void *attr) {
    (void)attr;
    InitializeConditionVariable(c);
    return 0;
}

static inline int pthread_cond_destroy(pthread_cond_t *c) {
    (void)c;
    return 0;
}

static inline int pthread_cond_signal(pthread_cond_t *c) {
    WakeConditionVariable(c);
    return 0;
}

static inline int pthread_cond_broadcast(pthread_cond_t *c) {
    WakeAllConditionVariable(c);
    return 0;
}

static inline int pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m) {
    SleepConditionVariableCS(c, m, INFINITE);
    return 0;
}

static inline BOOL CALLBACK slipstream_pthread_once_cb(PINIT_ONCE init_once, PVOID param, PVOID *context) {
    (void)init_once;
    void (**fn)(void) = (void (**)(void))param;
    (*fn)();
    *context = NULL;
    return TRUE;
}

static inline int pthread_once(pthread_once_t *once_control, void (*init_routine)(void)) {
    InitOnceExecuteOnce(once_control, slipstream_pthread_once_cb, (PVOID)init_routine, NULL);
    return 0;
}

#ifdef __cplusplus
}
#endif
#endif
