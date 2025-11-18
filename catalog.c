#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalog.h"

void init_catalog(catalog_t *c) {
    c->head = NULL;
    c->next_product_id = 1;
}

void insert_product_end(catalog_t *c, const char *name, float price) {
    product_t *temp = (product_t*)malloc(sizeof(product_t));
    temp->id = c->next_product_id++;
    strncpy(temp->name, name, sizeof(temp->name)-1);
    temp->name[sizeof(temp->name)-1] = '\0';
    temp->price = price;
    temp->link = NULL;

    if (c->head == NULL) {
        c->head = temp;
    } else {
        product_t *pres = c->head;
        while (pres->link != NULL) pres = pres->link;
        pres->link = temp;
    }
    printf("Product inserted with ID %d.\n", temp->id);
}

void display_catalog(catalog_t *c) {
    product_t *pres = c->head;
    if (pres == NULL) {
        printf("\nProduct catalog empty.\n");
        return;
    }
    printf("\nProduct Catalog:\n");
    printf("ID\tName\t\tPrice\n");
    while (pres != NULL) {
        printf("%d\t%-15s\t%.2f\n", pres->id, pres->name, pres->price);
        pres = pres->link;
    }
}

product_t* find_product(catalog_t *c, int id) {
    product_t *pres = c->head;
    while (pres != NULL) {
        if (pres->id == id) return pres;
        pres = pres->link;
    }
    return NULL;
}
