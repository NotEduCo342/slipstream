#pragma once

#ifdef _WIN32
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef CRITICAL_SECTION pthread_mutex_t;
typedef CONDITION_VARIABLE pthread_cond_t;
typedef INIT_ONCE pthread_once_t;
typedef DWORD pthread_t;

static inline int pthread_mutex_init(pthread_mutex_t *m, void *attr) {
    (void)attr;
    InitializeCriticalSection(m);
    return 0;
}

static inline int pthread_mutex_destroy(pthread_mutex_t *m) {
    DeleteCriticalSection(m);
    return 0;
}

static inline int pthread_mutex_lock(pthread_mutex_t *m) {
    EnterCriticalSection(m);
    return 0;
}

static inline int pthread_mutex_unlock(pthread_mutex_t *m) {
    LeaveCriticalSection(m);
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
