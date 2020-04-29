#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define CHUNK_SIZE 16

/*Use int strcmp (const char *str1, const char *str2); to compare strings.*/

/*
    This is a solution without balansed BST.
*/

/*BST for Student type*/
typedef struct Node_{
    struct Node_ *left;
    struct Node_ *right;
    char word[100];
}Node;

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

Node *Node_make(char *word, Node *left, Node *right) {
    Node *temp = (Node *) malloc(sizeof(Node));
    if (temp) {
        strcpy(temp->word, word);
        temp->left = left;
        temp->right = right;
        return temp;
    }
    return NULL;
}

int Node_empty(Node *root) {
    return root == NULL;
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

Node *Node_find(Node *root, char *word) {
    if (Node_empty) return NULL;
    Node *current = root;
    while (current != NULL) {
        if (strcmp(word, current->word) == 0) return current; //Match! Return node with match
        if (strcmp(word, current->word) > 1) {
            if (current->right)
                current = current->right;
            else return NULL;   //we won't find it, cuz branch is terminated
        } else {
            if (current->left)
               current = current->left;
            else return NULL; //we won't find it, cuz branch is terminated
        }
    }
}

void Node_insert(Node **root, char *word) {
    if (Node_empty(*root)) {
        *root = Node_make(word, NULL, NULL);
        printf("%s in root!\n", (*root)->word);
        return;
    }
    Node *new_node = Node_make(word, NULL, NULL);
    if (!new_node) {
        printf("ERROR : Insertion failed!");
        exit(1);
    }
    Node **current = *root;
    
    while ((*current)->left != NULL || (*current)->right != NULL) {
        printf("Current: %s\t", (*current)->word);
        if (strcmp(word, (*current)->word) == 0) return; //words are equal and we do nothing
        if (strcmp(word, (*current)->word) > 1) {
            if ((*current)->right)
                current = (*current)->right;
            else {
                current = new_node;
                break;
            }
        } else {
            if ((*current)->left)
                current = (*current)->left;
            else {
                current = new_node;
                break;
            }
        }
    }
    printf("in!\n");
    return;
}
/*Deletes a node with a word as key.*/
Node *Node_delete(Node **proot, char *word) {
/*
    Four cases of deletion :
        Case 1 : List
        Case 2 : One child
        Case 3 : Two children
        Case 4 : Root
*/
    Node *parent = NULL;
    Node *current = *proot;
    while (current != NULL) {
        if (strcmp(word, current->word) == 0) break;
        parent = current;
        current = strcmp(word, current->word) < 0 ? current->left : current->right;
    }
    /*Case 4 : root* */
    if (!parent) {
        Node *tmp = Node_make(current->right->word, current->left, current->right->right);
        free(current->right);
        free(current);
        current = tmp;
        return *proot;
    }
    /* Case 1 : List */

    free(current);
    printf("Gotcha!\n");
    return *proot;
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
        //printf("%d\n", find(root, line_buf));
        printf("Node: %s\n", Node_find(root, line_buf)->word);
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