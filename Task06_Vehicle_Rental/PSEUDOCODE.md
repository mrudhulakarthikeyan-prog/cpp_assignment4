# Task 6 – testable requirements and pseudocode

## Testable requirements
1. Every vehicle has a unique registration number and daily rate.
2. Bicycle, two-wheeler, car and electric car provide their own rental charge calculation.
3. Motor vehicles expose fuel/charge and service information; cars expose seats; electric cars expose battery capacity and per-kWh charging.
4. A vehicle cannot be rented twice without being returned.
5. A vehicle cannot be returned if it is not currently rented.
6. Returning late adds Rs.200 per late day in this implementation (explicit demonstration policy).
7. Fleet listing and charging work through base-class pointers and virtual functions.
8. ElectricBus can be added as a new derived class without modifying Vehicle or existing vehicle classes.

## Pseudocode
`RENT(registration, days):` locate vehicle; if absent report not found; else call rent(); if already rented report status; otherwise calculate and display `rentalCharge(days)`.

`RETURN(registration, lateDays):` locate vehicle; if absent report not found; else call giveBack(); if not rented report status; otherwise compute `max(lateDays, 0) * lateFeePerDay` and display fee.

## Complexity
With n vehicles in a vector, lookup/rent/return is O(n) due to linear search; charge calculation for one vehicle is O(1); listing is O(n). Storage is O(n) pointers/owners plus each concrete object. A switch-based single Vehicle class also has O(1) charge dispatch, but it stores fields for all categories and every new category changes the central switch and class.
