#include <tpool.h>

tpool_t *tpool_create(size_t n_threads) {
    tpool_t* pool;

    if ((pool = (tpool_t *)tpool_malloc(n_threads)) == NULL) {
        // TODO: implement error fallback
        return NULL;
    }

    return pool;
}