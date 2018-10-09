[BACK](https://mcarletti.github.io/)

*Last update: October 9th, 2018*

# MATLAB


## Getting started

You can write your command in the command line of the MATLAB interface right after the `>>` symbols. Otherwise you can create a new script file and write all the commends inside, then run the entire script.

### Let's start

Close every graphics context and windows, clean the workspace (release memory) and clean the console:

```matlab
>> close all;
>> clear;
>> clc;
```

Comment your code like there's no tomorrow.

```matlab
% With this single line comment, I introduce you to MATLAB.

%{
Multi-line comments are useful to explain more complex features.
For example, to print a variable, you could simply write its name
in the command line or use a function like DISP.
%}
```

```matlab
>> msg = 'Hello, World!'; % you can also comment like this
```

```matlab
>> msg

msg = 

    'Hello, World!'
```

```matlab
>> disp(msg)
Hello, World!
```

Initialize a variable, for example a real number `a` and a complex number `b`:

```matlab
>> a = 4

a = 
    4

>> b = 3 + 5i

b =
    3 + 5i
```

Note that:
* MATLAB is case-sensitive: for example, `var`, `Var` and `VAR` are different names;
* for complex numbers, you can use `i` or `j`;
* to avoid printing in the prompt the value of a variable, just finish the command with the `;` characater.

### Matrices

Everything is a matrix. Everything. Also scalar values are considered as 1x1 matrices. MATLAB is cool.

To generate a matrix, separate each row with `;` and to compute its transposed version, use the `'` character right after the variable name:

```matlab
>> M = [1 2 3; 4 5 6];

M =
    1 2 3
    4 5 6

>> M = [1; 2; 3; 4]

M =
    1
    2
    3
    4

>> M = [1 2; 3 4]

M = 
    1 2
    3 4
```

```matlab
>> M = [1 2 3 4; 5 6 7 8]

M = 
    1 2 3 4
    5 6 7 8

>> M'

ans =
    1 5
    2 6
    3 7
    4 8
```

The variable `ans` (*answer*) is a special variable used by MATLAB to store the output of an operation that is not assigned to any variable. Every time a new operation is computed without assignment, `ans` is assigned with the its results.

To save the transposition of the matrix `M`, that is computed by `M'` we must assign it to a new variable:

```matlab
>> Mt = M';
>> Mt

Mt = 
    1 5
    2 6
    3 7
    4 8
```

### To be continued...
TODO