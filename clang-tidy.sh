#!/bin/bash

# Define the directories to search for C++ files, excluding the tests directory
directories=("src")

# Define the clang-tidy checks to enable (all except llvmlibc, fuchsia, altera, and cppcoreguidelines-owning-memory)
checks="*, -llvmlibc-*, -fuchsia-*, -altera-*, -cppcoreguidelines-owning-memory, -llvm-header-guard"

# Loop through each directory and run clang-tidy
for dir in "${directories[@]}"; do
    # Find all C++ source files in the directory
    files=$(find "$dir" -name "*.cpp" -o -name "*.h")
    
    # Loop through each file and run clang-tidy
    for file in $files; do
        echo "Running clang-tidy on $file"
        # Run clang-tidy with specified checks and capture the output
        script -q -c "clang-tidy -checks='$checks' -p build $file 2>&1" /dev/null | \
        GREP_COLOR='1;32' grep --color=always -vE "(clang-diagnostic-error|file not found|Could not auto-detect|Error while processing|Found compiler error\(s\).|^[[:space:]]*#?[[:space:]]*include|^[[:space:]]*\^|/usr/include/x86_64-linux-gnu/qt6|Q_OBJECT|QT_TR_FUNCTIONS|QMetaObject|google-explicit-constructor|hicpp-explicit-conversions|modernize-use-trailing-return-type)"
        
        # Capture the return code of the clang-tidy command
        rc=$?
        # If there was an error, print the output to stderr
        if [ $rc -ne 0 ]; then
            script -q -c "clang-tidy -checks='$checks' -p build $file 2>&1" /dev/null | \
            grep --color=always -vE "(clang-diagnostic-error|file not found|Could not auto-detect|Error while processing|Found compiler error\(s\).|^[[:space:]]*#?[[:space:]]*include|^[[:space:]]*\^|/usr/include/x86_64-linux-gnu/qt6|Q_OBJECT|QT_TR_FUNCTIONS|QMetaObject|google-explicit-constructor|hicpp-explicit-conversions|modernize-use-trailing-return-type)" >&2
        fi
    done
done
