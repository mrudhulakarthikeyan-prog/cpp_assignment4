# Task 2 access table

Assuming Person declares a public, protected and private member: 

| Person member | public inheritance in Student | protected inheritance | private inheritance |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | inaccessible directly in Student | inaccessible directly in Student | inaccessible directly in Student |

The base class's own member functions can access its private members. Derived classes cannot directly access private base members.

Relationships: Student is-a Person (single); Staff is-a Person (single); TeachingAssistant is-a Student and Staff (multiple, forming hybrid inheritance); ResearchScholar is-a Student (multilevel from Person); multiple Student/Staff-derived branches form hierarchical and hybrid structures. Phone is a simple data attribute here, not a member-class relationship.

Virtual inheritance makes Student and Staff share one Person subobject in a TeachingAssistant. Without virtual inheritance, two Person subobjects exist and `name`/`id` access is ambiguous. The most-derived class initializes the virtual base.
