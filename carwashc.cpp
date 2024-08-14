#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

void login();
void registr();
void forgot();

class CarWashSystem {
private:
    string carType;
    string carNumber;
    string date;
    string time;

    float totalBill;

public:
    // Constructor to initialize member variables
    CarWashSystem() : totalBill(0.0) {}


   // Car Type
    void customerBooking() {
        do {
            cout << "\nEnter your car type (Sedan/SUV): ";
            getline(cin, carType);
            if (carType != "Sedan" && carType != "SUV") {
                cout << "\nInvalid car type! Please enter Sedan or SUV." << endl;
            }
        } while (carType != "Sedan" && carType != "SUV");
       
    //Car Number
        cout << "\nEnter your car number: ";
        getline(cin, carNumber);
        
    // Booking date
    regex datePattern("^\\d{4}/\\d{2}/\\d{2}$"); // Regex for dd/mm/yyyy format
    do {
        cout << "\nEnter your booking date (yyyy/mm/dd	): ";
        getline(cin, date);
        if (!regex_match(date, datePattern)) {
            cout << "\nInvalid date format! Please enter in dd/mm/yyyy format." << endl;
        }
    } while (!regex_match(date, datePattern));
    
    //Booking time
        regex timePattern("^(0[1-9]|1[0-2]):[0-5][0-9] (AM|PM)$"); // Regex for hh:mm AM/PM format
    do {
        cout << "\nEnter your booking time (12-Hour Format with AM/PM): ";
        getline(cin, time);
        if (!regex_match(time, timePattern)) {
            cout << "\n ------ Invalid time format! Please enter in hh:mm AM/PM format using space, (eg: 12:00 AM).-------" << endl;
        }
    } while (!regex_match(time, timePattern));
    }

    void choosePackage() {
        int packageOption;
        char morePackages;

        do {
            cout << "\nChoose a package:\n";
            if (carType == "Sedan") {
             cout << "\n ---------- | 1. Basic Wash (RM15) | 2. Polish (RM50) | 3. Wax (RM100) | ----------" << endl;
            } else if (carType == "SUV") {
             cout << "\n ---------- | 1. Basic Wash (RM35) | 2. Polish (RM80) | 3. Wax (RM130) | ----------" << endl;
            } else {
                cout << "Invalid car type!" << endl;
                return;
            }
            cout << "\nEnter the package number: ";
            cin >> packageOption;
            cin.ignore(); // To handle the newline character after entering package number

            switch (packageOption) {
                case 1:
                    if (carType == "Sedan")
                        totalBill += 15;
                    else if (carType == "SUV")
                        totalBill += 35;
                    break;
                case 2:
                    if (carType == "Sedan")
                        totalBill += 50;
                    else if (carType == "SUV")
                        totalBill += 80;
                    break;
                case 3:
                    if (carType == "Sedan")
                        totalBill += 100;
                    else if (carType == "SUV")
                        totalBill += 130;
                    break;
                default:
                    cout << "\n ------ Invalid package option! ------ " << endl;
                    return;
            }
            cout << "\nPackage added successfully!" << endl;

            cout << "\nDo you want to select another package? (y/n): ";
            cin >> morePackages;
            cin.ignore(); // To handle the newline character after entering 'y' or 'n'

        } while (morePackages == 'y' || morePackages == 'Y');
    }

    void sumBill() {
        cout << "\nCar Type: " << carType << endl;
        cout << "-----\nCar Number: " << carNumber << endl;
        cout << "-----\nBooking Date: " << date << endl;
        cout << "-----\nBooking Time: " << time << endl;
        cout << "-----\nTotal Bill: RM" << totalBill << endl;
         cout << "\n ------ Thank you for your booking with Sparkle Shine! ------ " << endl;
    }

    void run() {
        customerBooking();
        choosePackage();
        sumBill();
    }
};

void mainMenu() {
    CarWashSystem system;
    system.run();
}

