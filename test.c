#include "forward_list.h"
#include "test-framework/unity.h"
#include <stdlib.h>

#define SIZE 10

void setUp(void) {}

void tearDown(void) {}

static void test_create_list(void)
{
    List *list = create_list();

    TEST_ASSERT(list != NULL);

    destroy_list(list);
}

static void test_assign_to_an_empty_list(void)
{
    List *list = create_list();

    assign(list, SIZE, 69);

    TEST_ASSERT(SIZE == distance(cbegin(list), cend(list)));

    destroy_list(list);
}

static void test_assign_to_a_non_empty_list(void)
{
    List *list = create_list();

    push_front(list, 420);
    push_front(list, 420);
    push_front(list, 420);
    push_front(list, 420);
    push_front(list, 420);

    assign(list, SIZE, 69);

    TEST_ASSERT(SIZE == distance(cbegin(list), cend(list)));

    destroy_list(list);
}

static void test_clear_list_when_empty(void)
{
    List *list = create_list();
    clear(list);
    TEST_ASSERT_NULL(list->head);
    destroy_list(list);
}

static void test_clear_list_when_not_empty(void)
{
    List *list = create_list();
    push_front(list, 420);
    push_front(list, 420);
    push_front(list, 420);
    push_front(list, 420);
    push_front(list, 420);
    clear(list);
    TEST_ASSERT_NULL(list->head);
    destroy_list(list);
}

static void test_list_if_empty(void)
{
    List *list = create_list();

    TEST_ASSERT_TRUE(empty(list));
    destroy_list(list);
}

static void test_list_if_not_empty(void)
{
    List *list = create_list();
    push_front(list, 69);
    TEST_ASSERT_FALSE(empty(list));
    destroy_list(list);
}

static void test_if_front_equal_to_first(void)
{
    List *list = create_list();
    random_fill(list, 10);
    TEST_ASSERT(*front(list) == list->head->value);
    destroy_list(list);
}

static void test_begin_iterator(void)
{
    List *list = create_list();
    random_fill(list, 10);
    iterator beg = begin(list);
    TEST_ASSERT(beg.current->value == *front(list));
    destroy_list(list);
}

static void test_next_iterator(void)
{
    List *list = create_list();
    random_fill(list, 10);
    iterator beg = begin(list);
    next(&beg);
    TEST_ASSERT(beg.current->value == list->head->pNext->value);
    destroy_list(list);
}

static void test_insert_after(void)
{
    List *list = create_list();
    random_fill(list, 10);
    iterator beg = begin(list);

    beg = insert_after(beg, 69);

    TEST_ASSERT(beg.current->value == 69);
    destroy_list(list);
}

static void test_erase_after(void)
{
    List *list = create_list();
    random_fill(list, 10);
    iterator beg = begin(list);
    int temp = beg.current->pNext->pNext->value;
    beg = erase_after(beg);

    TEST_ASSERT(beg.current->value == temp);
    destroy_list(list);
}

static void test_merge_two_sorted_lists(void)
{
    List *list1 = create_list();
    List *list2 = create_list();

    randomize();

    random_fill(list1, rand() % 10);
    sort(list1);
    size_t list1_size = distance(cbegin(list1), cend(list1));

    random_fill(list2, rand() % 15);
    sort(list2);
    size_t list2_size = distance(cbegin(list2), cend(list2));

    merge(list1, list2);

    TEST_ASSERT_NULL(list2->head); // Empty list2

    TEST_ASSERT(distance(cbegin(list1), cend(list1)) == list1_size + list2_size); // New list1 size = old list1 + old list2

    destroy_list(list1);
    destroy_list(list2);
}

static void test_pop_front(void)
{
    size_t size = 10;
    List *list = create_list();

    assign(list, size, 69);

    pop_front(list);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == size - 1);

    destroy_list(list);
}

static void test_push_front_when_list_empty(void)
{
    List *list = create_list();

    push_front(list, 420);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == 1);

    destroy_list(list);
}

static void test_push_front_when_list_not_empty(void)
{
    List *list = create_list();

    size_t size = 10;

    assign(list, size, 69);

    int val = -1;

    push_front(list, val);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == size + 1);
    TEST_ASSERT(*front(list) == val);

    destroy_list(list);
}

static void test_remove(void)
{
    List *list = create_list();

    size_t size = 10;

    for (size_t i = 0; i < size; ++i)
        push_front(list, i % 2 ? 69 : 420);

    int removed = remove_(list, 420);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == size - removed);

    destroy_list(list);
}

static int unPred(const int *value)
{
    return *value % 5 == 0;
}

static void test_remove_if(void)
{
    List *list = create_list();

    size_t size = 20;

    for (size_t i = 0; i < size; ++i)
        push_front(list, i);

    int removed = remove_if(list, unPred);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == size - removed);

    destroy_list(list);
}

static void test_resize_empty_list(void)
{
    List *list = create_list();

    size_t count = 10;

    resize(list, count);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == count);

    destroy_list(list);
}

