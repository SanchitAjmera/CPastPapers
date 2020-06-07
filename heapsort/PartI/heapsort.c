#include "binaryheap.h"
#include <assert.h>
#include <string.h>


node_heap *allocate_node_heap(void){
  node_heap *node = calloc(1, sizeof(node));
  return node;
}

void intial_heap(node_heap **heap, char* sequence){
  assert(sequence != NULL);

  assert(heap != NULL);
  
  int sequence_length = (int) strlen(sequence);
  
  for(int i = 0; i < sequence_length; i++){
    node_heap *node = allocate_node_heap();
    heap[i] = node;
    node->key = sequence;
    sequence++;
    node->position  = i;
  }
}

void print_elem_heap(node_heap **heap, int length){
  assert(heap !=NULL);
  
  for(int i = 0; i < length; i++){
    node_heap *node = heap[i];
    printf("%s ", node->key);
  }

  printf("\n");

  for(int i = 0; i < length; i++){
    node_heap *node = heap[i];
    printf("%d ", node->position);
  }

  printf("\n");
}

int parent(int index){
  if(index == 1 || index <= 0){
    perror("no parent of root or invalid index given");
    exit(EXIT_FAILURE);
  }
  return index/2;
}

int left_child(int index){
  if(index <1){
    perror("invalid index given");
    exit(EXIT_FAILURE);
  }

  return index *2;
}

int right_child(int index){
  if(index <1){
    perror("invalid index given");
    exit(EXIT_FAILURE);
  }

  return (index *2)+1;
}

void swap(node_heap *node1, node_heap *node2){
  char *key1 = node1->key;
  int position1 = node1->position;

  node1->key = node2->key;
  node1->position = node2->position;

  node2->key = key1;
  node2->position = position1;
}

void max_heapify(node_heap **heap, int current, int heap_size){
  if (current < 1){
    perror("invalid current position");
    exit(EXIT_FAILURE);
  }  
  
  node_heap *parent = heap[current];
  
  if( heap_size < left_child(current)){
    return;
  }
 
  node_heap *left_child_node = heap[left_child(current)];
  
  if( heap_size < right_child(current)){
    //only has left child so only one comparision needed
    int comparison = strcmp(parent->key, left_child_node->key);
    if(comparison < 0 ){
      swap(parent, left_child_node);
    } else{
      return;
    }
  }
  else {
    node_heap *right_child_node = heap[right_child(current)];
    int comparison_children = strcmp(right_child_node, left_child_node);
    node_heap *largest_node;
    (comparison_children < 0) ? largest_node = left_child_node : right_child_node;
    int comparison = strcmp(largest_node, parent);
    if(comparison <= 0) {
      return;
    }
    swap(largest_node, parent);
    max_heapify(heap, largest_node->position, heap_size);
  }
}

int main(int argc, char **argv){
    
 //TO DO
 return EXIT_SUCCESS;
}
