## Chapter 1 - Getting Started.

### Section 1.1
---

#### Contents
    * Writing a simple c++ program.
    * A first look at input/Output
    * A word about Comments
    * Flow of Control.
    * The Book Store Program.
---
This chapter includes, basic elements such as Types, variables, expressions, statements, and functions.

In order to make the example program we will need to:
    * Define Variables
    * Do input/output
    * Use a data structure to hold data.
    * Test whether two records have the same ISBN.
    * Contain a loop that will process every record in the transaction file.
---
Functions - 
    * Must be named in main.

#### Function Definition:
    - Has four elements:
        * A return Type
        * Function Name
        * Parameter List ()
        * Function Body. {}

NOTE!!! main () must always have a return type of int, thus:

int main()
{
    return 0;
}
Usually a return of 0 from main means success. 

Return is a statement that terminates a function. As in the case here a return can also send a value back to the functions caller.

When a return statement includes a value, the value returned must have a type that is compatible with the return type of the function. In this case int.

IMPORTANT!!! The semi colon ; Semi colons mark the end of most statements in C++, when forgotten, can lead to mysterious compiler error messages.
---
#### KEY CONCEPT! 
    * Type: A type defines both the contents of a data element and the operations that are possible on those data. The data our programs manupulate are stored in variables and every variable has a type.
---

#### Compiling:
# G++ vs Clang (Quick Notes)
---
#### What They Are
- **G++** — GNU C++ compiler (GNU Compiler Collection)
- **Clang++** — C++ compiler built on LLVM  
- Both support modern C++ (C++17/20/23)

---

#### Basic Usage

```bash
g++ main.cpp -std=c++20 -Wall -Wextra -o program
clang++ main.cpp -std=c++20 -Wall -Wextra -o program
```

Common flags:
- `-std=c++20` → C++ version  
- `-Wall -Wextra` → warnings  
- `-O2` → optimization  
- `-g` → debug info  

---

#### When to Use G++
- Default on Linux  
- GNU toolchains / legacy projects  
- Strong optimization  

---

#### When to Use Clang
- Default on macOS  
- Better error messages  
- Strong static analysis & tooling  

---

#### Rule of Thumb
- Mac → Clang  
- Linux → G++  
- Serious development → Compile with both  
- Always enable warnings


---
### Section 1.2

- C++ uses a standard Library that provides IO
Examples:
    * <iostream>
        Two types which represent input and output streams
            * <istream>
            * <ostream>
- A stream is a swquence of chracters read from or written to an IO device. The term stream is intended to suggest that the characters are generated or consumed sequentiall over time.

- This library defines four IO objects:
    * cin - an object of type <istream> - Also reffered to as the standard input.
    * cout - an object of type <ostream> - Also reffered to as standard output.
        - other <ostream> objects:
            * cerr - standard roor, for warning and error messages.
            * clog - for general information about the execution of the program.

---
#### A simple program (add two numbers)

#include <iostream>
int main()
{
    std::cout << "Enter two numbers:" << std::endl; // this executes and expression, which use the output operator << to print a message:
    int v1 = 0, v2 = 0; // set variables to 0
    std::cin >> v1 >> v2; take input from keyboard and store into v1 and v2.
    std::cout << "The sum of " << v1 << " and " << v2 add v1 and v2 then print string literal v1 and v2  then 6, the flush the buffer
            << " is " << v1 + v2 << std::endl;
    return 0; // all is well we are done here.
}

- The first line tells our program we want to use iostream library. This uses the header : <iostream>
    -- Every program that uses a library facility must include its header.
- the #include directive must be writeen on a single line, that is the header and directive must be on same line.
- these ususally go at the top of the source file.

- An expression yeilds a result and is compsed on one or more operands and usually an operator.

- String Literal - a sequence of characters enclosed in double quotes, and is printed to the standard output (prints to screen)
- Order of operations on evaluations, C++ sees the + operator first so the program holds v1 + v2 then does the string literals.

- Always flush! The stream that is... endl

- NOTE ABOUT std:: The prefix std:: indicates that the names cout and endl are defined inside the namespace named std
    * Namespaces allow us to avoid inadvertent collisions between the names we difine and uses of those same names inside a library. All the names defined by the standard library are in the std namespace.

Exercises-
    * 1.3 write a program to print hello, world on the standard output.
    * 1.4 Write a program that uses multiplication operator to print the product of two numbers.
    * 1.5 Just like the add two program, we wrote the output as one long statement. Rewrite the statement to use a a separate statemtn to print each operand.
    * 1.6 Explain whether the following program fragment is legal.
        - std::cout << "The sum of " << v1;
                    << " and " << v2;
                    << " is " << v1 + v2 << std::endl;
        - If the program is legal, what does it do? if the program is not legal, why not? how would you fix it?