static void test_resize_non_empty_list_with_new_size_greater(void)
{
    List *list = create_list();

    size_t size = 5;
    assign(list, size, 69);

    size_t count = 10;

    resize(list, count);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == count);

    iterator iter = begin(list);

    advance(&iter, (int)size);

    TEST_ASSERT(iter.current->value == 0);

    destroy_list(list);
}

static void test_resize_with_value_non_empty_list_with_new_size_greater(void)
{
    List *list = create_list();

    size_t size = 5;
    assign(list, size, 69);

    size_t count = 10;

    resize_value(list, count, 420);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == count);

    iterator iter = begin(list);

    advance(&iter, (int)size);

    TEST_ASSERT(iter.current->value == 420);

    destroy_list(list);
}

static void test_resize_non_empty_list_with_new_size_less(void)
{
    List *list = create_list();

    size_t size = 10;
    assign(list, size, 69);

    size_t count = 5;

    resize(list, count);

    TEST_ASSERT(distance(cbegin(list), cend(list)) == count);

    destroy_list(list);
}

static void test_is_sorted_false(void)
{
    List *list = create_list();

    push_front(list, 1);
    push_front(list, 2);
    push_front(list, 3);
    push_front(list, 4);
    push_front(list, 5);

    TEST_ASSERT_FALSE(is_sorted(cbegin(list), cend(list)));

    destroy_list(list);
}

static void test_is_sorted_true(void)
{
    List *list = create_list();

    push_front(list, 5);
    push_front(list, 4);
    push_front(list, 3);
    push_front(list, 2);
    push_front(list, 1);

    TEST_ASSERT_TRUE(is_sorted(cbegin(list), cend(list)));

    destroy_list(list);
}

static void test_is_sorted_for_empty_list(void)
{
    List *list = create_list();

    TEST_ASSERT_TRUE(is_sorted(cbegin(list), cend(list)));

    destroy_list(list);
}

static void test_is_sorted(void)
{
    List *list = create_list();

    random_fill(list, 100);

    sort(list);

    TEST_ASSERT_TRUE(is_sorted(cbegin(list), cend(list)));

    destroy_list(list);
}

static void test_splice_after(void)
{
    List *list1 = create_list();
    List *list2 = create_list();

    randomize();

    random_fill(list1, rand() % 5 + 1);
    size_t list1_size = distance(cbegin(list1), cend(list1));

    random_fill(list2, rand() % 10 + 1);
    size_t list2_size = distance(cbegin(list2), cend(list2));

    iterator beg = begin(list1);

    size_t random_advance = rand() % list1_size;

    // Advances list1's begin iterator randomly between 0 and list1_size.
    advance(&beg, random_advance);

    splice_after(beg, list2);

    // Checks new size of list1 to be equal list1_size + list2_size
    TEST_ASSERT(distance(cbegin(list1), cend(list1)) == list1_size + list2_size);

    // Checks if list2 cleared.
    TEST_ASSERT_NULL(list2->head);

    destroy_list(list1);
    destroy_list(list2);
}

static void test_find_not_found(void)
{
    List *list = create_list();

    int searched = -1;

    push_front(list, 5);
    push_front(list, 4);
    push_front(list, 3);
    push_front(list, 2);
    push_front(list, 1);

    TEST_ASSERT_NULL(find(begin(list), end(list), searched).current);

    destroy_list(list);
}

static void test_find_found(void)
{
    List *list = create_list();

    int searched = 3;

    push_front(list, 5);
    push_front(list, 4);
    push_front(list, 3);
    push_front(list, 2);
    push_front(list, 1);

    TEST_ASSERT_TRUE(find(begin(list), end(list), searched).current->value == searched);

    destroy_list(list);
}

int main(void)
{
    UnityBegin("test.c");

    RUN_TEST(test_create_list);
    RUN_TEST(test_assign_to_an_empty_list);
    RUN_TEST(test_assign_to_a_non_empty_list);
    RUN_TEST(test_clear_list_when_empty);
    RUN_TEST(test_clear_list_when_not_empty);
    RUN_TEST(test_list_if_empty);
    RUN_TEST(test_list_if_not_empty);
    RUN_TEST(test_if_front_equal_to_first);
    RUN_TEST(test_begin_iterator);
    RUN_TEST(test_next_iterator);
    RUN_TEST(test_insert_after);
    RUN_TEST(test_erase_after);
    RUN_TEST(test_merge_two_sorted_lists);
    RUN_TEST(test_pop_front);
    RUN_TEST(test_push_front_when_list_empty);
    RUN_TEST(test_push_front_when_list_not_empty);
    RUN_TEST(test_remove);
    RUN_TEST(test_remove_if);
    RUN_TEST(test_resize_empty_list);
    RUN_TEST(test_resize_non_empty_list_with_new_size_greater);
    RUN_TEST(test_resize_with_value_non_empty_list_with_new_size_greater);
    RUN_TEST(test_resize_non_empty_list_with_new_size_less);
    RUN_TEST(test_is_sorted_false);
    RUN_TEST(test_is_sorted_true);
    RUN_TEST(test_is_sorted_for_empty_list);
    RUN_TEST(test_is_sorted);
    RUN_TEST(test_splice_after);
    RUN_TEST(test_find_not_found);
    RUN_TEST(test_find_found);

    return UnityEnd();
}
