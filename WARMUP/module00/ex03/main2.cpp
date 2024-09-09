#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Contact {
private:
    string Name;
    string PhoneNumber;
    string Nickname;
    bool is_bookmarked;

public:
    Contact(string n, string p, string nn) 
        : Name(n), PhoneNumber(p), Nickname(nn), is_bookmarked(false) {}

    string getName() const { return Name; }
    string getPhoneNumber() const { return PhoneNumber; }
    string getNickname() const { return Nickname; }
    bool isBookmarked() const { return is_bookmarked; }
    void setBookmarked(bool bookmarked) { is_bookmarked = bookmarked; }

    void show() const {
        cout << "Name: " << Name << ", Phone Number: " << PhoneNumber 
             << ", Nickname: " << Nickname << ", Bookmarked: " 
             << (is_bookmarked ? "Y" : "N") << endl;
    }
};

class Phonebook {
private:
    vector<Contact> contacts;

public:
    void add_contact(const string& name, const string& phone_number, const string& nickname) {
        for (const Contact& contact : contacts) {
            if (contact.getPhoneNumber() == phone_number) {
                cerr << "Phone number already exists!" << endl;
                return;
            }
        }
        Contact new_contact(name, phone_number, nickname);
        contacts.push_back(new_contact);
        cout << "New contact for " << name << " is successfully added" << endl;
    }

    void search_contacts() {
        if (contacts.empty()) {
            cerr << "Empty phonebook." << endl;
            return;
        }

        for (int i = 0; i < contacts.size(); ++i) {
            cout << i << ": " << contacts[i].getName() << " (" << contacts[i].getPhoneNumber() << ")" << endl;
        }

        cout << "Enter the index of the contact for details: ";
        int index;
        cin >> index;

        if (index >= 0 && index < contacts.size()) {
            contacts[index].show();
            cout << "Would you like to bookmark this contact? (Y/N): ";
            string bookmark;
            cin >> bookmark;
            if (bookmark == "Y") {
                contacts[index].setBookmarked(true);
                cout << "Bookmarked" << endl;
            }
        } else {
            cout << "Invalid index" << endl;
        }
    }

    void remove_contact() {
        cout << "Enter the index or phone number to remove: ";
        string input;
        cin >> input;

        // Check if the input is a number
        if (isdigit(input[0]) || (input[0] == '-' && isdigit(input[1]))) {
            // Input is an index
            int index = stoi(input);
            if (index >= 0 && index < contacts.size()) {
                cout << "Are you sure you want to remove this contact (" << contacts[index].getName() << ")? (Y/N) ";
                string confirmation;
                cin >> confirmation;
                if (confirmation == "Y") {
                    contacts.erase(contacts.begin() + index);
                    cout << "Contact removed" << endl;
                } else {
                    cout << "Removal canceled" << endl;
                }
            } else {
                cerr << "Invalid index" << endl;
            }
        } else {
            // Input is a phone number
            auto it = remove(contacts.begin(), contacts.end(),
                [&input](const Contact& contact) {
                    return contact.getPhoneNumber() == input;
                });

            if (it != contacts.end()) {
                cout << "Are you sure you want to remove this contact (" << it->getName() << ")? (Y/N) ";
                string confirmation;
                cin >> confirmation;
                if (confirmation == "Y") {
                    contacts.erase(it, contacts.end());
                    cout << "Contact removed" << endl;
                } else {
                    cout << "Removal canceled" << endl;
                }
            } else {
                cerr << "No such phone number" << endl;
            }
        }
    }

    void list_bookmarked() const {
        bool found = false;
        for (const Contact& contact : contacts) {
            if (contact.isBookmarked()) {
                contact.show();
                found = true;
            }
        }
        if (!found) {
            cerr << "No bookmarked contacts." << endl;
        }
    }
};

int main() {
    Phonebook phonebook;
    string cmd;
    cout << "-----Old Phonebook-----\n";
    while (true) {
        cout << "\nEnter Command (ADD, SEARCH, REMOVE, BOOKMARK, EXIT): ";
        cin >> cmd;
        if (cmd == "ADD") {
            string name, phone_number, nickname;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Phone Number (xxx-xxxx-xxxx): ";
            cin >> phone_number;
            cout << "Enter Nickname: ";
            cin >> nickname;
            phonebook.add_contact(name, phone_number, nickname);
        } else if (cmd == "SEARCH") {
            phonebook.search_contacts();
        } else if (cmd == "REMOVE") {
            phonebook.remove_contact();
        } else if (cmd == "BOOKMARK") {
            phonebook.list_bookmarked();
        } else if (cmd == "EXIT") {
            cout << "Exiting PhoneBook" << endl;
            break;
        } else {
            cout << "Invalid Command" << endl;
        }
    }
    return 0;
}