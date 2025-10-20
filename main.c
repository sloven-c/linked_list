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
    // we need to track it so the caller knows which element is first
    struct List *first = *list;
    // next element to check for removal
    struct List *next;

    for (struct List *it = *list; it != NULL; it = next) {
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
            if (has_next) {
                it->next->prev = nullptr;
                first = it->next; // track the first element for caller
            } else {
                first = nullptr; // no elements left
            }
        }

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
