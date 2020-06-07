#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exam.h"

/*
 * Private function prototypes.
 */

static void _print_huffman_tree(const huffman_tree_t *, int);
static void _print_huffman_tree_codes(const huffman_tree_t *, char *, char *);

/*
 * Prints the given Huffman tree.
 */
void print_huffman_tree(const huffman_tree_t *t) {
  printf("Huffman tree:\n");
  _print_huffman_tree(t, 0);
}

/*
 * Private helper function for print_huffman_tree.
 */
static void _print_huffman_tree(const huffman_tree_t *t, int level) {
  int i;
  for (i = 0; i <= level; i++) {
    printf("  ");
  }

  if (t->left == NULL && t->right == NULL) {
    printf("Leaf: '%c' with count %d\n", t->letter, t->count);
  } else {
    printf("Node: accumulated count %d\n", t->count);

    if (t->left != NULL) {
      _print_huffman_tree(t->left, level + 1);
    }

    if (t->right != NULL) {
      _print_huffman_tree(t->right, level + 1);
    }
  }
}

/*
 * Prints the codes contained in the given Huffman tree.
 */
void print_huffman_tree_codes(const huffman_tree_t *t) {
  printf("Huffman tree codes:\n");

  char *code = calloc(MAX_CODE_LENGTH, sizeof(char)), *code_position = code;
  if (code == NULL) {
    perror("calloc");
    exit(EXIT_FAILURE);
  }

  _print_huffman_tree_codes(t, code, code_position);
  free(code);
}

/*
 * Private helper function for print_huffman_tree_codes.
 */
static void _print_huffman_tree_codes(const huffman_tree_t *t,
                                      char *code, char *code_position) {

  if (t->left == NULL && t->right == NULL) {
    printf("'%c' has code \"%s\"\n", t->letter, code);
  } else if (t->left != NULL) {
    *code_position++ = 'L';
    *code_position = '\0';

    _print_huffman_tree_codes(t->left, code, code_position--);
  }

  if (t->right != NULL) {
    *code_position++ = 'R';
    *code_position = '\0';

    _print_huffman_tree_codes(t->right, code, code_position--);
  }
}

/*
 * Prints a list of Huffman trees.
 */
void print_huffman_tree_list(const huffman_tree_list_t *l) {
  printf("Huffman tree list:\n");

  for (; l != NULL; l = l->next) {
    print_huffman_tree(l->tree);
  }
}

/*
 * Frees a Huffman tree.
 */
void huffman_tree_free(huffman_tree_t *t) {
  if (t != NULL) {
    huffman_tree_free(t->left);
    huffman_tree_free(t->right);
    free(t);
  }
}

/*
 * Frees a list of Huffman trees.
 */
void huffman_tree_list_free(huffman_tree_list_t *l) {
  if (l != NULL) {
    huffman_tree_list_free(l->next);
    huffman_tree_free(l->tree);
    free(l);
  }
}

/*
 * Returns 1 if the string s contains the character c and 0 if it does not.
 */
int contains(char *s, char c) {
  assert(s != NULL);
  for(int i = 0 ; i < strlen(s); i++){
    if(s[i] == c){
      return 1;
    }
  }
  return 0;
}

/*
 * Returns the number of occurrences of c in s.
 */
int frequency(char *s, char c) {
  assert(s!=NULL);
  int frequency = 0;
  for(int i =0; i< strlen(s); i++){
    if (s[i] == c){
      frequency++;
    }
  }
  return frequency;
}

/*
 * Takes a string s and returns a new heap-allocated string containing only the
 * unique characters of s.
 *
 * Pre: all strings will have fewer than or equal to MAX_STRING_LENGTH - 1
 *      characters.
 */
char *nub(char *s) {
  char *unique_letters = malloc((MAX_STRING_LENGTH -1) * sizeof(char));
  for(int i = 0; i < strlen(s); i++){
    // checks if letter is already within unique letters
    // in which case it isn't unqiue and isnt appended
    if(!contains(unique_letters,s[i])){
      unique_letters[strlen(unique_letters)] = s[i];
    }
  }
  return unique_letters;
  
}

