#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXNODE 20
char E68Heap[MAXNODE]= "*++x/u*__yz__vw";

typedef struct _BSTnode {
  char op;
  struct _BSTnode *lson, *rson;
} BSTnode;
BSTnode node[MAXNODE];

void MakeExpTree(char op[]) {
  int i= 0;
  while (op[i] != '\0') {
    node[i].op= op[i];
    if (isalpha(op[i]) || op[i] == '_') {
      node[i].lson= NULL;
      node[i].rson= NULL;
    } else {
      node[i].lson= &node[2 * i + 1];
      node[i].rson= &node[2 * i + 2];
    }
    i++;
  }
}

void PrintExpRPN(BSTnode *node) {
  if (node == 0) return;
  PrintExpRPN(node->lson);
  PrintExpRPN(node->rson);
  printf("%c", node->op);
}

void PrintNode(BSTnode *node) {
  for (int i= 0; i < strlen(E68Heap); i++) {
    printf("[%d] %c", i, node[i].op);
    if (node[i].lson != 0) printf("%c", node[i].lson->op);
    if (node[i].rson != 0) printf("%c", node[i].rson->op);
    printf("\n");
  }
  printf("\n");
}

int main(int argc, const char *argv[]) {
  PrintNode(node);
  MakeExpTree(E68Heap);
  PrintNode(node);
  PrintExpRPN(node);
  printf("\n");
}
