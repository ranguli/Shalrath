#!/bin/bash

files=$(find ./src \( -name '*.cpp' -o -name '*.h' \))

clang-tidy -p build/ $files | grep -v '\[clang-diagnostic-.*\]' --color=auto

#-- -extra-arg=-fno-system-headers \
#    -extra-arg=-fno-caret-diagnostics -extra-arg=-ferror-limit=0 -extra-arg=-Wno-error \
#    -extra-arg=-I/usr/include/x86_64-linux-gnu/qt6 -extra-args=-I/usr/lib/gcc \
#    -extra-arg=-I/usr/include/c++/ \
#    -extra-arg=-I/usr/include/x86_64-linux-gnu \
