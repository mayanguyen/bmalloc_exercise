/***
 * Keith O'Hara <kohara@bard.edu>
 * Sep 2013
 * CMSC328: Embedded Operating Systems
 * 
 * simple (unbalanced) binary tree
 * - takes a list of numbers as command line parameters or from standard input
 * 
 */

#include <stdio.h>
#include "bmem.h"

/*
 * A simple binary tree structure
 */
typedef struct treenode {
    int value;
    struct treenode* left;
    struct treenode* right;
} tree_t;

/* 
 * Insert a value (value) into the binary tree (t)
 */
tree_t* insert_tree(tree_t* t, int value);

/* 
 * Clean up the tree
 */
void delete_tree(tree_t* t);

/* 
 * Display the tree using in-order traversal
 */
void print_sorted(tree_t* t);

/* 
 * Display the tree pre-order traversal (like Linux tree)
 */
void print_tree(tree_t* t);

int main(int argc, char* argv[]){        

    int i;
    tree_t* tree;    
    tree = NULL;

    if (argc == 1){
        // standard-in
        while(scanf("%d", &i) > 0){
            tree = insert_tree(tree, i);
            print_tree(tree);            
        }
    }
    else{
        // command-line 
        for (i = 1; i < argc; i++){
            tree = insert_tree(tree, atoi(argv[i]));
        }        
        print_tree(tree);
    }

    printf("\n");
    print_sorted(tree);
    printf("\n");      

    delete_tree(tree);
    return 0;
}

tree_t* insert_tree(tree_t* t, int value){
    if (!t){
        t = (tree_t*)bmalloc(sizeof(tree_t));
        if (t <= 0){
            perror("OUT OF MEMORY");
        }
        t->value = value;
        t->left = NULL;
        t->right = NULL;
    }
    else if (value <= t->value){
        t->left = insert_tree(t->left, value);
    }
    else {
        t->right = insert_tree(t->right, value);
    }
    return t; 
}

void delete_tree(tree_t* t){    
    if (!t) return;
    delete_tree(t->left);
    delete_tree(t->right);
    bfree(t);
}

void print_sorted(tree_t* t){
    if (!t) return;
    print_sorted(t->left);
    printf("%d ", t->value);
    print_sorted(t->right);
}

void print_tree1(tree_t* t, char* prefix, int otail){

    char leftstr[150], rightstr[150];
    
    if (!t) return;
   
    printf("%s%s%d\n", prefix, otail ? "└── " : "├── ",  t->value);
    if(t->left){
        snprintf(leftstr, 80, "%s%s", prefix, otail? "    " : "│   ");
        print_tree1(t->left, leftstr, !t->right);
    }
    if (t->right){
        snprintf(rightstr, 80, "%s%s", prefix, otail? "    " : "│   ");
        print_tree1(t->right, rightstr, 1);
    }
}


void print_tree(tree_t* t){
    print_tree1(t, "", 1);
}

