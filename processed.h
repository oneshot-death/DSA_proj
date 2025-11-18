#ifndef PROCESSED_H
#define PROCESSED_H

#include "order_heap.h"
#include "catalog.h"

typedef struct processed {
    order_t ord;
    struct processed *link;
} processed_t;

typedef struct processed_list {
    processed_t *head;
} processed_list_t;

void init_processed(processed_list_t *pl);
void log_processed(processed_list_t *pl, order_t ord);
void display_processed(processed_list_t *pl, catalog_t *c);

#endif
