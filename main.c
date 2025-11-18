#include <stdio.h>
#include <string.h>
#include "catalog.h"
#include "order_heap.h"
#include "processed.h"

int main() {
    catalog_t catalog;
    order_heap_t orders;
    processed_list_t processed;

    init_catalog(&catalog);
    init_heap(&orders);
    init_processed(&processed);

    int ch;
    while (1) {
        printf("\n--- E-Commerce Order System ---\n");
        printf("1. Add/Display Products\n");
        printf("2. Add New Order\n");
        printf("3. Process Highest Priority Order\n");
        printf("4. Show Top Pending Order\n");
        printf("5. Show All Pending Orders\n");
        printf("6. Show Processed Orders\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (ch == 1) {
            int sub;
            printf("\n1. Insert Product\n2. Display Catalog\nEnter choice: ");
            scanf("%d", &sub);
            if (sub == 1) {
                char pname[50];
                float price;
                int c; while ((c = getchar()) != '\n' && c != EOF);
                printf("Enter product name: ");
                fgets(pname, sizeof(pname), stdin);
                size_t ln = strlen(pname);
                if (ln && pname[ln-1] == '\n') pname[ln-1] = '\0';
                printf("Enter price: ");
                scanf("%f", &price);
                insert_product_end(&catalog, pname, price);
            } else if (sub == 2) display_catalog(&catalog);
        }
        else if (ch == 2) {
            int pid, qty, pr;
            display_catalog(&catalog);
            printf("Enter product ID: ");
            scanf("%d", &pid);
            product_t *p = find_product(&catalog, pid);
            if (!p) {
                printf("Invalid product ID.\n");
                continue;
            }
            printf("Enter quantity: ");
            scanf("%d", &qty);
            printf("Enter priority (higher = faster): ");
            scanf("%d", &pr);
            heap_insert(&orders, pid, qty, pr);
        }
        else if (ch == 3) {
            order_t done = heap_extract_max(&orders);
            if (done.order_id != 0) {
                printf("Processed Order %d (PID:%d Qty:%d)\n", done.order_id, done.product_id, done.quantity);
                log_processed(&processed, done);
            }
        }
        else if (ch == 4) {
            order_t top = heap_peek(&orders);
            if (top.order_id == 0) printf("No pending orders.\n");
            else {
                product_t *p = find_product(&catalog, top.product_id);
                printf("Top Order -> OID:%d Product:%s Qty:%d Priority:%d\n",
                       top.order_id, p ? p->name : "Unknown", top.quantity, top.priority);
            }
        }
        else if (ch == 5) display_heap(&orders, &catalog);
        else if (ch == 6) display_processed(&processed, &catalog);
        else if (ch == 7) {
            printf("Exiting...\n");
            break;
        } else printf("Invalid choice.\n");
    }
    return 0;
}
