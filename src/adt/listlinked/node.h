/* File: node.h */
/* Definisi Node */

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

#include "../../object/item/item.h"

typedef Item* ElTypeListLinked;
typedef struct node *Address;
typedef struct node {
  ElTypeListLinked info;
  Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

Address newNode(ElTypeListLinked val);

#endif