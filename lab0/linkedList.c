#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void append(struct node *root, int value)
{
    // Travers the list until we get to the end
    while (root->next != NULL)
    {
        root = root->next;
    }
    // Create the new node
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    // Set the value of the new node

    newNode->value = value;
    // Set the next node to NULL
    newNode->next = NULL;
    // Set the previous node to point to the new node
    root->next = newNode;
}

void prepend(struct node *root, int value)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->next = root->next;

    root->next = newNode;
}

void print(struct node *root)
{
    printf("[ ");
    struct node *current = root; // create a pointer to the root node
    while (current->next != NULL)
    {                                         // while the pointer is not NULL
        printf("%d, ", current->next->value); // print the value of the node
        current = current->next;              // move the pointer to the next node
    }
    printf("]");
    printf("\n");
}

void input_sorted(struct node *root, int value)
{
    struct node *current = root;
    while (current->next != NULL && current->next->value < value)
    {
        current = current->next;
    }
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->next = current->next;
    current->next = newNode;
}

void clear(struct node *root)
{
    struct node *current;
    current = root->next;
    root->next = NULL;
    while (current != NULL)
    {
        root = current;
        current = root->next;
        free(root);
    }
}

int main(int argc, char **argv)
{
    struct node root;
    root.value -= 1;
    root.next = NULL;

    printf("First list: ");
    append(&root, 10);
    append(&root, 9);
    append(&root, 8);
    append(&root, 7);
    append(&root, 6);
    prepend(&root, 20);
    print(&root);
    clear(&root);

    printf("Second list: ");
    append(&root, 10);
    append(&root, 9);
    append(&root, 8);
    prepend(&root, 20);
    append(&root, 7);
    append(&root, 6);
    prepend(&root, 19);
    print(&root);
    clear(&root);

    printf("Third list is sorted: ");
    input_sorted(&root, 10);
    input_sorted(&root, 9);
    input_sorted(&root, 8);
    input_sorted(&root, 20);
    input_sorted(&root, 7);
    input_sorted(&root, 6);
    input_sorted(&root, 19);
    print(&root);
    clear(&root);
}