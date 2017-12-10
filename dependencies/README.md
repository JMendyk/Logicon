# Dependencies


## General information 

Project to work properly requires:
- OpenGL3
- GL3W
- GLFW
- ImGUI
- imgui\_impl\_glfw\_gl3

## Dependencies description

### OpenGL3
OpenGL3 is required to be installed on user's computer for proper compilation and non-development usage.

### [GL3W](https://github.com/skaslev/gl3w) (included in project's source)
*Maintainer does not provide versions nor releases thus master branch is used.*
Requires Python and building before usage with commands:
```
cmake .
make
```

### [GLFW](https://github.com/glfw/glfw) (included in project's source)
*Version tagged 3.2.1.*

### [ImGUI](https://github.com/ocornut/imgui) (included in project's source)
*Version tagged v1.52.*

### [imgui\_impl\_glfw\_gl3](https://github.com/ocornut/imgui) (included in project's source)
*Version tagged v1.52. Sourced directly from ImGUI's repo.*
ImGUI integration for OpenGL3 & GLFW.

## Platform specific

### UNIX/Linux

On UNIX/Linux **xorg-dev** and **RandR** are required for complilation of the project.
It is usually possibile using your distribution package manager, for example on Ubuntu: `sudo apt install xorg-dev`.


### Windows

Building on Windows was tested with 2 configurations:

1. CLion IDE with included build tools

Plainly import cloned repository's folder into CLion. As build configuration pick `imgui_with_opengl3` and make sure that in CMake's settings "Generation path" is set to ".". See related issue why this is required: (https://github.com/JMendyk/ImGUI_with_OpenGL3/issues/1)[https://github.com/JMendyk/ImGUI_with_OpenGL3/issues/1].

2. [MinGW](http://www.mingw.org/) + [CMake](https://cmake.org/) + [FreeGLUT](https://www.transmissionzero.co.uk/software/freeglut-devel/)

Make sure that CMake as well as MinGW build tools are present in PATH. The easiest way to install FreeGLUT is to put it's folders into respective ones in your MinGW folder. 

In some cases CMake may complain about missing Visual C++ compiler. Assuming you want to compile using MinGW, call cmake with flag `cmake -G "MinGW Makefiles"`.