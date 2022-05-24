#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node BstNode;
struct node {
  int data;
  BstNode *left;
  BstNode *right;
};

BstNode *bst_create_new_node(int data);
BstNode *bst_insert(BstNode *root, int data);
bool bst_search(BstNode *root, int data);

////// Main

int main() {
  BstNode *root = NULL;
  root = bst_insert(root, 100);
  return 0;
}

////// Functions

BstNode *bst_create_new_node(int data) {
  BstNode *new_node = calloc(1, sizeof(BstNode));
  new_node->data = data;
  new_node->left = new_node->right = NULL;
  return new_node;
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
    printf("ERROR: tree is empty");
    exit(EXIT_FAILURE);
  } else if (data < root->data) {
    root->left = bst_delete_value(root->left, data);
  } else if (data > root->data) {
    root->right = bst_delete_value(root->right, data);
  } else {
    return root;
  }
}

int bst_find_min(BstNode *root) {
  if (root == NULL) {
    printf("Error: Tree is empty\n");
    return -1;
  } else if (root->left == NULL) {
    return root->data;
  }
  return bst_find_min(root->left);
}

int bst_find_height(BstNode *root) {
  if (root == NULL) return -1;
  // + 1 is for root height
  return max(bst_find_height(root->left), bst_find_height(root->right)) + 1;
}

bool bst_get_is_bst(BstNode *root, int minValue, int maxValue) {
  if (root == NULL) return true;

  if (root->data < minValue && root->data > maxValue &&
      bst_get_is_bst(root->left, minValue, root->data) &&
      bst_get_is_bst(root->right, root->data, maxValue)) {
    return true;
  } else {
    return false;
  }
}

BstNode *bst_delete_value(BstNode *root, int data) {
  if (root == NULL) {
    return root;
  } else if (data < root->data) {
    root->left = bst_delete_value(root->left, data);
  } else if (data > root->data) {
    root->right = bst_delete_value(root->right, data);
  } else {
    // Case 1: No child
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    }

    // Case 2: 1 child
    else if (root->left == NULL) {
      BstNode *temp = root;
      root = root->right;
      free(temp);
    } else if (root->right == NULL) {
      BstNode *temp = root;
      root = root->left;
      free(temp);
    }

    // Case 3: 2 children
    else {
      BstNode *temp = bst_find_min(root->right);
      root->data = temp->data;
      root->right = bst_delete_value(root->right, temp->data);
    }
  }
  return root;
}

void bst_print_value(BstNode *root) {
  if (root == NULL) {
    return;
  }

  bst_print_value(root->left);
  printf("%d\n", root->data);
  bst_print_value(root->right);
}

BstNode *bst_get_successor(BstNode *root, int data) {
  BstNode *cur = bst_find_node(root, data);
  if (cur == NULL) {
    return NULL;
  }

  // Case 1: Node has right subtree
  if (cur->right != NULL) {
    return bst_find_min(cur->right);
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
