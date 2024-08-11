# Contributing

## Code Style
- Use the C++20 standard


### Memory and pointers

#### Avoid double deletion with objects derived from `QObject`
- The Qt framework has a parent-child model, and expects to manage and have ownership of `QObject`-derived objects.
- If a `QObject`-derived object has a parent widget, Qt will generally handle freeing that object.
- This means you generally aren't responsibly for calling `delete`, nor should you use a smart pointer - Qt expects control regarding ownership and lifecycle. You should use a smart pointer for everything else though. The use of smart pointers in this case can cause issues with double deletion.
- This means that ideally you should strive for each `QObject`-derived object to have a parent widget, otherwise you are in charge of freeing it later.

### Naming conventions

### Letter case
- `.cpp` and `.h` files as well as C++ classes should be in `PascalCase`.
- Method names and variables should use `camelCase()`
- Constants should be written `LIKE_THIS`
