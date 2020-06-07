#include "binaryheap.h"
#include <assert.h>
#include <string.h>
 
node_heap *allocate_node_heap(void){
  node_heap *node = malloc(sizeof(node_heap));
  if(node ==NULL){
    perror("memory not allocated to node properly");
    exit(EXIT_FAILURE);
  }
  node->key = "";
  node->position = 0;
  return node;
} 

void initial_heap(node_heap **heap, char* sequence){
  assert(sequence != NULL);
  assert(heap != NULL);
  
  int sequence_length = strlen(sequence);
  for(int i = 1; i <= sequence_length; i++){
    node_heap *node = allocate_node_heap();
    node->key=&sequence[i-1];
    node->position  = i;
    heap[i] = node;
  }
}

void print_elem_heap(node_heap **heap, int length){
  assert(heap !=NULL);
  
  for(int i = 1; i <= length; i++){
    assert(heap[i] !=NULL);
    printf("%c ", *(heap[i])->key);
  }

  printf("\n");

  for(int i = 1; i <= length; i++){
    node_heap *node = heap[i];
    printf("%d ", node->position);
  }

  printf("\n");
}

int parent(int index){
  if(index <= 1){
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

  if(left_child(current) > heap_size ){
    return;
  }
  
  node_heap *parent = heap[current];
  node_heap *left_child_node = heap[left_child(current)];
  node_heap *right_child_node = heap[right_child(current)];
  int child_comparison = strcmp(right_child_node->key, left_child_node->key);
  if(child_comparison < 0) {
    int comparison = strcmp(left_child_node->key, parent->key);
    if(comparison > 0){
      swap(left_child_node, parent);
    }
    max_heapify(heap, parent->position, heap_size);
  } else {
    int comparison = strcmp(right_child_node->key, parent->key);
    if(comparison > 0){
      swap(right_child_node, parent);
    }
    max_heapify(heap, parent->position, heap_size);
  }
}


void build_max_heap(node_heap **heap, int heap_size){
  int last_parent_node =  heap_size/2;
  for(int i  = last_parent_node; i > 0; i--){
    max_heapify(heap, i, heap_size);
  }
}

void heapsort(node_heap **heap, int length){
  assert(heap != NULL);
  while(length > 1){
    swap(heap[1], heap[length]);
    length--;
    max_heapify(heap, 1,  length);
  }
}

void free_node(node_heap *node){
  if(node != NULL){
    free(node);
  }
}

void free_heap(node_heap **heap, int length){
  assert(heap !=NULL);
  for(int i = 1; i <= length; i++ ){
    free_node(heap[i]);
  }
  
}

