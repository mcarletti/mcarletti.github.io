---
author: "Marco Carletti"
title: "CMake in 10 minutes"
date: 2024-05-15T15:47:03+02:00
draft: false
tags: ["cmake", "c/c++"]
---

<center>
<img src="https://cmake.org/wp-content/uploads/2023/08/CMake-Mark-1.svg" style="height: 200px; padding: 2rem;">
</center>

If you are the type who likes to have control over your work, C++ is probably the language for you.

Before we get heated... I'm not here to say that C++ is the best language out there (although I particularly love it), but I think it is among the ones that best allows you to understand how the machine works, how to write a program, and how to run it.

The big problems with C++, especially for beginners, are syntax and the compilation process.

As for syntax, there are wonderful resources online, first and foremost [cppreference.com](https://en.cppreference.com/).
I encourage you to take a look at this site, it is a gold mine for understanding syntax and testing new features of the language.

Regarding compilation, I believe [CMake](https://cmake.org/) is the no-brainer solution for anyone who wants to write C++ code professionally.

For this very small guide, I assume you already have a basic knowledge of C++ and you have a compiler installed on your machine (if you are using Linux, you should have `g++` installed).

# What is CMake?

CMake is a Makefile generator.

Basically, CMake allows you to write a configuration file (`CMakeLists.txt`) that describes how to compile your project.
This file can reference other `CMakeLists.txt` files in subfolders of your project so that you can focus on specific parts of the project.

Once you start CMake, if there are no errors, a Makefile is generated that you can use to compile your project.

CMake produces a series of files (eg. .o, executables, Makefiles, libraries) that are normally placed in a `build` folder in the root of your project, so as not to litter your root folder. This (absolutely configurable) choice is called an *out-of-source build*.

# Why you need it?

Anyone wants a personal assistant, right?  
Well, CMake takes care of all the boring stuff for you.

If you write a single file program, you can compile it with a single command and you don't need any build system but the bare compiler.

Unfortunately, projects grow rapidly in both dimension and complexity.
This is where CMake comes in handy since it takes care of linking all dependecies for you.

Ah, it's [open source](https://gitlab.kitware.com/cmake/cmake) and multi-platform.

# Let's dive in

Ok. Time for a real example.

You want to build your own application called `hello-cmake`, and you try to structure your code in a well organized folder hierarchy. You store all headers in a `include` directory, while definitions are are in the `source` folder. For example:

```
hello-cmake/
├── include/
│   └── application.hpp
├── source/
│   ├── application.cpp
│   └── main.cpp
├── LICENCE
└── README
```

Here we don't mind about the actual implementation: we only focus on the compilation steps.

How do we compile such a program?  

```bash
mkdir build/
SOURCES="source/application.cpp source/main.cpp"
g++ --std=c++11 ${SOURCES} -I include/ -o build/hello
```

That's totally fine, but we are here to compile with CMake 😬

Create a file called `CMakeLists.txt` in the root folder and copy-paste the following lines in it:

```cmake
cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project("hello-cmake")

include_directories("include")
file(GLOB_RECURSE sources "source/*.cpp")

add_executable(hello ${sources})
```

Before running the compiler, a few comments on this file, line by line.

* `cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)`  
Set the minimum version of CMake. If not, CMake raises an error which closes the compilation. How to fix? Upgrade your `cmake` app. Under Ubuntu, you can simply type: `sudo apt update && sudo apt install cmake --upgrade`.

* `project("hello-cmake")`  
Every project has a cool name. This line sets one for ours, which is callable with `${PROJECT_NAME}`. Like in Bash, we access variables through `$` symbol.

* `include_directories("include")`  
Pretty clear, I think. It also includes all subdirectories, if any. Headers are now available to CMake cache, making them accessible from source application via `#include <application>`.

* `file(GLOB_RECURSE sources "source/*.cpp")`  
This line recursively searches for all files matching the regex at the end of the line, saving the resulting files list in `sources` variable, which is used with `${sources}` as for the project name.

* `add_executable(hello ${sources})`  
Magic happens here. We ask CMake to produce a executable called `hello` starting from the sources we have listed in the `sources` variable. What about includes? CMake already knows about them thanks to the `include_directories` command, links declaration with definition and produce the desired output.

# Compilation time!

As said at the beginning of the page, CMake creates its own cache files to store the state of the project compilation (such as the list of includes). This is why you should create a destination folder for the compilation, so you don't mess up the project folder.

To compile the project via CMake (and don't mess up everything), type the following commands:

```bash
mkdir build && cd build
cmake ..
make
```

Firstly, we create and move to the destination folder of compilation. By running the `cmake ..` command, we ask CMake to search for a `CMakeFiles.txt` in the parent directory. If found, CMake creates a set of cache files in the current working directory, that is `build`, preparing for the actual compilation command. The last line runs `make` program to produce the output of the project, for example our executable.

Now you can test the program by running the `hello` executable in `build` folder.

Great! You have created and compiled your first CMake project 🎉

# Final thoughts

CMake quickly becomes your ally as your project grows in complexity (in terms of folder hierarchy, not functions).

At first, CMake is hard and the documentation is a maze of options we can't simply map to the needs of our projects. Hopefully, the simple CMakeLists file we wrote is the starting point of every C++ project you want to compile using CMake.

To improve and learn more about CMake, I strongly suggest to search for open source projects and basically copy-paste their CMakeLists file. It's easier, faster and more reliable than most of online doc.

Keep learning!