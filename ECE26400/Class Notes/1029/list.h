#ifndef __LIST_H__
#define __LIST_H__

typedef struct _listnode {
   char *str;
   struct _listnode *next;
} listnode;

listnode *insert_in_front(listnode **list, char *str);

void print_list(listnode *list);

void destroy_list(listnode *list);

#endif
