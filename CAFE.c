#include <stdio.h>
#include <string.h>

#define MAX_ORDERS 100
#define ESPRESSO_SHOT_PRICE 28.0
#define POINTS_CONVERSION_RATE 0.5

typedef struct {
    char itemName[50];
    float price;
    int quantity;
    char sugarLevel[20];
    int espressoShot;
} Order;

typedef struct {
    char username[50];
    float points;
} Account;

Order orders[MAX_ORDERS];
int orderCount = 0;
int itemAdded = 0;
Account account;

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
    printf("1. Croissant (Plain, Almond, Chocolate) - 168.00 PHP\n");
    printf("2. Muffins (Blueberry, Banana Nut, Chocolate Chip) - 154.00 PHP\n");
    printf("3. Scones (Raisin, Cranberry) - 140.00 PHP\n");
    printf("4. Cinnamon Rolls - 182.00 PHP\n");
    printf("5. Danish Pastries - 196.00 PHP\n");
    printf("6. Back to Main Menu\n");
    printf("==============================\n");
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
        char usePoints;
        printf("You have %.2f points. Would you like to use them to get a discount? (y/n): ", account.points);
        fflush(stdin);
        scanf(" %c", &usePoints);
        if (usePoints == 'y' || usePoints == 'Y') {
            float discount = account.points / POINTS_CONVERSION_RATE;
            if (discount > total) {
                discount = total;
            }
            total -= discount;
            account.points -= discount * POINTS_CONVERSION_RATE;
            printf("Discount applied: %.2f PHP\n", discount);
            printf("New Total: %.2f PHP\n", total);
        }
    }
    printf("==============================\n");
}

void addPoints(float amount) {
    account.points += amount * POINTS_CONVERSION_RATE;
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
    printf("\n==============================\n");
    printf("     Create an Account\n");
    printf("==============================\n");
    printf("Enter username: ");
    fflush(stdin);
    scanf("%s", username);
    printf("Enter password: ");
    fflush(stdin);
    scanf("%s", password);
    strcpy(account.username, username);
    account.points = 0.0;
    printf("Account created successfully!\n");
    printf("==============================\n");
}

int login(char *username, int *accountCreated) {
    int choice;
    printf("\n==============================\n");
    printf("           Login\n");
    printf("==============================\n");
    printf("1. Create an Account\n");
    printf("2. Continue as Guest\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    fflush(stdin);
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
        fflush(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCoffeeMenu();
                printf("Please select an item by entering the corresponding number: ");
                fflush(stdin);
                scanf("%d", &itemChoice);
                if (itemChoice == 10) break;
                printf("Enter quantity: ");
                fflush(stdin);
                scanf("%d", &quantity);
                printf("Enter sugar level (None, Low, Medium, High): ");
                fflush(stdin);
                scanf("%s", sugarLevel);
                printf("Add an espresso shot? (1 for Yes, 0 for No): ");
                fflush(stdin);
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
                fflush(stdin);
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
                fflush(stdin);
                scanf("%d", &itemChoice);
                if (itemChoice == 6) break;
                switch (itemChoice) {
                    case 1:
                        printf("You selected Croissant (Plain, Almond, Chocolate).\n");
                        addOrder("Croissant (Plain, Almond, Chocolate)", 168.00, 1, "None", 0);
                        addPoints(168.00);
                        break;
                    case 2:
                        printf("You selected Muffins (Blueberry, Banana Nut, Chocolate Chip).\n");
                        addOrder("Muffins (Blueberry, Banana Nut, Chocolate Chip)", 154.00, 1, "None", 0);
                        addPoints(154.00);
                        break;
                    case 3:
                        printf("You selected Scones (Raisin, Cranberry).\n");
                        addOrder("Scones (Raisin, Cranberry)", 140.00, 1, "None", 0);
                        addPoints(140.00);
                        break;
                    case 4:
                        printf("You selected Cinnamon Rolls.\n");
                        addOrder("Cinnamon Rolls", 182.00, 1, "None", 0);
                        addPoints(182.00);
                        break;
                    case 5:
                        printf("You selected Danish Pastries.\n");
                        addOrder("Danish Pastries", 196.00, 1, "None", 0);
                        addPoints(196.00);
                        break;
                    default:
                        printf("Invalid selection. Please try again.\n");
                        break;
                }
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
