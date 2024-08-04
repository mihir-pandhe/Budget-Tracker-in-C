#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define DATE_LENGTH 11

typedef struct {
    char date[DATE_LENGTH];
    char description[100];
    float amount;
} Transaction;

typedef struct {
    Transaction transactions[MAX_ENTRIES];
    int count;
} Budget;

void addTransaction(Budget *budget, const char *date, const char *description, float amount);
void displayTransactions(const Budget *budget);
float calculateTotal(const Budget *budget);

int main() {
    Budget budget;
    budget.count = 0;

    int choice;
    char date[DATE_LENGTH];
    char description[100];
    float amount;

    while (1) {
        printf("Budget Tracker\n");
        printf("1. Add Transaction\n");
        printf("2. Display All Transactions\n");
        printf("3. Calculate Total\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter transaction date (YYYY-MM-DD): ");
                fgets(date, DATE_LENGTH, stdin);
                date[strcspn(date, "\n")] = '\0';
                printf("Enter transaction description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0';
                printf("Enter transaction amount: ");
                scanf("%f", &amount);
                getchar();
                addTransaction(&budget, date, description, amount);
                break;

            case 2:
                displayTransactions(&budget);
                break;

            case 3:
                printf("Total Balance: $%.2f\n", calculateTotal(&budget));
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addTransaction(Budget *budget, const char *date, const char *description, float amount) {
    if (budget->count < MAX_ENTRIES) {
        Transaction *transaction = &budget->transactions[budget->count];
        strncpy(transaction->date, date, DATE_LENGTH - 1);
        transaction->date[DATE_LENGTH - 1] = '\0'; // Ensure null termination
        strncpy(transaction->description, description, sizeof(transaction->description) - 1);
        transaction->description[sizeof(transaction->description) - 1] = '\0'; // Ensure null termination
        transaction->amount = amount;
        budget->count++;
    } else {
        printf("Error: Cannot add more transactions, budget is full.\n");
    }
}
void displayTransactions(const Budget *budget) {
    if (budget->count == 0) {
        printf("No transactions found.\n");
        return;
    }

    for (int i = 0; i < budget->count; i++) {
        const Transaction *transaction = &budget->transactions[i];
        printf("Date: %s | Description: %s | Amount: $%.2f\n",
               transaction->date, transaction->description, transaction->amount);
    }
}

float calculateTotal(const Budget *budget) {
    float total = 0.0f;
    for (int i = 0; i < budget->count; i++) {
        total += budget->transactions[i].amount;
    }
    return total;
}
