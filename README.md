# C Forward List

This repository contains a C implementation of a singly-linked list, inspired by C++'s `forward_list`. The goal is to provide similar functionality to C++'s `forward_list`, including various operations such as assignment, iteration, manipulation, and utility functions.

## Table of Contents

- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Functionality](#functionality)
- [Utility Functions](#utility-functions)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The C Forward List is designed to provide a convenient and efficient way to work with singly-linked lists in the C programming language. It aims to mimic the functionality of C++'s `forward_list` while maintaining a similar interface.

The implementation consists of a `List` structure, which contains a pointer to the head node of the list. Each node, represented by the `Node` structure, holds an integer value and a pointer to the next node in the list. Additionally, an `iterator` structure is provided to facilitate list traversal and manipulation.

## Getting Started

To use the C Forward List in your project, follow these steps:

1. Clone the repository:

```bash
git clone https://github.com/aogulcemal/c-forward-list.git
```

2. Include the necessary files in your project:

```c
#include "forward_list.h"
```

3. Compile your project with the list implementation:

```bash
clang main.c forward_list.c -o main
```

4. Run your executable:

```bash
./main
```

## Usage

To create a new list, use the `create_list` function:

```c
List* myList = create_list();
```

To destroy a list and free the associated memory, use the `destroy_list` function:

```c
destroy_list(myList);
```

Refer to the [Functionality](#functionality) section for a list of available operations on the C Forward List.

## Functionality

The C Forward List provides the following operations, similar to C++'s `forward_list`:

- `assign`: Assigns new values to the list, replacing its current contents.
- `begin`: Returns an iterator pointing to the first element of the list.
- `clear`: Removes all elements from the list, leaving it empty.
- `distance`: Calculates the number of elements between two iterators.
- `empty`: Checks if the list is empty.
- `end`: Returns an iterator referring to the past-the-end element in the list.
- `erase_after`: Removes a single element following a specific position.
- `front`: Returns a pointer to the first element in the list.
- `find`: Searches the list for a specific value and returns an iterator to it.
- `insert_after`: Inserts a new element into the list after a specific position.
- `next`: Advances an iterator to the next position.
- `pop_front`: Removes the first element in the list.
- `push_front`: Inserts a new element at the beginning of the list.
- `remove`: Removes all elements equal to a specific value from the list.
- `remove_if`: Removes all elements for which a specific predicate is true.
- `resize`: Resizes the list to contain a specific number of elements.
- `reverse`: Reverses the order of the elements in the list.
- `sort`: Sorts the elements in ascending order.
- `splice_after`: Moves elements from one list to another.
- `swap`: Swaps the contents of two lists.
- `unique`: Removes consecutive duplicate elements from the list.

## Utility Functions

In addition to the core functionality, the C Forward List also provides utility functions for testing and printing purposes:

- `random_fill`: Fills a list with randomly generated integers.
- `print_list`: Prints the elements of a given list in a singly-linked list fashion.
- `print_list_iterator`: Same as print_list but it takes const_iterator begin and end.
- `to_array`: Creates a dynamically allocated array to hold the items in a singly-linked list.
- `to_forward_list`: Takes an array and creates a singly-linked list from its elements.

Feel free to explore and utilize these functions as needed.

## Testing

The C Forward List includes a set of unit tests to verify the correctness of its implementation. These tests can be run using `make test`.

To run the tests, follow these steps:

1. Make sure you have `make` and a C compiler (e.g., `clang`) installed on your system.

2. Navigate to the project directory in your terminal.

3. Run the following command to compile and run the tests:

```bash
make test
```

4. The test results will be displayed in the terminal, indicating whether each test has passed or failed.

Please note that the tests assume a Unix-like environment with the `make` utility. If you're using a different operating system or development environment, you may need to adjust the command accordingly or manually compile and run the test files.

You can also examine the test files (`test.c`) to understand how the C Forward List is tested and to modify or expand the tests as needed.

## Contributing

Contributions to the C Forward List are welcome! If you encounter any issues or have suggestions for improvements, please open an issue or submit a pull request. Your contributions will help enhance the functionality and usability of the project.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use and modify the code for your own purposes.