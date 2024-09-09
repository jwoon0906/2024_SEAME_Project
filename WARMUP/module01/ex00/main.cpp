#include <iostream>
#include <string>

using namespace std;

class Car{
private:
    string name;
    int speed;
public:
    Car() : name(""), speed(0){}
    Car(const string& n, int s) : name(n), speed(s){}
    Car(const Car &other) : name(other.name), speed(other.speed){}
    Car& operator=(const Car& other) {
        if (this != &other) {
            name = other.name;
            speed = other.speed;
        }
        return *this;
    }
    ~Car(){cout<<"destructor :"<<name<<endl;}
    
    void show() const{
        cout<<"Car name : " << name << " Speed : " << speed << endl;
    }
};

int main(void){
    Car a("a_car", 100);
    Car b = a;
    Car c;
    c = a;
    a.show();
    b.show();
    c.show();
    return 0;
}