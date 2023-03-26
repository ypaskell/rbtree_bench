#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include "rb.c"
#include "rb.h"

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

enum { NNODES = 1000 * 1000 };

int main(int argc, char *argv[])
{
    map_t* tree = map_init(int, int, uint_key_cmp);

    int key[NNODES];
    int val[NNODES];

    /*
     *  Generate data for insertion
     */
    for (int i = 0; i < NNODES; i++) {
        key[i] = i;
        val[i] = i;
    }

    /* This is not a reconmended way to randomize stuff, just a simple test */
    /* I know MT19937 might be better */
    srand((unsigned) time(NULL));
    for (int i = 0; i < 1e7; i++) {
        int pos_a = rand() % NNODES;
        int pos_b = rand() % NNODES;
        swap(&key[pos_a], &key[pos_b]);
        swap(&val[pos_a], &val[pos_b]);
    }

    for (int i = 0; i < NNODES; i++) {
        map_insert(tree, key + i, val + i);
    }

    for (int i = 0; i < 10; i++) {
        node_t* tmp;
        map_find(tree, &tmp, key + i);
        printf("{%p}\n", tmp);
    }

    return 0;
}