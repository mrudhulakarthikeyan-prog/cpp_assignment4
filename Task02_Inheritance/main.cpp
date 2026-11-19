#include <iostream>
#include <string>
#include <utility>

class Person {
protected:
    std::string name_;
    int id_;
    std::string phone_;
public:
    Person(std::string name = "", int id = 0, std::string phone = "")
        : name_(std::move(name)), id_(id), phone_(std::move(phone)) {}
    virtual ~Person() = default;
    const std::string& name() const { return name_; }
};
class Student : virtual public Person {
protected:
    std::string programme_;
    double cgpa_;
public:
    Student(std::string name = "", int id = 0, std::string phone = "",
            std::string programme = "", double cgpa = 0.0)
        : Person(std::move(name), id, std::move(phone)), programme_(std::move(programme)), cgpa_(cgpa) {}
};
class Staff : virtual public Person {
protected:
    std::string department_;
    double salary_;
public:
    Staff(std::string name = "", int id = 0, std::string phone = "",
          std::string department = "", double salary = 0.0)
        : Person(std::move(name), id, std::move(phone)), department_(std::move(department)), salary_(salary) {}
};
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(std::string name, int id, std::string phone,
                      std::string programme, double cgpa,
                      std::string department, double salary)
        : Person(name, id, phone), Student(name, id, phone, programme, cgpa),
          Staff(name, id, phone, department, salary) {}
    void print() const {
        std::cout << "Teaching Assistant: " << name_ << ", ID: " << id_
                  << ", Programme: " << programme_ << ", CGPA: " << cgpa_
                  << ", Department: " << department_ << ", Salary: " << salary_ << '\n';
    }
};
class ResearchScholar : public Student {
    double fellowship_;
public:
    ResearchScholar(std::string name, int id, std::string phone,
                    std::string programme, double cgpa, double fellowship)
        : Person(name, id, phone), Student(name, id, phone, programme, cgpa), fellowship_(fellowship) {}
    void print() const { std::cout << "Research Scholar: " << name_ << ", Fellowship: " << fellowship_ << '\n'; }
};
// Non-virtual variant is kept separate to demonstrate the duplicated Person subobjects.
struct PlainPerson { std::string name; };
struct PlainStudent : PlainPerson {};
struct PlainStaff : PlainPerson {};
struct PlainTA : PlainStudent, PlainStaff {};
int main() {
    TeachingAssistant ta("Kavya", 201, "9876500000", "AIDS", 9.1, "CSE", 25000);
    ResearchScholar scholar("Mohan", 202, "9876500001", "AIDS", 9.4, 18000);
    ta.print(); scholar.print();
    PlainTA nonVirtual;
    std::cout << "sizeof(PlainTA) = " << sizeof(nonVirtual) << " bytes (contains two PlainPerson bases)\n";
    std::cout << "sizeof(TeachingAssistant) = " << sizeof(TeachingAssistant) << " bytes (virtual shared Person base)\n";
    std::cout << "Composition alternative: a TA containing Student and Staff members has two independent Person subobjects.\n";
}
