#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

List *create_list(void)
{
    List *this = (List *)malloc(sizeof(struct List));
    if (!this)
    {
        fprintf(stderr, "Allocation failed");
        exit(EXIT_FAILURE);
    }
    this->head = NULL;

    return this;
}

void destroy_list(List *this)
{
    while (!empty(this))
        pop_front(this);

    free(this);
}

// Static Functions

static Node *createNode(void)
{
    Node *pNewNode = (Node *)malloc(sizeof(Node));
    if (!pNewNode)
    {
        fprintf(stderr, "Allocation failed");
        exit(EXIT_FAILURE);
    }

    return pNewNode;
}

static int icmp(const void *vp1, const void *vp2)
{
    return *(const int *)vp1 - *(const int *)vp2;
}

void assign(List *this, size_t count, int value)
{
    clear(this);
    while (count--)
        push_front(this, value);
}

iterator begin(List *this)
{
    iterator iter;
    iter.current = this->head;

    return iter;
}

const_iterator cbegin(List *this)
{
    const_iterator iter;
    iter.current = this->head;

    return iter;
}

const_iterator cend(List *this)
{
    const_iterator iter;
    iter.current = NULL;

    return iter;
}

void clear(List *this)
{
    while (!empty(this))
        pop_front(this);
}

int empty(List *this)
{
    return begin(this).current == end(this).current;
}

iterator end(List *this)
{
    iterator iter;
    iter.current = NULL;

    return iter;
}

iterator erase_after(iterator pos)
{
    Node *temp = pos.current->pNext;
    pos.current->pNext = pos.current->pNext->pNext;
    pos.current = pos.current->pNext;
    free(temp);

    return pos;
}

int *front(List *this)
{
    return &(this->head->value);
}

iterator insert_after(iterator pos, int value)
{
    Node *pNewNode = createNode();

    pNewNode->value = value;
    pNewNode->pNext = pos.current->pNext;
    pos.current->pNext = pNewNode;
    pos.current = pNewNode;

    return pos;
}

void merge(List *this, List *other)
{
    if (this->head == other->head)
        return;

    if (!this->head) // If list1 is empty, simply point its head to list2's head
        this->head = other->head;

    else if (other->head) // If list2 is not empty
    {
        Node *curr1 = this->head;
        Node *curr2 = other->head;
        Node *prev1 = NULL;

        while (curr1 && curr2)
        {
            if (curr2->value < curr1->value)
            {
                if (!prev1)
                    this->head = curr2;
                else
                    prev1->pNext = curr2;

                prev1 = curr2;
                curr2 = curr2->pNext;
                prev1->pNext = curr1;
            }
            else
            {
                prev1 = curr1;
                curr1 = curr1->pNext;
            }
        }

        if (!curr1 && prev1)
            prev1->pNext = curr2;

        else if (!this->head)
            this->head = other->head;
    }

    other->head = NULL;
}

void pop_front(List *this)
{
    Node *pDel = this->head;
    this->head = this->head->pNext;

    free(pDel);
}

void push_front(List *this, int value)
{
    Node *pNewNode = createNode();

    pNewNode->value = value;
    pNewNode->pNext = this->head;
    this->head = pNewNode;
}

int remove_(List *this, int value)
{
    int count = 0;
    int first = 1;
    Node *p = this->head;
    Node *prev = this->head;
    while (p)
    {
        if (p->value != value)
        {
            if (first)
                first = 0;
            prev = p;
            p = p->pNext;
            continue;
        }

        Node *temp = p;
        prev->pNext = p->pNext;
        if (first)
            this->head = prev->pNext;

        p = p->pNext;
        ++count;
        free(temp);
    }

    return count;
}

int remove_if(List *this, int (*unPred)(const int *value))
{
    int count = 0;
    int first = 1;
    Node *p = this->head;
    Node *prev = this->head;
    while (p)
    {
        if (!unPred(&p->value))
        {
            if (first)
                first = 0;
            prev = p;
            p = p->pNext;
            continue;
        }

        Node *temp = p;
        prev->pNext = p->pNext;
        if (first)
            this->head = prev->pNext;

        p = p->pNext;
        ++count;
        free(temp);
    }

    return count;
}

void resize(List *this, size_t count)
{
    size_t size = distance(cbegin(this), cend(this));

    if (count == size)
        return;

    else if (count < size)
    {
        reverse(this);
        for (size_t i = 0; i < count; i++)
            pop_front(this);
        reverse(this);
    }

    else
    {
        reverse(this);
        for (size_t i = 0; i < count - size; i++)
            push_front(this, 0);
        reverse(this);
    }
}

void resize_value(List *this, size_t count, int value)
{
    size_t size = distance(cbegin(this), cend(this));

    if (count == size)
        return;

    else if (count < size)
    {
        reverse(this);
        for (size_t i = 0; i < count; i++)
            pop_front(this);
        reverse(this);
    }

    else
    {
        reverse(this);
        for (size_t i = 0; i < count - size; i++)
            push_front(this, value);
        reverse(this);
    }
}

