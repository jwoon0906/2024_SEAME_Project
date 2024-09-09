#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Contact
{
private:
    string Name;
    string PhoneNumber;
    string Nickname;
    bool is_bookmarked;

public:
    Contact(string n, string p, string nn) 
        : Name(n), PhoneNumber(p), Nickname(nn), is_bookmarked(false){}

    string getName() const { return Name; }
    string getPhoneNumber() const { return PhoneNumber; }
    string getNickname() const { return Nickname; }
    bool isBookmarked() const { return is_bookmarked; }
    void setBookmarked(bool bookmarked) { is_bookmarked = bookmarked; }
    void show() const{
        cout << "Name :" << Name << ", PhoneNumber : "<<PhoneNumber<<" NickName :" <<NickName<<" isBookmared : "<<(is_bookmared? "Y" :"N")<<endl;
    }
};

class Phonebook
{
private:
    vector<Contact> contacts;
public:
    void add_contact(const string& name, const string& phone_number, const string& nickname) {
        for (const Contact& contact : contacts){
            if(contact.getPhoneNumber == phone_number){
                cerr << "phone number already exist";
                return;
            }
        }
        Contact new_contact(name, phone_number, nickname);
        contacts.push_back(new_contact);
        cout << "new contact for " << name << "is successfully added" <<endl;
        return;
    }
    void search_contacts() {
        if (contacts.empty()) {
            cerr << "Empth phonebook." << endl;
            return;
        }

        for (int i = 0; i < contacts.size(); ++i) {
            cout << i << ": " << contacts[i].getName() << " (" << contacts[i].getPhoneNumber() << ")" << endl;
        }

        cout << "Enter the index of the contact for details:";

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
        string num;
        cin >> num;
        string removal;
        if(atoi(num)!=0 || num.compare("0") ==0){
            //index
            int int_num = atoi(num);
            if(int_num >= 0 && int_num < contacts.size()){
                cout << "Are you sure to remove this contact("<<contacts[int_num].getName<< ") : ? (Y/N)"<<endl;
                cin >> removal;
                if(removal == "Y"){
                    cout << "Contact Removed";
                    contacts.erase(contacts.begin() + index);
                    return;
                }else{
                    cout << "Removal Canceled";
                    return;
                }
            }else{
                cerr<<"invalid index"<<endl;
            }
        }else{
            //phone number
            for (const Contact& contact : contacts){
                if(contact.getPhoneNumber == num){
                    cout << "Are you sure to remove this contact("<<contact.getName<< ") : ? (Y/N)"<<endl;
                    cin >>removal;
                    if(removal == "Y"){
                        cout << "Contact Removed";
                        contacts.erase(contact);
                        return;
                    }else{
                        cout << "Removal Canceled";
                        return;
                    }
                }
            }
            cerr<<"No Such Phone Number"<<endl;
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
            cerr << "No bookmarked Contacts." << endl;
        }
    }



    

}

int main (){
    Phonebook phonebook;
    string cmd;
    cout << "-----Old Phonebook-----\n";
    while(1){
        cout << "\nEnter Command(ADD, SEARCH, REMOVE, BOOKMARK, EXIT) : ";
        cin >> cmd;
        if (cmd == "ADD") {
            string name, phone_number, nickname;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Phone Number(xxx-xxxx-xxxx): ";
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