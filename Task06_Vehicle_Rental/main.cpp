#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Vehicle {
protected:
    std::string registration_;
    double dailyRate_;
    bool rented_ = false;
public:
    Vehicle(std::string registration, double dailyRate)
        : registration_(std::move(registration)), dailyRate_(dailyRate) {}
    virtual ~Vehicle() = default;
    virtual std::string type() const = 0;
    virtual double rentalCharge(int days) const = 0;
    virtual void details() const = 0;
    const std::string& registration() const { return registration_; }
    bool isRented() const { return rented_; }
    bool rent() { if (rented_) return false; rented_ = true; return true; }
    bool giveBack() { if (!rented_) return false; rented_ = false; return true; }
};
class Bicycle : public Vehicle {
public:
    Bicycle(std::string reg, double rate) : Vehicle(std::move(reg), rate) {}
    std::string type() const override { return "Bicycle"; }
    double rentalCharge(int days) const override { return dailyRate_ * days; }
    void details() const override { std::cout << type() << " | " << registration_ << " | daily Rs." << dailyRate_ << " | " << (rented_?"Rented":"Available") << '\n'; }
};
class TwoWheeler : public Vehicle {
    double fuelLevel_;
    std::string serviceDue_;
public:
    TwoWheeler(std::string reg, double rate, double fuel, std::string due)
        : Vehicle(std::move(reg), rate), fuelLevel_(fuel), serviceDue_(std::move(due)) {}
    std::string type() const override { return "Two-wheeler"; }
    double rentalCharge(int days) const override { return dailyRate_ * days + 30.0; }
    void details() const override { std::cout << type() << " | " << registration_ << " | fuel " << fuelLevel_ << "% | service " << serviceDue_ << " | " << (rented_?"Rented":"Available") << '\n'; }
};
class Car : public Vehicle {
protected:
    int seats_;
    double fuelLevel_;
    std::string serviceDue_;
public:
    Car(std::string reg, double rate, int seats, double fuel, std::string due)
        : Vehicle(std::move(reg), rate), seats_(seats), fuelLevel_(fuel), serviceDue_(std::move(due)) {}
    std::string type() const override { return "Car"; }
    double rentalCharge(int days) const override { return dailyRate_ * days + 100.0; }
    void details() const override { std::cout << type() << " | " << registration_ << " | seats " << seats_ << " | fuel " << fuelLevel_ << "% | service " << serviceDue_ << " | " << (rented_?"Rented":"Available") << '\n'; }
};
class ElectricCar : public Car {
    double batteryKWh_;
    double chargePerKWh_;
public:
    ElectricCar(std::string reg, double rate, int seats, double battery, double perKWh, std::string due)
        : Car(std::move(reg), rate, seats, 100.0, std::move(due)), batteryKWh_(battery), chargePerKWh_(perKWh) {}
    std::string type() const override { return "Electric car"; }
    double rentalCharge(int days) const override { return dailyRate_ * days + batteryKWh_ * chargePerKWh_; }
    void details() const override { std::cout << type() << " | " << registration_ << " | seats " << seats_ << " | battery " << batteryKWh_ << " kWh | " << (rented_?"Rented":"Available") << '\n'; }
};
// Extension: a new vehicle type is added without editing Vehicle or existing derived classes.
class ElectricBus : public Vehicle {
    int seats_;
    double batteryKWh_;
public:
    ElectricBus(std::string reg, double rate, int seats, double battery)
        : Vehicle(std::move(reg), rate), seats_(seats), batteryKWh_(battery) {}
    std::string type() const override { return "Electric bus"; }
    double rentalCharge(int days) const override { return dailyRate_ * days + batteryKWh_ * 2.0; }
    void details() const override { std::cout << type() << " | " << registration_ << " | seats " << seats_ << " | battery " << batteryKWh_ << " kWh | " << (rented_?"Rented":"Available") << '\n'; }
};
class Fleet {
    std::vector<std::unique_ptr<Vehicle>> vehicles_;
public:
    void add(std::unique_ptr<Vehicle> v) { vehicles_.push_back(std::move(v)); }
    Vehicle* find(const std::string& reg) const { for (const auto& v : vehicles_) if (v->registration()==reg) return v.get(); return nullptr; }
    void list() const { for (const auto& v : vehicles_) v->details(); }
    void rent(const std::string& reg, int days) const {
        Vehicle* v=find(reg); if (!v) { std::cout << "Vehicle not found: " << reg << '\n'; return; }
        if (!v->rent()) { std::cout << reg << " is already rented.\n"; return; }
        std::cout << "Rented " << v->type() << " " << reg << " for " << days << " day(s): Rs." << v->rentalCharge(days) << '\n';
    }
    void returnVehicle(const std::string& reg, int lateDays) const {
        Vehicle* v=find(reg); if (!v) { std::cout << "Vehicle not found: " << reg << '\n'; return; }
        if (!v->giveBack()) { std::cout << reg << " was not currently rented.\n"; return; }
        constexpr double lateFeePerDay=200.0;
        std::cout << "Returned " << reg << ". Late fee: Rs." << (lateDays>0?lateDays*lateFeePerDay:0.0) << '\n';
    }
};
int main() {
    std::cout << std::fixed << std::setprecision(2);
    Fleet fleet;
    fleet.add(std::make_unique<Bicycle>("CYC-101", 100));
    fleet.add(std::make_unique<TwoWheeler>("BIKE-202", 350, 75, "2027-03-01"));
    fleet.add(std::make_unique<Car>("CAR-303", 1500, 5, 80, "2027-04-15"));
    fleet.add(std::make_unique<ElectricCar>("EV-404", 1800, 5, 60, 8, "2027-05-20"));
    fleet.add(std::make_unique<ElectricBus>("EBUS-505", 5000, 30, 180));
    std::cout << "--- Fleet listing ---\n"; fleet.list();
    std::cout << "--- Rentals ---\n";
    fleet.rent("CYC-101", 2); fleet.rent("BIKE-202", 3); fleet.rent("CAR-303", 2);
    fleet.rent("EV-404", 2); fleet.rent("EBUS-505", 1);
    std::cout << "--- Returns (late fee demonstration) ---\n";
    fleet.returnVehicle("CAR-303", 2); fleet.returnVehicle("EV-404", 0);
    std::cout << "--- Fleet after returns ---\n"; fleet.list();
}
