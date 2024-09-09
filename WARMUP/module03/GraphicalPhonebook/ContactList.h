#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <vector>
#include "Contact.h"

using namespace std;

class ContactList
{
private:
    vector<Contact> contactList;

public:
    void addContact(const Contact &);

    void removeContact(const QString &name);

    vector<Contact> listContacts() const;

    void saveContactListToFile(const QString& filename) const;

    void loadContactListFromFile(const QString& filename);
};
#endif // CONTACTLIST_H
