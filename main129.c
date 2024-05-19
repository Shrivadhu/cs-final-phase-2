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

void generateInvoice();
void showAllInvoices();
void searchInvoice();
void freeMemory(struct order *customers, int numCustomers);

int main() {
    int opt;

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
                generateInvoice();
                break;
            case 2:
                showAllInvoices();
                break;
            case 3:
                searchInvoice();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid option\n");
        }
    }

    return 0;
}

void generateInvoice() {
    struct order customer;
    printf("Enter customer name: ");
    scanf("%s", customer.name);
    printf("Enter date: ");
    scanf("%s", customer.date);
    printf("Enter number of items: ");
    scanf("%d", &customer.noofitems);

    customer.itm = (struct items *)malloc(customer.noofitems * sizeof(struct items));

    printf("Enter details for each item:\n");
    for (int i = 0; i < customer.noofitems; i++) {
        printf("Item %d name: ", i + 1);
        scanf("%s", customer.itm[i].item);
        printf("Price: ");
        scanf("%f", &customer.itm[i].price);
        printf("Quantity: ");
        scanf("%d", &customer.itm[i].qty);
    }

    FILE *file = fopen("invoices.txt", "a");
    if (file == NULL) {
        perror("Unable to open file");
        free(customer.itm);
        return;
    }

    fprintf(file, "%s %s %d ", customer.name, customer.date, customer.noofitems);
    for (int i = 0; i < customer.noofitems; i++) {
        fprintf(file, "%s %.2f %d ", customer.itm[i].item, customer.itm[i].price, customer.itm[i].qty);
    }
    fprintf(file, "\n");
    fclose(file);

    free(customer.itm);
}

void showAllInvoices() {
    FILE *file = fopen("invoices.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    printf("All Invoices:\n");

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

void searchInvoice() {
    char searchName[50];
    printf("Enter customer name to search: ");
    scanf("%s", searchName);

    FILE *file = fopen("invoices.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    char buffer[1024];
    int found = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, searchName)) {
            found = 1;
            printf("Invoice Found: %s", buffer);
        }
    }

    if (!found) {
        printf("No invoice found for customer '%s'\n", searchName);
    }

    fclose(file);
}

void freeMemory(struct order *customers, int numCustomers) {
    for (int i = 0; i < numCustomers; i++) {
        free(customers[i].itm);
    }
    free(customers);
}
