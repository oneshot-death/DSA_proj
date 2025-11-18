#ifndef CATALOG_H
#define CATALOG_H

typedef struct product {
    int id;
    char name[50];
    float price;
    struct product *link;
} product_t;

typedef struct catalog {
    product_t *head;
    int next_product_id;
} catalog_t;

void init_catalog(catalog_t *c);
void insert_product_end(catalog_t *c, const char *name, float price);
void display_catalog(catalog_t *c);
product_t* find_product(catalog_t *c, int id);

#endif
