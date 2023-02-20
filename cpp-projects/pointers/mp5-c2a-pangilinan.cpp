#include <iostream>
using namespace std;

struct node {
  int key;
  struct node *left, *right;
};

// A utility function to create a new BST node
struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

void printBT(const std::string &prefix, const node *node, bool isLeft) {
  if (node != nullptr) {
    std::cout << prefix;

    std::cout << (isLeft ? "|--" : "L--");

    // print the value of the node
    std::cout << node->key << std::endl;

    // enter the next tree level - left and right branch
    printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
    printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
  }
}

void printBT(const node *node) { printBT("", node, false); }

/* A utility function to
insert a new node with given key in
 * BST */
struct node *insert(struct node *node, int key) {
  /* If the tree is empty, return a new node */
  if (node == NULL)
    return newNode(key);

  /* Otherwise, recur down the tree */
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  /* return the (unchanged) node pointer */
  return node;
}

/* Given a non-empty binary search tree, return the node
with minimum key value found in that tree. Note that the
entire tree does not need to be searched. */
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  /* loop down to find the leftmost leaf */
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

/* Given a binary search tree and a key, this function
deletes the key and returns the new root */
struct node *deleteNode(struct node *root, int key) {
  // base case
  if (root == NULL)
    return root;

  // If the key to be deleted is
  // smaller than the root's
  // key, then it lies in left subtree
  if (key < root->key)
    root->left = deleteNode(root->left, key);

  // If the key to be deleted is
  // greater than the root's
  // key, then it lies in right subtree
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  // if key is same as root's key, then This is the node
  // to be deleted
  else {
    // node with only one child or no child
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // node with two children: Get the inorder successor
    // (smallest in the right subtree)
    struct node *temp = minValueNode(root->right);

    // Copy the inorder successor's content to this node
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// C function to search a given key in a given BST

// Driver Code
int main() {
  struct node *root = NULL;
  root = insert(root, 78);
  root = insert(root, 85);
  root = insert(root, 12);
  root = insert(root, 45);
  root = insert(root, 57);
  root = insert(root, 23);
  root = insert(root, 90);
  root = insert(root, 48);
  root = insert(root, 120);
  root = insert(root, 56);

  cout << "Insertion Operation:" << endl;
  printBT(root);

  root = deleteNode(root, 12);
  root = deleteNode(root, 23);
  root = deleteNode(root, 90);
  root = deleteNode(root, 78);

  cout << "\nDeletion Operation (Removed 12, 23, 90, 78):" << endl;
  printBT(root);

  root = insert(root, 55);
  root = insert(root, 42);

  cout << "\nInsertion Operation (Added 55, 42):" << endl;
  printBT(root);

  return 0;
}
