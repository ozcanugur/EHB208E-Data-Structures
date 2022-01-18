//
//  main.c
//  DataStructures_1
//
//  Created by Uğur Özcan on 30.04.2020.
//  Copyright © 2020 Uğur Özcan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define STUDENT_N 3
#define NUMBER_LENGTH 9

typedef struct node {
    int val;
    struct node* next;
} node_n;

typedef struct stack {
    int top;
    node_n * Adress[STUDENT_N];
    int ID[STUDENT_N];
} stack_n;

void pushlist(node_n * head, int val) {
        node_n * current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = (node_n *) malloc(sizeof(node_n));
        current->next->val = val;
        current->next->next = NULL;
}

void pushstack(stack_n *s, int newID, node_n * newadress) {
  s->top++;
  s->ID[s->top] = newID;
  s->Adress[s->top] = newadress;
}

void printNumbers(stack_n * s) {
    for(int k=s->top;k>=0;k--){
        node_n * head = s->Adress[k];
        node_n * current = head->next->next;

        while (current != NULL) {
            printf("%d", current->val);
            current = current->next;
        }
        printf("\n");}
}


stack_n * minNumber(stack_n *s){
   
   int i, j;
    for (i = 0; i < STUDENT_N; i++){
        for (j = 0; j <=i; j++){
           if (s->ID[j] > s->ID[j+1]){
             node_n * temp = s->Adress[j];
                s->Adress[j] = s->Adress[j+1];
                s->Adress[j+1] = temp;}}}
    stack_n * min = NULL;
    min = (stack_n *) malloc(sizeof(stack_n));
    min->top= -1;
    pushstack(min, -1, s->Adress[0]);
    return min;
}


int main(int argc, const char * argv[]) {
    
    char Number[STUDENT_N][NUMBER_LENGTH];
   
    
    printf("Please enter the first student number\n");
    gets(Number[0]);
    
    for (int i=1; i<STUDENT_N; i++) {
        printf("Please enter the next student number\n");
        gets(Number[i]);
    }

    
    stack_n * s = NULL;
    s = (stack_n *) malloc(sizeof(stack_n));
    s->top= -1;
        
    for (int i=0; i<STUDENT_N; i++) {
        
        node_n * head = NULL;
        head = (node_n *) malloc(sizeof(node_n));
        
        char id[3];
        for (int s=0;s<3;s++){
            id[s] = Number[i][s+sizeof(Number[i])-3];}
    
        int ID = atoi(id);
    
        head->val = -1;
        head->next = NULL;
    
        pushlist(head,ID);
        for (int j=0;j<NUMBER_LENGTH;j++){
            int x = Number[i][j]-48;
            pushlist(head,x);
        };
    
        pushstack(s, head->next->val, head);
        
    }
    
    printf("School numbers are:\n");
    printNumbers(s);
    printf("The minimum school number is:\n");
    printNumbers(minNumber(s));
    
    
    return 0;
}

