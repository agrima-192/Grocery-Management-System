#include <stdio.h>
#include <stdlib.h>
#include "grocery.h"
#include "utils.h"

void generateBill() {
    FILE *fp = fopen(CART_FILE, "rb");
    if (!fp) { printf("Cart is empty!\n"); pauseProgram(); return; }

    struct CartItem c;
    float total = 0;

    printf("\n==================== BILL ====================\n");
    printf("%-10s %-20s %-10s %-10s %-10s\n",
           "ID", "Name", "Qty", "Price", "Total");

    while (fread(&c, sizeof(c), 1, fp)) {
        float item_total = c.quantity * c.price;
        total += item_total;

        printf("%-10d %-20s %-10d %-10.2f %-10.2f\n",
               c.id, c.name, c.quantity, c.price, item_total);
    }

    printf("-----------------------------------------------\n");
    printf("GRAND TOTAL: %.2f\n", total);

    fclose(fp);
    remove(CART_FILE);

    printf("\nBill generated. Cart cleared.\n");
    pauseProgram();
}
