#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grocery.h"
#include "utils.h"

void addToCart() {
    FILE *inv = fopen(INV_FILE, "rb+");
    FILE *cart = fopen(CART_FILE, "ab");

    if (!inv || !cart) { printf("Error opening files!\n"); return; }

    int id, qty, found = 0;
    struct Grocery g;
    struct CartItem c;

    printf("\nEnter Item ID: ");
    scanf("%d", &id);

    while (fread(&g, sizeof(g), 1, inv)) {
        if (g.id == id) {
            found = 1;

            printf("Enter quantity: ");
            scanf("%d", &qty);

            if (qty > g.quantity) {
                printf("\nNot enough stock!\n");
                fclose(inv); fclose(cart);
                pauseProgram();
                return;
            }

            c.id = g.id;
            strcpy(c.name, g.name);
            c.quantity = qty;
            c.price = g.price;

            fwrite(&c, sizeof(c), 1, cart);

            g.quantity -= qty;
            fseek(inv, -sizeof(g), SEEK_CUR);
            fwrite(&g, sizeof(g), 1, inv);

            printf("\nAdded to cart!\n");
            break;
        }
    }

    if (!found) printf("\nItem not found!\n");

    fclose(inv);
    fclose(cart);
    pauseProgram();
}


void viewCart() {
    FILE *fp = fopen(CART_FILE, "rb");
    if (!fp) { printf("Cart empty!\n"); pauseProgram(); return; }

    struct CartItem c;
    float total = 0;

    printf("\n================ CART ================\n");
    printf("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Qty", "Price");

    while (fread(&c, sizeof(c), 1, fp)) {
        printf("%-10d %-20s %-10d %-10.2f\n",
               c.id, c.name, c.quantity, c.price);

        total += c.price * c.quantity;
    }

    printf("----------------------------------------\n");
    printf("Total: %.2f\n", total);

    fclose(fp);
    pauseProgram();
}
