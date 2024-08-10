# Building

## Linux

### Prerequisites

```sh
sudo apt install cmake qt6-base-dev qt6-base-dev-tools qt6-tools-dev libgl1-mesa-dev libglu1-mesa-dev clang-tidy clang-format cppcheck
```

### Building

```sh
mkdir build && cd build
cmake ..
make
```

## Windows
Building on Windows is much more involved than on Linux or macOS. 

### Prerequsites


#### Qt 6
>**Note:** Unfortunately, installing Qt on Windows requires that you register with a Qt account.

You will need to download the [Qt 6 Installer](https://www.qt.io/download-qt-installer-oss). When running the installer, choose **Custom Installation**
and enable at least the following:

- [ ] Qt Design Studio
- [ ] Extensions
- [ ] Qt
  - [x] Qt 6.7.2
    - [x] MSVC 2019 64-bit
  - [ ] Developer and Designer Tools
    - [x] Debugging Tools for Windows
       
This will keep the installation from growing too large (selecting lots of options can balloon the installation to as much as 50GB).

#### LLVM
>**Note:** While we are installing LLVM, it is only in order to get access to `clang-format` and `clang-tidy`. LLVM is not used for compilation on Windows.

You will need to download the [LLVM Installer](https://github.com/llvm/llvm-project/releases). During installation, ensure that you select **Add LLVM to the system path for all users**

#### VS 2022

You will need to download and install [Visual Studio 2022](https://visualstudio.microsoft.com/vs/community/).

When running the installer, ensure that you enable the **Desktop and development with C++** workload. Ensure that **MSVC v143 - VS 2022 C++** is selected.

