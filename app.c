#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSACTIONS 100
#define MAX_DESC_LEN 100
#define MAX_CAT_LEN 50
#define MAX_CATEGORIES 20
#define MAX_REPORT_LENGTH 500

typedef struct {
    char date[11];
    char description[MAX_DESC_LEN];
    float amount;
    char category[MAX_CAT_LEN];
} Transaction;

typedef struct {
    char category[MAX_CAT_LEN];
    float budget;
} CategoryBudget;

Transaction transactions[MAX_TRANSACTIONS];
CategoryBudget category_budgets[MAX_CATEGORIES];
int transaction_count = 0;
int budget_count = 0;

void display_menu() {
    printf("Budget Tracker\n");
    printf("1. Add Transaction\n");
    printf("2. Display All Transactions\n");
    printf("3. Filter Transactions by Date\n");
    printf("4. Filter Transactions by Category\n");
    printf("5. Show Summary\n");
    printf("6. Edit Transaction\n");
    printf("7. Delete Transaction\n");
    printf("8. Set Budget\n");
    printf("9. Track Spending\n");
    printf("10. Generate Report\n");
    printf("11. Export Data\n");
    printf("12. Search Transactions\n");
    printf("13. Exit\n");
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

void delete_transaction() {
    int index;
    printf("Enter the index of the transaction to delete (0-%d): ", transaction_count - 1);
    scanf("%d", &index);

    if (index < 0 || index >= transaction_count) {
        printf("Invalid index.\n");
        return;
    }

    char confirm;
    printf("Are you sure you want to delete the transaction at index %d? (y/n): ", index);
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < transaction_count - 1; ++i) {
            transactions[i] = transactions[i + 1];
        }
        transaction_count--;
        printf("Transaction deleted successfully.\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

void set_budget() {
    if (budget_count >= MAX_CATEGORIES) {
        printf("Budget limit reached.\n");
        return;
    }

    CategoryBudget cb;
    printf("Enter category for the budget: ");
    scanf(" %[^\n]%*c", cb.category);
    printf("Enter budget amount: ");
    scanf("%f", &cb.budget);

    category_budgets[budget_count++] = cb;
    printf("Budget set successfully.\n");
}

void track_spending() {
    char category[MAX_CAT_LEN];
    printf("Enter category to track: ");
    scanf(" %[^\n]%*c", category);

    float total_spent = 0;
    float budget = 0;
    for (int i = 0; i < transaction_count; ++i) {
        if (strcmp(transactions[i].category, category) == 0) {
            total_spent += transactions[i].amount;
        }
    }
    
    for (int i = 0; i < budget_count; ++i) {
        if (strcmp(category_budgets[i].category, category) == 0) {
            budget = category_budgets[i].budget;
            break;
        }
    }

    printf("Total spent in category '%s': $%.2f\n", category, total_spent);
    printf("Budget for category '%s': $%.2f\n", category, budget);
    
    if (total_spent > budget) {
        printf("Warning: You have exceeded your budget!\n");
    } else if (budget - total_spent <= 10) {
        printf("Alert: You are nearing your budget limit!\n");
    }
}

void generate_report(const char *filename, const char *period) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "Report for %s\n", period);
    fprintf(file, "Date,Description,Amount,Category\n");

    for (int i = 0; i < transaction_count; ++i) {
        fprintf(file, "%s,%s,%.2f,%s\n", transactions[i].date,
                transactions[i].description, transactions[i].amount,
                transactions[i].category);
    }

    fclose(file);
    printf("Report generated successfully.\n");
}

void export_data() {
    generate_report("transactions_report.csv", "All Transactions");
}

void search_transactions() {
    char search_term[MAX_DESC_LEN];
    printf("Enter search term: ");
    scanf(" %[^\n]%*c", search_term);

    int found = 0;
    for (int i = 0; i < transaction_count; ++i) {
        if (strstr(transactions[i].description, search_term) ||
            strstr(transactions[i].category, search_term)) {
            printf("Date: %s | Description: %s | Amount: $%.2f | Category: %s\n",
                   transactions[i].date, transactions[i].description,
                   transactions[i].amount, transactions[i].category);
            found = 1;
        }
    }
    if (!found) {
        printf("No transactions found matching the search term.\n");
    }
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
                delete_transaction();
                break;
            case 8:
                set_budget();
                break;
            case 9:
                track_spending();
                break;
            case 10:
                generate_report("monthly_report.csv", "Monthly");
                break;
            case 11:
                export_data();
                break;
            case 12:
                search_transactions();
                break;
            case 13:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
