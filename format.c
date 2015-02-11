#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_list.h"

int main() {
  FILE * stream;
  FILE * output;
  char *filename = "dict.txt";
  char *outname = "sortdict.txt";
  output = fopen(outname, "w");
  char input[95];
  char inCopy[95];
  int addFlag = 1;
  int i;
  int l;

  // We make several passes through the dictionary file, each time adding all of the words
  // of length l to the word list, then we process those words and write them to the file.
  for (l = 1; l < 50; l++) {
    stream = fopen(filename, "r");

    if (stream == NULL) {
      fprintf(stderr, "Error Opening File: %s\n", filename);
      return 0;
    }
    
    WordList * wlist = wlist_create();
    while (fscanf(stream, "%s",input)!=EOF) {
      int length = strlen(input);

      for (i = 0; i < length; i++) { // Remove all capital letters from the input
	if (input[i] >= 65 && input[i] <= 90) {
	  input[i] += 32;
	}
      }

      if (length == l) {
	addFlag = strcmp(input, inCopy);
	strcpy(inCopy, input);
	if (length > 1) {

	  for (i = 0; i < length; i++) {
	    char value = input[i];
	    int space = i;

	    while (space > 0 && value < input[space - 1]) { // This sorts the input word alphabetically
	      input[space] = input[space - 1];
	      space--;
	    }
	    input[space] = value;
	  }
	}
	strcat(input, "@"); // We put the input into the form sorted version + "@" + unsorted version
	strcat(input, inCopy);
	if (addFlag) {
	  wlist_insert(wlist, input);
	}
      }
    }
    if (wlist_size(wlist)) {
      printf("Words of length %d sorted...\n", l);
      for (i = 0; i < wlist_size(wlist); i++) {
	fprintf(output, "%s\n", wlist_get_data_at(wlist, i));
      }
    }
    wlist_destroy(wlist);
  }
  printf("Finished writing\n");
  fclose(stream);
  fclose(output);
  return 0;
}
