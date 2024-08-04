#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define DATE_LENGTH 11
#define CATEGORY_LENGTH 20

typedef struct {
    char date[DATE_LENGTH];
    char description[100];
    float amount;
    char category[CATEGORY_LENGTH];
} Transaction;

typedef struct {
    Transaction transactions[MAX_ENTRIES];
    int count;
} Budget;

void addTransaction(Budget *budget, const char *date, const char *description, float amount, const char *category);
void displayTransactions(const Budget *budget);
void filterTransactionsByDate(const Budget *budget, const char *date);
void filterTransactionsByCategory(const Budget *budget, const char *category);
void displaySummary(const Budget *budget);

int main() {
    Budget budget;
    budget.count = 0;

    int choice;
    char date[DATE_LENGTH];
    char description[100];
    char category[CATEGORY_LENGTH];
    float amount;

    while (1) {
        printf("Budget Tracker\n");
        printf("1. Add Transaction\n");
        printf("2. Display All Transactions\n");
        printf("3. Filter Transactions by Date\n");
        printf("4. Filter Transactions by Category\n");
        printf("5. Show Summary\n");
        printf("6. Exit\n");
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
                fgets(category, CATEGORY_LENGTH, stdin);
                category[strcspn(category, "\n")] = '\0';
                addTransaction(&budget, date, description, amount, category);
                break;

            case 2:
                displayTransactions(&budget);
                break;

            case 3:
                printf("Enter date to filter by (YYYY-MM-DD): ");
                fgets(date, DATE_LENGTH, stdin);
                date[strcspn(date, "\n")] = '\0';
                filterTransactionsByDate(&budget, date);
                break;

            case 4:
                printf("Enter category to filter by: ");
                fgets(category, CATEGORY_LENGTH, stdin);
                category[strcspn(category, "\n")] = '\0';
                filterTransactionsByCategory(&budget, category);
                break;

            case 5:
                displaySummary(&budget);
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addTransaction(Budget *budget, const char *date, const char *description, float amount, const char *category) {
    if (budget->count < MAX_ENTRIES) {
        Transaction *transaction = &budget->transactions[budget->count];
        strncpy(transaction->date, date, DATE_LENGTH - 1);
        transaction->date[DATE_LENGTH - 1] = '\0';
        strncpy(transaction->description, description, sizeof(transaction->description) - 1);
        transaction->description[sizeof(transaction->description) - 1] = '\0';
        transaction->amount = amount;
        strncpy(transaction->category, category, CATEGORY_LENGTH - 1);
        transaction->category[CATEGORY_LENGTH - 1] = '\0';
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
        printf("Date: %s | Description: %s | Amount: $%.2f | Category: %s\n",
               transaction->date, transaction->description, transaction->amount, transaction->category);
    }
}

void filterTransactionsByDate(const Budget *budget, const char *date) {
    int found = 0;
    for (int i = 0; i < budget->count; i++) {
        const Transaction *transaction = &budget->transactions[i];
        if (strcmp(transaction->date, date) == 0) {
            printf("Date: %s | Description: %s | Amount: $%.2f | Category: %s\n",
                   transaction->date, transaction->description, transaction->amount, transaction->category);
            found = 1;
        }
    }
    if (!found) {
        printf("No transactions found for the specified date.\n");
    }
}

void filterTransactionsByCategory(const Budget *budget, const char *category) {
    int found = 0;
    for (int i = 0; i < budget->count; i++) {
        const Transaction *transaction = &budget->transactions[i];
        if (strcmp(transaction->category, category) == 0) {
            printf("Date: %s | Description: %s | Amount: $%.2f | Category: %s\n",
                   transaction->date, transaction->description, transaction->amount, transaction->category);
            found = 1;
        }
    }
    if (!found) {
        printf("No transactions found for the specified category.\n");
    }
}

void displaySummary(const Budget *budget) {
    float totalIncome = 0.0f;
    float totalExpenses = 0.0f;
    for (int i = 0; i < budget->count; i++) {
        const Transaction *transaction = &budget->transactions[i];
        if (transaction->amount >= 0) {
            totalIncome += transaction->amount;
        } else {
            totalExpenses += transaction->amount;
        }
    }
    printf("Summary:\n");
    printf("Total Income: $%.2f\n", totalIncome);
    printf("Total Expenses: $%.2f\n", totalExpenses);
    printf("Net Balance: $%.2f\n", totalIncome + totalExpenses);
}
