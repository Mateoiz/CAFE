#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ORDERS 100
#define ESPRESSO_SHOT_PRICE 28.0

typedef struct Order {
    char itemName[50];
    float price;
    int quantity;
    char sugarLevel[20];
    int espressoShot;
} Order;

typedef struct Account {
    char username[50];
    float points;
    struct tm creationDate;
} Account;

Order orders[MAX_ORDERS];
int orderCount = 0;
int itemAdded = 0;
struct Account account;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void displayCoffeeMenu() {
    printf("\n==============================\n");
    printf("  Coffee & Espresso Menu\n");
    printf("==============================\n");
    printf("1. Espresso - 140.00 PHP\n");
    printf("2. Americano - 168.00 PHP\n");
    printf("3. Cappuccino - 196.00 PHP\n");
    printf("4. Latte - 224.00 PHP\n");
    printf("5. Mocha - 252.00 PHP\n");
    printf("6. Macchiato - 210.00 PHP\n");
    printf("7. Flat White - 182.00 PHP\n");
    printf("8. Cold Brew - 168.00 PHP\n");
    printf("9. Affogato - 266.00 PHP\n");
    printf("10. Back to Main Menu\n");
    printf("==============================\n");
}

void displayTeaMenu() {
    printf("\n==============================\n");
    printf("  Teas & Infusions Menu\n");
    printf("==============================\n");
    printf("1. English Breakfast Tea - 112.00 PHP\n");
    printf("2. Earl Grey - 140.00 PHP\n");
    printf("3. Green Tea - 154.00 PHP\n");
    printf("4. Chai Latte - 196.00 PHP\n");
    printf("5. Matcha Latte - 224.00 PHP\n");
    printf("6. Peppermint Tea - 126.00 PHP\n");
    printf("7. Chamomile Tea - 126.00 PHP\n");
    printf("8. Iced Tea - 140.00 PHP\n");
    printf("9. Back to Main Menu\n");
    printf("==============================\n");
}

void displayBakeryMenu() {
    printf("\n==============================\n");
    printf("  Bakery & Pastries Menu\n");
    printf("==============================\n");
    printf("1. Croissant (Plain, Almond, Chocolate) - 168.00 PHP (Plain), 182.00 PHP (Almond), 196.00 PHP (Chocolate)\n");
    printf("2. Muffins (Blueberry, Banana Nut, Chocolate Chip) - 154.00 PHP (Blueberry), 168.00 PHP (Banana Nut), 182.00 PHP (Chocolate Chip)\n");
    printf("3. Scones (Raisin, Cranberry) - 140.00 PHP (Raisin), 154.00 PHP (Cranberry)\n");
    printf("4. Cinnamon Rolls - 182.00 PHP\n");
    printf("5. Danish Pastries - 196.00 PHP\n");
    printf("6. Back to Main Menu\n");
    printf("==============================\n");
}

void addPoints(float amount);
void addOrder(const char *itemName, float price, int quantity, const char *sugarLevel, int espressoShot);

void addBakeryOrder(int itemChoice, int subChoice, int quantity) {
    switch (itemChoice) {
        case 1:
            switch (subChoice) {
                case 1:
                    addOrder("Plain Croissant", 168.00, quantity, "None", 0);
                    addPoints(3.2 * quantity);
                    break;
                case 2:
                    addOrder("Almond Croissant", 182.00, quantity, "None", 0);
                    addPoints(1 * quantity);
                    break;
                case 3:
                    addOrder("Chocolate Croissant", 196.00, quantity, "None", 0);
                    addPoints(1 * quantity);
                    break;
                default:
                    printf("Invalid selection. Please try again.\n");
                    break;
            }
            break;
        case 2:
            switch (subChoice) {
                case 1:
                    addOrder("Blueberry Muffin", 154.00, quantity, "None", 0);
                    addPoints(1 * quantity);
                    break;
                case 2:
                    addOrder("Banana Nut Muffin", 168.00, quantity, "None", 0);
                    addPoints(1 * quantity);
                    break;
                case 3:
                    addOrder("Chocolate Chip Muffin", 182.00, quantity, "None", 0);
                    addPoints(1 * quantity);
                    break;
                default:
                    printf("Invalid selection. Please try again.\n");
                    break;
            }
            break;
        case 3:
            switch (subChoice) {
                case 1:
                    addOrder("Raisin Scone", 140.00, quantity, "None", 0);
                    addPoints(1 * quantity);
                    break;
                case 2:
                    addOrder("Cranberry Scone", 154.00, quantity, "None", 0);
                    addPoints(1 * quantity);
                    break;
                default:
                    printf("Invalid selection. Please try again.\n");
                    break;
            }
            break;
        default:
            printf("Invalid selection. Please try again.\n");
            break;
    }
}

