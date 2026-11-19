# Task 1 design notes

Deficiencies in the original payroll classes: duplicated name/ID/basic fields; public data permits invalid states; inconsistent identifiers (`name`/`nm`, `id`/`code`); `da` is unused; 0.42 is a magic number; pay logic is duplicated; guest faculty uses a different pay basis; adding categories requires separate processing logic; no common polymorphic collection.

Hierarchy: abstract `Staff` owns shared identity and basic-pay data; `Professor`, `LabAssistant` and `GuestFaculty` override `pay()` and `category()`. A vector of `unique_ptr<Staff>` allows one loop.

Alternative one-class switch: store a category code and all possible fields, then branch in `pay()`. Per-call time remains O(1); object storage wastes fields for categories that do not use them. Adding a category requires changing the enum/type code, data layout/constructor logic, switch, and often reporting/validation code. Polymorphic extension adds a derived class and its implementation, leaving the processing loop unchanged.
