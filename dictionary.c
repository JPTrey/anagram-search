/* Dictionary.c
 *
 * Stores a dictionary and handles determining anagrams of words.
 * Author: L. Porter
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "word_list.h"

// Each dictionary node contains a word list
struct DNode{
  WordList * list;
  struct DNode * next;
};

// struct for the dictionary
struct Dictionary{
  struct DNode *head;
  struct DNode *tail;
   int size;
};

struct WordList {
  struct Node *head;
  struct Node *tail;
  int size;
};

struct Node {
  char word[95];
  struct Node *next;
};

Dictionary * dict_create(char *filename)
{
   Dictionary * retval = malloc(sizeof(Dictionary));
   DEBUGPRINTF("Creating Dictionary\n");

   FILE * stream;
   char input[95];
   int curlen = 1;
   struct DNode * cur = malloc(sizeof(DNode));
   retval->size = 1;
   cur->list = wlist_create();
   retval->head = cur;

   stream = fopen(filename, "r");
   if (stream == NULL) {
     fprintf(stderr, "Error Opening File %s\n", filename);
     return 0;
   }
   
   // Each time a new line is read, if it is the same length as the lines in the current word list,
   // it is added. If it is longer, it is the beginning of the next list. Since the dictionary is sorted by length,
   // this works out.
   while (fscanf(stream, "%s", input) != EOF) {
     if (strlen(input) > curlen) {
       curlen = strlen(input);
       DNode * new = malloc(sizeof(DNode));
       retval->size++;
       new->list = wlist_create();
       cur->next = new;
       cur = new;
     }
     wlist_insert(cur->list, input);
   }
   fclose(stream);
   printf("Dictionary filled\n");
   return retval;
}

void dict_print_anagrams(Dictionary *dict, char *word)
{
  int wordlen = strlen(word);
  if (wordlen <= dict->size) { // If the given word is longer than the longest word in the dictionary, why bother?
    int i;
    DNode * current;
    current = dict->head;
    for (i = 0; i < wordlen; i++) { // This loop sorts the input alphabetically and finds the right list to scan
      char value = word[i];
      int space = i;
      while (space > 0 && value < word[space - 1]) {
	word[space] = word[space - 1];
	space--;
      }
      word[space] = value;
      current = current->next;
    }
    Node * windex = wlist_get_head(current->list);
    while (windex) { // We scan the list of words of the right length for anagrams
      int match = 1;
      i = 0;
      int j;
      while (match) { // Here we check if the input matches the sorted part of the dictionary word
	if (windex->word[i] == '@') {
	  for (j = i+1; j < strlen(windex->word); j++) { // If it does, we print the original dictionary word
	    printf("%c", windex->word[j]);
	  }
	  printf(" ");
	  match = 0;
	} else {
	  if (word[i] != windex->word[i]) {
	    match = 0;
	  } else {
	    i++;
	  }
	}
      }
      windex = windex->next;
    }
    printf("\n");
  }
}

void dict_destroy(Dictionary *dict)
{
  struct DNode *curr1;
  struct DNode *curr2;
  if (dict->head) {
    curr1 = dict->head;
    while (curr1) {
      curr2 = curr1->next;
      free(curr1);
      curr1 = curr2;
    }
  }
  free(dict);
}
