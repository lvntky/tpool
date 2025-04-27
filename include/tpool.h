#ifndef TPOOL_H_
#define TPOOL_H_

#include <tpool_platform.h>
#include <tpool_config.h>

typedef struct {
    void (*function)(void *); // function pointer for the task
    void *argument;           // argument to pass to the function
} tpool_task_t;

typedef struct {
    tpool_task_t task;
    size_t worker_size;
} tpool_t;

/**
 * Public API Functions
 */

tpool_t *tpool_create(size_t n_threads);
int tpool_destroy(tpool_t *pool);
int tpool_submit(void);
int tpool_wait(void);

#endif TPOOL_H_