from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("apr/1.7.4", override=True)
        self.requires("activemq-cpp/3.9.5")

    def layout(self):
        cmake_layout(self)