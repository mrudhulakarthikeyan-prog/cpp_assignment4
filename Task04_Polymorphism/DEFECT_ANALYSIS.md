# Task 4 forensic analysis

1. `rate()` is non-virtual in the faulty Account, so `Account*` calls the base implementation (3.5), even when it points to SeniorAccount.
2. Deleting a SeniorAccount through Account* is undefined behaviour when Account lacks a virtual destructor; the derived destructor may not run, so its allocated `history` array may leak.
3. `Account copy = SeniorAccount();` slices the derived object: only the Account base subobject is copied; derived state and dynamic type are lost.

Repair: make the polymorphic operation virtual, mark overrides with `override`, provide a virtual base destructor, and own objects through `std::unique_ptr<Account>` in a vector. This avoids manual delete and preserves dynamic dispatch.

The fixed program is suitable for AddressSanitizer. Do not rely on the output of the defective delete-through-base example: it is undefined behaviour and may vary by compiler/runtime.
