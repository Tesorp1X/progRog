#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/* Shortcut for conditions */
/*Use int strcmp (const char *str1, const char *str2); to compare strings.*/
#define _compLT(x, y) (strcmp(x, y) < 0)      //compare x Less Then y
#define _compEQ(x, y) (strcmp(x, y) == 0)     //compare x equal y
#define CHUNK_SIZE 16

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

char *readWord(FILE *in) {
    int allocated = 0;
    int used = 1;
    char *p = NULL; char c;
    while ((c = fgetc(in)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') break;
        if (allocated <= used) {
            char *q = realloc(p, sizeof(char) * (allocated + CHUNK_SIZE));
            if (!q) break;
            p = q; 
            allocated += CHUNK_SIZE;
        }
        p[used - 1] = c; used++;
    }
    if (p) p[used - 1] = 0;
    return p;
}

void print(Node *root) {
    if (root == NIL) {
        printf("x");
        return;
    }
    printf("(%s", root->word);
    print(root->left);
    print(root->right);
    printf(")");
}

Node *Node_find(Node *root, char *word) {
    if (root == NIL) {
        return NIL;
    }
    if _compEQ(root->word, word) {
        return root;
    }

    return _compLT(root->word, word) ? Node_find(root->right, word) : Node_find(root->left, word);
}

void Node_fprintLevel(FILE *out, Node *node, int level) {
    if (level == 0)
        if (node){
            fprintf(out, "%s ", node->word);
            return;
        }
    Node_fprintLevel(out, node->left, level - 1);
    Node_fprintLevel(out, node->right, level - 1);
}

/*Creates a new Node*/
Node *Node_make(nodeColor color, char *word, Node *parent, Node *left, Node *right) {
    Node *temp = (Node *) malloc(sizeof(Node));
    if (!temp) {
        printf("ERROR: Allocation failed.\n");
        exit(1);
    }
    temp->color = color;
    strcpy(temp->word, word);
    temp->parent = parent;
    temp->left = left;
    temp->right = right;
    return temp;
}

void Node_rightRotate(Node **root, Node *x) {
    Node *y = x->left;

    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else 
            x->parent->left = y;
    } else 
        *root = y;

    y->right = x;
    if (x != NIL)
        x->parent = y;
}

void Node_leftRotate(Node **root, Node *x) {
    Node *y = x->right;

    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else 
        *root = y;

    y->left = x;
    if (x != NIL) x->parent = y;
        
}


/*Re-balancing RBT root with new node newNode. */
void Node_fixInsertion(Node **root, Node *newNode) {
    Node *grandParent;   //grandparent of newNode
    /*While we have a violation*/
    while (newNode != *root && newNode->parent->color == RED) {
        grandParent = newNode->parent->parent;
        assert(grandParent != NIL);
        if (newNode->parent == grandParent->left) {
            Node *uncle = grandParent->right;
            if (uncle->color == RED) {
                /*Uncle is RED*/
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                grandParent->color = RED;
                newNode = grandParent;
            } else {
                /*Uncle id BLACK*/
                if (newNode == newNode->parent->right) {
                    /* Make newNode a left child */
                    newNode = newNode->parent;
                    Node_leftRotate(root, newNode);
                }
                newNode->parent->color = BLACK;
                grandParent->color = RED;
                Node_rightRotate(root, grandParent);
            }
        } else {
            /*Mirror situation*/
            Node *uncle = grandParent->left;
            if (uncle->color == RED) {
                /* uncle is RED */
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                grandParent->color = RED;
                newNode = grandParent;
            } else {
                /*Uncle is BLACK*/
                if (newNode == newNode->parent->left) {
                    /*Make newNode a right child*/
                    newNode = newNode->parent;
                    Node_rightRotate(root, newNode);
                }
                newNode->parent->color = BLACK;
                grandParent->color = RED;
                Node_leftRotate(root, grandParent);
            }
        }
    }
    (*root)->color = BLACK;
}

