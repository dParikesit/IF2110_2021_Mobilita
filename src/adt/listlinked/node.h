/* File: node.h */
/* Definisi Node */

#ifndef NODE_H
#define NODE_H

#include "../../object/item/item.h"
#include <stdlib.h>

typedef Item ElType;
typedef struct node *Address;
typedef struct node {
  ElType info;
  Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

Address newNode(ElType val);

#endif