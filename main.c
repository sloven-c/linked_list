#include <stdio.h>
#include <stdlib.h>

struct List {
    struct List *prev, *next;
    int value;
};

struct List *init(int value);

void add(struct List *list, int value);

void rem(struct List **list, int value_to_remove);

void print_list(const struct List *list);

int main(void) {
    struct List *seznam = init(1);
    add(seznam, 5);
    add(seznam, 2);
    print_list(seznam);

    rem(&seznam, 1);
    print_list(seznam);

    rem(&seznam, 2);
    print_list(seznam);

    rem(&seznam, 5);
    print_list(seznam);

    return 0;
}

struct List *init(const int value) {
    struct List *list = malloc(sizeof(struct List));
    list->next = nullptr;
    list->prev = nullptr;
    list->value = value;

    return list;
}

void add(struct List *list, const int value) {
    while (list->next != NULL) {
        list = list->next;
    }

    struct List *alloc_list = init(value);
    alloc_list->next = nullptr;
    alloc_list->prev = list;
    alloc_list->value = value;

    list->next = alloc_list;
}

void rem(struct List **list, const int value_to_remove) {
    struct List *first = *list;
    // we need in case first element (which caller holds is destroyed), or there are no more elements (the list is destroyed)
    struct List *it = *list;
    struct List *next;

    for (; it != NULL; it = next) {
        next = it->next;
        if (it->value != value_to_remove) continue;

        // we have to remove this element
        const bool has_prev = it->prev != NULL;
        const bool has_next = it->next != NULL;

        if (has_prev) {
            // we have an element to the left
            if (has_next) {
                // we have an element to the right
                it->prev->next = it->next;
                it->next->prev = it->prev;
            } else {
                // we don't have an element to the right
                it->prev->next = nullptr;
            }
        } else {
            // we don't have an element to the left
            // we can surmise this is the first element and caller will crash if they don't have the correct element
            if (has_next) {
                it->next->prev = nullptr;
                first = it->next;
            } else {
                first = nullptr;
            }
        }

        // free the memory taken by current element
        free(it);
    }

    *list = first;
}

void print_list(const struct List *list) {
    if (list == NULL) printf("Empty list");

    for (; list != NULL; list = list->next) {
        printf("%d ", list->value);
    }
    printf("\n");
}