int main() {
    int choice;
    cout << "------------------------------------------------------------------\n\n";
    cout << "           Welcome to Sparkle Shine Car Wash                \n\n";
    cout << "-------------------        MENU        ---------------------------\n\n";
    cout << "\n1.Login" << endl;
    cout << "\n2.Register" << endl;
    cout << "\n3.Forgot Username or Password" << endl;
    cout << "\n4.Exit" << endl;
    cout << "\nEnter your choice :";
    cin >> choice;
    cout << endl;

    switch (choice) {
        case 1:
            login();
            break;
        case 2:
            registr();
            break;
        case 3:
            forgot();
            break;
        case 4:
            break;
        default:
            system("cls");
            cout << "You've made a mistake, Try again..\n" << endl;
            main();
    }

    return 0;
}

void login() {
    int count = 0;
    string user, pass, u, p;
    system("cls");
    cout << "Please enter the following details" << endl;
    cout << "\nUsername: ";
    cin >> user;
    cout << "\nPassword: ";
    cin >> pass;

    ifstream input("database.txt");
    while (input >> u >> p) {
        if (u == user && p == pass) {
            count = 1;
            system("cls");
        }
    }
    input.close();

    if (count == 1) {
    cout << "------------------------------------------------------------------\n\n";
    cout << "                Welcome to Sparkle Shine Car Wash                \n\n";
    cout << "---------- Hello, " << user << " You're Successfully Logged In -------------" ;
        cin.get();
        cin.get();
        mainMenu(); // Redirect to Car Wash System after successful login
    } else {
        cout << "\nLOGIN ERROR\nPlease check your username and password\n";
        main();
    }
}

void registr() {
    string reguser, regpass;
    system("cls");
    cout << "Enter the username: ";
    cin >> reguser;
    cout << "\nEnter the password: ";
    cin >> regpass;

    ofstream reg("database.txt", ios::app);
    reg << reguser << ' ' << regpass << endl;
    system("cls");
    cout << "\nRegistration Successful\n";
    main();
}

void forgot() {
    int ch;
    system("cls");
    cout << "------------------------------------------------------------------\n\n";
    cout << "                Welcome to Sparkle Shine Car Wash                \n\n";
    cout << "-------- Forgotten your Password or Username? Don't worry! ----------" ;
    cout << "\n\n1. Search your ID by username" << endl;
    cout << "\n2. Search your ID by password" << endl;
    cout << "\n3. Main menu" << endl;
    cout << "\nEnter your choice: ";
    cin >> ch;

    switch (ch) {
        case 1: {
            int count = 0;
            string searchuser, su, sp;
            cout << "\nEnter your remembered username: ";
            cin >> searchuser;

            ifstream searchu("database.txt");
            while (searchu >> su >> sp) {
                if (su == searchuser) {
                    count = 1;
                }
            }
            searchu.close();

            if (count == 1) {
                cout << "\n\nHurray, account found\n";
                cout << "\nYour password is " << sp;
                cin.get();
                cin.get();
                system("cls");
                main();
            } else {
                cout << "\nSorry, Your userID is not found in our database\n";
                cout << "\nPlease kindly contact your system administrator for more details \n";
                cin.get();
                cin.get();
                main();
            }
            break;
        }
        case 2: {
            int count = 0;
            string searchpass, su2, sp2;
            cout << "\nEnter the remembered password: ";
            cin >> searchpass;

            ifstream searchp("database.txt");
            while (searchp >> su2 >> sp2) {
                if (sp2 == searchpass) {
                    count = 1;
                }
            }
            searchp.close();

            if (count == 1) {
                cout << "\nYour password is found in the database\n";
                cout << "\nYour ID is: " << su2;
                cin.get();
                cin.get();
                system("cls");
                main();
            } else {
                cout << "\nSorry, We cannot find your password in our database\n";
                cout << "\nKindly contact your administrator for more information\n";
                cin.get();
                cin.get();
                main();
            }
            break;
        }
        case 3: {
            cin.get();
            main();
        }
        default: {
            cout << "\nSorry, You entered the wrong choice. Kindly try again" << endl;
            forgot();
        }
    }
}

