#include <iostream>
#include <string>
using namespace std;

class Car{
private:
    string make;
    string model;
    int year;
public:
    Car() : make(""), model(""), year(0) {}
    Car(const string& mk, const string& md, const int y) : make(mk), model(md), year(y) {}
    Car(const Car& other) : make(other.make), model(other.model), year(other.year) {}
    Car& operator = (const Car& other){
        if (this != &other) {
            make = other.make;
            model = other.model;
            year = other.year;
        }
        return *this;
    }
    ~Car(){}
    void drive(){
        cout << "make: " << make << " model : " << model << " year : " << year << " driving" <<endl;
    }
};

class SportCar : public Car{
private:
    int topSpeed;
public:
    SportCar() : Car(), topSpeed(0) {}
    SportCar(const string& mk, const string& md, int y, int ts) : Car(mk, md, y), topSpeed(ts){}
    SportCar(const SportCar& other) : Car(other), topSpeed(other.topSpeed) {}
    SportCar& operator=(const SportCar& other) {
        if (this != &other) {
            Car::operator=(other);
            topSpeed = other.topSpeed;
        }
        return *this;
    }
    ~SportCar() {}
    void drive(){
        Car::drive();
        cout << "top speed is " << topSpeed<<endl;
    }
};

int main() {
    SportCar a;
    a.drive();

    SportCar b("b", "the all new b", 2024, 200);
    b.drive();

    SportCar c(b);
    c.drive();

    SportCar d;
    d = b;
    d.drive();

    return 0;
}