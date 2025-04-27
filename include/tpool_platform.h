#ifndef TPOOL_PLATFORM_H_
#define TPOOL_PLATFORM_H_

// Platform Detection
#if defined(_WIN32) || defined(_WIN64)
    #define TPOOL_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
    #define TPOOL_PLATFORM_MAC
#elif defined(__linux__)
    #define TPOOL_PLATFORM_LINUX
#else
    #error "Unknown platform!"
#endif

// Standard Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef TPOOL_PLATFORM_WINDOWS
    #include <windows.h>
#else
    #include <pthread.h>
    #include <unistd.h>
#endif

// --- Type Abstractions ---
#ifdef TPOOL_PLATFORM_WINDOWS

typedef HANDLE tpool_thread_t;
typedef CRITICAL_SECTION tpool_mutex_t;
typedef CONDITION_VARIABLE tpool_cond_t;

#else

typedef pthread_t tpool_thread_t;
typedef pthread_mutex_t tpool_mutex_t;
typedef pthread_cond_t tpool_cond_t;

#endif

// --- Function Abstractions ---

// Thread
#ifdef TPOOL_PLATFORM_WINDOWS
    #define tpool_thread_create(thread, func, arg) \
        *(thread) = CreateThread(NULL, 0, func, arg, 0, NULL)

    #define tpool_thread_join(thread) \
        WaitForSingleObject(thread, INFINITE); CloseHandle(thread)

#else
    #define tpool_thread_create(thread, func, arg) \
        pthread_create(thread, NULL, func, arg)

    #define tpool_thread_join(thread) \
        pthread_join(thread, NULL)
#endif

// Mutex
#ifdef TPOOL_PLATFORM_WINDOWS
    #define tpool_mutex_init(mutex) \
        InitializeCriticalSection(mutex)

    #define tpool_mutex_destroy(mutex) \
        DeleteCriticalSection(mutex)

    #define tpool_mutex_lock(mutex) \
        EnterCriticalSection(mutex)

    #define tpool_mutex_unlock(mutex) \
        LeaveCriticalSection(mutex)

#else
    #define tpool_mutex_init(mutex) \
        pthread_mutex_init(mutex, NULL)

    #define tpool_mutex_destroy(mutex) \
        pthread_mutex_destroy(mutex)

    #define tpool_mutex_lock(mutex) \
        pthread_mutex_lock(mutex)

    #define tpool_mutex_unlock(mutex) \
        pthread_mutex_unlock(mutex)
#endif

// Condition Variable
#ifdef TPOOL_PLATFORM_WINDOWS
    #define tpool_cond_init(cond) \
        InitializeConditionVariable(cond)

    #define tpool_cond_destroy(cond) \
        // No destroy needed for CONDITION_VARIABLE

    #define tpool_cond_wait(cond, mutex) \
        SleepConditionVariableCS(cond, mutex, INFINITE)

    #define tpool_cond_signal(cond) \
        WakeConditionVariable(cond)

    #define tpool_cond_broadcast(cond) \
        WakeAllConditionVariable(cond)

#else
    #define tpool_cond_init(cond) \
        pthread_cond_init(cond, NULL)

    #define tpool_cond_destroy(cond) \
        pthread_cond_destroy(cond)

    #define tpool_cond_wait(cond, mutex) \
        pthread_cond_wait(cond, mutex)

    #define tpool_cond_signal(cond) \
        pthread_cond_signal(cond)

    #define tpool_cond_broadcast(cond) \
        pthread_cond_broadcast(cond)
#endif

#endif // TPOOL_PLATFORM_H
