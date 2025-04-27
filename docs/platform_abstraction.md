# Platform Abstraction

tpool is designed to be cross-platform, working on Windows, Linux, and macOS.
To achieve this, all platform-specific operations (like threads, mutexes, and condition variables) are abstracted cleanly inside `tpool_platform.h`.

## Types

| Abstracted Type | Windows Version | POSIX (Linux/macOS) Version |
|:---|:---|:---|
| `tpool_thread_t` | `HANDLE` | `pthread_t` |
| `tpool_mutex_t` | `CRITICAL_SECTION` | `pthread_mutex_t` |
| `tpool_cond_t` | `CONDITION_VARIABLE` | `pthread_cond_t` |

---

## Functions

### Threads

| Abstracted Macro | Windows Implementation | POSIX Implementation |
|:---|:---|:---|
| `tpool_thread_create(thread, func, arg)` | `*(thread) = CreateThread(NULL, 0, func, arg, 0, NULL)` | `pthread_create(thread, NULL, func, arg)` |
| `tpool_thread_join(thread)` | `WaitForSingleObject(thread, INFINITE); CloseHandle(thread)` | `pthread_join(thread, NULL)` |

---

### Mutexes

| Abstracted Macro | Windows Implementation | POSIX Implementation |
|:---|:---|:---|
| `tpool_mutex_init(mutex)` | `InitializeCriticalSection(mutex)` | `pthread_mutex_init(mutex, NULL)` |
| `tpool_mutex_destroy(mutex)` | `DeleteCriticalSection(mutex)` | `pthread_mutex_destroy(mutex)` |
| `tpool_mutex_lock(mutex)` | `EnterCriticalSection(mutex)` | `pthread_mutex_lock(mutex)` |
| `tpool_mutex_unlock(mutex)` | `LeaveCriticalSection(mutex)` | `pthread_mutex_unlock(mutex)` |

---

### Condition Variables

| Abstracted Macro | Windows Implementation | POSIX Implementation |
|:---|:---|:---|
| `tpool_cond_init(cond)` | `InitializeConditionVariable(cond)` | `pthread_cond_init(cond, NULL)` |
| `tpool_cond_destroy(cond)` | *(No action needed)* | `pthread_cond_destroy(cond)` |
| `tpool_cond_wait(cond, mutex)` | `SleepConditionVariableCS(cond, mutex, INFINITE)` | `pthread_cond_wait(cond, mutex)` |
| `tpool_cond_signal(cond)` | `WakeConditionVariable(cond)` | `pthread_cond_signal(cond)` |
| `tpool_cond_broadcast(cond)` | `WakeAllConditionVariable(cond)` | `pthread_cond_broadcast(cond)` |

---

