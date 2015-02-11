#include <assert.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// include header files from the dictionary and word_list
#include "dictionary.h"
#include "word_list.h"

int main()
{
   FILE * stream;
   char *words_filename = "mywords.txt";
   char *dict_filename = "sortdict.txt";

  
   /* Code used to do very basic testing of a WordList
   WordList * wlist = wlist_create();
   wlist_insert(wlist,"Hi");
   wlist_insert(wlist,"World");
   printf("WordList size is %i\n",wlist_size(wlist));
   wlist_print(wlist);
   */

   // create the dictionary from the file
   Dictionary *dict = dict_create(dict_filename);

   // open the file for anagram words
   stream = fopen(words_filename, "r");

   if(stream == NULL)
   {
	fprintf(stderr, "Error Opening File: %s\n",words_filename);
	return 0;
   }
   char input[95];
   while (fscanf(stream, "%s",input)!=EOF)
   {
	printf("%s:\n",input);
	dict_print_anagrams(dict,input);
	printf("\n");
   }
   fclose(stream);
   dict_destroy(dict);
   return 0;
}
