#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string accountHolderName;
    int accountNumber;
    double balance;

public:
    // Constructor
    User(std::string name, int accountNum, double initialBalance);

    // Function to deposit money
    void deposit(double amount);

    // Function to withdraw money
    void withdraw(double amount);

    // Function to display account information
    void displayAccountInfo();
};

#endif // USER_H
