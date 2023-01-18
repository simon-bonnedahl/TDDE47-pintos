
#include <stdio.h>
#include <stdlib.h>
struct node
{
    int value;
    struct node *next;
};

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
    struct node *current = root; // create a pointer to the root node
    while (current != NULL)
    {                                   // while the pointer is not NULL
        printf("%d, ", current->value); // print the value of the node
        current = current->next;        // move the pointer to the next node
    }
    printf("%d ", root->value);
    printf("\n");
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

    append(&root, 10);
    append(&root, 9);
    append(&root, 8);
    append(&root, 7);
    append(&root, 6);
    prepend(&root, 20);
    print(&root);

    print(&root);
}