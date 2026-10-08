# activemq-cpp-broker
A simple Apache ActiveMQ CPP broker example.

## Building from source
### Prerequisites
| Tool                                | Recommended Version |
| ----------------------------------- | ------------------- |
| [`Clang`](https://clang.llvm.org/)  | 18.0.0 or higher    |
| [`Python`](https://www.python.org/) | 3.14.0 or higher    |
| [`CMake`](https://cmake.org/)       | 3.15.0 or higher    |
| [`Conan`](https://conan.io/)        | 2.33.0 or higher    |

Ensure project is built with `clang` (and `clang++`), see [profile_template](profile_template) for more details.

### Compiling
```shell
conan install . --profile=<profile_template> --output-folder=build --build=missing
```

```shell
cmake --preset conan-default
```

```shell
cmake --build --preset conan-release
```

### Running
```shell
./activemq-cpp-broker
```