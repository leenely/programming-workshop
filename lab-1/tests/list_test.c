#include "../list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_init_single_list() {
    single_list list;
    init_single_list(&list);

    assert(list.head == NULL);
    assert(list.tail == NULL);
    printf("test_init_single_list passed!\n");
}


void test_add_to_beginning() {
    single_list list;
    init_single_list(&list);

    add_to_beginning(&list, 10);
    assert(list.head->item == 10);
    assert(list.tail->item == 10);

    add_to_beginning(&list, 20);
    assert(list.head->item == 20);
    assert(list.tail->item == 10);

    printf("test_add_to_beginning passed!\n");
}


void test_add_to_end() {
    single_list list;
    init_single_list(&list);

    add_to_end(&list, 10);
    assert(list.head->item == 10);
    assert(list.tail->item == 10);

    add_to_end(&list, 20);
    assert(list.head->item == 10);
    assert(list.tail->item == 20);

    printf("test_add_to_end passed!\n");
}


void test_add_to_middle() {
    single_list list;
    init_single_list(&list);

    add_to_end(&list, 10);
    add_to_end(&list, 20);
    add_to_end(&list, 30);

    add_to_middle(&list, 1, 15);
    assert(find_element(&list, 1) == 15);
    assert(find_element(&list, 2) == 20);

    printf("test_add_to_middle passed!\n");
}


void test_find_element() {
    single_list list;
    init_single_list(&list);

    add_to_end(&list, 10);
    add_to_end(&list, 20);
    add_to_end(&list, 30);

    assert(find_element(&list, 0) == 10);
    assert(find_element(&list, 1) == 20);
    assert(find_element(&list, 2) == 30);

    printf("test_find_element passed!\n");
}


void test_delete_last() {
    single_list list;
    init_single_list(&list);

    add_to_end(&list, 10);
    add_to_end(&list, 20);
    add_to_end(&list, 30);

    delete_last(&list);
    assert(list.tail->item == 20);

    delete_last(&list);
    assert(list.tail->item == 10);

    delete_last(&list);
    assert(list.head == NULL);
    assert(list.tail == NULL);

    printf("test_delete_last passed!\n");
}


void test_count_elements() {
    single_list list;
    init_single_list(&list);

    assert(count_elements(&list) == 0);

    add_to_end(&list, 10);
    add_to_end(&list, 20);
    add_to_end(&list, 30);

    assert(count_elements(&list) == 3);

    delete_last(&list);
    assert(count_elements(&list) == 2);

    printf("test_count_elements passed!\n");
}


int main() {
    printf("------------ list tests -----------\n");
    test_init_single_list();
    test_add_to_beginning();
    test_add_to_end();
    test_add_to_middle();
    test_find_element();
    test_delete_last();
    test_count_elements();
    printf("-------- All tests passed! ---------\n");
    return 0;
}
