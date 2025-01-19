# Bank-Management-System
Bank Management System for Tsinghua university C++ Class.

Personal Bank Account Management System
Rixin Academy Cai Xinqi 2020012756

I. Topic Selection and Demand Analysis Report
1. Research and Analysis of Similar Software: Online Banking - Taking Bank of China as an Example
Currently, all major banks on the market have personal bank account management systems in their online banking. Here, I have researched the functions of Bank of China's online banking, and I will introduce some specific functions of this software below. These functions are also simply implemented in the program I developed subsequently.
Function 1: Registration, Login, and Password Modification

This function is mainly to protect users' privacy. To modify the password, a verification code sent to the verified mobile phone number is required.
Function 2: Credit Account


This is the credit card opening function of Bank of China's online banking, which can open credit accounts, make repayments, transfer out funds, and manage credit limits.
Function 3: Investment and Financial Management Functions

This is the investment and financial management function of Bank of China. In addition to buying and selling financial products, it also has functions such as real-time foreign exchange conversion.
Function 4: Transfer, Savings, and Other Functions

The code I designed implements some of the above basic functions, but there are still the following improvement directions: First, the user interface is not user-friendly enough. The current system is based on the command-line interface. Although basic functions are implemented, the user experience is poor. In the future, a graphical user interface (GUI) can be considered for development to make the system more intuitive and easy to use. Second, data storage and persistence: Currently, the data in the system is stored in memory, and the data will be lost after the system is closed. A database system, such as SQLite or MySQL, can be introduced to persistently store user information and account data to ensure data security and persistence. Third, concurrency and multi-user support: The current system is in single-user mode and cannot handle operations of multiple users simultaneously. A multi-threading or concurrency processing mechanism can be introduced to support concurrent operations of multiple users, thereby improving the system's response speed and processing capability.
2. Detailed Functional Design
2.1 User Management
(1) Function Description:
This module is responsible for user registration, login, and user information management.
(2) Specific Functions:
① User Registration: Allows new users to register. The system will check whether the username already exists. If it does not exist, a new user will be added.
Method: Bank::registerUser(const std::string& name, const std::string& password)
② User Login: Allows registered users to log in. The system will verify whether the username and password match.
Method: Bank::loginUser(const std::string& name, const std::string& password)
③ Display User Information: Displays basic information of all registered users in the system.
Method: Bank::showUsers() const
2.2 Account Management
(1) Function Description:
This module is responsible for managing various types of bank accounts, including checking accounts, credit accounts, and savings accounts.
(2) Specific Functions:
① Account Creation: Creates different types of accounts, such as checking accounts, credit accounts, and savings accounts.
Classes: CheckingAccount, CreditAccount, SavingsAccount
② Account Deposit: Allows users to deposit funds into accounts and calculate interest during the deposit period.
Method: Account::deposit(double amount, const Date& date)
③ Account Withdrawal: Allows users to withdraw funds from accounts and calculate interest during the withdrawal period.
Method: Account::withdraw(double amount, const Date& date)
④ Account Transfer: Allows users to transfer funds between different accounts and calculate interest during the transfer.
Method: Account::transfer(Account& to, double amount, const Date& date)
④ Account Settlement: Settles accounts, calculates, and updates the accumulated interest of accounts.
Method: Account::settle(const Date& date)
⑤ Display Account Information: Displays detailed information of accounts, including account ID, account name, balance, etc.
Method: Account::show() const
2.3 Date Management
(1) Function Description:
This module is responsible for handling date-related operations, such as date calculation and date formatting.
(2) Specific Functions:
① Date Initialization: Initializes the date object and sets the specific year, month, and day.
Method: Date::Date(int year, int month, int day)
② Obtain Date Information: Obtains the specific year, month, and day of the date.
Method: Date::getYear() const, Date::getMonth() const, Date::getDay() const
③ Date Calculation: Calculates the difference in days between two dates and supports date addition and subtraction operations.
Method: Date::operator-(const Date& other) const, Date::operator++(), Date::operator++(int)
2.4 Interest Calculation
(1) Function Description:
This module is responsible for calculating the daily interest and accumulated interest of accounts.
(2) Specific Functions:
① Daily Interest Calculation: Calculates the daily interest based on the last operation date of the account and the current date, and updates the account balance.
Method: Account::calculateDailyInterest(const Date& date)
② Accumulated Interest Calculation: Calculates the accumulated interest based on fund changes and interest rates and updates the total amount.
Class: Accumulator
Method: Accumulator::change(double value, const Date& date), Accumulator::accumulate(const Date& date) const
2.5 Financial Product Management
(1) Function Description:
This module is used to manage and display information of financial products.
(2) Specific Functions:
① Display Detailed Information of Financial Products.
Method: FinancialProduct::showDetails() const
② Calculate the Profit of Financial Products.
Method: FinancialProduct::calculateProfit() const


