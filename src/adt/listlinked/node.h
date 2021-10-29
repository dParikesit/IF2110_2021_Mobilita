/* File: node.h */
/* Definisi Node */

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

#include "../../object/item/item.h"

typedef struct node *Address;
typedef struct node {
  Item info;
  Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

Address newNode(Item val);

#endif