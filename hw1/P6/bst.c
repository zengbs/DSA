#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>

struct node
{
    int key;
    int count;
    struct node *left, *right;
};
  
// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->count = 1;
    return temp;
}
  
// A utility function to do inorder traversal of BST
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d(%d) ", root->key, root->count);
        inorder(root->right);
    }
}
  
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);
  
    // If key already exists in BST, icnrement count and return
    if (key == node->key)
    {
       (node->count)++;
        return node;
    }
  
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
  
    /* return the (unchanged) node pointer */
    return node;
}
  
/* Given a non-empty binary search tree, return the node with
   minimum key value found in that tree. Note that the entire
   tree does not need to be searched. */
struct node * minValueNode(struct node* node)
{
    struct node* current = node;
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
  
    return current;
}
  
/* Given a binary search tree and a key, this function
   deletes a given key and returns root of modified tree */
struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL) return root;
  
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
  
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
  
    // if key is same as root's key
    else
    {
        // If key is present more than once, simply decrement
        // count and return
        if (root->count > 1)
        {
           (root->count)--;
           return root;
        }
  
        // ElSE, delete the node
  
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
  
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);
  
        // Copy the inorder successor's content to this node
        root->key = temp->key;
  
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main(){
  int n; // length of sequence
  int q; // number of operations
  int number; // appended number

  scanf("%d %d", &n, &q);

  struct node *root = NULL;

  int *array     = (int*)calloc(n, sizeof(int));

  for(int i=0;i<n;i++){
    scanf("%d", &number);
    array[i]     = number;
  }


  /* read operations */
  char operation[10];
  int l_pos, r_pos, value, k;

  for(int i=0;i<q;i++){
   scanf("%7s", operation);

     if(strcmp(operation, "Query"  )== 0){

       scanf("%d %d %d", &l_pos, &r_pos, &k);

       for(int i=l_pos-1;i<=r_pos-1;i++){
         root = insert(root, array[i]);
       }
     
       inorder(root);

     }
  }


  return 0;
}