II. Design Specification
1. Class Diagram

2. Detailed Description of Classes
(1) Account Class
Function: The Account class is the base class for all account types and defines the basic attributes and operations of accounts. It contains general account information and behaviors, such as deposit, withdrawal, and settlement functions.
Data Members:
id: Stores the unique identifier of the account.
name: Stores the name of the account holder.
lastDate: Stores the date of the last account operation.
balance: Stores the account balance.
accumulation: Stores the accumulated amount of the account.
nextAccountID: A static integer variable that stores the ID number of the next account.
Function Members:
Account(const std::string& name, const Date& date): Constructor, used to initialize the account, set the account name and initial date, and generate a unique account ID.
deposit(double amount, const Date& date): Deposit function, which increases the account balance according to the specified date and calculates the interest during the deposit period.
withdraw(double amount, const Date& date): Withdrawal function, which reduces the account balance according to the specified date and calculates the interest during the withdrawal period.
settle(const Date& date): Settlement function, which settles the account according to the specified date, mainly used for year-end interest settlement.
show() const: A pure virtual function, used to display account information, and the specific implementation is completed by derived classes.
getAccountID() const: Returns the account ID to identify the account.
getBalance() const: Returns the account balance to query the current fund status of the account.
calculateDailyInterest(const Date& date): Calculates the daily interest of the account according to the specified date and updates the account balance.
transfer(Account& to, double amount, const Date& date) = 0: A pure virtual function, used for account transfer, and the specific implementation is completed by derived classes.
(2) CheckingAccount Class (Inherited from Account)
Function: The CheckingAccount class is a derived class of the Account class, representing a checking account, and provides basic deposit, withdrawal, and transfer functions.
Data Members: Inherited from the `Account` class.
Function Members:
CheckingAccount(const std::string& name, const Date& date): Constructor, used to initialize the checking account, set the account name and initial date.
deposit(double amount, const Date& date): Deposit function, which increases the balance of the checking account and calculates the interest during the deposit period.
withdraw(double amount, const Date& date): Withdrawal function, which reduces the balance of the checking account and calculates the interest during the withdrawal period.
settle(const Date& date): Settlement function, and there is no specific settlement content for the checking account.
show() const: Displays information of the checking account, including account ID, account name, and balance.
transfer(Account& to, double amount, const Date& date): Checking account transfer function, which transfers a specified amount from the current account to the target account and calculates the interest during the transfer.

(3) CreditAccount Class (Inherited from Account)
Function: The CreditAccount class is a derived class of the Account class, representing a credit account. In addition to basic deposit and withdrawal functions, it also adds credit limit management.
Data Members:
creditLimit: Stores the credit limit of the credit account.
Function Members:
CreditAccount(const std::string& name, const Date& date, double creditLimit): Constructor, used to initialize the credit account, set the account name, initial date, and credit limit.
deposit(double amount, const Date& date): Deposit function, which increases the balance of the credit account and calculates the interest during the deposit period.
withdraw(double amount, const Date& date): Withdrawal function, which reduces the balance of the credit account and calculates the interest during the withdrawal period.
settle(const Date& date): Settlement function, and the settlement of the credit account mainly involves interest calculation.
show() const: Displays information of the credit account, including account ID, account name, balance, and credit limit.
transfer(Account& to, double amount, const Date& date): Credit account transfer function, which transfers a specified amount from the current account to the target account and calculates the interest during the transfer.

(4) SavingsAccount Class (Inherited from Account)

Function: The SavingsAccount class is a derived class of the Account class, representing a savings account, providing basic deposit and withdrawal functions, and having interest rate management functions.
Data Members:
interestRate: Stores the interest rate of the savings account.
Function Members:
SavingsAccount(const std::string& name, const Date& date, double interestRate): Constructor, used to initialize the savings account, set the account name, initial date, and interest rate.
deposit(double amount, const Date& date): Deposit function, which increases the balance of the savings account and calculates the interest during the deposit period.
withdraw(double amount, const Date& date): Withdrawal function, which reduces the balance of the savings account and calculates the interest during the withdrawal period.
settle(const Date& date): Settlement function, and the settlement of the savings account mainly involves interest calculation.
show() const: Displays information of the savings account, including account ID, account name, balance, and interest rate.
transfer(Account& to, double amount, const Date& date): Savings account transfer function, which transfers a specified amount from the current account to the target account and calculates the interest during the transfer.

(5) User Class
Function: The User class is used to represent bank users and contains basic user information, such as username and password.
Data Members:
name: Stores the username.
password: Stores the user password.
Function Members:
User(const std::string& name, const std::string& password): Constructor, used to initialize the user, set the username and password.
getName() const: Obtains the username for display and verification of user information.
verifyPassword(const std::string& password) const: Verifies whether the user-entered password is correct, used for user login verification.

