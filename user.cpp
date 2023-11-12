#include "user.h"
#include <iostream>
#include "sqlite3.h"

#include <sstream>
#include <stdexcept>

// Constructor
User::User(std::string name, int accountNum, double initialBalance) {
    accountHolderName = name;
    accountNumber = accountNum;
    balance = initialBalance;
    insertUserIntoDatabase(*this);
}

// Function to deposit money
void User::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        updateBalanceInDatabase(accountNumber, balance);
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
        updateBalanceInDatabase(accountNumber, balance);
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

const std::string& User::getAccountHolderName() const {
    return accountHolderName;
}

int User::getAccountNumber() const {
    return accountNumber;
}

double User::getBalance() const {
    return balance;
}

void User::insertUserIntoDatabase(const User& user) {
    sqlite3* db;
    int rc = sqlite3_open("bank.db", &db);

    if (rc == SQLITE_OK) {
        std::stringstream query;
        query << "INSERT INTO Users (Name, AccountNumber, Balance) VALUES (?, ?, ?);";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr);

        if (rc == SQLITE_OK) {
            // Bind parameters
            sqlite3_bind_text(stmt, 1, user.getAccountHolderName().c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, user.getAccountNumber());
            sqlite3_bind_double(stmt, 3, user.getBalance());

            // Execute the query
            rc = sqlite3_step(stmt);

            if (rc != SQLITE_DONE) {
                std::cerr << "Failed to insert user into the database: " << sqlite3_errmsg(db) << std::endl;
            }

            sqlite3_finalize(stmt);
        }
        else {
            std::cerr << "Failed to prepare the statement: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_close(db);
    }
    else {
        std::cerr << "Failed to open the database: " << sqlite3_errmsg(db) << std::endl;
    }
}

void User::updateBalanceInDatabase(int accountNum, double newBalance) {
    sqlite3* db;
    int rc = sqlite3_open("bank.db", &db);

    if (rc == 0) {
        std::string query = "UPDATE Users SET Balance = " + std::to_string(newBalance)
            + " WHERE AccountNumber = " + std::to_string(accountNum) + ";";

        rc = sqlite3_exec(db, query.c_str(), 0, 0, 0);

        if (rc != 0) {
            std::cerr << "Failed to update balance in the database: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_close(db);
    }
    else {
        std::cerr << "Failed to open the database: " << sqlite3_errmsg(db) << std::endl;
    }
}

