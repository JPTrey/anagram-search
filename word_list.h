#ifndef WORD_LIST_H
#define WORD_LIST_H

typedef struct WordList WordList;
typedef struct Node Node;

// Create a list of words
WordList *wlist_create();

// Insert an element (currently at the tail)
int wlist_insert(WordList *wlist, char *word);

// Get the head of the list
Node * wlist_get_head(WordList *wlist);

// Request the size of the list
int wlist_size(WordList *wlist);

// Retrieve the word at that index
char * wlist_index(WordList *wlist, int i);

// Print the words in the list
void wlist_print(WordList *wlist);

// Get a specific node
char * wlist_get_data_at(WordList *wlist, int index);

// Set a specific node
void wlist_set_data_at(WordList *wlist, int index, char *data);

// Free the nodes in the list
void wlist_destroy(WordList *wlist);

#endif // WORD_LIST_H
