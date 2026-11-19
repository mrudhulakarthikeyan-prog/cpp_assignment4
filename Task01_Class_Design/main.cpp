#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Staff {
protected:
    std::string name_;
    int id_;
    double basic_;
public:
    Staff(std::string name, int id, double basic)
        : name_(std::move(name)), id_(id), basic_(basic) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    virtual std::string category() const = 0;
    void print() const {
        std::cout << std::left << std::setw(16) << category()
                  << std::setw(14) << name_ << std::setw(8) << id_
                  << std::right << std::fixed << std::setprecision(2) << pay() << '\n';
    }
};

class Professor final : public Staff {
    double research_;
    static constexpr double DA_RATE = 0.42;
public:
    Professor(std::string name, int id, double basic, double research)
        : Staff(std::move(name), id, basic), research_(research) {}
    double pay() const override { return basic_ * (1.0 + DA_RATE) + research_; }
    std::string category() const override { return "Professor"; }
};
class LabAssistant final : public Staff {
    static constexpr double DA_RATE = 0.42;
public:
    LabAssistant(std::string name, int id, double basic)
        : Staff(std::move(name), id, basic) {}
    double pay() const override { return basic_ * (1.0 + DA_RATE); }
    std::string category() const override { return "Lab Assistant"; }
};
class GuestFaculty final : public Staff {
    double hours_, rate_;
public:
    GuestFaculty(std::string name, int id, double hours, double rate)
        : Staff(std::move(name), id, 0.0), hours_(hours), rate_(rate) {}
    double pay() const override { return hours_ * rate_; }
    std::string category() const override { return "Guest Faculty"; }
};
int main() {
    std::vector<std::unique_ptr<Staff>> payroll;
    payroll.push_back(std::make_unique<Professor>("Anita", 101, 50000, 8000));
    payroll.push_back(std::make_unique<LabAssistant>("Bala", 102, 30000));
    payroll.push_back(std::make_unique<GuestFaculty>("Charan", 103, 40, 900));
    std::cout << "Category       Name          ID      Pay\n";
    for (const auto& person : payroll) person->print();
}
