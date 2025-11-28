#include <stdio.h>
#include <stdlib.h>

#include "inventory.h"
#include "cart.h"
#include "billing.h"
#include "utils.h"

int main() {
    int choice;

    while (1) {
        clearScreen();

        printf("\n========== GROCERY MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Item\n");
        printf("2. View Items\n");
        printf("3. Search Item\n");
        printf("4. Update Item\n");
        printf("5. Delete Item\n");
        printf("6. Add to Cart\n");
        printf("7. View Cart\n");
        printf("8. Generate Bill\n");
        printf("9. Exit\n");
        printf("===============================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addItem(); break;
            case 2: viewItems(); break;
            case 3: searchItem(); break;
            case 4: updateItem(); break;
            case 5: deleteItem(); break;
            case 6: addToCart(); break;
            case 7: viewCart(); break;
            case 8: generateBill(); break;
            case 9: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice!\n"); pauseProgram();
        }
    }

    return 0;
}
