
## Building

### Dependencies

```
sudo apt install qt6-base-dev qt6-base-dev-tools qt6-tools-dev libgl1-mesa-dev libglu1-mesa-dev googletest googletest-tools clang-tidy clang-format cppcheck 
```

```meson setup build --backend=ninja --buildtype=debug -Db_sanitize=address -Db_lundef=false -Ddebug=true -Dwarning_level=2 --default-library=static -Dcpp_std=c++17 --reconfigure
```


## Contributing

### Steps for creating a PR

- Ensure unit tests are written for any new code
- Ensure any new source files are added to the listing in `tools/meson.build` so they are seen by code quality tools.