## bbbbmatrix

Implementation of matrix class in C++.

Tested on Linux and macOS.

## Building

G++ is required for building.

To build the lib run make

```bash
make
```

If you want to run tests, please install GTest

#### Ubuntu/Debian
```bash
sudo apt install libgtest-dev
make test
```

#### macOS
```bash
brew install googletest
make test
```

For Gcov GTest and lcov are required

#### Ubuntu/Debian
```bash
sudo apt install lcov
make gcov_report
```

#### macOS
```bash
brew install lcov
make gcov_report
```

##

This project is licensed under the terms of the MIT license.
