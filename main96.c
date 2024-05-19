#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items {
    char item[20];
    float price;
    int qty;
};

struct order {
    char name[50];
    char date[50];
    int noofitems;
    struct items *itm;
};

void generateInvoice(struct order *customer);
void showAllInvoices(struct order *customers, int numCustomers);
void searchInvoice(struct order *customers, int numCustomers);
void freeMemory(struct order *customers, int numCustomers);

int main() {
    int opt;
    int numCustomers = 0;
    struct order *customers = NULL;

    printf("\t\tWELCOME\n");
    printf("==============PESU STORE==============\n\n");
    
    while (1) {
        printf("1 Generate Invoice\n");
        printf("2 Show All Invoices\n");
        printf("3 Search Invoice\n");
        printf("4 Exit\n\n");
        printf("Please Select Your Option: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                numCustomers++;
                customers = (struct order *)realloc(customers, numCustomers * sizeof(struct order));
                generateInvoice(&customers[numCustomers - 1]);
                break;
            case 2:
                showAllInvoices(customers, numCustomers);
                break;
            case 3:
                searchInvoice(customers, numCustomers);
                break;
            case 4:
                freeMemory(customers, numCustomers);
                exit(0);
            default:
                printf("Invalid option\n");
        }
    }

    return 0;
}

void generateInvoice(struct order *customer) {
    printf("Enter customer name: ");
    scanf("%s", customer->name);
    printf("Enter date: ");
    scanf("%s", customer->date);
    printf("Enter number of items: ");
    scanf("%d", &customer->noofitems);

    customer->itm = (struct items *)malloc(customer->noofitems * sizeof(struct items));

    printf("Enter details for each item:\n");
    for (int i = 0; i < customer->noofitems; i++) {
        printf("Item %d name: ", i + 1);
        scanf("%s", customer->itm[i].item);
        printf("Price: ");
        scanf("%f", &customer->itm[i].price);
        printf("Quantity: ");
        scanf("%d", &customer->itm[i].qty);
    }
}

void showAllInvoices(struct order *customers, int numCustomers) {
    if (numCustomers == 0) {
        printf("No invoices available\n");
        return;
    }

    printf("All Invoices:\n");
    for (int i = 0; i < numCustomers; i++) {
        printf("Customer Name: %s\n", customers[i].name);
        printf("Date: %s\n", customers[i].date);
        printf("Items Purchased:\n");
        for (int j = 0; j < customers[i].noofitems; j++) {
            printf("%s - Price: %.2f, Quantity: %d\n", customers[i].itm[j].item, customers[i].itm[j].price, customers[i].itm[j].qty);
        }
        printf("\n");
    }
}

void searchInvoice(struct order *customers, int numCustomers) {
    char searchName[50];
    printf("Enter customer name to search: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(customers[i].name, searchName) == 0) {
            found = 1;
            printf("Customer Name: %s\n", customers[i].name);
            printf("Date: %s\n", customers[i].date);
            printf("Items Purchased:\n");
            for (int j = 0; j < customers[i].noofitems; j++) {
                printf("%s - Price: %.2f, Quantity: %d\n", customers[i].itm[j].item, customers[i].itm[j].price, customers[i].itm[j].qty);
            }
            printf("\n");
        }
    }

    if (!found) {
        printf("No invoice found for customer '%s'\n", searchName);
    }
}

void freeMemory(struct order *customers, int numCustomers) {
    for (int i = 0; i < numCustomers; i++) {
        free(customers[i].itm);
    }
    free(customers);
}
