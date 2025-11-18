#ifndef ORDER_HEAP_H
#define ORDER_HEAP_H

#include "catalog.h"

#define MAX_ORDERS 100

typedef struct order {
    int order_id;
    int product_id;
    int quantity;
    int priority;
} order_t;

typedef struct order_heap {
    order_t heap[MAX_ORDERS];
    int size;
    int next_order_id;
} order_heap_t;

void init_heap(order_heap_t *h);
void heap_insert(order_heap_t *h, int product_id, int quantity, int priority);
order_t heap_extract_max(order_heap_t *h);
order_t heap_peek(order_heap_t *h);
void display_heap(order_heap_t *h, catalog_t *c);
void delete_heap(order_heap_t *h);

#endif
