
# Smart Expense Tracker Using C++

## 1. Project Overview

Smart Expense Tracker is a console-based personal finance
management application developed using C++ and Object-Oriented
Programming (OOP).

It helps users record their income and expenses, categorize
transactions, calculate their available balance, and monitor
their spending budget.

## 2. Objectives

- To develop a personal finance management application.
- To record income and expenses.
- To calculate total income, expenses, and balance.
- To categorize and search transactions.
- To set a spending budget.
- To store records using file handling.
- To apply OOP concepts in a real-world application.

## 3. Features

- Add income transactions.
- Add expense transactions.
- View all transaction records.
- Calculate total income and expenses.
- Display the remaining balance.
- Search transactions by category.
- Set and monitor a spending budget.
- Save and load records using text files.
- Validate numeric input.

## 4. Technologies Used

- Programming Language: C++
- Compiler: GCC or Clang
- Code Editor: Visual Studio Code
- Concepts: OOP, vectors, strings, and file handling
- Standard: C++17

## 5. OOP Concepts Used

### Classes and Objects
The Transaction class represents a financial transaction.
The ExpenseTracker class manages the application's operations.

### Encapsulation
Transaction data members are private and accessed through
public member functions.

### Constructors
Constructors initialize transaction objects and the tracker.

### Vectors
A vector stores multiple transaction objects in memory.

### File Handling
The program uses transactions.txt to store transaction records
and budget.txt to save the spending budget.

### Exception Handling
The program handles invalid stored numeric records and
validates user-entered amounts.

## 6. Requirements

- A computer running macOS, Windows, or Linux.
- A C++ compiler supporting C++17.
- Visual Studio Code or another code editor.

## 7. How to Compile and Run

### macOS or Linux

Compile:

clang++ -std=c++17 main.cpp -o expense_tracker

Run:

./expense_tracker

### Windows with GCC

Compile:

g++ -std=c++17 main.cpp -o expense_tracker.exe

Run:

expense_tracker.exe

## 8. Data Storage

The application automatically creates these files when needed:

- transactions.txt: Stores income and expense records.
- budget.txt: Stores the spending budget.

Keep these generated data files in the same working directory
when you want to retain your records between sessions.

## 9. Limitations

- Console-based interface.
- Designed for a single user.
- No bank account integration.
- No automatic monthly reports.
- Category searches are case-sensitive.

## 10. Future Enhancements

- Monthly expense reports.
- Graphs and charts.
- Editing and deleting transactions.
- Savings goal tracking.
- Graphical user interface.
- Password protection.

## 11. Conclusion

The Smart Expense Tracker demonstrates how C++ and OOP can be
used to develop a practical personal finance management system.
It combines classes, objects, encapsulation, constructors,
vectors, and file handling to organize financial records and
calculate balances.

## 12. Author

OOP in C++ Mini Project
