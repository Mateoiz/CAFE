
struct Order {
    char itemName[50];
    float price;
    int quantity;
    char sugarLevel[20];
    int espressoShot;
};

struct Account {
    char username[50];
    float points;
    struct tm creationDate;
};

struct Order orders[MAX_ORDERS];
int orderCount = 0;
int itemAdded = 0;
struct Account account;