/*
 * Adds the Huffman tree t to the list l, returning a pointer to the new list.
 *
 * Pre:   The list l is sorted according to the frequency counts of the trees
 *        it contains.
 *
 * Post:  The list l is sorted according to the frequency counts of the trees
 *        it contains.
 */
huffman_tree_list_t *huffman_tree_list_add(huffman_tree_list_t *l,
                                            huffman_tree_t *t) {

  assert( t != NULL);
  //is pre condition is met then the list is already ordered (ascending)
  // check if at the end of the list
  if (l == NULL){
    huffman_tree_list_t *new_list = malloc(sizeof(huffman_tree_list_t));
    if(new_list ==NULL){
      perror("no memory allocated to new list");
      exit(EXIT_SUCCESS);
    }
    new_list->tree = t;
    new_list->next = NULL;
    return new_list;
  }
  // tree to be inserted after
  else if(t->count > l->tree->count){
    l->next = huffman_tree_list_add(l->next, t);
    return l;
  }
  else {
    huffman_tree_list_t *new_list = malloc(sizeof(huffman_tree_list_t));
    if(new_list ==NULL){
      perror("no memory allocated to new list");
      exit(EXIT_FAILURE);
    }
    new_list->tree = t;
    new_list->next = l;
    return new_list;
  }
}

/*
 * Takes a string s and a lookup table and builds a list of Huffman trees
 * containing leaf nodes for the characters contained in the lookup table. The
 * leaf nodes' frequency counts are derived from the string s.
 *
 * Pre:   t is a duplicate-free version of s.
 *
 * Post:  The resulting list is sorted according to the frequency counts of the
 *        trees it contains.
 */
huffman_tree_list_t *huffman_tree_list_build(char *s, char *t) {
  // checking if anymore leaf nodes to add to list:
  assert(s != NULL);
  assert(t != NULL);
  
  huffman_tree_list_t *list= NULL;

  for(int i = 0; i <strlen(t); i++){
    char current_letter = t[i];
    huffman_tree_t *tree = malloc(sizeof(huffman_tree_t));
    if(tree== NULL){
      perror("no memory allocated to leaf node");
      exit(EXIT_FAILURE);
    }
    tree->count = frequency(s, current_letter);
    tree->letter= current_letter;
    tree->right = NULL;
    tree->left  = NULL;
    list = huffman_tree_list_add(list, tree);
  }
  return list;
}

/*
 * Reduces a sorted list of Huffman trees to a single element.
 *
 * Pre:   The list l is non-empty and sorted according to the frequency counts
 *        of the trees it contains.
 *
 * Post:  The resuling list contains a single, correctly-formed Huffman tree.
 */
huffman_tree_list_t *huffman_tree_list_reduce(huffman_tree_list_t *l) {
  assert(l != NULL);
  if (l->next == NULL){
    return l;
  }
  huffman_tree_t *first = l->tree;
  huffman_tree_t *second = l->next->tree;
  huffman_tree_t *new_tree = malloc(sizeof(huffman_tree_t));
  if (new_tree == NULL){
    perror("memory not allocated to list");
    exit(EXIT_FAILURE);
  }
  new_tree->count = first->count + second->count;
  new_tree->left = first;
  new_tree->right = second;
  huffman_tree_list_t *list = l->next->next;
  list = huffman_tree_list_add(list, new_tree);
  free(l->next);
  free(l);
  
  return huffman_tree_list_reduce(list);
}

/*
 * Accepts a Huffman tree t and a string s and returns a new heap-allocated
 * string containing the encoding of s as per the tree t.
 *
 * Pre: s only contains characters present in the tree t.
 */
char *huffman_tree_encode(huffman_tree_t *t, char *s) {
  return NULL;
}

/*
 * Accepts a Huffman tree t and an encoded string and returns a new
 * heap-allocated string contained the decoding of the code as per the tree t.
 *
 * Pre: the code given is decodable using the supplied tree t.
 */
char *huffman_tree_decode(huffman_tree_t *t, char *code) {
  return NULL;
}
