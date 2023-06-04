// https://en.cppreference.com/w/cpp/container/forward_list

#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stddef.h>

typedef struct Node
{
    int value;
    struct Node *pNext;
} Node;

typedef struct List
{
    Node *head;
} List;

typedef struct iterator
{
    Node *current;
} iterator;

typedef struct const_iterator
{
    const Node *current;
} const_iterator;

List *create_list(void);
void destroy_list(List *this);

// Replaces the contents of the container with "count" copies of value "value".
// All iterators and pointers to the elements of the container are invalidated.
void assign(List *this, size_t count, int value);

// Returns an iterator to the first element of the forward_list.
// If the forward_list is empty, the returned iterator will be equal to end().
iterator begin(List *this);
const_iterator cbegin(List *this);

// Erases all elements from the container.
// Invalidates any pointers, or iterators referring to contained elements.
// Any past-the-end iterator remains valid.
void clear(List *this);

// Checks if the container has no elements, i.e. whether begin() == end().
// Returns true(1) if the container is empty, false(0) otherwise
int empty(List *this);

// Returns an iterator to the element following the last element of the forward_list.
// This element acts as a placeholder; attempting to access it results in undefined behavior.
iterator end(List *this);
const_iterator cend(List *this);

// Removes specified elements from the container.
// Returns iterator to the element following the erased one, or end() if no such element exists.
iterator erase_after(iterator pos);

// Returns a pointer to the first element in the container.
// Calling front on an empty container causes undefined behavior.
int *front(List *this);

// Inserts "value" after the element pointed to by "pos"
// No iterators are invalidated.
// Returns iterator to the inserted element.
// The behavior is undefined if list has no elements.
iterator insert_after(iterator pos, int value);

// The function does nothing if "other" refers to the same object as "this".
// Otherwise, merges two sorted lists into one. The lists should be sorted into ascending order.
// No elements are copied, and the container other becomes empty after the merge.
void merge(List *this, List *other);

// Removes the first element of the container. If there are no elements in the container, the behavior is undefined.
// Iterators to the erased element are invalidated.
void pop_front(List *this);

// Prepends the given element "value" to the beginning of the container.
// No iterators are invalidated.
void push_front(List *this, int value);

// Removes all elements that are equal to "value".
// Returns the number of elements removed.
int remove_(List *this, int value);

// Removes all elements for which predicate "unPred" returns true.
// Returns the number of elements removed.
int remove_if(List *this, int (*unPred)(const int *value));

// Resizes the container to contain "count" elements, does nothing if count == size().
// If the current size is greater than "count", the container is reduced to its first "count" elements.
// If the current size is less than "count", additional zeroes are appended
void resize(List *this, size_t count);
void resize_value(List *this, size_t count, int value);

// Reverses the order of the elements in the container. No iterators become invalidated.
void reverse(List *this);

// Sorts the elements in ascending order. The order of equal elements is preserved.
void sort(List *this);

// Checks if the elements in range [first, last) are sorted in non-descending order.
int is_sorted(const_iterator first, const_iterator last);

// Moves elements from another forward_list to "this".
// Moves all elements from other into *this.
// The elements are inserted after the element pointed to by pos.
// The container other becomes empty after the operation.
// The behavior is undefined if other refers to the same object as *this.
void splice_after(iterator pos, List *other);

// Exchanges the contents of the container with those of "other".
// Does not invoke any move, copy, or swap operations on individual elements.
void swap(List *this, List *other);

// Removes all consecutive duplicate elements from the container.
// Only the first element in each group of equal elements is left.
void unique(List *this);

// Global Functions

// Increments given iterator "iter" by "n" elements. n must be greater or equal to 0.
void advance(iterator *iter, int n);

// Returns the number of hops from first to last.
// The behavior is undefined if last is not reachable from first by incrementing first.
size_t distance(const_iterator first, const_iterator last);

// Increments given iterator "iter" by 1 elements.
void next(iterator *iter);
void const_next(const_iterator *iter);

// Returns an iterator to the first element in the range [first, last) that satisfies specific criteria (or last if there is no such iterator
iterator find(iterator first, iterator last, int value);
const_iterator cfind(const_iterator first, const_iterator last, int value);

//  Utility Functions

void random_fill(List *this, size_t size);
void print_list(List *this);
void print_list_iterator(const_iterator begin, const_iterator end);
void print_size(List *this);
void randomize(void);
int *to_array(List *this);
List *to_forward_list(int *arr, size_t size);

#endif // FORWARD_LIST_H