(6) Bank Class
Function: The Bank class is used to manage the banking system and handle operations such as user registration, login, and display of user information.
Data Members:
users: A vector type that stores a list of all users.
Function Members:
Bank(): Constructor, used to initialize the banking system.
registerUser(const std::string& name, const std::string& password): Registers a new user, checks whether the username already exists, and adds a new user if it does not exist.
loginUser(const std::string& name, const std::string& password): User login, verifies whether the username and password match.
showUsers() const: Displays information of all registered users.

(7) Date Class
Function: The Date class is used to represent and handle dates, including basic date operations and calculations between dates.
Data Members:
year: Stores the year.
month: Stores the month.
day: Stores the date.
Function Members:
Date(int year, int month, int day): Constructor, used to initialize the date, set the year, month, and day.
getYear() const: Obtains the year.
getMonth() const: Obtains the month.
getDay() const: Obtains the date.
operator-(const Date& other) const: Overloads the subtraction operator to calculate the difference in days between two dates.
operator++(): Overloads the pre-increment operator to increase by one day.
operator++(int): Overloads the post-increment operator to increase by one day.

(8) Accumulator Class
Function: The Accumulator class is used to calculate and accumulate interest and handle changes in funds and accumulated interest.
Data Members:
total: Stores the total amount.
rate: Stores the interest rate.
lastDate: Stores the date of the last operation.
Function Members:
Accumulator(double rate): Constructor, used to initialize the accumulator and set the interest rate.
change(double value, const Date& date): Changes the amount, calculates interest based on the date, and updates the total amount.
accumulate(const Date& date) const: Accumulates the amount, calculates and returns the accumulated interest based on the date.

(9) FinancialProduct Class
Function: The FinancialProduct class is used to represent financial products and provides functions for displaying detailed information and calculating profits.
Function Members:
showDetails() const: Displays detailed information of financial products.
calculateProfit() const: Calculates the profit of financial products.

3. Main Technical Difficulties
(1) Polymorphic Design of Account Types:
Design an abstract base class Account and implement different types of accounts, such as CheckingAccount, CreditAccount, and SavingsAccount, by inheriting this base class. Each account type has its specific behaviors and attributes, and these behaviors and attributes need to be defined in the base class and specifically implemented in derived classes.
This program defines the Account class as an abstract base class, which contains some general account attributes (such as id, name, balance, etc.) and pure virtual functions (such as show() and transfer()).
In derived classes (such as CheckingAccount, CreditAccount, and SavingsAccount), these pure virtual functions are specifically implemented to make each account type exhibit its unique behavior. In this way, using the polymorphism of C++, new account types can be expanded without modifying the base class, thereby enhancing the scalability of the system.
(2) Date Calculation:
Implement a Date class to handle various date operations, including date addition and subtraction operations. This is very important for interest calculation and settlement dates.
The Date class needs to provide basic date operations, such as methods for obtaining the year, month, and day. At the same time, the subtraction operator operator-(const Date& other) const is implemented to calculate the difference in days between two dates. This is crucial for calculating daily interest. Finally, implement the increment operator operator++() and operator++(int) to support date increment operations. Through these operators, date looping processing, such as calculating interest by day, can be easily performed.
(3) User Management and Authentication:
Design a Bank class to manage user registration and login. The secure storage and verification of user passwords is a technical difficulty, and it is necessary to ensure the security of user information and the ease of use of the system.
This program designs the Bank class to include a users vector for storing all users. Through the vector, multiple users can be managed conveniently, and quick search and operations can be performed. At the same time, the registerUser(const std::string& name, const std::string& password) method is used to register new users. When registering, it is necessary to check whether the username already exists to prevent duplicate registration, and the loginUser(const std::string& name, const std::string& password) method is used for user login. When logging in, the user's identity is verified by comparing the entered password with the stored password. Finally, the user password can be encrypted and stored using a simple hashing algorithm to enhance system security. In this way, even if the database is leaked, attackers cannot easily obtain the plaintext password.
(4) Daily Interest Calculation:
Implement the daily interest calculation function in the Account class. It is necessary to calculate interest based on the last operation date of the account and the current date and update the account balance in real time. This program defines the calculateDailyInterest(const Date& date) method in the Account class. This method first calculates the difference in days from lastDate to date, and then uses a predefined daily interest rate (for example, 0.0001, representing 0.01%) to calculate the interest during this period. The interest calculation formula is: Interest = Balance * Daily Interest Rate * Days. Then, the calculated interest is added to the account balance, and lastDate is updated to the current date. In this way, the interest of the account can be accurately calculated and updated whenever an account operation (such as deposit, withdrawal, settlement) occurs, thereby maintaining the accuracy of the account balance.
4. Implementation Solutions and Algorithm Designs for Technical Difficulties
(1) Polymorphic Design of Account Types:
① In the Account class, define the following pure virtual functions

