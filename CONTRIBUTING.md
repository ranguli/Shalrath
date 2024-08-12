# Contributing


## Coding Style

Use `clang-tidy` and `clang-format`. These tools enforce the majority of the coding style, so if you are using those tools you will be more or less rail-roaded into following the right track. Particular points of the coding style to note that either aren't covered by these tools or are re-iterated for their importance are written below and are as follows:

1. The **C++20** standard is used. Code should be idiomatic and prefer modern features of the language.
2. **Smart pointers** should always be preferred, _with_ one notable exception:
    * The Qt frameworks parent-child model expects to manage the ownership and lifecycle of `QObject`-derived objects. Thus, using smart pointers can be problematic here due to ownership issues or double deletion. Instead in this case (and only in this case) you should use `new()`. **Always ensure that a Qt widget is assigned to a parent.** If a widget has a parent, Qt handles its lifecycle, and you are not responsible for calling `delete()`.
3. The following conventions should be observed for **case naming**:
    *  `.cpp` and `.h` files as well as C++ classes should be in `PascalCase`.
    * Method names and variables should use `camelCase()`
    * Constants should be written `LIKE_THIS`
4. **Magic numbers** should be avoided when possible. These can come about quite often when passing width or height values to Qt Widgets. In these situations, a `QSize` object utilizing named constants can be useful for solving this problem.