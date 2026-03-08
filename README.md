# Arbitrary Precision Calculator (APC)

This is a C-based calculator that works with integers of **any size**. Instead of using standard data types like `int` or `long long` (which have size limits), the program stores each digit in a node of a **doubly linked list**. This approach allows arithmetic operations on numbers much larger than what built-in types can normally handle.

## Features

* Works with very large integers
* Handles both positive and negative numbers
* Supports addition, subtraction, multiplication, and division (`+`, `-`, `x`, `/`)
* Uses **doubly linked lists** to store digits
* Performs calculations similar to manual arithmetic

## How It Works

Each number is stored as a linked list where **every node contains a single digit**.

Example representation of **12345**:

```
1 <-> 2 <-> 3 <-> 4 <-> 5
```

During calculations, digits are processed step by step, similar to how arithmetic is performed manually.

## Operations Implemented

* **Addition**       – Handles carry while adding digits from right to left
* **Subtraction**    – Uses borrow logic and removes leading zeros
* **Multiplication** – Uses the schoolbook multiplication method with partial products
* **Division**       – Implements integer division using repeated subtraction

## Input Rules
* The expression must be given without spaces
* Only one operator is allowed in an expression
* Supported operators are +, -, x, and /
* Use x for multiplication instead of *
* Both positive and negative integers are supported
* Input format must be
  ```
  <number1><operator><number2>
  ```
  
## Compilation

```
gcc *.c -o apc
```

## Execution

```
./apc <number1><operator><number2>
```

Example runs:
```
./apc 123+456
./apc 1000-245
./apc 123x45
./apc 20/4
```
## Concepts Used
While developing this project, the following concepts were applied:

* Doubly Linked Lists
* Dynamic Memory Allocation
* Command Line Arguments
* Modular Programming in C
* Arithmetic algorithms (carry, borrow, partial products)
* Handling large numbers beyond built-in data type limits
  
## Limitations
* Supports only **single operator expressions**
* Division returns **integer results only**
* No support for parentheses or operator precedence

## Author
**Hensilin Rithista S**
B.Tech ECE
