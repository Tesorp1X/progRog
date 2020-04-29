#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/* Shortcut for conditions */
/*Use int strcmp (const char *str1, const char *str2); to compare strings.*/
#define _compLT(newNode, y) (strcmp(newNode, y) < 0)      //compare newNode Less Then y
#define _compEQ(newNode, y) (strcmp(newNode, y) == 0)     //compare newNode equal y

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
        printf("newNode");
        return;
    }
    printf("(%s", root->word);
    print(root->left);
    print(root->right);
    printf(")");
}

Node *Node_find(Node *root, char *word) {
    if (!root) {
        return NULL;
    }
    if _compEQ(root->word, word) {
        return root;
    }

    return _compLT(root->word, word) ? Node_find(root->right, word) : Node_find(root->left, word);
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

void Node_rightRotate(Node *newNode) {

}

void Node_leftRotate(Node *newNode) {

}

/*Re-balancing RBT root*/
void Node_fixInsertion(Node *root, Node *newNode) {
    /*While we have a violation*/
    while (newNode != root && newNode->parent->color == RED) {
        if (newNode->parent == newNode->parent->parent->right) {
            Node *uncle = newNode->parent->parent->left;
            if (uncle->color == RED) {
                /*Uncle is RED*/
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode = newNode->parent->parent;
            } else {
                /*Uncle id BLACK*/
                if (newNode == newNode->parent->right) {
                    /* Make newNode a left child */
                    newNode = newNode->parent;
                    Node_leftRotate(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                Node_rightRotate(newNode->parent->parent);
            }
        } else {
            /*Mirror situation*/
            Node *uncle = newNode->parent->parent->right;
            if (uncle->color == RED) {
                /* uncle is RED */
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                /*Uncle is BLACK*/
                if (newNode == newNode->parent->left) {
                    /*Make newNode a right child*/
                    newNode = newNode->parent;
                    Node_rightRotate(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                Node_leftRotate(newNode->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

Node *Node_findParent(Node *root, Node *node) {
    Node *parent = NULL;
    Node *curent = root;
    while (curent)
    {
        /* code */
    }
    
}

void Node_addNodeInBST(Node **rootPtr, Node *newNode) {
    while (*rootPtr != NULL) {
        if _compLT((*rootPtr)->word, newNode->word) {
            if ((*rootPtr)->right != NULL) 
                rootPtr = &((*rootPtr)->right);
            else {
                newNode->parent = (*rootPtr);
                (*rootPtr)->right = newNode;
                break;
            }
        }else {
            if ((*rootPtr)->left != NULL)
                rootPtr = &((*rootPtr)->left);
            else {
                newNode->parent = (*rootPtr);
                (*rootPtr)->left = newNode;
                break;
            }
        }
    }
}

/*Inserts 'key' in Red-black tree 'root' and balanses it*/
Node *Node_insert(Node **root, char *word) {
    Node *newNode = Node_make(RED, word, NULL, NULL, NULL);
    Node_addNodeInBST(root, newNode);
    //Node_fixInsertion(root, newNode);
    return *root;
}


Node *Node_findMinNode(Node *root) {
    if (root->left == NULL) return root;
    return Node_findMinNode(root->left);
}

void Node_fixRemove(Node *root, Node *newNode) {
    
}

Node *Node_deleteNodeFromBST(Node **root, Node *node) {

}
/*  Finds adn removes a node with key word, also keeping the balace in the BST. */
Node *Node_remove(Node **root, char *word) {
    Node *current = Node_find(*root, word);

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
        printf("Node: %s\n", Node_find(root, line_buf)->word);
        printf("Parrent: %s\n", Node_findParent(root, Node_find(root, line_buf))->word);
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