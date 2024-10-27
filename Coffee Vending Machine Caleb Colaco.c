#include <stdio.h>
#include <stdlib.h>

// Define coffee recipe constants
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define ESPRESSO_MILK 0

#define CAPPUCCINO_BEANS 8
#define CAPPUCCINO_WATER 30
#define CAPPUCCINO_MILK 70

#define MOCHA_BEANS 8
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_CHOCOLATE 30

// Define other constants
#define ADP 1984                        // Admin password
#define THRESHOLD_BEANS 10              // Ingredient threshold for alert
#define THRESHOLD_WATER 100
#define THRESHOLD_MILK 50
#define THRESHOLD_CHOCOLATE 20

// Declare global variables
float total_sales = 0.0;                // Total sales amount
int coffee_beans = 100;                 // Ingredient levels
int water = 200;
int milk = 300;
int chocolate = 100;

float espresso_price = 3.5;             // Coffee prices
float cappuccino_price = 4.5;
float mocha_price = 5.5;

// Function declarations
void order_coffee();
void admin_mode();
int check_ingredients(int type);
void handle_payment(float coffeeprice);
void update_ingredients(int type);
void replenish_ingredients();
void change_coffee_price();
void summary();

int main() {
    int choice;

    // Main menu loop
    while (1) {
        printf("Welcome to the Coffee Machine Menu:\n");
        printf("[1] Choose a specific coffee type\n");
        printf("[2] Access admin mode (only for operator)\n");
        printf("[3] Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        // Switch case to assign appropriate function
        switch (choice) {
            case 1:
                order_coffee();  // Call coffee ordering function
                break;

            case 2:
                admin_mode();    // Call admin mode
                break;

            case 3:
                printf("Thank you... Exiting\n");
                return 0;        // Exit the program

            default:
                printf("Invalid selection, please try again\n");
        }
    }
}

// Updated check_ingredients function that returns 0 if unavailable and 1 if available
int check_ingredients(int type) {
    if (type == 1) {  // Espresso
        if (coffee_beans < ESPRESSO_BEANS || water < ESPRESSO_WATER) {
            printf("Espresso Unavailable due to insufficient ingredients.\n");
            return 0;
        }
    } 
    else if (type == 2) {  // Cappuccino
        if (coffee_beans < CAPPUCCINO_BEANS || water < CAPPUCCINO_WATER || milk < CAPPUCCINO_MILK) {
            printf("Cappuccino Unavailable due to insufficient ingredients.\n");
            return 0;
        }
    } 
    else if (type == 3) {  // Mocha
        if (coffee_beans < MOCHA_BEANS || water < MOCHA_WATER || milk < MOCHA_MILK || chocolate < MOCHA_CHOCOLATE) {
            printf("Mocha Unavailable due to insufficient ingredients.\n");
            return 0;
        }
    }
    return 1;
}

void order_coffee() {
    int choice;
    float coffeeprice;
    char confirmation;

    // Coffee ordering loop
    while (1) {
        printf("\nAvailable Coffee Types:\n");
        if (check_ingredients(1)) {
            printf("1. Espresso - AED %.2f\n", espresso_price);
        } else {
            printf("1. Espresso - Unavailable\n");
        }
        
        if (check_ingredients(2)) {
            printf("2. Cappuccino - AED %.2f\n", cappuccino_price);
        } else {
            printf("2. Cappuccino - Unavailable\n");
        }
        
        if (check_ingredients(3)) {
            printf("3. Mocha - AED %.2f\n", mocha_price);
        } else {
            printf("3. Mocha - Unavailable\n");
        }
        
        printf("0. Exit\n");
        printf("Select a coffee type: ");
        scanf("%d", &choice);

        // Exit coffee ordering if user selects 0
        if (choice == 0) {
            return; 
        }

        // Check ingredient availability for the selected coffee
        if (choice == 1 && check_ingredients(1)) {
            coffeeprice = espresso_price;
        } 
        else if (choice == 2 && check_ingredients(2)) {
            coffeeprice = cappuccino_price;
        } 
        else if (choice == 3 && check_ingredients(3)) {
            coffeeprice = mocha_price;
        } 
        else {
            printf("Selected coffee type is unavailable. Please select another.\n");
            continue;
        }

        // Ask for confirmation before proceeding with the order
        printf("You selected: ");
        if (choice == 1) {
            printf("Espresso\n");
        } else if (choice == 2) {
            printf("Cappuccino\n");
        } else if (choice == 3) {
            printf("Mocha\n");
        }
        
        printf("Are you sure you want to proceed? (y/n): ");
        scanf(" %c", &confirmation); // Note the space before %c to ignore previous newline

        if (confirmation == 'y' || confirmation == 'Y') {
            handle_payment(coffeeprice);  // Handle the payment for the coffee
            update_ingredients(choice);   // Update the ingredient levels
            break;  // Exit after successful order
        } else {
            printf("Order canceled. Please select again.\n");
        }
    }
}

void handle_payment(float coffeeprice) {
    float payment;
    float totalpaid = 0.0;

    // Loop to handle coin input
    while (totalpaid < coffeeprice) {
        printf("Insert a 1 dirham or 0.5 dirham coin: ");
        scanf("%f", &payment);

        // Validate the coin and add it to the total
        if (payment == 1.0 || payment == 0.5) {
            totalpaid += payment;
        } 
        else {
            printf("Invalid coin, please try again.\n");
        }
    }

    printf("Payment successful, total payment is AED %.2f\n", totalpaid);

    // Calculate and return change if needed
    float change = totalpaid - coffeeprice;
    if (change > 0) {
        printf("Your change is AED %.2f\n", change);
    }

    total_sales += coffeeprice;  // Update total sales
}

void update_ingredients(int type) {
    if (type == 1) {  // Espresso
        coffee_beans -= ESPRESSO_BEANS;
        water -= ESPRESSO_WATER;
    } 
    else if (type == 2) {  // Cappuccino
        coffee_beans -= CAPPUCCINO_BEANS;
        water -= CAPPUCCINO_WATER;
        milk -= CAPPUCCINO_MILK;
    } 
    else if (type == 3) {  // Mocha
        coffee_beans -= MOCHA_BEANS;
        water -= MOCHA_WATER;
        milk -= MOCHA_MILK;
        chocolate -= MOCHA_CHOCOLATE;
    }

    // Alert if any ingredient is low
    if (coffee_beans <= THRESHOLD_BEANS) {
        printf("Alert: Low on Coffee Beans!\n");
    }
    if (water <= THRESHOLD_WATER) {
        printf("Alert: Low on Water!\n");
    }
    if (milk <= THRESHOLD_MILK) {
        printf("Alert: Low on Milk!\n");
    }
    if (chocolate <= THRESHOLD_CHOCOLATE) {
        printf("Alert: Low on Chocolate Syrup!\n");
    }
}

void replenish_ingredients() {
    // Replenish ingredients with random amounts between 600 and 1000 and chocolate between 400 and 700
    coffee_beans = rand() % 401 + 600;
    water = rand() % 401 + 600;
    milk = rand() % 401 + 600;  
    chocolate = rand() % 301 + 400;;
    printf("Ingredients replenished successfully\n");
}

void change_coffee_price() {
    int choice;
    float newprice;

    printf("\nChoose coffee type to change the price:\n");
    printf("1. Espresso\n");
    printf("2. Cappuccino\n");
    printf("3. Mocha\n");
    printf("0. Exit\n");
    printf("Select a coffee type: ");
    scanf("%d", &choice);

    // Get new price based on the coffee type
    switch (choice) {
        case 1:
            printf("Enter new price for Espresso: ");
            scanf("%f", &newprice);
            espresso_price = newprice;
            printf("Espresso price updated to AED %.2f\n", espresso_price);
            break;

        case 2:
            printf("Enter new price for Cappuccino: ");
            scanf("%f", &newprice);
            cappuccino_price = newprice;
            printf("Cappuccino price updated to AED %.2f\n", cappuccino_price);
            break;

        case 3:
            printf("Enter new price for Mocha: ");
            scanf("%f", &newprice);
            mocha_price = newprice;
            printf("Mocha price updated to AED %.2f\n", mocha_price);
            break;

        case 0:
            return;  // Exit price change menu

        default:
            printf("Invalid selection, please try again.\n");
    }
}

void summary() {
    char reset_choice;

    printf("\nTotal Ingredients:\n");
    printf("Coffee Beans: %d\n", coffee_beans);
    printf("Water: %d\n", water);
    printf("Milk: %d\n", milk);
    printf("Chocolate: %d\n", chocolate);
    printf("Total Sales: AED %.2f\n", total_sales);
    
    // Ask if the user wants to reset total sales
    printf("Would you like to reset total sales? ");
    scanf(" %c", &reset_choice);
    
    if (reset_choice == 'y' || reset_choice == 'Y') {
        total_sales = 0.0;  // Reset total sales
        printf("Total sales have been reset.\n");
    } else {
        printf("Total sales remain unchanged.\n");
    }
}

void admin_mode() {
    int password, choice;

    // Prompt for password to access admin mode
    printf("Enter admin password: ");
    scanf("%d", &password);

    if (password == ADP) {
        // Admin mode menu loop
        while (1) {
            printf("\nAdmin Mode Menu:\n");
            printf("[1] Replenish ingredients\n");
            printf("[2] Change coffee prices\n");
            printf("[3] Summary of total ingredients and sales\n");
            printf("[0] Exit admin mode\n");
            printf("Select an option: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    replenish_ingredients();  // Replenish ingredients
                    break;

                case 2:
                    change_coffee_price();    // Change coffee prices
                    break;

                case 3:
                    summary();                // Display summary
                    break;

                case 0:
                    printf("Exiting admin mode.\n");
                    return;

                default:
                    printf("Invalid selection, please try again.\n");
            }
        }
    } else {
        printf("Incorrect password. Access denied.\n");
    }
}
