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

Requires 
```shell
wget -c "https://www.apache.org/dyn/closer.cgi?filename=/activemq/6.3.2/apache-activemq-6.3.2-bin.tar.gz&action=download"
```

### Compiling
```shell
conan install . --profile=<profile_template> --output-folder=build --build=missing
```

```shell
cmake --preset conan-release
```

```shell
cmake --build --preset conan-release
```

### Running
```shell
/opt/apache-activemq-6.3.2/bin/activemq console
```

```shell
# In another process
./activemq-cpp-broker
```

## Resources
[ActiveMQ-CPP Example](https://activemq.apache.org/components/cms/example)