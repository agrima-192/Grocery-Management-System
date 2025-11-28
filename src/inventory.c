#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grocery.h"
#include "utils.h"

void addItem() {
    FILE *fp = fopen(INV_FILE, "ab");
    if (!fp) { printf("Error opening file!\n"); return; }

    struct Grocery g;

    printf("\nEnter Item ID: ");
    scanf("%d", &g.id);
    getchar();

    printf("Enter Item Name: ");
    fgets(g.name, sizeof(g.name), stdin);
    g.name[strcspn(g.name, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d", &g.quantity);

    printf("Enter Price: ");
    scanf("%f", &g.price);

    fwrite(&g, sizeof(g), 1, fp);
    fclose(fp);

    printf("\nItem added successfully!\n");
    pauseProgram();
}


void viewItems() {
    FILE *fp = fopen(INV_FILE, "rb");
    if (!fp) { printf("No inventory found!\n"); pauseProgram(); return; }

    struct Grocery g;

    printf("\n================ INVENTORY ================\n");
    printf("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Qty", "Price");

    while (fread(&g, sizeof(g), 1, fp))
        printf("%-10d %-20s %-10d %-10.2f\n", g.id, g.name, g.quantity, g.price);

    fclose(fp);
    pauseProgram();
}


void searchItem() {
    FILE *fp = fopen(INV_FILE, "rb");
    if (!fp) { printf("Inventory empty!\n"); pauseProgram(); return; }

    int choice, id;
    char name[50];
    struct Grocery g;
    int found = 0;

    printf("\nSearch by:\n1. ID\n2. Name\nChoice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter ID: ");
        scanf("%d", &id);

        while (fread(&g, sizeof(g), 1, fp)) {
            if (g.id == id) {
                printf("\nFound: %s | Qty: %d | Price: %.2f\n", g.name, g.quantity, g.price);
                found = 1;
                break;
            }
        }
    } else {
        printf("Enter Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        while (fread(&g, sizeof(g), 1, fp)) {
            if (strcasecmp(g.name, name) == 0) {
                printf("\nFound: %s | Qty: %d | Price: %.2f\n", g.name, g.quantity, g.price);
                found = 1;
                break;
            }
        }
    }

    if (!found) printf("\nItem not found!\n");

    fclose(fp);
    pauseProgram();
}


void updateItem() {
    FILE *fp = fopen(INV_FILE, "rb+");
    if (!fp) { printf("Error opening file!\n"); pauseProgram(); return; }

    int id, found = 0;
    struct Grocery g;

    printf("\nEnter ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fread(&g, sizeof(g), 1, fp)) {
        if (g.id == id) {
            found = 1;

            printf("\nNew Name: ");
            fgets(g.name, sizeof(g.name), stdin);
            g.name[strcspn(g.name, "\n")] = '\0';

            printf("New Quantity: ");
            scanf("%d", &g.quantity);

            printf("New Price: ");
            scanf("%f", &g.price);

            fseek(fp, -sizeof(g), SEEK_CUR);
            fwrite(&g, sizeof(g), 1, fp);

            printf("\nItem updated!\n");
            break;
        }
    }

    if (!found) printf("\nItem not found!\n");

    fclose(fp);
    pauseProgram();
}


void deleteItem() {
    FILE *fp = fopen(INV_FILE, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) { printf("Error opening files!\n"); pauseProgram(); return; }

    int id, found = 0;
    struct Grocery g;

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    while (fread(&g, sizeof(g), 1, fp)) {
        if (g.id == id) found = 1;
        else fwrite(&g, sizeof(g), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(INV_FILE);
    rename("temp.dat", INV_FILE);

    printf(found ? "\nItem deleted!\n" : "\nItem not found!\n");

    pauseProgram();
}

