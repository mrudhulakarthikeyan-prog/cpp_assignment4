# Task 5 comparison

| Form | Access | Lifetime / safety | Typical use |
|---|---|---|---|
| Named object | `cart.total()` | Automatic lifetime in its scope | Preferred simple ownership |
| Pointer | `ptr->total()` | Does not own unless explicitly designed to; can be null/dangle | Optional or polymorphic access |
| Reference | `ref.total()` | Alias; must bind to a valid object | Required non-owning alias |
| Dynamic owner | `unique_ptr<Cart>` and `->` | Owns heap object and releases automatically | Runtime-controlled lifetime |

`this` is the implicit pointer to the current object inside a non-static member function. `*this` is the current object as an lvalue reference. Returning `Cart&` enables chaining without making a copy. Returning Cart by value returns a copy, can add copying and subsequent calls may operate on temporaries.
