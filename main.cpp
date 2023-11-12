#include <iostream>
#include "user.h"
using namespace std;
int main() {
    User user("John Doe", 12345, 1000.0);

    // Display initial account information
    user.displayAccountInfo();

    // Deposit money
    user.deposit(500.0);

    // Withdraw money
    user.withdraw(200.0);

    // Display updated account information
    user.displayAccountInfo();

    return 0;
}
