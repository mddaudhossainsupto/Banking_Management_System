#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

// Enum representing bill types
enum class BillType {
    ELECTRICITY,
    GAS,
    WATER,
    INTERNET,
    TELEPHONE,
    TV,
    CREDIT_CARD,
    GOVERNMENT_FEE,
    INSURANCE
};

// Base class representing a bill
class Bill {
protected:
    double amount;

public:
    Bill(double amt) : amount(amt) {}
    virtual ~Bill() {}
    double getAmount() const { return amount; }
    virtual void pay() = 0;
};

// Derived classes representing different types of bills
class ElectricityBill : public Bill {
public:
    ElectricityBill(double amt) : Bill(amt) {}
    void pay() override {
        cout << "Paid $" << amount << " for Electricity bill." << endl;
    }
};

class GasBill : public Bill {
public:
    GasBill(double amt) : Bill(amt) {}
    void pay() override {
        cout << "Paid $" << amount << " for Gas bill." << endl;
    }
};

// Class representing a customer's profile
class CustomerProfile {
private:
    string username;
    string password;
    double balance;
    string phoneNumber;

public:
    CustomerProfile(string uname, string pwd, string phone) : username(uname), password(pwd), balance(0), phoneNumber(phone) {}

    string getUsername() const { return username; }
    double getBalance() const { return balance; }
    string getPhoneNumber() const { return phoneNumber; }
    string getPassword() const { return password; }

    void addMoney(double amount) {
        balance += amount;
        cout << "Added $" << amount << " to your account. Current balance: $" << fixed << setprecision(2) << balance << endl;
    }

    bool subtractMoney(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Subtracted $" << amount << " from your account. Current balance: $" << fixed << setprecision(2) << balance << endl;
            return true;
        } else {
            cout << "Insufficient funds." << endl;
            return false;
        }
    }

    void rechargeMobile(double amount) {
        cout << "Recharged $" << amount << " to mobile number " << phoneNumber << "." << endl;
    }

    void payBill(Bill* bill) {
        if (bill->getAmount() >= 0) {
            cout << "Bill Amount: $" << fixed << setprecision(2) << bill->getAmount() << endl;
            cout << "Please confirm the payment (y/n): ";
            char choice;
            cin >> choice;
            if (tolower(choice) == 'y') {
                bill->pay();
            } else {
                cout << "Payment canceled." << endl;
            }
        } else {
            cout << "Invalid bill amount." << endl;
        }
        delete bill;
    }
};

// Class representing the online banking system
class OnlineBankingSystem {
private:
    map<string, CustomerProfile> customerDatabase;

public:
    void createAccount(string username, string password, string phone) {
        customerDatabase.insert({username, CustomerProfile(username, password, phone)});
        cout << "Account created successfully." << endl;
    }

    CustomerProfile* login(string username, string password) {
        auto it = customerDatabase.find(username);
        if (it != customerDatabase.end() && it->second.getPassword() == password) {
            cout << "Login successful. Welcome, " << username << "!" << endl;
            return &(it->second);
        } else {
            cout << "Login failed. Invalid username or password." << endl;
            return nullptr;
        }
    }

    void addMoney(CustomerProfile& customer, double amount) {
        customer.addMoney(amount);
    }

    void sendMoney(CustomerProfile& sender, CustomerProfile& recipient, double amount) {
        if (sender.subtractMoney(amount)) {
            recipient.addMoney(amount);
            cout << "Money sent successfully." << endl;
        } else {
            cout << "Unable to send money. Insufficient funds." << endl;
        }
    }

    void rechargeMobile(CustomerProfile& customer, double amount) {
        customer.rechargeMobile(amount);
    }

    void payBill(CustomerProfile& customer, Bill* bill) {
        customer.payBill(bill);
    }
    void withdrawMoney(CustomerProfile& customer, double amount) {
    if (customer.subtractMoney(amount)) {
        cout << "Withdrawn $" << amount << " from your account." << endl;
    } else {
        cout << "Unable to withdraw money. Insufficient funds." << endl;
    }
}
};

