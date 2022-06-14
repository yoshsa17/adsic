#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct node BstNode;
struct node {
  int data;
  BstNode *left;
  BstNode *right;
};

BstNode *bst_create_new_node(int data);
BstNode *bst_insert(BstNode *root, int data);
bool bst_search(BstNode *root, int data);
BstNode *bst_find_node(BstNode *root, int data);
BstNode *bst_get_min(BstNode *root);
int bst_get_height(BstNode *root);
void bst_print_value(BstNode *root);
bool bst_get_is_bst(BstNode *root);
BstNode *bst_delete_value(BstNode *root, int data);

void run_all_tests();
void test_insert();
void test_search();
void test_get_min();
void test_get_height();
void test_get_is_bst();
void test_delete_value();

// Main

int main() {
  run_all_tests();
  return 0;
}

// Functions

BstNode *bst_create_new_node(int data) {
  BstNode *new_node = calloc(1, sizeof(BstNode));
  new_node->data = data;
  new_node->left = new_node->right = NULL;
  return new_node;
}

void bst_destroy_tree(BstNode *root) {
  if (root == NULL) return;

  bst_destroy_tree(root->left);
  bst_destroy_tree(root->right);
  free(root);
}

BstNode *bst_insert(BstNode *root, int data) {
  if (root == NULL) {
    root = bst_create_new_node(data);
  } else if (data <= root->data) {
    root->left = bst_insert(root->left, data);
  } else {
    root->right = bst_insert(root->right, data);
  }

  return root;
}

bool bst_search(BstNode *root, int data) {
  if (root == NULL)
    return false;
  else if (root->data == data)
    return true;
  else if (data <= root->data)
    return bst_search(root->left, data);
  else
    return bst_search(root->right, data);
}

BstNode *bst_find_node(BstNode *root, int data) {
  if (root == NULL) {
    printf("Error: tree is empty");
    exit(EXIT_FAILURE);
  } else if (data < root->data) {
    root->left = bst_delete_value(root->left, data);
  } else if (data > root->data) {
    root->right = bst_delete_value(root->right, data);
  } else {
    return root;
  }
}

BstNode *bst_get_min(BstNode *root) {
  if (root == NULL) {
    printf("Error: Tree is empty\n");
    exit(EXIT_FAILURE);
  } else if (root->left == NULL) {
    return root;
  }
  return bst_get_min(root->left);
}

int bst_get_height(BstNode *root) {
  if (root == NULL) return -1;
  // + 1 is for root height
  return MAX(bst_get_height(root->left), bst_get_height(root->right)) + 1;
}

// print values with Depth-first traversal (In-order)
void bst_print_value(BstNode *root) {
  if (root == NULL) {
    return;
  }

  bst_print_value(root->left);
  printf("%d\n", root->data);
  bst_print_value(root->right);
}

bool is_between(BstNode *root, int minValue, int maxValue) {
  if (root == NULL) return true;

  return root->data > minValue && root->data < maxValue &&
         is_between(root->left, minValue, root->data) &&
         is_between(root->right, root->data, maxValue);
}

bool bst_get_is_bst(BstNode *root) {
  if (root == NULL) return true;

  return is_between(root, INT_MIN, INT_MAX);
}

BstNode *bst_delete_value(BstNode *root, int data) {
  if (root == NULL) {
    return root;
  } else if (data < root->data) {
    root->left = bst_delete_value(root->left, data);
  } else if (data > root->data) {
    root->right = bst_delete_value(root->right, data);
  } else {
    // Case 1: No child : delete the node
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    }

    // Case 2: 1 child : delete the node and connect the parent and the child
    else if (root->left == NULL) {
      BstNode *temp = root;
      root = root->right;
      free(temp);
    } else if (root->right == NULL) {
      BstNode *temp = root;
      root = root->left;
      free(temp);
    }

    // Case 3: 2 children : 1. find min in right or find max in left
    //                      2. copy the value
    //                      3. delete duplicate
    else {
      BstNode *temp = bst_get_min(root->right);
      root->data = temp->data;
      root->right = bst_delete_value(root->right, temp->data);
    }
  }
  return root;
}

BstNode *bst_get_successor(BstNode *root, int data) {
  BstNode *cur = bst_find_node(root, data);
  if (cur == NULL) {
    return NULL;
  }

  // Case 1: Node has right subtree
  if (cur->right != NULL) {
    return bst_get_min(cur->right);
  }

  // Case 2: No right subtree
  else {
    BstNode *successor = NULL;
    BstNode *ancestor = root;
    while (ancestor != cur) {
      if (cur->data < ancestor->data) {
        successor = ancestor;
        ancestor - ancestor->left;
      } else {
        ancestor = ancestor->right;
      }
    }
  }
}

// Functions

void run_all_tests() {
  test_insert();
  test_search();
  test_get_min();
  test_get_height();
  test_get_is_bst();
  test_delete_value();
  printf("OK\n");
}

BstNode *create_tree() {
  BstNode *root = NULL;
  root = bst_insert(root, 30);
  root = bst_insert(root, 10);  // min
  root = bst_insert(root, 50);
  root = bst_insert(root, 232);  // max
  root = bst_insert(root, 40);
  root = bst_insert(root, 20);
  root = bst_insert(root, 32);
  return root;
}

void test_insert() {
  BstNode *root = create_tree();
  // bst_print_value(root);
  bst_destroy_tree(root);
}

void test_search() {
  BstNode *root = create_tree();
  assert(bst_search(root, 50) == true);
  assert(bst_search(root, 11) == false);
  bst_destroy_tree(root);
}

void test_get_min() {
  BstNode *root = create_tree();
  assert(bst_get_min(root)->data == 10);
  bst_destroy_tree(root);
}

void test_get_height() {
  BstNode *root = create_tree();
  // printf("Height: %d\n", bst_get_height(root));
  assert(bst_get_height(root) == 3);
  bst_destroy_tree(root);
}

void test_get_is_bst() {
  BstNode *root = create_tree();
  assert(bst_get_is_bst(root) == true);
  bst_destroy_tree(root);
}

void test_delete_value() {
  BstNode *root = create_tree();
  // bst_print_value(root);
  // printf("-----------\n");
  bst_delete_value(root, 20);
  // bst_print_value(root);
  bst_destroy_tree(root);
}