#include <stdlib.h>
#include <stdio.h>

struct node
{
    int value;
    struct node *next;
};

void append(struct node *root, int value);

void prepend(struct node *root, int value);

void print(struct node *root);

void clear(struct node *root);

int main(int argc, char **argv);