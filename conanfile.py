from pathlib import Path

from conan import ConanFile
from conan.tools.files import copy


class MultiplayerGameRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("sdl/2.26.5")
        self.requires("sdl_image/2.0.5")
        # self.requires("sdl_mixer/2.0.4")
        self.requires("sdl_ttf/2.20.2")
        self.requires("glm/cci.20230113")
        self.requires("lua/5.4.4")
        self.requires("sol2/3.3.0")

    # def configure(self):
    #     self.options["stduuid"].with_cxx20_span=True

    # def generate(self):
        # for dep in self.dependencies.values():
        #     if str(dep) == "glslang/8.13.3559":
        #         for binDir in dep.cpp_info.bindirs:
        #             copy(self, "glslangValidator*", binDir, "../../bin")
        #
        #     if str(dep) == "ktx/4.0.0":
        #         for binDir in dep.cpp_info.bindirs:
        #             copy(self, "toktx*", binDir, "../../bin")
        #             copy(self, "ktxinfo*", binDir, "../../bin")
