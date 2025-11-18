#include <stdio.h>
#include <stdlib.h>
#include "processed.h"

void init_processed(processed_list_t *pl) {
    pl->head = NULL;
}

void log_processed(processed_list_t *pl, order_t ord) {
    processed_t *temp = (processed_t*)malloc(sizeof(processed_t));
    temp->ord = ord;
    temp->link = NULL;
    if (pl->head == NULL)
        pl->head = temp;
    else {
        processed_t *pres = pl->head;
        while (pres->link != NULL) pres = pres->link;
        pres->link = temp;
    }
}

void display_processed(processed_list_t *pl, catalog_t *c) {
    processed_t *pres = pl->head;
    if (pres == NULL) {
        printf("\nNo processed orders yet.\n");
        return;
    }
    printf("\nProcessed Orders:\n");
    printf("OID\tPID\tProductName\tQty\tPriority\n");
    while (pres != NULL) {
        product_t *p = find_product(c, pres->ord.product_id);
        const char *pname = p ? p->name : "Unknown";
        printf("%d\t%d\t%-12s\t%d\t%d\n",
               pres->ord.order_id,
               pres->ord.product_id,
               pname,
               pres->ord.quantity,
               pres->ord.priority);
        pres = pres->link;
    }
}
