#ifndef CONTACT_H
#define CONTACT_H
#include <QString>

class Contact
{
private:
    QString name;
    QString phone_number;
    QString email_address;

public:
    Contact(const QString &,const QString &,const QString &);
    Contact(const Contact&);
    ~Contact();
    QString getName() const;
    QString getPhoneNumber() const;
    QString getEmailAddress() const;
    void setName(const QString &);
    void setPhoneNumber(const QString &);
    void setEmailAddress(const QString &);
};

#endif // CONTACT_H
