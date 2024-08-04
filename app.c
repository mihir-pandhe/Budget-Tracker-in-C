#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSACTIONS 100
#define MAX_DESC_LEN 100
#define MAX_CAT_LEN 50

typedef struct {
    char date[11];
    char description[MAX_DESC_LEN];
    float amount;
    char category[MAX_CAT_LEN];
} Transaction;

Transaction transactions[MAX_TRANSACTIONS];
int transaction_count = 0;

void display_menu() {
    printf("Budget Tracker\n");
    printf("1. Add Transaction\n");
    printf("2. Display All Transactions\n");
    printf("3. Filter Transactions by Date\n");
    printf("4. Filter Transactions by Category\n");
    printf("5. Show Summary\n");
    printf("6. Edit Transaction\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

void add_transaction() {
    if (transaction_count >= MAX_TRANSACTIONS) {
        printf("Transaction limit reached.\n");
        return;
    }

    Transaction t;
    printf("Enter transaction date (YYYY-MM-DD): ");
    scanf("%10s", t.date);
    printf("Enter transaction description: ");
    scanf(" %[^\n]%*c", t.description);
    printf("Enter transaction amount: ");
    scanf("%f", &t.amount);
    printf("Enter transaction category: ");
    scanf(" %[^\n]%*c", t.category);

    transactions[transaction_count++] = t;
    printf("Transaction added successfully.\n");
}

void display_transactions() {
    if (transaction_count == 0) {
        printf("No transactions available.\n");
        return;
    }
    for (int i = 0; i < transaction_count; ++i) {
        printf("Date: %s | Description: %s | Amount: $%.2f | Category: %s\n",
               transactions[i].date, transactions[i].description,
               transactions[i].amount, transactions[i].category);
    }
}

void filter_by_date() {
    char date[11];
    printf("Enter date to filter (YYYY-MM-DD): ");
    scanf("%10s", date);

    int found = 0;
    for (int i = 0; i < transaction_count; ++i) {
        if (strcmp(transactions[i].date, date) == 0) {
            printf("Date: %s | Description: %s | Amount: $%.2f | Category: %s\n",
                   transactions[i].date, transactions[i].description,
                   transactions[i].amount, transactions[i].category);
            found = 1;
        }
    }
    if (!found) {
        printf("No transactions found for the given date.\n");
    }
}

void filter_by_category() {
    char category[MAX_CAT_LEN];
    printf("Enter category to filter: ");
    scanf(" %[^\n]%*c", category);

    int found = 0;
    for (int i = 0; i < transaction_count; ++i) {
        if (strcmp(transactions[i].category, category) == 0) {
            printf("Date: %s | Description: %s | Amount: $%.2f | Category: %s\n",
                   transactions[i].date, transactions[i].description,
                   transactions[i].amount, transactions[i].category);
            found = 1;
        }
    }
    if (!found) {
        printf("No transactions found for the given category.\n");
    }
}

void show_summary() {
    float total_amount = 0;
    for (int i = 0; i < transaction_count; ++i) {
        total_amount += transactions[i].amount;
    }
    printf("Total amount spent: $%.2f\n", total_amount);
}

void edit_transaction() {
    int index;
    printf("Enter the index of the transaction to edit (0-%d): ", transaction_count - 1);
    scanf("%d", &index);

    if (index < 0 || index >= transaction_count) {
        printf("Invalid index.\n");
        return;
    }

    printf("Editing transaction at index %d\n", index);
    printf("Enter new date (YYYY-MM-DD): ");
    scanf("%10s", transactions[index].date);
    printf("Enter new description: ");
    scanf(" %[^\n]%*c", transactions[index].description);
    printf("Enter new amount: ");
    scanf("%f", &transactions[index].amount);
    printf("Enter new category: ");
    scanf(" %[^\n]%*c", transactions[index].category);

    printf("Transaction updated successfully.\n");
}

int main() {
    int choice;
    while (1) {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_transaction();
                break;
            case 2:
                display_transactions();
                break;
            case 3:
                filter_by_date();
                break;
            case 4:
                filter_by_category();
                break;
            case 5:
                show_summary();
                break;
            case 6:
                edit_transaction();
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
