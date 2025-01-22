#ifndef __LIST_H__
#define __LIST_H__

typedef struct _listnode {
   char *str;
   struct _listnode *next;
} listnode;

// list.c

listnode *insert_in_front(listnode **list, char *str);

void print_list(listnode *list);

void destroy_list(listnode *list);

// list_1.c

int search_and_delete_1(listnode **list, char *key);

int search_and_delete_2(listnode **list, char *key);

int search_and_delete_3(listnode **list, char *key);

// list_2.c

listnode *insert_in_order(listnode **list, char *str);

listnode *insert_in_reverse(listnode **list, char *str);

listnode *insert_in_order_generic(listnode **list, char *str, int (*cmp)(char const *, char const *));

// list_3.c

listnode *bubble_sort(listnode *list);

// list_4.c

void recursive_reverse_print(listnode *list);

void reverse_print(listnode *list);

#endif
