#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Cart {
    std::string items_[10];
    double prices_[10]{};
    int n_ = 0;
    double discount_ = 0.0;
public:
    Cart& add(const std::string& item, double price) {
        if (n_ < 10 && price >= 0.0) { items_[n_] = item; prices_[n_] = price; ++n_; }
        return *this;
    }
    Cart& setDiscount(double discount) { this->discount_ = discount < 0 ? 0 : (discount > 100 ? 100 : discount); return *this; }
    double total() const { double sum = 0; for (int i=0; i<n_; ++i) sum += prices_[i]; return sum * (100.0-discount_) / 100.0; }
    void print() const { for (int i=0; i<n_; ++i) std::cout << "  " << items_[i] << ": " << prices_[i] << '\n'; }
};
int main() {
    std::cout << std::fixed << std::setprecision(2);
    // (a) direct object access
    Cart direct; direct.add("Bread", 40); std::cout << "Direct total: " << direct.total() << '\n';
    // (b) pointer with ->
    Cart pointed; Cart* raw = &pointed; raw->add("Milk", 50); std::cout << "Pointer total: " << raw->total() << '\n';
    // (c) reference access
    Cart referenced; Cart& ref = referenced; ref.add("Eggs", 90); std::cout << "Reference total: " << ref.total() << '\n';
    // (d) dynamically allocated object; unique_ptr owns and releases it safely
    auto dynamicCart = std::make_unique<Cart>(); dynamicCart->add("Oil", 180); std::cout << "Dynamic total: " << dynamicCart->total() << '\n';
    // Required chaining and this pointer behaviour
    Cart c; c.add("Rice",60).add("Dal",120).setDiscount(10);
    Cart* p = &c; p->add("Oil",180);
    std::cout << "Expected chaining example total: " << p->total() << '\n';
    // Array of pointers; find highest total by indexing
    Cart a, b, d; a.add("A",100); b.add("B",250).setDiscount(5); d.add("D",180);
    Cart* active[] = {&a, &b, &d};
    std::size_t best = 0;
    for (std::size_t i=1; i<3; ++i) if (active[i]->total() > active[best]->total()) best=i;
    std::cout << "Highest active cart total: " << active[best]->total() << " (index " << best << ")\n";
    std::cout << "Returning Cart& preserves the original object for chaining; returning Cart makes copies.\n";
}
