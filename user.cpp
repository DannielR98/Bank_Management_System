#include "user.h"
#include <iostream>

// Constructor
User::User(std::string name, int accountNum, double initialBalance) {
    accountHolderName = name;
    accountNumber = accountNum;
    balance = initialBalance;
}

// Function to deposit money
void User::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Deposit successful. Updated balance: " << balance << std::endl;
    }
    else {
        std::cout << "Invalid deposit amount." << std::endl;
    }
}

// Function to withdraw money
void User::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        std::cout << "Withdrawal successful. Updated balance: " << balance << std::endl;
    }
    else {
        std::cout << "Invalid withdrawal amount or insufficient funds." << std::endl;
    }
}

// Function to display account information
void User::displayAccountInfo() {
    std::cout << "Account Holder: " << accountHolderName << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Balance: " << balance << std::endl;
}
