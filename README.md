# OpenGL UniLab
## Compilation Option

All these ```define```s are listed in [```main.cpp```](src/main.cpp) at the begining of the file, right after ```include```s.


### Cube vs Triangle
```c++
#define DRAW_CUBE_INSTEAD_OF_A_TRIANGLE 1
```
When this flag is set to ```1```, the program is compiled with rotating Cube in the middle of the window. If ```USE_OLD_RENDERER``` is set to ```1```, it's rendered as plainly white. it changes its color (more about it later).
When this flag is set to ```0```, the program is compiles with rotating Triangle in the middle of the window.
Any other value is invalid.

### OpenGL 2.1- vs OpenGL 3.0+
```c++
#define USE_OLD_RENDERER 0
```
When this flag is set to ```1```, the program is compiled for OpenGL 2.1 or lower. In this mode it doesn't use shaders.
When this flag is set to ```0```, the program is compiled for OpenGL 3.0 or newer. In this mode it does use shaders (located in [resources folder](resources)).
Any other value is invalid.

### Window Number
```c++
#define WIN_COUNT 1
```
This flag defines the amount of windows program will create. Closing any of it will lead to termination of the program.
If ```USE_OLD_RENDERER``` is set to ```1```, any number between ```1``` and ```3``` is allowed, otherwise - only ```1``` and this is statically asserted.
Any other value is invalid.

## Predefined Controls

### General
* ```Escape``` - close the program.

### Camera Movements (TODO)
* ```W``` - forward
* ```A``` - left
* ```S``` - backwards
* ```D``` - right
* Mouse movements - rotation
* Mouse scroll - zoom

### Color Change
* ```C``` - switch between constant color change and one random color
* ```Q``` - if constant color change is off, will paint the cube in random color.
