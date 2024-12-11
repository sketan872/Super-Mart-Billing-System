#include<iostream>
#include<fstream>
#include<windows.h>
#include<sstream>
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void SetItem(string item) {
        Item = item;
    }

    void SetRate(int rate) {
        Rate = rate;
    }

    void SetQuantity(int quantity) {
        Quantity = quantity;
    }

    string GetItem() {
        return Item;
    }

    int GetRate() {
        return Rate;
    }

    int GetQuantity() {
        return Quantity;
    }
};

void AddItem(Bill &b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            // For item
            string item;
            int rate, quant;
            cout << "\tEnter Item Name: ";
            cin >> item;
            b.SetItem(item);

            // For rate
            cout << "\tEnter Rate: ";
            cin >> rate;
            b.SetRate(rate);

            // For Quantity
            cout << "\tEnter Quantity: ";
            cin >> quant;
            b.SetQuantity(quant);

            ofstream out("D:\\Super market System\\Bill.txt", ios::app);
            if (!out) {
                cout << "\tError: File can't open" << endl;
            } else {
                out << "\t" << b.GetItem() << ":" << b.GetRate() << ":" << b.GetQuantity() << endl << endl;
            }
            out.close();
            cout << "\tItem Added Successfully" << endl;
            Sleep(5000);
        }
        else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(3000);
        }
    }
}

void PrintBill() {
    system("cls");
    int count = 0;
    bool close = false;

    while (!close) {
        system("cls");
        int choice;
        cout << "\t1. Add Bill" << endl;
        cout << "\t2. Close Session" << endl;
        cout << "\t3. Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("D:\\Super market System\\Bill.txt");
            ofstream out("D:\\Super market System\\Bill Temp.txt");

            string line;
            bool found = false;

            while (getline(in, line)) {
                stringstream ss;
                ss << line;
                string ItemName;
                int ItemRate, ItemQuant;
                char delimiter;
                ss >> ItemName >> delimiter >> ItemRate >> delimiter >> ItemQuant;

                if (item == ItemName) {
                    found = true;
                    if (quant <= ItemQuant) {  // Corrected the condition to handle quantity properly
                        int amount = ItemRate * quant;
                        cout << "\tItem | Rate | Quantity | Amount" << endl;
                        cout << "\t" << ItemName << " | " << ItemRate << " | " << ItemQuant << " | " << amount << endl;
                        ItemQuant -= quant;  // Decrease the quantity after purchase
                        count += amount;  // Add amount to total

                        out << "\t" << ItemName << ":" << ItemRate << ":" << ItemQuant << endl;
                    }
                    else {
                        cout << "\tSorry, insufficient quantity for " << item << "!" << endl;
                    }
                }
                else {
                    out << line << endl;
                }
            }

            if (!found) {
                cout << "\tItem Not Available!" << endl;
            }

            out.close();
            in.close();
            remove("D:\\Super market System\\Bill.txt");
            rename("D:\\Super market System\\Bill Temp.txt", "D:\\Super market System\\Bill.txt");
        }
        else if (choice == 2) {
            close = true;  // Fixed the issue with exit condition
            cout << "\tCounting Total Bill..." << endl;
        }
        Sleep(2000);
    }

    system("cls");
    cout << "\tTotal Bill: " << count << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(5000);
}

int main() {
    Bill b;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome to Super Market Billing Program" << endl;
        cout << "\t######################################" << endl;
        cout << "\t\t1. Add Item." << endl;
        cout << "\t\t2. Print Total Bill" << endl;
        cout << "\t\t3. Exit" << endl;
        cout << "\t\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            AddItem(b);
            Sleep(3000);
        }
        else if (val == 2) {
            PrintBill();
        }
        else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tDone" << endl;
            Sleep(3000);
        }
    }

    return 0;
}

