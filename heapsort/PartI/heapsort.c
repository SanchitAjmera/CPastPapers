#include "binaryheap.h"
#include <string.h>
#include <assert.h>
#define MAX_STRING_LENGTH (20)

int main(int argc, char **argv){

  if(argc != 1){
    perror("invalid number of arguments given to program");
    exit(EXIT_FAILURE);
  }
  
  //char *input = argv[1];
  char *input = "SANCHIT";
  int length = strlen(input);
  printf("%s\n", input);
  assert(length <= MAX_STRING_LENGTH);

  node_heap *heap[MAX_STRING_LENGTH+1];
  
  initial_heap(heap, input);
  print_elem_heap(heap, length);

  free_heap(heap, length);
}