// Class representing bank accounts
class Account {
private:
    int accNo;
    string name;
    int deposit;
    char type;

public:
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

void Account::create_account() {
    cout << "\n\t\t\tEnter the Account No. : ";
    cin >> accNo;
    cin.ignore(); // Clear the input buffer
    cout << "\n\n\t\t\tPlease Enter the Name of the Account holder Here : ";
    getline(cin, name);
    cout << "\n\t\t\tEnter Type of the Account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\t\t\tEnter The Initial amount : ";
    cin >> deposit;

    ofstream outFile("account.txt", ios::app); // Open the file in append mode
    if (!outFile) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    // Write account details to the file
    outFile << accNo << '\t' << name << '\t' << type << '\t' << deposit << endl;

    outFile.close();
    cout << "\n\n\t\t\tAccount Created.." << endl;
}

void Account::show_account() const {
    cout << "\n\t\t\tAccount No. : " << accNo;
    cout << "\n\t\t\tAccount Holder Name : " << name;
    cout << "\n\t\t\tType of Account : " << type;
    cout << "\n\t\t\tBalance amount : " << deposit << endl;
}

void Account::modify() {
    cout << "\n\t\t\tAccount No. : " << accNo;
    cout << "\n\t\t\tModify Account Holder Name : ";
    cin.ignore();
    getline(cin, name);
    cout << "\n\t\t\tModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\t\t\tModify Balance amount : ";
    cin >> deposit;

    fstream File("account.txt", ios::in | ios::out);
    if (!File) {
        cout << "Error: Unable to open file for modification." << endl;
        return;
    }

    int fileAccNo;
    string line;
    while (getline(File, line)) {
        stringstream ss(line);
        ss >> fileAccNo;
        if (fileAccNo == accNo) {
            // Found the account, update the record
            File.seekp(0, ios::cur); // Move put pointer to the correct position
            File << accNo << '\t' << name << '\t' << type << '\t' << deposit << endl;
            cout << "\n\n\t\t\tRecord Updated" << endl;
            File.close();
            return;
        }
    }

    // If the loop ends without finding the account, it doesn't exist
    cout << "\n\n\t\t\tRecord Not Found" << endl;
    File.close();
}

void Account::dep(int x) {
    deposit += x;

    // Update the deposit amount in the file
    fstream File("account.txt", ios::in | ios::out);
    if (!File) {
        cout << "Error: Unable to open file for deposit." << endl;
        return;
    }

    int fileAccNo;
    string line;
    while (getline(File, line)) {
        stringstream ss(line);
        ss >> fileAccNo;
        if (fileAccNo == accNo) {
            // Found the account, update the record
            File.seekp(0, ios::cur); // Move put pointer to the correct position
            File << accNo << '\t' << name << '\t' << type << '\t' << deposit << endl;
            File.close();
            return;
        }
    }

    // If the loop ends without finding the account, it doesn't exist
    cout << "\n\n\t\t\tRecord Not Found" << endl;
    File.close();
}

void Account::draw(int x) {
    deposit -= x;

    // Update the deposit amount in the file
    fstream File("account.txt", ios::in | ios::out);
    if (!File) {
        cout << "Error: Unable to open file for withdrawal." << endl;
        return;
    }

    int fileAccNo;
    string line;
    while (getline(File, line)) {
        stringstream ss(line);
        ss >> fileAccNo;
        if (fileAccNo == accNo) {
            // Found the account, update the record
            File.seekp(0, ios::cur); // Move put pointer to the correct position
            File << accNo << '\t' << name << '\t' << type << '\t' << deposit << endl;
            File.close();
            return;
        }
    }

    // If the loop ends without finding the account, it doesn't exist
    cout << "\n\n\t\t\tRecord Not Found" << endl;
    File.close();
}

void Account::report() const {
    cout << accNo << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int Account::retacno() const {
    return accNo;
}

int Account::retdeposit() const {
    return deposit;
}

char Account::rettype() const {
    return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main() {
    OnlineBankingSystem bankingSystem;

    char ch;
    int num;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "\n\n\t\t\t\t======================\n";
        cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
        cout << "\n\t\t\t\t======================\n";

        cout << "\t\t\t\t    ::MAIN MENU::\n";
        cout << "\n\t\t\t\t1. NEW ACCOUNT";
        cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
        cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
        cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
        cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
        cout << "\n\t\t\t\t7. MODIFY AN ACCOUNT";
        cout << "\n\t\t\t\t8. ONLINE BANKING SYSTEM";
        cout << "\n\t\t\t\t9. EXIT";
        cout << "\n\n\t\t\t\tSelect Your Option (1-9): ";
        cin >> ch;

        switch (ch) {
            case '1':
                write_account();
                break;
            case '2':
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                deposit_withdraw(num, 1);
                break;
            case '3':
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                deposit_withdraw(num, 2);
                break;
            case '4':
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                delete_account(num);
                break;
            case '7':
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                modify_account(num);
                break;
            case '8': {
                cout << "Online Banking System" << endl;
                string username, password;
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;

                // Attempt to log in
                CustomerProfile* loggedInCustomer = bankingSystem.login(username, password);
                if (loggedInCustomer != nullptr) {
                    // Successfully logged in
                    char option;
                    do {
                        cout << "\n\n\t\t\t==============================\n";
                        cout << "\t\t\t\tONLINE BANKING MENU";
                        cout << "\n\t\t\t==============================\n";
                        cout << "\t\t\t1. Deposit Money\n";
                        cout << "\t\t\t2. Withdraw Money\n";
                        cout << "\t\t\t3. Transfer Money\n";
                        cout << "\t\t\t4. Recharge Mobile\n";
                        cout << "\t\t\t5. Pay Bill\n";
                        cout << "\t\t\t6. Logout\n";
                        cout << "\n\t\t\tSelect Your Option (1-6): ";
                        cin >> option;

                        switch (option) {
                            case '1': {
                                double amount;
                                cout << "Enter the amount to deposit: ";
                                cin >> amount;
                                bankingSystem.addMoney(*loggedInCustomer, amount);
                                break;
                            }
                            case '2': {
                                double amount;
                                cout << "Enter the amount to withdraw: ";
                                cin >> amount;
                                bankingSystem.withdrawMoney(*loggedInCustomer, amount);
                                break;
                            }
                            case '3': {
                                // Implement money transfer functionality
                                int recipientAccountNo;
                                double amount;
                                cout << "Enter the recipient's account number: ";
                                cin >> recipientAccountNo;
                                cout << "Enter the amount to transfer: ";
                                cin >> amount;
                                // Check if the recipient account exists (you may need a function for this)
                                // If the account exists, perform the money transfer
                                // bankingSystem.sendMoney(*loggedInCustomer, recipientAccountNo, amount);
                                break;
                            }
                            case '4': {
                                double amount;
                                cout << "Enter the amount to recharge: ";
                                cin >> amount;
                                bankingSystem.rechargeMobile(*loggedInCustomer, amount);
                                break;
                            }
                            case '5': {
                                int billTypeInt;
                                double billAmount;
                                cout << "Select Bill Type:" << endl;
                                cout << "1. Electricity\n2. Gas\n3. Water\n4. Internet\n5. Telephone\n6. TV\n7. Credit Card\n8. Government Fee\n9. Insurance\n";
                                cin >> billTypeInt;
                                cout << "Enter Bill Amount: $";
                                cin >> billAmount;
                                BillType billType;
                                switch (billTypeInt) {
                                    case 1: billType = BillType::ELECTRICITY; break;
                                    case 2: billType = BillType::GAS; break;
                                    case 3: billType = BillType::WATER; break;
                                    case 4: billType = BillType::INTERNET; break;
                                    case 5: billType = BillType::TELEPHONE; break;
                                    case 6: billType = BillType::TV; break;
                                    case 7: billType = BillType::CREDIT_CARD; break;
                                    case 8: billType = BillType::GOVERNMENT_FEE; break;
                                    case 9: billType = BillType::INSURANCE; break;
                                    default: cout << "Invalid bill type." << endl; return 0;
                                }
                                // Create bill object based on the selected bill type and amount
                                Bill* bill = nullptr;
                                switch (billType) {
                                    case BillType::ELECTRICITY: bill = new ElectricityBill(billAmount); break;
                                    case BillType::GAS: bill = new GasBill(billAmount); break;
                                    // Add cases for other bill types as needed
                                }
                                if (bill != nullptr) {
                                    bankingSystem.payBill(*loggedInCustomer, bill);
                                }
                                break;
                            }
                            case '6': {
                                cout << "Logging out..." << endl;
                                break;
                            }
                            default: {
                                cout << "Invalid option. Please try again." << endl;
                            }
                        }
                    } while (option != '6');
                }
                break;
            }
            case '9':
                cout << "\n\n\t\t\tBrought To You By M" << endl;
                // Exit the loop and end the program
                break;
            default:
                cout << "\a";
        }
        // Clear input buffer
       cout << "Press 'E' to exit or any other key to return to the main menu: ";
        char exitChoice;
        cin >> exitChoice;
        if (tolower(exitChoice) == 'e') {
            exitProgram = true;
        }
    }
    return 0;
}


void write_account() {
    Account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);

    if (!outFile.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    cout << "Creating a new account..." << endl;
    ac.create_account();

    cout << "Writing account information to file..." << endl;
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));

