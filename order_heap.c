#include <stdio.h>
#include "order_heap.h"

static void swap_orders(order_t *a, order_t *b) {
    order_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void init_heap(order_heap_t *h) {
    h->size = 0;
    h->next_order_id = 1;
}

void heap_insert(order_heap_t *h, int product_id, int quantity, int priority) {
    if (h->size >= MAX_ORDERS) {
        printf("Order queue full.\n");
        return;
    }
    int i = h->size;
    h->heap[i].order_id = h->next_order_id++;
    h->heap[i].product_id = product_id;
    h->heap[i].quantity = quantity;
    h->heap[i].priority = priority;
    h->size++;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->heap[parent].priority < h->heap[i].priority) {
            swap_orders(&h->heap[parent], &h->heap[i]);
            i = parent;
        } else break;
    }
    printf("Order %d inserted (priority %d)\n", h->heap[i].order_id, h->heap[i].priority);
}

order_t heap_extract_max(order_heap_t *h) {
    order_t ret = {0,0,0,0}; //explain this
    if (h->size == 0) {
        printf("No pending orders.\n");
        return ret;
    }
    ret = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;

    int i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;
        if (left < h->size && h->heap[left].priority > h->heap[largest].priority) largest = left;
        if (right < h->size && h->heap[right].priority > h->heap[largest].priority) largest = right;
        if (largest != i) {
            swap_orders(&h->heap[i], &h->heap[largest]);
            i = largest;
        } else break;
    }
    return ret;
}

order_t heap_peek(order_heap_t *h) {
    order_t empty = {0,0,0,0};
    if (h->size == 0) return empty;
    return h->heap[0];
}

void display_heap(order_heap_t *h, catalog_t *c) {
    if (h->size == 0) {
        printf("\nNo pending orders.\n");
        return;
    }
    printf("\nPending Orders:\n");
    printf("OID\tPID\tProductName\tQty\tPriority\n");
    for (int i = 0; i < h->size; ++i) {
        product_t *p = find_product(c, h->heap[i].product_id);
        const char *pname = p ? p->name : "Unknown";
        printf("%d\t%d\t%-12s\t%d\t%d\n",
               h->heap[i].order_id,
               h->heap[i].product_id,
               pname,
               h->heap[i].quantity,
               h->heap[i].priority);
    }
}

void delete_heap(order_heap_t *h) {
    h->size = 0;
    h->next_order_id = 1;
}
