#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// by including your own header, you automatically include function
// prototypes
#include "word_list.h"

// struct which makes up each node in the list
struct Node{
   char word[95];
   struct Node *next;
}; 

// struct to manage a basic linked list
struct WordList{
   struct Node *head;
   struct Node *tail;
   int size;
};

WordList * wlist_create()
{
   WordList * retval = malloc(sizeof(WordList));
   retval->head = 0;
   retval->tail = 0;
   retval->size = 0;
   return retval;
}

int wlist_insert(WordList *wlist, char * word)
{
   struct Node *current = malloc(sizeof(Node));
   current->next = 0;
   strcpy(current->word,word);
   if(wlist->head == 0)
   {
	wlist->head = current;
	wlist->tail = current;
   }
   else
   {
	//Node *end = wlist->tail;
	wlist->tail->next = current;
	wlist->tail = current; 
   }
   wlist->size++;
   return 1;
}

Node * wlist_get_head(WordList *wlist) {
  if (wlist == 0) {
    return 0;
  } else {
    return wlist->head;
  }
}

int wlist_size(WordList *wlist)
{
	if(wlist == 0)  // testing for null pointer
	{
		return -1;
	}
	else
	{
		return wlist->size;
	}
}

void wlist_print(WordList *wlist)
{
   struct Node *current;
   if(wlist->head) // same as testing if != 0
   {
	current = wlist->head;
	while(current)
	{
	   printf("%s\t",current->word);
	   current = current->next;
	}
	printf("\n");
   }
}

// Gets the string value at a given index of the list
char * wlist_get_data_at(WordList *wlist, int index)
{
  struct Node *current;
  if (wlist->size > index) {
    current = wlist->head;
    int i;
    for (i = 0; i < index; i++) {
      current = current->next;
    }
    return current->word;
  } else {
    return 0;
  }
}

// Sets the string value at a given index of the list
void wlist_set_data_at(WordList *wlist, int index, char *data)
{
  struct Node *current;
  if (wlist->size > index) {
    current = wlist->head;
    int i;
    for (i = 0; i < index; i++) {
      current = current->next;
    }
    strcpy(current->word, data);
  }
}

void wlist_destroy(WordList *wlist)
{
  struct Node *curr1;
  struct Node *curr2;
  if (wlist->head) {
    curr1 = wlist->head;
    while(curr1) {
      curr2 = curr1->next;
      free(curr1);
      curr1 = curr2;
    }
  }
  free(wlist);
}
