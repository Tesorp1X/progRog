#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/* Shortcut for conditions */
/*Use int strcmp (const char *str1, const char *str2); to compare strings.*/
#define _compLT(x, y) (strcmp(x, y) < 0)      //compare x Less Then y
#define _compEQ(x, y) (strcmp(x, y) == 0)     //compare x equal y

typedef enum { BLACK, RED } nodeColor;


/*Red-black tree for c-string type*/
typedef struct Node_{
    struct Node_ *parent;
    struct Node_ *left;     //left child
    struct Node_ *right;    //right child
    nodeColor color;        //BLACK or RED node color
    char word[255];         //c-string
}Node;

#define NIL &leaf          
Node leaf = { NULL, NIL, NIL, BLACK, 0 };

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

Node *Node_findParent(Node *root, Node *node) {
    if (root->left == NULL && root->right == NULL)
        return NULL;
    if _compEQ(root->word, node->word)
        return NULL;

    if _compLT(root->word, node->word) {
        if _compEQ(root->right->word, node->word) {
            return root;
        }
    }else if _compLT(node->word, root->word) 
        if _compEQ(root->left->word, node->word)
            return root;

    return _compLT(root->word, node->word) ? Node_find(root->right, node->word) : Node_find(root->left, node->word);
}

/*Adds node newNode to BST root.*/
/*Node *Node_addNodeToBST(Node **root, Node *newNode) {
    if (*root == NULL) {    //found a place for newNode
        *root = newNode;
        //(*root)->parent = Node_findParent(*root, newNode->word);
        return *root;
    }
    if _compEQ((*root)->word, newNode->word) return *root; //This word is already in the tree
    Node **newNodePtr = _compLT((*root)->word, newNode->word) ? &((*root)->right) : &((*root)->left);
    //(*newNodePtr)->parent = &(*root);

    return Node_addNodeToBST(newNodePtr, newNode);  //keep searching place for newNode
}*/

/*Inserts 'key' in Red-black tree 'root' and balanses it*/
/*Node *Node_insert(Node **root, char *key) {
    Node *newNode = Node_make(RED, key, NULL, NULL, NULL);
    Node_addNodeToBST(root, newNode);
    newNode->parent = Node_findParent(*root, newNode);
    //Node_fixInsertion(root, newNode);
    return *root;
}*/

void Node_insert(Node **root, char *word) {
    Node *current = *root;
    Node *parent = NULL;
    while (current != NIL) {
        if _compEQ(word, current->word) //word is already in BST and we do nothing
            return;
        parent = current;
        current = _compLT(current->word, word) ? current->right : current->left;
    }
    //Node *newNode = Node_make(RED, word, parent, NIL, NIL);
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->color = RED; newNode->left = NIL;
    newNode->right = NIL; newNode->parent = parent;
    strcpy(newNode->word, word);
    if (!newNode) {
        printf("ERROR : Node allocation error.\n");
        exit(1);
    }
    if (parent) {
        if _compLT(current->word, word)
            parent->right = newNode;
        else
            parent->left = newNode;
    } else
        *root = newNode;
    
    //Node_fixInsertion(*root, newNode);

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
    Node *current = Node_find(*root, word);

}

int main() {
    Node *root = NIL;
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
    while (!_compEQ(line_buf, "DELETE:") && !feof(in)) {
        printf("Input: %s\t", line_buf);
        Node_insert(&root, line_buf);
        printf("Root: %s\t", root->word);
        printf("Node: %s\n", Node_find(root, line_buf)->word);
        //if (Node_find(root, line_buf))
        fscanf(in, "%s", line_buf);
    }
    fscanf(in, "%s", line_buf);
    print(root);
    Node *par = Node_find(root, "omelet");
    
    printf("\nNode: omelet\t Parent: %s\n", par->parent->word);
    /*while (strcmp(line_buf, "LEVEL:") != 0 && !feof(in)) {
        printf("Del: %s\t", line_buf);
        root = Node_delete(root, line_buf);
        fscanf(in, "%s", line_buf);
    }
    */
    return 0;
}