void reverse(List *this)
{
    Node *current = this->head;
    Node *prev = NULL;
    Node *next = NULL;

    while (current)
    {
        next = current->pNext;
        current->pNext = prev;
        prev = current;
        current = next;
    }

    this->head = prev;
}

void sort(List *this)
{
    if (!this->head)
        return;
    
    int *arr = to_array(this);
    size_t size = distance(cbegin(this), cend(this));
    qsort(arr, size, sizeof(*arr), &icmp);
    List *sorted = to_forward_list(arr, size);
    swap(this, sorted);
    free(arr);
    destroy_list(sorted);

    // the first iteration had this very slow bubble sort
    // if (!empty(this))
    // {
    //     int swapCounter = -1;
    //     while (swapCounter)
    //     {
    //         Node *p = this->head;
    //         swapCounter = 0;
    //         for (size_t i = 0; i < distance(cbegin(this), cend(this)) - 1; ++i)
    //         {
    //             if (p->value > p->pNext->value)
    //             {
    //                 ++swapCounter;
    //                 swap_(&p->value, &p->pNext->value);
    //             }
    //             p = p->pNext;
    //         }
    //     }
    // }
}

int is_sorted(const_iterator first, const_iterator last)
{
    if (!first.current)
        return 1; // if there is no element C++' is_sorted returns true that is why i also decided to return true bacause in a way empty list should be considered as sorted.

    int prev = first.current->value;
    const_next(&first);
    while (first.current != last.current)
    {
        if (prev > first.current->value)
            return 0;

        prev = first.current->value;
        const_next(&first);
    }
    return 1;
}

void splice_after(iterator pos, List *other)
{
    Node *current = pos.current;
    Node *next = pos.current->pNext;

    current->pNext = other->head;

    Node *p = other->head;
    while (p->pNext)
        p = p->pNext;

    p->pNext = next;

    other->head = NULL;
}

void swap(List *this, List *other)
{
    List temp;
    temp.head = this->head;

    this->head = other->head;

    other->head = temp.head;
}

void unique(List *this)
{
    Node *first = this->head;
    Node *after = this->head->pNext;

    while (after)
    {
        if (first->value != after->value)
        {
            first = first->pNext;
            after = after->pNext;
        }
        else
        {
            Node *temp = after;
            first->pNext = after->pNext;
            if (!after && after->pNext->value != first->value)
                first = after->pNext;
            after = first->pNext;
            free(temp);
        }
    }
}

// Global Functions

void advance(iterator *iter, int n)
{
    if (n < 0)
    {
        fprintf(stderr, "You cannot go backward in a singly-linked lists\n");
        exit(EXIT_FAILURE);
    }
    while (n--)
        next(iter);
}

size_t distance(const_iterator first, const_iterator last)
{
    size_t count = 0;

    while (first.current != last.current)
    {
        ++count;
        const_next(&first);
    }

    return count;
}

void next(iterator *iter)
{
    iter->current = iter->current->pNext;
}

void const_next(const_iterator *iter)
{
    iter->current = iter->current->pNext;
}

iterator find(iterator first, iterator last, int value)
{
    while (first.current != last.current)
    {
        if (first.current->value == value)
            return first;
        first.current = first.current->pNext;
    }
    return last;
}

const_iterator cfind(const_iterator first, const_iterator last, int value)
{
    while (first.current != last.current)
    {
        if (first.current->value == value)
            return first;
        first.current = first.current->pNext;
    }
    return last;
}

//  Utility Functions

void random_fill(List *this, size_t size)
{
    while (size--)
        push_front(this, rand() % 100);
}

void print_list(List *this)
{
    if (!empty(this))
    {
        for (Node *p = this->head; p != NULL; p = p->pNext)
            printf("%d -> ", (p->value));

        printf("NULL\n");
        return;
    }

    printf("NULL(Empty)\n");
}

void print_list_iterator(const_iterator first, const_iterator last)
{
    while (first.current != last.current)
    {
        printf("%d -> ", (first.current->value));
        const_next(&first);
    }
    printf("NULL\n");
}

void print_size(List *this)
{
    printf("Size: %zu\n", distance(cbegin(this), cend(this)));
}

void randomize(void)
{
    srand((unsigned)time(NULL));
}

int *to_array(List *this)
{
    size_t size = distance(cbegin(this), cend(this));
    int *arr = (int *)malloc(size * sizeof(int));
    if (!arr)
    {
        fprintf(stderr, "Allocation failed");
        exit(EXIT_FAILURE);
    }

    size_t i = 0;
    for (Node *p = this->head; p != NULL; p = p->pNext)
        arr[i++] = p->value;

    return arr;
}

List *to_forward_list(int *arr, size_t size)
{
    List *this = create_list();
    for (size_t i = size - 1; i > 0; --i)
        push_front(this, arr[i]);

    return this;
}
