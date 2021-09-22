# Introduction

Cayley is C++ header only template library for algebra matrix 2-dimensional representation.
This library provides two types of matrices: static and dynamic.  

# Getting Started

Under construction

# Static Matrix 2-dimensional

The static matrix 2-dimensional is a sipmle interface which provides a matrix who cannot change
its dimensions (MxN).

## Constructor

The default constructor just create the instance where you define the data type of your matrix, number of rows and columns.
Take a look at the example below.

```c++
    using namespace cayley;
    static_matrix_2d<int, 4, 4> s_mat;
```