② Specifically implement these functions in the CreditAccount class and SavingsAccount class
(2) Date Calculation
In the Date class, define subtraction operators and increment operators

(2) Daily Interest Calculation
① In the Account class, define calculateDailyInterest

② Call the calculateDailyInterest method to update interest during each account operation


III. User Manual
1. Introduction
Welcome to the bank management system. This system aims to provide users with convenient and fast bank account management functions, including user registration, login, account creation, deposit and withdrawal, transfer, and account information viewing. This manual will explain in detail how to use various functions of the system to ensure that users can operate smoothly.
2. System Requirements
Operating System: Windows, macOS, or Linux
Compiler: A compiler that supports C++ (such as g++, clang)
The compilation and running environment is configured correctly
3. Installation and Running
Download all source code files of the system and save them in the same directory.
Use IDEs such as CLion and VS to run the code.
4. Functional Usage Instructions
4.1 User Registration
(1) Operation Steps:
① After starting the program, select the "User Registration" option.
② Enter the username and password.
③ The system will check whether the username already exists. If it does not exist, the registration will be completed, and a registration success message will be displayed.
(2) Input Requirements:
· Username: Must be a unique string and cannot be repeated with registered usernames.
· Password: Any string, and it is recommended to include letters and numbers to enhance security.
4.2 User Login
(1) Operation Steps:
① After starting the program, select the "User Login" option.
② Enter the registered username and password.
③ The system will verify the username and password. If they match, the login will be successful, and a welcome message will be displayed.
(2) Input Requirements:
The username and password must be the same as those entered during registration.
4.3 Account Creation (Account Opening)
(1) Operation Steps:
① After successful login, enter [p] to select the "Create Account" option for account opening.
② Select the account type: Enter [ca] for a credit account or [sa] for a savings account. If a savings account is selected, you need to choose current or time deposit again.
③ The system will create the corresponding account and display a creation success message.
(2) Input Requirements:
Please do not enter other letters unrelated to the above letters.
4.4 Deposit
(1) Operation Steps:
① Enter [d] to select the "Deposit" option.
② Enter the account ID and deposit amount.
③ The system will update the account balance and display a deposit success message.
(2) Input Requirements:
· Account ID: A unique identifier automatically generated by the system, used to identify a specific account.
· Deposit Amount: A double-precision floating-point number, which must be positive.
4.5 Withdrawal
(1) Operation Steps:
① After successful login, enter [w] to select the "Withdrawal" option.
② Enter the account ID and withdrawal amount.
③ The system will update the account balance and display a withdrawal success message.
(2) Input Requirements:
· Account ID: A unique identifier automatically generated by the system, used to identify a specific account.
· Withdrawal Amount: A double-precision floating-point number, which must be positive and not exceed the account balance.
4.6 Transfer
(1) Operation Steps:
① After successful login, enter [t] to select the "Transfer" option.
② Enter the transfer-out account ID, transfer-in account ID, and transfer amount.
③ The system will update the account balance and display a transfer success message.
(2) Input Requirements:
· Transfer-out Account ID and Transfer-in Account ID: Unique identifiers automatically generated by the system, used to identify specific accounts.
· Transfer Amount: A double-precision floating-point number, which must be positive and not exceed the transfer-out account balance.
4.7 Account Settlement Date Jump
(1) Operation Steps:
① After successful login, enter [c] to select the "Account Settlement" option.
② Enter a number.
③ The system will jump to the corresponding date and update the balance.
(2) Input Requirements:
· The entered number < 30.
4.8 Display Account Information
(1) Operation Steps:
① After successful login, select the [p] "Display Account Information" option.
② The system will display detailed information of all accounts, including account ID, balance, etc.
(2) Input Requirements:
· Account ID: A unique identifier automatically generated by the system, used to identify a specific account.
4.9 Buying and Selling Financial Products
(1) Operation Steps:
① After successful login, enter [f] to select the "Buying and Selling Financial Products" option.
② Enter [buy] or [sell] to choose to buy or sell.
③ Enter the account ID.
④ Enter the transaction amount.
⑤ If you choose buy, enter the number of months, and the system will automatically generate an investment and financial management account.
(2) Input Requirements
· Do not enter irrelevant characters.
· The number of months must be < 24 and > 0.
5. Precautions
· The input data must meet the format requirements.
· Ensure the uniqueness of account IDs and usernames to avoid duplication.
· Ensure sufficient account balance during withdrawal and transfer operations.
· Follow the above operation and input steps of the system to ensure correct use.
·
