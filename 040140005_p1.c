//
//  main.c
//  DSProject
//
//  Created by Uğur Özcan on 23.05.2020.
//  Copyright © 2020 Uğur Özcan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define NUMBER_LENGTH 9
#define MAX_STUDENT 10 //Arbitrarily selected as 10.

//Defining a linked list node.
typedef struct node {
    int val;
    struct node* next;
} node_n;

//Defining a stack.
typedef struct stack {
    int top;
    int last_four[MAX_STUDENT];
    int years[MAX_STUDENT];
    node_n * Numbers[MAX_STUDENT];
} stack_n;

//The function adding a value to the linked list.
void pushlist(node_n * head, int val) {
    node_n * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = (node_n *) malloc(sizeof(node_n));
    current->next->val = val;
    current->next->next = NULL;
}

//The function adding the last four digits, the year and the head adress to given stack.
void pushstack(stack_n *s, int lf, int y, node_n * head) {
    s->top++;
    s->Numbers[s->top] = head;
    s->last_four[s->top] = lf;
    s->years[s->top]=y;
    
}

//The function displaying the numbers in ascending order.
void DisplayOrderedNumbers(stack_n *s){
    
    int i, j;
    for (i = 0; i <= s->top; i++){
        for (j = 0; j<s->top; j++){
            if (s->last_four[j] < s->last_four[j+1]){
                int temp1 = s->last_four[j];
                s->last_four[j] = s->last_four[j+1];
                s->last_four[j+1] = temp1;
                int temp2 = s->years[j];
                s->years[j] = s->years[j+1];
                s->years[j+1] = temp2;
                node_n * temp = s->Numbers[j];
                s->Numbers[j] = s->Numbers[j+1];
                s->Numbers[j+1] = temp;
            }
        }
    }
    for(int k=s->top;k>=0;k--){
        node_n * head = s->Numbers[k];
        node_n * current = head->next;
        
        while (current != NULL) {
            printf("%d", current->val);
            current = current->next;
        }
        printf("\n");}
}

//The function displaying the numbers grouped in year.
void DisplayGroupedNumbers(stack_n *s){
    
    int i, j;
    for (i = 0; i <= s->top; i++){
        for (j = 0; j<s->top; j++){
            if (s->years[j] < s->years[j+1]){
                int temp1 = s->years[j];
                s->years[j] = s->years[j+1];
                s->years[j+1] = temp1;
                int temp2 = s->last_four[j];
                s->last_four[j] = s->last_four[j+1];
                s->last_four[j+1] = temp2;
                node_n * temp = s->Numbers[j];
                s->Numbers[j] = s->Numbers[j+1];
                s->Numbers[j+1] = temp;
            }
        }
    }
    for(int k=s->top;k>=0;k--){
        node_n * head = s->Numbers[k];
        node_n * current = head->next;
        
        while (current != NULL) {
            printf("%d", current->val);
            current = current->next;
        }
        printf("\n");}
}


int main(int argc, const char * argv[]) {
    
    //Defining the number as a string.
    char * Number = (char *) malloc(sizeof(char));
    
    //Creating a stack named 's'.
    stack_n * s = NULL;
    s = (stack_n *) malloc(sizeof(stack_n));
    s->top= -1;
    
    printf("\n 1 - Enter school number");
    printf("\n 2 - Display all school numbers in ascending order");
    printf("\n 3 - Display all school numbers grouped in year");
    printf("\n 4 - Exit");
    
    int option = 0;
    while(option != 4)
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
                
                //Getting the year of the number.
                int y = 10*(Number[3]-48)+(Number[4]-48);
            
                //Creating a new linked list node named 'head'.
                node_n * head = NULL;
                head = (node_n *) malloc(sizeof(node_n));
                
                //Initializing the linked list.
                head->val = -1;
                head->next = NULL;
                
                //Adding every digit to the linked list with the head node named 'head'.
                for (int j=0;j<NUMBER_LENGTH;j++){
                    int x = Number[j]-48;
                    pushlist(head,x);
                };
                
                //Adding the heads of the linked lists, years and the last four digits into the stack 's'.
                pushstack(s,lf,y,head);
                break;
                
            case 2:
                DisplayOrderedNumbers(s);
                break;
                
            case 3:
                DisplayGroupedNumbers(s);
                break;
                
            case 4:
                break;
        }
    }
    return 0;
}
