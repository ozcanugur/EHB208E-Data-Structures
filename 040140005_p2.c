//
//  main.c
//  DSProject2
//
//  Created by Uğur Özcan on 25.05.2020.
//  Copyright © 2020 Uğur Özcan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define NUMBER_LENGTH 9
#define MAX_STUDENT 10 //Arbitrarily selected as 10.

//Defining a linked list node.
typedef struct node_l {
    int val;
    struct node_l * next;
}node_l;

//Defining a BST node.
typedef struct node_b
{
    int key;
    node_l * adress;
    struct node_b *left, *right;
}node_b;

//The function adding a value to the linked list.
void pushlist(node_l * head, int val) {
    node_l * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = (node_l *) malloc(sizeof(node_l));
    current->next->val = val;
    current->next->next = NULL;
}

//The function creating a new BST node.
node_b * newNode(int key, node_l * adress)
{
    node_b *temp =  (node_b *)malloc(sizeof(node_b));
    temp->key = key;
    temp->adress = adress;
    temp->left = temp->right = NULL;
    return temp;
}

//The function adding the last four digits and the number adress to the given BST.
node_b * insert(node_b* node, int key, node_l * adress)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key,adress);
    
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key, adress);
    else if (key > node->key)
        node->right = insert(node->right, key, adress);
    
    return node;
}

//The function displays the values of BST in preorder traversal according to last four digits.
void printPreorder(node_b * node)
{
    if (node == NULL)
        return;
    
    //First, display the linked list being pointed by the node.
    node_l * head = node->adress;
    node_l * current = head->next->next;
    
    while (current != NULL) {
        printf("%d", current->val);
        current = current->next;
    }
    printf("\n");
    
    //Then recur it on the left sub-tree.
    printPreorder(node->left);
    
    //Then recur it on the right sub-tree.
    printPreorder(node->right);
}

//The function displays the values of BST in descending order according to last four digits.
void printInorder(node_b * node)
{
    if (node == NULL)
        return;
    
    //Recur it on the left child.
    printInorder(node->left);
    
    //Display the linked list being pointed by the node.
    node_l * head = node->adress;
    node_l * current = head->next->next;
    
    while (current != NULL) {
        printf("%d", current->val);
        current = current->next;
    }
    printf("\n");
    
    //Then recur it on the right child.
    printInorder(node->right);
}

//Finding the minimum valued node according to the last four digits.
node_b * minValueNode(node_b* node)
{
    node_b* current = node;
    
    //Finding the leftmost node.
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}

//Deleting a node by givin the last four digits.
node_b * deleteNode(node_b * root, int key)
{
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key, go to left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    
    // If the key to be deleted is greater than the root's key, go to right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    
    // If key is the same as the root's key, then this is the node to be deleted
    else
    {
        // Node with only one child or no child
        if (root->left == NULL)
        {
            node_b *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node_b *temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children: Get the smallest in the right sub-tree.
        node_b * temp = minValueNode(root->right);
        
        // Copy the its content to this node
        root->key = temp->key;
        
        // Delete the smallest in the right sub-tree.
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main(int argc, const char * argv[]) {
    
    //Defining the number as a string.
    char * Number = (char *) malloc(sizeof(char));
    
    //Input value for deletion.
    int value = 0;
    
    //Initializing a root node.
    node_b *root = NULL;
    
    printf("\n 1 - Enter school number");
    printf("\n 2 - Delete an entry");
    printf("\n 3 - Visit all the entered school numbers in ascending order");
    printf("\n 4 - Preorder traversal");
    printf("\n 5 - Exit");
    
    int option = 0;
    while(option != 5)
    {
        printf("\n Enter choice: ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                printf("\nEnter school number: ");
                scanf("%s",Number);
                
                //Getting the last four digits of the number.
                int lf = 1000*(Number[5]-48)+100*(Number[6]-48)+10*(Number[7]-48)+Number[8]-48;
                
                //Creating a new linked list node named 'head'.
                node_l * head = NULL;
                head = (node_l *) malloc(sizeof(node_l));
                
                //Initializing the linked list.
                head->val = -1;
                head->next = NULL;
                
                //Adding every digit to the linked list with the head node named 'head'.
                for (int j=0;j<NUMBER_LENGTH;j++){
                    int x = Number[j]-48;
                    pushlist(head,x);
                };
                
                //Adding the last four digits and the adress to the BST having the root node named 'root'.
                root = insert(root,lf,head);
                break;
                
            case 2:
                printf("\nEnter the value of the node to be deleted\n");
                scanf("%d",&value);
                deleteNode(root,value);
                break;
                
            case 3:
                printInorder(root);
                break;
                
            case 4:
                printPreorder(root);
                break;
        }
    }
    return 0;
}


