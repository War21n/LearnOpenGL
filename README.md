# LearnOpenGL
Record the process of learning OpenGL

## Compile
Successfully compiled glfw from source using cmake.
Need to use MinGW compiler in Windows system, so use the follow commonds to complie this project:
```sh
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

## GLAD
Using python to generate glad code(need to install glad first):
```python
glad --api gl=3.3 --profile=core --generator=c --out-path=./glad
```
Then copy include and src files to project. 