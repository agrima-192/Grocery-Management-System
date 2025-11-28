#ifndef GROCERY_H
#define GROCERY_H

#define INV_FILE "grocery.dat"
#define CART_FILE "cart.dat"

struct Grocery {
    int id;
    char name[50];
    int quantity;
    float price;
};

struct CartItem {
    int id;
    char name[50];
    int quantity;
    float price;
};

#endif