void addOrder(const char *itemName, float price, int quantity, const char *sugarLevel, int espressoShot) {
    if (orderCount < MAX_ORDERS) {
        strcpy(orders[orderCount].itemName, itemName);
        orders[orderCount].price = (price + (espressoShot * ESPRESSO_SHOT_PRICE)) * quantity;
        orders[orderCount].quantity = quantity;
        strcpy(orders[orderCount].sugarLevel, sugarLevel);
        orders[orderCount].espressoShot = espressoShot;
        orderCount++;
        itemAdded = 1;
    } else {
        printf("Order limit reached. Cannot add more items.\n");
    }
}

int isAccountValid(struct tm creationDate) {
    time_t now = time(NULL);
    struct tm *currentDate = localtime(&now);

    double seconds = difftime(mktime(currentDate), mktime(&creationDate));
    double days = seconds / (60 * 60 * 24);

    if (days > 365) {
        return 0;
    } else if (days > 335) { // 365 - 30 = 335
        printf("Warning: Your account is about to expire in less than a month.\n");
    }
    return 1;
}

void printReceipt() {
    float total = 0.0;
    printf("\n==============================\n");
    printf("           Receipt\n");
    printf("==============================\n");
    int i;
    for (i = 0; i < orderCount; i++) {
        printf("%d. %s - %d x %.2f PHP (Sugar: %s, Espresso Shot: %s)\n", i + 1, orders[i].itemName, orders[i].quantity, orders[i].price, orders[i].sugarLevel, orders[i].espressoShot ? "Yes" : "No");
        total += orders[i].price;
    }
    printf("------------------------------\n");
    printf("Total: %.2f PHP\n", total);
    if (account.points > 1) {
        if (isAccountValid(account.creationDate)) {
            char usePoints;
            printf("You have %.2f points. Would you like to use them to get a discount? (y/n): ", account.points);
            clearInputBuffer();
            scanf("%c", &usePoints);
            if (usePoints == 'y' || usePoints == 'Y') {
                float discount = account.points;
                if (discount > total) {
                    discount = total;
                }
                total -= discount;
                account.points -= discount;
                printf("Discount applied: %.2f PHP\n", discount);
                printf("New Total: %.2f PHP\n", total);
            }
        } else {
            printf("Your account is no longer valid for points usage.\n");
        }
    }
    printf("==============================\n");
}

void addPoints(float amount) {
    account.points += (int)(amount / 50);
}

void viewPointsBalance() {
    printf("\n==============================\n");
    printf("     Points Balance\n");
    printf("==============================\n");
    printf("Points Balance: %.2f\n", account.points);
    printf("==============================\n");
}

void createAccount(char *username) {
    char password[50];
    int year, month, day;

    printf("\n==============================\n");
    printf("     Create an Account\n");
    printf("==============================\n");
    printf("Enter username: ");
    while ((getchar()) != '\n');
    scanf("%s", username);
    printf("Enter password: ");
    while ((getchar()) != '\n');
    scanf("%s", password);
    printf("Enter account creation date (YYYY/MM/DD): ");
    while ((getchar()) != '\n');
    scanf("%d %d %d", &year, &month, &day);

    strcpy(account.username, username);
    account.points = 0.0;

    account.creationDate.tm_year = year - 1900; 
    account.creationDate.tm_mon = month - 1;
    account.creationDate.tm_mday = day;
    account.creationDate.tm_hour = 0;
    account.creationDate.tm_min = 0;
    account.creationDate.tm_sec = 0;
    account.creationDate.tm_isdst = -1;        

    printf("Account created successfully!\n");
    printf("==============================\n");
}

