#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() { std::cout << "Account destructor\n"; }
};
class SeniorAccount : public Account {
    double* history_;
public:
    SeniorAccount() : history_(new double[100]{}) {}
    double rate() const override { return 4.0; }
    ~SeniorAccount() override { delete[] history_; std::cout << "SeniorAccount destructor\n"; }
};
class NonVirtualAccount { public: double rate() const { return 3.5; } ~NonVirtualAccount() = default; };
class NonVirtualSenior : public NonVirtualAccount { public: double rate() const { return 4.0; } };
int main() {
    std::cout << "--- Repaired polymorphic accounts ---\n";
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& account : accounts) std::cout << "Rate: " << account->rate() << "%\n";
    std::cout << "--- Non-virtual vs virtual dispatch and slicing ---\n";
    NonVirtualSenior oldSenior;
    NonVirtualAccount* oldPtr = &oldSenior;
    Account* p = new SeniorAccount;
    Account copy = SeniorAccount(); // object slicing: only Account base part is copied
    std::cout << "Non-virtual call through base pointer: " << oldPtr->rate() << '\n';
    std::cout << "Virtual call through base pointer: " << p->rate() << '\n';
    std::cout << "Sliced Account copy rate: " << copy.rate() << '\n';
    delete p;
    std::cout << "Unique pointers release remaining objects automatically.\n";
}
