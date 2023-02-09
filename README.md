# Stack

TL; DR: implementation of the std::stack structure

## Documentation for Stack

Defines in header "stack.h"

`template<typename ValueType> class Stack`

The **Stack** class is a container that gives the programmer 
the functionality of a stack — specifically, a LIFO (last-in, 
first-out) data structure. The **Stack** pushes and pops the 
element from the back of the underlying container, known 
as the top of the stack.

### Rule of five

**Stack** has destructor, copy and move semantics:

+ Destructor

+ Copy constructor

+ Copy assignment operator

+ Move constructor

+ Move assignment operator

### Methods

`Top` — accesses the top element

`Empty` — checks whether the underlying container is empty

`Size` — returns the number of elements

`Clear` — removes all elements

`Push` — inserts element at the top

`Pop` — removes the top element

`Swap` — swaps the contents