    outFile.close();
    cout << "Account creation successful." << endl;
}

void display_sp(int n) {
    system("CLS");
    Account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key..." << endl;
        return;
    }
    cout << "\n\t\t\tBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.retacno() == n) {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\n\t\t\tAccount number does not exist" << endl;
}

void modify_account(int n) {
    bool found = false;
    Account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key..." << endl;
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*> (&ac), sizeof(Account));
        if (ac.retacno() == n) {
            ac.show_account();
            cout << "\n\n\t\t\tEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(Account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(Account));
            cout << "\n\n\t\t\tRecord Updated" << endl;
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n\t\t\tRecord Not Found" << endl;
}

void delete_account(int n) {
    Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key..." << endl;
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account))) {
        if (ac.retacno() != n) {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\nRecord Deleted .." << endl;
}

void display_all() {
    system("CLS");
    Account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key..." << endl;
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    Account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key..." << endl;
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*> (&ac), sizeof(Account));
        if (ac.retacno() == n) {
            ac.show_account();
            if (option == 1) {
                cout << "\n\n\t\t\tTO DEPOSIT AMOUNT" << endl;
                cout << "\n\n\t\t\tEnter The amount to be deposited";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2) {
                cout << "\n\n\t\t\tTO WITHDRAW AMOUNT" << endl;
                cout << "\n\n\t\t\tEnter The amount to be withdraw";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
                    cout << "Insufficience balance" << endl;
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(Account));
            cout << "\n\n\t\t\tRecord Updated" << endl;
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n\t\t\tRecord Not Found" << endl;
}
