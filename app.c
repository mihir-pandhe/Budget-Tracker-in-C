#include <stdio.h>
#include <stdlib.h>

#define MAX_ENTRIES 100

typedef struct {
    char description[100];
    float amount;
} Entry;

typedef struct {
    Entry entries[MAX_ENTRIES];
    int count;
} Budget;

void addEntry(Budget *budget, const char *description, float amount);
void displayEntries(const Budget *budget);
float calculateTotal(const Budget *budget);

int main() {
    Budget budget;
    budget.count = 0;

    int choice;
    char description[100];
    float amount;

    while (1) {
        printf("Budget Tracker\n");
        printf("1. Add Income\n");
        printf("2. Add Expense\n");
        printf("3. Display All Entries\n");
        printf("4. Calculate Total\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter income description: ");
                scanf(" %[^\n]s", description);
                printf("Enter income amount: ");
                scanf("%f", &amount);
                addEntry(&budget, description, amount);
                break;

            case 2:
                printf("Enter expense description: ");
                scanf(" %[^\n]s", description);
                printf("Enter expense amount: ");
                scanf("%f", &amount);
                addEntry(&budget, description, -amount);
                break;

            case 3:
                displayEntries(&budget);
                break;

            case 4:
                printf("Total Balance: $%.2f\n", calculateTotal(&budget));
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addEntry(Budget *budget, const char *description, float amount) {
    if (budget->count < MAX_ENTRIES) {
        Entry *entry = &budget->entries[budget->count];
        snprintf(entry->description, sizeof(entry->description), "%s", description);
        entry->amount = amount;
        budget->count++;
    } else {
        printf("Error: Cannot add more entries, budget is full.\n");
    }
}

void displayEntries(const Budget *budget) {
    if (budget->count == 0) {
        printf("No entries found.\n");
        return;
    }

    for (int i = 0; i < budget->count; i++) {
        const Entry *entry = &budget->entries[i];
        printf("%s: $%.2f\n", entry->description, entry->amount);
    }
}

float calculateTotal(const Budget *budget) {
    float total = 0.0f;
    for (int i = 0; i < budget->count; i++) {
        total += budget->entries[i].amount;
    }
    return total;
}
