#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implement a BINARY tree
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

Node* getNodeByChild(Node* root, Node* n) {
    // return the parent node of node n
    if (root==NULL || n == NULL) return NULL;
    if (root->left == n || root->right == n) return root;
    Node* p = getNodeByChild(root->left, n);
    if (p!=NULL) return p;
    return getNodeByChild(root->right, n);
}
Node* mergeTree2Tree(Node* root, Node* root2) {
    // merging nodes in tree "root2" to existing tree "root"
    if (root==NULL) return root2;
    if (root2==NULL) return root;
    root = addNode2Tree_BinarySearch_Name(root, root2); //add root node of tree2
    // add left subtree of root2
    root = mergeTree2Tree(root, root2->left);
    
    // add right subtree of root2
    root = mergeTree2Tree(root, root2->right);
    return root;
}
Node* removeNodeByName(Node* root, char* name) {
    // remove a node on the tree, that has "name"
    Node* n = getNodeByName(root, name);
    if (n==NULL) return NULL;
    Node* l = n->left;
    Node* r = n->right;
    Node* p = getNodeByChild(root, n); // returns the node that has child being n
    if (p->left == n) {
        // n is LEFT child of p
        // remove LEFT child link
        p->left = NULL;
    }
    else {
        // n is RIGHT child of p
        // remove the RIGHT child link
        p->right = NULL;
    }
    root = mergeTree2Tree(root, l);
    root = mergeTree2Tree(root, r);
    free(n); // free memory allocation of node n
    return root;
}

int main() {
    Node* root = NULL;
    root = addNode2Tree_BinarySearch_Name(root, createNode("John", 20));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Jane", 30));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Alice", 40));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Bob", 50));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Kai", 60));
    root = addNode2Tree_BinarySearch_Name(root, createNode("Zack", 50));
    
    printf("BEFORE:\n");
    printTree(root, "inorder");
    
    root = removeNodeByName(root, "Zack");
    
    printf("AFTER:\n");
    printTree(root, "inorder");
    
    
    return 0;
}