/*  Ads node with key-word 'word' and adds it to BST.   */
void Node_insert(Node **root, char *word) {
    Node *current = *root;
    Node *parent = NULL;
    while (current != NIL) {
        if _compEQ(word, current->word) //word is already in BST and we do nothing
            return;
        parent = current;
        current = _compLT(current->word, word) ? current->right : current->left;
    }
    Node *newNode = Node_make(RED, word, parent, NIL, NIL);
    
    if (parent) {
        if _compLT(parent->word, word)
            parent->right = newNode;
        else
            parent->left = newNode;
    } else
        *root = newNode;
    
    Node_fixInsertion(root, newNode);

}

Node *Node_findMinNode(Node *root) {
    if (root->left == NIL) return root;
    return Node_findMinNode(root->left);
}

void Node_transplant(Node **root, Node *u, Node *v){
	if(u->parent == NIL){
		*root = v;
	}
	else if(u == u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}

	v->parent = u->parent;
}

void Node_deleteFixup(Node **root, Node *x){
	Node *sibling;	

	while (x != *root && x->color == BLACK){
		
		if (x == x->parent->left){
			sibling = x->parent->right;

			if(sibling->color == RED){
				sibling->color = BLACK;
				x->parent->color = RED;
				Node_leftRotate(root, x->parent);
				sibling = x->parent->right;
			}

			if(sibling->left->color == BLACK && sibling->right->color == BLACK){
				sibling->color = RED;
				x->parent->color = BLACK;
				x = x->parent;
			}
			else{

				if(sibling->right->color == BLACK){
					sibling->color = RED;
					sibling->left->color = BLACK;
					Node_leftRotate(root, sibling);
					sibling = x->parent->right;
				}

				sibling->color = x->parent->color;
				x->parent->color = BLACK;
				x->right->color = BLACK;
				Node_leftRotate(root, x->parent);
				x = *root;
			}

		}
		else{
			sibling = x->parent->left;

			if(sibling->color == RED){
				sibling->color = BLACK;
				x->parent->color = BLACK;
				Node_rightRotate(root, x->parent);
				sibling = x->parent->left;
			}

			if(sibling->left->color == BLACK && sibling->right->color == BLACK){
				sibling->color = RED;
				x->parent->color = BLACK;
				x = x->parent;
			}
			else{

				if(sibling->left->color == BLACK){
					sibling->color = RED;
					sibling->right->color = BLACK;
					Node_leftRotate(root, sibling);
					sibling = x->parent->left;
				}

				sibling->color = x->parent->color;
				x->parent->color = BLACK;
				sibling->left->color = BLACK;
				Node_rightRotate(root, x->parent);
				x = *root;

			}
		}

	}

	x->color = BLACK;
}

void Node_delete(Node **root, char *word){
    Node *node = Node_find(*root, word);
	Node *x, *y;

    if (node == NIL) return;


    if (node->left == NIL || node->right == NIL) {
        /* y has a NIL node as a child */
        y = node;
    } else {
        /* find tree successor with a NIL node as a child */
        y = node->right;
        while (y->left != NIL) y = y->left;
    }

    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        *root = x;

    if (y != node) strcpy(node->word, y->word);


    if (y->color == BLACK)
        Node_deleteFixup(root, x);

    free (y);
}

void Node_free(Node *root) {
    if (root == NIL) return;
    Node_free(root->left);
    Node_free(root->right);
    free(root);
}

int main() {
    Node *root = NIL;
    FILE *in, *out;
    in = fopen("input.txt", "r");
    char *line_buf;
    char line[10];
    int level;

    if (!in) {
        printf("ERROR : No such file as input. txt.");
        exit(1);
    }
    fscanf(in, "%s", line); //skiping "TEXT:"
    fgetc(in);
    line_buf = readWord(in);
    while (!_compEQ(line_buf, "DELETE:")) {
        Node_insert(&root, line_buf);
        free(line_buf);
        line_buf = readWord(in);
    }
    print(root);
    putchar('\n');
    line_buf = readWord(in);
    while (strcmp(line_buf, "LEVEL:") != 0) {
        Node_delete(&root, line_buf);
        free(line_buf);
        line_buf = readWord(in);
    }
    fscanf(in, "%d", &level);
    fclose(in);
    out = fopen("output.txt", "w+");
    Node_fprintLevel(out, root, level);
    print(root);
    Node_free(root);
    fclose(out);

    
    return 0;
}