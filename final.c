#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MIN_BALANCE 1000
#define ARMY_BENEFIT 100000

/* ================= STRUCTURES ================= */
typedef struct {
    char name[30];
    char email[30];
    char aadhaar[13];
    char pan[11];
    char consumerNo[20];
    char password[20];
    float balance;
    int kycDone;
} Account;

typedef struct {
    char consumerNo[20];
    float amount; // Positive for deposit/receive, negative for withdrawal/send
} Transaction;

/* ================= FILE HANDLING HELPERS ================= */

void update_account_in_file(Account *loggedUser) {
    FILE *fp = fopen("accounts.dat", "rb+");
    if (fp == NULL) return;

    Account temp;
    while (fread(&temp, sizeof(Account), 1, fp)) {
        if (strcmp(temp.consumerNo, loggedUser->consumerNo) == 0) {
            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(loggedUser, sizeof(Account), 1, fp);
            break;
        }
    }
    fclose(fp);
}

void log_transaction(char *consumerNo, float amount) {
    FILE *fp = fopen("transactions.dat", "ab");
    if (fp == NULL) return;

    Transaction t;
    strcpy(t.consumerNo, consumerNo);
    t.amount = amount;
    
    fwrite(&t, sizeof(Transaction), 1, fp);
    fclose(fp);
}

