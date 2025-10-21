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

int *get(const struct List *list, int n);

int llen(const struct List *list);

int main(void) {
    struct List *seznam = init(1);
    add(seznam, 5);
    add(seznam, 2);
    print_list(seznam);

    constexpr int n = 2;
    int *get_n = get(seznam, n);
    printf("Attempting to find %d. element => ", n);
    if (get_n == NULL) {
        // element doesn't exist
        printf("failed!");
    } else {
        printf("succeeded. Value = %d", *get_n);
        free(get_n);
    }
    printf("\n\n");

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

// we will pretend the user is not a programmer and enters n=1 for first element and so on
int *get(const struct List *list, const int n) {
    const int list_len = llen(list);
    if (n > list_len || n <= 0) return nullptr;

    for (int i = 0; i < n - 1; i++) {
        list = list->next;
    }

    int *val = malloc(sizeof(int));
    *val = list->value;
    return val;
}

int llen(const struct List *list) {
    int len = 0;

    for (; list != NULL; list = list->next) {
        len++;
    }

    return len;
}
