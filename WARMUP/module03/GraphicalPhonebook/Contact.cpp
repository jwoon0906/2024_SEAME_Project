#include "Contact.h"

Contact::Contact(const QString& name, const QString& phoneNum, const QString& emailAddress)
    : name(name), phone_number(phoneNum), email_address(emailAddress)
{
}

Contact::Contact(const Contact& other)
    :name(other.name), phone_number(other.phone_number), email_address(other.email_address)
{
}

Contact::~Contact(){}

QString Contact::getName() const{
    return name;
}

QString Contact::getPhoneNumber() const{
    return phone_number;
}

QString Contact::getEmailAddress() const{
    return email_address;
}

void Contact::setName(const QString & name){
    this->name = name;
}

void Contact::setPhoneNumber(const QString & phone_number){
    this->phone_number = phone_number;
}

void Contact::setEmailAddress(const QString & email_address){
    this->email_address = email_address;
}