int login(char *username, int *accountCreated) {
    int choice;
    printf("\n==============================\n");
    printf("           Login\n");
    printf("==============================\n");
    printf("1. Create Account\n");
    printf("2. Continue as Guest\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    clearInputBuffer();
    scanf("%d", &choice);

    if (choice == 1) {
        createAccount(username);
        *accountCreated = 1;
    } else if (choice == 2) {
        strcpy(username, "Guest");
    } else if (choice == 3) {
        return 0;
    }
    printf("==============================\n");
    return 1;
}

int main() {
    int choice;
    int itemChoice;
    int subChoice;
    int quantity;
    char sugarLevel[20];
    int espressoShot;
    char username[50];
    int accountCreated = 0;

    printf("Welcome to the Cafe Ordering System!\n");
    if (!login(username, &accountCreated)) {
        return 0;
    }

    while (1) {
        printf("\n==============================\n");
        printf("Hello, %s!\n", username);
        printf("==============================\n");
        printf("Please select a menu to view:\n");
        printf("1. Coffee & Espresso\n");
        printf("2. Teas & Infusions\n");
        printf("3. Bakery & Pastries\n");
        if (itemAdded) {
            printf("4. Finalize Order and Print Receipt\n");
        }
        if (accountCreated) {
            printf("5. View Points Balance\n");
        }
        printf("6. Logout\n");
        printf("Enter your choice: ");
        while ((getchar()) != '\n');
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCoffeeMenu();
                printf("Please select an item by entering the corresponding number: ");
                while ((getchar()) != '\n');
                scanf("%d", &itemChoice);
                if (itemChoice == 10) break;
                printf("Enter quantity: ");
                while ((getchar()) != '\n');
                scanf("%d", &quantity);
                printf("Enter sugar level (None, Low, Medium, High): ");
                while ((getchar()) != '\n');
                scanf("%s", sugarLevel);
                printf("Add an espresso shot? (1 for Yes, 0 for No): ");
                while ((getchar()) != '\n');
                scanf("%d", &espressoShot);
                switch (itemChoice) {
                    case 1:
                        printf("You selected Espresso.\n");
                        addOrder("Espresso", 140.00, quantity, sugarLevel, espressoShot);
                        addPoints(140.00 * quantity);
                        break;
                    case 2:
                        printf("You selected Americano.\n");
                        addOrder("Americano", 168.00, quantity, sugarLevel, espressoShot);
                        addPoints(168.00 * quantity);
                        break;
                    case 3:
                        printf("You selected Cappuccino.\n");
                        addOrder("Cappuccino", 196.00, quantity, sugarLevel, espressoShot);
                        addPoints(196.00 * quantity);
                        break;
                    case 4:
                        printf("You selected Latte.\n");
                        addOrder("Latte", 224.00, quantity, sugarLevel, espressoShot);
                        addPoints(224.00 * quantity);
                        break;
                    case 5:
                        printf("You selected Mocha.\n");
                        addOrder("Mocha", 252.00, quantity, sugarLevel, espressoShot);
                        addPoints(252.00 * quantity);
                        break;
                    case 6:
                        printf("You selected Macchiato.\n");
                        addOrder("Macchiato", 210.00, quantity, sugarLevel, espressoShot);
                        addPoints(210.00 * quantity);
                        break;
                    case 7:
                        printf("You selected Flat White.\n");
                        addOrder("Flat White", 182.00, quantity, sugarLevel, espressoShot);
                        addPoints(182.00 * quantity);
                        break;
                    case 8:
                        printf("You selected Cold Brew.\n");
                        addOrder("Cold Brew", 168.00, quantity, sugarLevel, espressoShot);
                        addPoints(168.00 * quantity);
                        break;
                    case 9:
                        printf("You selected Affogato.\n");
                        addOrder("Affogato", 266.00, quantity, sugarLevel, espressoShot);
                        addPoints(266.00 * quantity);
                        break;
                    default:
                        printf("Invalid selection. Please try again.\n");
                        break;
                }
                break;
            case 2:
                displayTeaMenu();
                printf("Please select an item by entering the corresponding number: ");
                while ((getchar()) != '\n');
                scanf("%d", &itemChoice);
                if (itemChoice == 9) break;
                switch (itemChoice) {
                    case 1:
                        printf("You selected English Breakfast Tea.\n");
                        addOrder("English Breakfast Tea", 112.00, 1, "None", 0);
                        addPoints(112.00);
                        break;
                    case 2:
                        printf("You selected Earl Grey.\n");
                        addOrder("Earl Grey", 140.00, 1, "None", 0);
                        addPoints(140.00);
                        break;
                    case 3:
                        printf("You selected Green Tea.\n");
                        addOrder("Green Tea", 154.00, 1, "None", 0);
                        addPoints(154.00);
                        break;
                    case 4:
                        printf("You selected Chai Latte.\n");
                        addOrder("Chai Latte", 196.00, 1, "None", 0);
                        addPoints(196.00);
                        break;
                    case 5:
                        printf("You selected Matcha Latte.\n");
                        addOrder("Matcha Latte", 224.00, 1, "None", 0);
                        addPoints(224.00);
                        break;
                    case 6:
                        printf("You selected Peppermint Tea.\n");
                        addOrder("Peppermint Tea", 126.00, 1, "None", 0);
                        addPoints(126.00);
                        break;
                    case 7:
                        printf("You selected Chamomile Tea.\n");
                        addOrder("Chamomile Tea", 126.00, 1, "None", 0);
                        addPoints(126.00);
                        break;
                    case 8:
                        printf("You selected Iced Tea.\n");
                        addOrder("Iced Tea", 140.00, 1, "None", 0);
                        addPoints(140.00);
                        break;
                    default:
                        printf("Invalid selection. Please try again.\n");
                        break;
                }
                break;
            case 3:
                displayBakeryMenu();
                printf("Please select an item by entering the corresponding number: ");
                while ((getchar()) != '\n');
                scanf("%d", &itemChoice);
                if (itemChoice == 6) break;
                if (itemChoice == 1) {
                    printf("Please select the type of Croissant:\n");
                    printf("1. Plain\n");
                    printf("2. Almond\n");
                    printf("3. Chocolate\n");
                    printf("Enter your choice: ");
                    while ((getchar()) != '\n');
                    scanf("%d", &subChoice);
                } else if (itemChoice == 2) {
                    printf("Please select the type of Muffin:\n");
                    printf("1. Blueberry\n");
                    printf("2. Banana Nut\n");
                    printf("3. Chocolate Chip\n");
                    printf("Enter your choice: ");
                    while ((getchar()) != '\n');
                    scanf("%d", &subChoice);
                } else if (itemChoice == 3) {
                    printf("Please select the type of Scone:\n");
                    printf("1. Raisin\n");
                    printf("2. Cranberry\n");
                    printf("Enter your choice: ");
                    while ((getchar()) != '\n');
                    scanf("%d", &subChoice);
                } else {
                    subChoice = 1;
                }
                printf("Enter quantity: ");
                while ((getchar()) != '\n');
                scanf("%d", &quantity);
                addBakeryOrder(itemChoice, subChoice, quantity);
                break;
            case 4:
                if (itemAdded) {
                    printReceipt();
                    orderCount = 0;
                    itemAdded = 0;
                } else {
                    printf("You must add at least one item before finalizing the order.\n");
                }
                break;
            case 5:
                if (accountCreated) {
                    viewPointsBalance();
                } else {
                    printf("Invalid selection. Please try again.\n");
                }
                break;
            case 6:
                printf("Logging out...\n");
                if (!login(username, &accountCreated)) {
                    return 0;
                }
                break;
            default:
                printf("Invalid selection. Please try again.\n");
                break;
        }
    }

    return 0;
}

