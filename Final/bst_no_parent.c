#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// singly-linked-list
// chain structure: node->node->node->..
// today: implement a linked list representing a tree structure
// node can have a number of child nodes
// root node: that does not have any parent
// no cycle: A->B->...->A

// TODAY: implement a BINARY tree
//a node has LEFT child node (can  be NULL) and RIGHT child node (can be NULL)
// if a node has no child node: both LEFT and RIGHT are NULL
// if a node has LEFT child node only: RIGHT child pointer is NULL

struct STUDENT {
    char* name;
    int age;
};
struct BINARY_TREE_NODE {
    struct STUDENT content;
    struct BINARY_TREE_NODE* left; // address of the left child node of the current node
    struct BINARY_TREE_NODE* right; // address of the right child node of the current node
};

typedef struct BINARY_TREE_NODE Node;
Node* createNode(char* name, int age) {
    Node* new = malloc(sizeof(Node));
    new->content.name = malloc(strlen(name)+1);
    strcpy(new->content.name, name);
    new->content.age = age;
    new->left = NULL;
    new->right = NULL;
    return new;
}
Node* addNode2Tree_BinarySearch_Name(Node* root, Node* n ) {
    // add a node to an existing tree
    // return the root of the updated tree
    // how to add this node?
    // BINARY-SEARCH  property:
    // Left <= Parent <= Right (in student name, alphabetically increasing)
    if (root == NULL) return n;
    if (strcmp(n->content.name, root->content.name) <=0) {
        // need to add node n to LEFT sub-tree
        Node* updated_left_root = addNode2Tree_BinarySearch_Name(root->left, n);
        root->left = updated_left_root;
        return root;
    }
    Node* updated_right_root = addNode2Tree_BinarySearch_Name(root->right, n);
    root->right = updated_right_root;
    return root;
}

Node* addNode2Tree_BinarySearch_Age(Node* root, Node* n ) {
    // add a node to an existing tree
    // return the root of the updated tree
    // how to add this node?
    // BINARY-SEARCH  property:
    // Left <= Parent <= Right (in student name, alphabetically increasing)
    if (root==NULL) return n;
    if (n->content.age <= root->content.age) {
        // need to add node n to LEFT sub-tree
        Node* updated_left_root = addNode2Tree_BinarySearch_Age(root->left, n);
        root->left = updated_left_root;
        return root;
    }
    Node* updated_right_root = addNode2Tree_BinarySearch_Age(root->right, n);
    root->right = updated_right_root;
    return root;
}
void printTree(Node* root, char* order) {
    // order: "inorder", "preorder", "postorder", "inorderReverse"
    // "inorder": left, parent, right
    // "inorderReverse": right, parent, left (reverse of inorder
    // "preorder": parent, left, right
    // "postorder": left, right, parent
    if (root==NULL) return;
    if (strcmp(order, "inorder")==0) {
        printTree(root->left, "inorder");
        printf("name:%s, age:%d\n", root->content.name, root->content.age);
        printTree(root->right, "inorder");
    }
    if (strcmp(order, "inorderReverse")==0) {
        printTree(root->right, "inorderReverse");
        printf("name:%s, age:%d\n", root->content.name, root->content.age);
        printTree(root->left, "inorderReverse");
    }
    if (strcmp(order, "preorder")==0) {
        printf("name:%s, age:%d\n", root->content.name, root->content.age);
        printTree(root->left, "preorder");
        printTree(root->right, "preorder");
    }
    if (strcmp(order, "postorder")==0) {
        printTree(root->left, "postorder");
        printTree(root->right, "postorder");
        printf("name:%s, age:%d\n", root->content.name, root->content.age);
    }
}
Node* getNodeByName(Node* root, char* name) {
    // return the node having "name"
    if (root==NULL) return NULL;
    if (strcmp(root->content.name, name)==0) return root;
    if (strcmp(root->content.name, name)>0) return getNodeByName(root->left, name);
    return getNodeByName(root->right, name);
}
Node* getNodeByAge(Node* root, int age) {
    if (root==NULL) return NULL;
    if (root->content.age==age) return root;
    Node* n = getNodeByAge(root->left, age);
    if (n!=NULL) return n;
    return getNodeByAge(root->right, age);
}

int main() {
    Node* root = NULL;
    root = addNode2Tree_BinarySearch_Name(root, createNode("John", 20));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Jane", 30));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Alice", 40));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Bob", 50));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Kai", 60));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Zack", 50));
    printTree(root, "preorder");
    
    Node* p = getNodeByName(root, "Bob");
    printf("name:%s, age:%d\n", p->content.name, p->content.age);
    
    p = getNodeByAge(root, 30);
    printf("name:%s, age:%d\n", p->content.name, p->content.age);
    
    return 0;
}
