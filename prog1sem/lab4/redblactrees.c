#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/* Shortcut for conditions */
/*Use int strcmp (const char *str1, const char *str2); to compare strings.*/
#define _compLT(x, y) (strcmp(x, y) < 0)      //compare x Less Then y
#define _compEQ(x, y) (strcmp(x, y) == 0)     //compare x equal y

typedef enum { BLACK, RED } nodeColor;


/*Red-black tree for Student type*/
typedef struct Node_{
    struct Node_ *parent;
    struct Node_ *left;     //left child
    struct Node_ *right;    //right child
    nodeColor color;        //BLACK or RED node color
    char word[255];         //c-string
}Node;

int Node_empty(Node *root) {
    return root == NULL;
}

void print(Node *root) {
    if (!root) {
        printf("x");
        return;
    }
    printf("(%s", root->word);
    print(root->left);
    print(root->right);
    printf(")");
}

int find(Node *root, char *v) {
    if (!root) {
        return 0;
    }
    if (strcmp(root->word, v) == 0) {
        return 1;
    }
    return find(root->left, v) || find(root->right, v);
}



/*Creates a new Node*/
Node *Node_make(nodeColor color, char *word, Node *parent, Node *left, Node *right) {
    Node *temp = (Node *) malloc(sizeof(Node));
    if (temp) {
        temp->color = color;
        strcpy(temp->word, word);
        temp->parent = parent;
        temp->left = left;
        temp->right = right;
        return temp;
    }
    return NULL;
}

void Node_rightRotate(Node *x) {

}

void Node_leftRotate(Node *x) {

}

/*Re-balancing RBT root*/
void Node_fixInsertion(Node *root, Node *x) {
    /*While we have a violation*/
    while (x != root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->right) {
            Node *uncle = x->parent->parent->left;
            if (uncle->color == RED) {
                /*Uncle is RED*/
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x = x->parent->parent;
            } else {
                /*Uncle id BLACK*/
                if (x == x->parent->right) {
                    /* Make x a left child */
                    x = x->parent;
                    Node_leftRotate(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                Node_rightRotate(x->parent->parent);
            }
        } else {
            /*Mirror situation*/
            Node *uncle = x->parent->parent->right;
            if (uncle->color == RED) {
                /* uncle is RED */
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                /*Uncle is BLACK*/
                if (x == x->parent->left) {
                    /*Make x a right child*/
                    x = x->parent;
                    Node_rightRotate(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                Node_leftRotate(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}
/*Adds node x to BST root.*/
Node *Node_addNodeToBST(Node **root, Node *newNode) {
    if (*root == NULL) {    //found a place for newNode
        *root = newNode;
        return *root;
    }
    if _compEQ((*root)->word, newNode->word) return *root; //This word is already in the tree
    Node **newNodePtr = _compLT((*root)->word, newNode->word) ? &((*root)->left) : &((*root)->right);

    return Node_addNodeToBST(newNodePtr, newNode);  //keep searching place for newNode
}

/*Inserts 'key' in Red-black tree 'root' and balanses it*/
Node *Node_insert(Node **root, char *key) {
    Node *newNode = Node_make(RED, key, NULL, NULL, NULL);
    Node_addNodeToBST(root, newNode);
    //Node_fixInsertion(root, newNode);
    return *root;
}


Node *Node_findMinNode(Node *root) {
    if (root->left == NULL) return root;
    return Node_findMinNode(root->left);
}

void Node_fixRemove(Node *root, Node *x) {
    
}

Node *Node_deleteNodeFromBST(Node **root, Node *node) {

}
/*  Finds adn removes a node with key word, also keeping the balace in the BST. */
Node *Node_remove(Node **root, char *word) {

}

int main() {
    Node *root = NULL;
    FILE *in, *out;
    in = fopen("input.txt", "r");
    char line_buf[255];
    int level;

    if (!in) {
        printf("ERROR : No such file as input. txt.");
        exit(1);
    }
    fscanf(in, "%s", line_buf); //skiping "TEXT:"
    fscanf(in, "%s", line_buf);
    while (strcmp(line_buf, "DELETE:") != 0 && !feof(in)) {
        printf("Input: %s\t", line_buf);
        Node_insert(&root, line_buf);
        printf("Root: %s\t", root->word);
        printf("%d\n", find(root, line_buf));
        fscanf(in, "%s", line_buf);
    }
    fscanf(in, "%s", line_buf);
    print(root);
    /*while (strcmp(line_buf, "LEVEL:") != 0 && !feof(in)) {
        printf("Del: %s\t", line_buf);
        root = Node_delete(root, line_buf);
        fscanf(in, "%s", line_buf);
    }
    */
    return 0;
}