void print_transactions(char *consumerNo) {
    FILE *fp = fopen("transactions.dat", "rb");
    if (fp == NULL) {
        printf("No transactions found.\n");
        return;
    }

    Transaction t;
    int count = 1;
    int found = 0;
    
    printf("\n--- TRANSACTION HISTORY ---\n");
    while (fread(&t, sizeof(Transaction), 1, fp)) {
        if (strcmp(t.consumerNo, consumerNo) == 0) {
            printf("%d. %s Rs. %.2f\n", count++, 
                   t.amount > 0 ? "Deposit/Credit " : "Withdraw/Debit", 
                   fabs(t.amount));
            found = 1;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No transactions yet.\n");
    }
    printf("---------------------------\n");
}


/* ================= EMI FUNCTION ================= */
float calculateEMI(float p, float ar, float ty) {
    float r = ar / (12 * 100);
    float n = ty * 12;

    if (p <= 0 || r <= 0) return 0;

    return (p * r * pow(1 + r, n)) / (pow(1 + r, n) - 1);
}

/* ================= LOAN PROCESS ================= */
void process_loan(char *loan_name, float rate, float min_amt, int max_y) {
    float p, emi, total_return;
    char is_army;
    float final_t = max_y;
    float final_r = rate;

    printf("\nAre you Army Personnel? (y/n): ");
    scanf(" %c", &is_army);

    if ((is_army == 'y' || is_army == 'Y') &&
        strcmp(loan_name, "Personal Loan") == 0) {
        final_t += 1.5;
        final_r -= 1.09;
        if (final_r < 1.0)
            final_r = 1.0;
    }

    printf("\n--- %s Setup ---\n", loan_name);
    printf("Minimum Amount: Rs. %.2f\n", min_amt);
    printf("Enter Loan Amount: ");
    scanf("%f", &p);

    if (p < min_amt) {
        printf("ERROR: Minimum loan amount not met.\n");
        return;
    }

    if ((is_army == 'y' || is_army == 'Y') &&
        strcmp(loan_name, "Personal Loan") != 0) {
        p -= ARMY_BENEFIT;
        if (p < 1000) {
            printf("Adjusted principal too low for EMI.\n");
            return;
        }
        printf("Army Benefit Applied: Principal reduced by Rs.1,00,000\n");
    }

    emi = calculateEMI(p, final_r, final_t);
    total_return = emi * final_t * 12;

    printf("\n----- LOAN DETAILS -----\n");
    printf("Interest Rate: %.2f%%\n", final_r);
    printf("Tenure: %.1f years\n", final_t);
    printf("Monthly EMI: Rs. %.2f\n", emi);
    printf("Total Interest: Rs. %.2f\n", total_return - p);
    printf("Total Payable: Rs. %.2f\n", total_return);
}

/* ================= PENSION SYSTEM ================= */

void government_employee() {
    float salary, pension;
    printf("\n--- Government Employee Pension ---\n");
    printf("Enter Basic Salary: ");
    scanf("%f", &salary);
    getchar();
    pension = salary * 0.50;
    printf("Monthly Pension Amount: Rs %.2f\n", pension);
}

void private_employee() {
    float salary, contribution, pension;
    printf("\n--- Private Employee Pension ---\n");
    printf("Enter Monthly Salary: ");
    scanf("%f", &salary);
    getchar();
    contribution = salary * 0.10;
    pension = contribution * 20;
    printf("Monthly Contribution: Rs %.2f\n", contribution);
    printf("Estimated Monthly Pension: Rs %.2f\n", pension);
}

void self_employed() {
    float monthly_contribution, pension;
    printf("\n--- Self-Employed Pension ---\n");
    printf("Enter Monthly Contribution: ");
    scanf("%f", &monthly_contribution);
    getchar();
    pension = monthly_contribution * 25;
    printf("Estimated Monthly Pension: Rs %.2f\n", pension);
}

void daily_wage_worker() {
    float contribution, pension;
    printf("\n--- Daily Wage Worker Pension ---\n");
    printf("Enter Monthly Contribution: ");
    scanf("%f", &contribution);
    getchar();
    pension = contribution * 30 + 1000;
    printf("Estimated Monthly Pension (with subsidy): Rs %.2f\n", pension);
}

void pension_system() {
    int choice;
    printf("\n===== BANKING PENSION SYSTEM =====\n");
    printf("1. Government Employee\n");
    printf("2. Private Employee\n");
    printf("3. Self-Employed Professional\n");
    printf("4. Daily Wage Worker\n");
    printf("5. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1: government_employee(); break;
        case 2: private_employee(); break;
        case 3: self_employed(); break;
        case 4: daily_wage_worker(); break;
        case 5: printf("\nExiting Pension System.\n"); break;
        default: printf("\nInvalid choice!\n");
    }
}

/* ================= FIXED DEPOSIT SYSTEM ================= */

void fixed_deposit_system() {
    int choice;
    float p, TIY, rate, min_p, interest, ma;
    int TM;

    while (1) {
        printf("\n===== Bank FD Portal (2026) =====\n");
        printf("1. Common Scheme   (5.0%% | 18 Months | Min: 1000)\n");
        printf("2. Special Scheme  (7.5%% | 12 Months | Min: 1500)\n");
        printf("3. Female Scheme   (6.2%% | 16 Months | Min: 1250)\n");
        printf("4. Army Scheme     (7.0%% | 11 Months | Min: 950)\n");
        printf("5. Exit\n");
        printf("Select your scheme (1-5): ");
        scanf("%d", &choice);
        getchar();

        if (choice == 5) {
            printf("Exiting FD Portal...\n");
            break;
        }

        if (choice == 1) {
            rate = 5.0; min_p = 1000.0; TM = 18;
            printf("\nSelected: Common Scheme\n");
        }
        else if (choice == 2) {
            rate = 7.5; min_p = 1500.0; TM = 12;
            printf("\nSelected: Special Scheme\n");
        }
        else if (choice == 3) {
            rate = 6.2; min_p = 1250.0; TM = 16;
            printf("\nSelected: Female Scheme\n");
        }
        else if (choice == 4) {
            rate = 7.0; min_p = 950.0; TM = 11;
            printf("\nSelected: Army Personnel Scheme\n");
        }
        else {
            printf("\nInvalid selection! Please try again.\n");
            continue;
        }

        printf("Enter the Principal amount: ");
        scanf("%f", &p);
        getchar();

        if (p < min_p) {
            printf("\nError: Minimum principal for this scheme is Rs. %.2f\n", min_p);
            continue;
        }

        TIY = (float)TM / 12.0;
        interest = (p * rate * TIY) / 100;
        ma = p + interest;

        printf("\n--- FD Maturity Statement ---\n");
        printf("Principal Amount:   Rs. %.2f\n", p);
        printf("Interest Rate:      %.1f%% p.a.\n", rate);
        printf("Tenure:             %d months\n", TM);
        printf("Interest Earned:    Rs. %.2f\n", interest);
        printf("Maturity Value:     Rs. %.2f\n", ma);
        printf("-----------------------------\n");
    }
}

/* ================= MAIN PROGRAM ================= */

int main() {
    int choice, bankChoice;
    char loginId[20], loginPass[20];
    float amount;
    char receiverAccNo[25];
    
    srand(time(NULL));

    while (1) {
        printf("\n==============================\n");
        printf("   WELCOME TO World Peace Bank\n");
        printf("==============================\n");
        printf("1. Not an account? Create Account!\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            Account newAcc;
            memset(&newAcc, 0, sizeof(Account));
            
            printf("\n--- SIGNUP ---\n");
            printf("Enter Name: ");
            fgets(newAcc.name, sizeof(newAcc.name), stdin);
            newAcc.name[strcspn(newAcc.name, "\n")] = 0;

            printf("Enter Email-ID: ");
            fgets(newAcc.email, sizeof(newAcc.email), stdin);
            newAcc.email[strcspn(newAcc.email, "\n")] = 0;

            printf("Enter Password: ");
            fgets(newAcc.password, sizeof(newAcc.password), stdin);
            newAcc.password[strcspn(newAcc.password, "\n")] = 0;
            
            while(1) {
                printf("Enter Aadhaar Number (12 digits): ");
                fgets(newAcc.aadhaar, sizeof(newAcc.aadhaar), stdin);
                newAcc.aadhaar[strcspn(newAcc.aadhaar, "\n")] = 0;
                if (strlen(newAcc.aadhaar) != 12) {
                    printf("Invalid Aadhaar Number. Please enter 12 digits\n");
                } else {
                    printf("Aadhaar Number accepted\n");
                    break;
                }
            }

            // Generate 10-digit consumer number
            sprintf(newAcc.consumerNo, "%d%d", rand() % 90000 + 10000, rand() % 90000 + 10000);
            newAcc.balance = 0;
            newAcc.kycDone = 0;

            FILE *fp = fopen("accounts.dat", "ab");
            if (fp == NULL) {
                printf("Error saving account!\n");
                continue;
            }
            fwrite(&newAcc, sizeof(Account), 1, fp);
            fclose(fp);

            printf("\nAccount Created Successfully! Make sure to fill the KYC form later.\n");
            printf(">>> Your Consumer No: %s <<< (SAVE THIS FOR LOGIN!)\n", newAcc.consumerNo);
        }

        else if (choice == 2) {
            printf("\n--- LOGIN ---\n");
            printf("Consumer No: ");
            fgets(loginId, sizeof(loginId), stdin);
            loginId[strcspn(loginId, "\n")] = 0;

            printf("Password: ");
            fgets(loginPass, sizeof(loginPass), stdin);
            loginPass[strcspn(loginPass, "\n")] = 0;

            FILE *fp = fopen("accounts.dat", "rb");
            if (fp == NULL) {
                printf("\nNo accounts exist yet. Please create one.\n");
                continue;
            }

            Account loggedInUser;
            int found = 0;

            while (fread(&loggedInUser, sizeof(Account), 1, fp)) {
                if (strcmp(loggedInUser.consumerNo, loginId) == 0 &&
                    strcmp(loggedInUser.password, loginPass) == 0) {
                    found = 1;
                    break;
                }
            }
            fclose(fp);

            if (found) {
                printf("\nLogin Successful! Welcome %s.\n", loggedInUser.name);
                
                if (loggedInUser.balance == 0) {
                    float initialDeposit = 0;
                    do {
                        printf("\nEnter Initial Deposit (Greater than 1000): ");
                        scanf("%f", &initialDeposit);
                        if (initialDeposit < 1000) {
                            printf("Invalid amount. Please try again.\n");
                        }
                    } while (initialDeposit < 1000);
                    
                    loggedInUser.balance += initialDeposit;
                    update_account_in_file(&loggedInUser);
                    log_transaction(loggedInUser.consumerNo, initialDeposit);
                }

                while (1) {
                    printf("\n----- BANK MENU -----\n");
                    printf("1. Deposit Money\n2. Withdraw Money\n3. Check Balance\n");
                    printf("4. Transactions History\n5. Know-Your-Customer (KYC)\n");
                    printf("6. Loan Services\n7. Bank Transfer\n8. Pension Schemes\n");
                    printf("9. Fixed Deposit (FD)\n10. Logout\nChoice: ");
                    
                    scanf("%d", &bankChoice);
                    getchar();

                    if (bankChoice == 1) {
                        if (!loggedInUser.kycDone) { printf("Complete KYC first.\n"); continue; }
                        printf("Amount: ");
                        scanf("%f", &amount); getchar();
                        
                        if (amount > 0) {
                            loggedInUser.balance += amount;
                            update_account_in_file(&loggedInUser);
                            log_transaction(loggedInUser.consumerNo, amount);
                            printf("Rs. %.2f added to account successfully!\n", amount);
                        } else {
                            printf("Invalid amount!\n");
                        }
                    }
                    else if (bankChoice == 2) {
                        if (!loggedInUser.kycDone) { printf("Complete KYC first.\n"); continue; }
                        printf("Amount: ");
                        scanf("%f", &amount); getchar();
                        
                        if (amount > 0 && amount <= loggedInUser.balance) {
                            loggedInUser.balance -= amount;
                            update_account_in_file(&loggedInUser);
                            log_transaction(loggedInUser.consumerNo, -amount);
                            printf("Rs. %.2f deducted successfully!\n", amount);
                        } else {
                            printf("Insufficient balance or invalid amount.\n");
                        }
                    }
                    else if (bankChoice == 3) {
                        printf("Current Balance: Rs. %.2f\n", loggedInUser.balance);
                    }
                    else if (bankChoice == 4) {
                        print_transactions(loggedInUser.consumerNo);
                    }
                    else if (bankChoice == 5) {
                        if (loggedInUser.kycDone == 1) {
                            printf("KYC already completed!\n");
                            continue;
                        }
                        printf("Enter PAN (10 chars): ");
                        fgets(loggedInUser.pan, sizeof(loggedInUser.pan), stdin);
                        loggedInUser.pan[strcspn(loggedInUser.pan, "\n")] = 0;

                        if (strlen(loggedInUser.pan) == 10) {
                            loggedInUser.kycDone = 1;
                            update_account_in_file(&loggedInUser);
                            printf("KYC Completed Successfully.\n");
                        } else {
                            printf("Invalid PAN.\n");
                        }
                    }
                    else if (bankChoice == 6) {
                        int lc;
                        printf("\n--- LOAN MENU ---\n");
                        printf("1. Car Loan\n2. Business Loan\n3. Home Loan\n4. Personal Loan\n5. Exit\n");
                        printf("Choice: ");
                        scanf("%d", &lc);
                        getchar();

                        switch (lc) {
                            case 1: process_loan("Car Loan", 7.9, 100000, 5); break;
                            case 2: process_loan("Business Loan", 8.7, 1000000, 10); break;
                            case 3: process_loan("Home Loan", 9.6, 1250550, 20); break;
                            case 4: process_loan("Personal Loan", 12.7, 200000, 2); break;
                            default: break;
                        }
                    }
                    else if (bankChoice == 7) {
                        if (!loggedInUser.kycDone) { printf("Complete KYC first.\n"); continue; }
                        
                        printf("Enter Receiver Account (Consumer) Number: ");
                        fgets(receiverAccNo, sizeof(receiverAccNo), stdin);
                        receiverAccNo[strcspn(receiverAccNo, "\n")] = 0;

                        printf("Enter Amount to Transfer: ");
                        scanf("%f", &amount); getchar();

                        if (amount <= 0 || amount > loggedInUser.balance) {
                            printf("Invalid amount or insufficient balance.\n");
                            continue;
                        }

                        // Find Receiver and update
                        FILE *fp_transfer = fopen("accounts.dat", "rb+");
                        Account receiver;
                        int receiverFound = 0;
                        
                        while (fread(&receiver, sizeof(Account), 1, fp_transfer)) {
                            if (strcmp(receiver.consumerNo, receiverAccNo) == 0) {
                                receiverFound = 1;
                                break;
                            }
                        }

                        if (receiverFound) {
                            // Update receiver balance
                            receiver.balance += amount;
                            fseek(fp_transfer, -sizeof(Account), SEEK_CUR);
                            fwrite(&receiver, sizeof(Account), 1, fp_transfer);
                            fclose(fp_transfer);

                            // Update sender balance
                            loggedInUser.balance -= amount;
                            update_account_in_file(&loggedInUser);

                            // Log transactions for both
                            log_transaction(loggedInUser.consumerNo, -amount);
                            log_transaction(receiver.consumerNo, amount);

                            printf("Rs. %.2f transferred successfully to Account %s.\n", amount, receiverAccNo);
                        } else {
                            printf("Receiver account not found.\n");
                            fclose(fp_transfer);
                        }
                    }
                    else if (bankChoice == 8) {
                        pension_system();
                    }
                    else if (bankChoice == 9) {
                        fixed_deposit_system();
                    }
                    else if (bankChoice == 10) {
                        printf("Logged out successfully.\n");
                        break;
                    }
                }
            } else {
                printf("\nInvalid Consumer Number or Password.\n");
            }
        }
        else if (choice == 3) {
            printf("\nThank you for visiting World Peace Bank.\n");
            break;
        }
    }
    return 0;
}