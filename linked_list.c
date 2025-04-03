#include "linked_list.h"
#include <stdlib.h>

struct list_node *new_node(size_t value) 
{  
  struct list_node *fresh = malloc(sizeof(struct list_node));
  if(!fresh)
  {
  return(NULL);
  }

  fresh->value = value;
  fresh->next = NULL;

  return(fresh);
}

void insert_at_head(struct linked_list *list, size_t value)  
{
  struct list_node *fresh = new_node(value);
  if(!fresh)
  {
    return;
  }

  fresh->next = list->head;
  list->head = fresh;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node *fresh = new_node(value);
  if(!fresh)
  {
    return;
  }

  if(!list->head)
  {
    list->head = fresh;
  }
  else
  {
    struct list_node *walker = list->head;
    while(walker->next)
    {
      walker = walker->next;
    }

    walker->next = fresh;
  }
        
}

size_t remove_from_head(struct linked_list *list) 
{ 
  if(!list->head)
  {
    return(0);
  }
  struct list_node *fresh = list->head;
  size_t value = fresh->value;
  list->head = fresh->next;
  free(fresh);

  return(value);
}

size_t remove_from_tail(struct linked_list *list) 
{ 
  if(!list->head)
  {
    return(0);
  }

  struct list_node *walker = list->head;
  if(!walker->next)
  {
    size_t value = walker->value;
    free(walker);
    list->head = NULL;
    return(value);
  }

  while(walker->next->next)
  {
    walker = walker->next;
  }

  value = walker->next->value;
  free(walker->next);
  walker->next = NULL;

  return(value);
}

void free_list(struct linked_list list) 
{
  struct list_node *walker = list.head;
  while(walker)
  {
    struct list_node *next = walker->next;
    free(walker);
    walker = next;
  }
  
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
