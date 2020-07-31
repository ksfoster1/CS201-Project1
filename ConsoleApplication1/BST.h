#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "value.h"
#include "node.h"

typedef struct bstnode
{
	char *name; //name of var
	Value *v; //value of var
	struct bstnode *left;
	struct bstnode *right;
} BSTNode;

//extern BSTNode *createBST(); //creates empty BST
extern BSTNode *insert(BSTNode *, char *, Value *);
extern void Inorder(BSTNode *);
extern Value *search(BSTNode *, char *);

