#include <iostream>
#include <string>
#include <utility>

class Address {
    std::string city_;
    int pin_;
public:
    Address(std::string city, int pin) : city_(std::move(city)), pin_(pin) { std::cout << "Address constructed\n"; }
    ~Address() { std::cout << "Address destroyed\n"; }
    std::string str() const { return city_ + "-" + std::to_string(pin_); }
};
class Course {
    std::string title_;
public:
    explicit Course(std::string title) : title_(std::move(title)) { std::cout << "Course constructed\n"; }
    ~Course() { std::cout << "Course destroyed\n"; }
};
class Person {
protected:
    std::string name_;
    int age_;
    Address address_;
public:
    Person(std::string name, int age, std::string city, int pin)
        : name_(std::move(name)), age_(age), address_(std::move(city), pin) { std::cout << "Person constructed\n"; }
    virtual ~Person() { std::cout << "Person destroyed\n"; }
};
class Student : virtual public Person {
    long long regNo_;
    Course course_;
public:
    Student(std::string name, int age, long long regNo, std::string city, int pin, std::string course)
        : Person(std::move(name), age, std::move(city), pin), regNo_(regNo), course_(std::move(course)) {
        std::cout << "Student constructed\n";
    }
    ~Student() override { std::cout << "Student destroyed\n"; }
    void print() const { std::cout << regNo_ << ' ' << name_ << " (" << age_ << ") " << address_.str() << '\n'; }
};
class Staff : virtual public Person {
    std::string department_;
public:
    Staff(std::string name, int age, std::string city, int pin, std::string department)
        : Person(std::move(name), age, std::move(city), pin), department_(std::move(department)) { std::cout << "Staff constructed\n"; }
    ~Staff() override { std::cout << "Staff destroyed\n"; }
};
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant()
        : Person("Riya", 22, "Chennai", 600001),
          Student("Riya", 22, 301, "Chennai", 600001, "C++"),
          Staff("Riya", 22, "Chennai", 600001, "CSE") { std::cout << "TeachingAssistant constructed\n"; }
};
int main() {
    std::cout << "--- Complete-the-code constructor using initializer list ---\n";
    Student s("Kavya", 19, 192311001, "Salem", 636001, "OOP with C++");
    s.print();
    std::cout << "--- Student destruction follows at end of scope ---\n";
    {
        std::cout << "--- TeachingAssistant virtual-base construction trace ---\n";
        TeachingAssistant ta;
        (void)ta;
    }
    std::cout << "--- Non-virtual inheritance size experiment ---\n";
    struct P { int id; }; struct S : P {}; struct W : P {}; struct TA : S, W {};
    std::cout << "sizeof(TA) with two non-virtual P subobjects = " << sizeof(TA) << '\n';
    std::cout << "sizeof(TeachingAssistant) with virtual Person base = " << sizeof(TeachingAssistant) << '\n';
}
