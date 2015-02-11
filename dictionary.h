#ifndef DICTIONARY_H
#define DICTIONARY_H

// Macro.  if(1) disables printing, if(0) turns it on.
#define DEBUGPRINTF if(1){}else printf

typedef struct Dictionary Dictionary;
typedef struct DNode DNode;

// Create your dictionary struct using the filename of a dictionary
Dictionary * dict_create(char *filename);

// key method for the project.  Provide the method with
// a dictionary and a word and it will output all the anagrams
// of the word (including the word, assuming it is in the dictionary)
void dict_print_anagrams(Dictionary * dict, char *word);

// Function to clean up the data structure, free pointers, etc.
// Optional but good coding practice
void dict_destroy();

#endif // DICTIONARY_H
