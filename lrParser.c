/*
Rahma Toulaye Sarr - B231202551 - Concepts Of Programming Languages HW1 - Spring 2025
*/


#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include<string.h>
#include "string_stack.h"
#include "string_queue.h"
#include "grammar.h"
#include "tree.h"



#define MAX_LINE_LENGTH 1024
#define MAX_SIZE 100

char*** readFile(char file[MAX_SIZE], int *rows, int *cols);
Grammar* readGrammar(char file[MAX_SIZE]);
Queue getInput(char file[MAX_SIZE]);



int main(){

   int aRows;
   int aCols;
   int goRows;
   int goCols;
   //loading the action and GOTO tables
   char*** actionTable = readFile("ActionTable.txt", &aRows, &aCols);
   char*** goToTable = readFile("GotoTable.txt", &goRows, &goCols);
   //loading the grammar
   Grammar* grammarTable = readGrammar("Grammar.txt");

   //initializing the queue that will hold the input 
   Queue input = getInput("inputs/input1.txt");
   
   
   //initializing the stack
   Stack stack;
   initializeStack(&stack);
   char* initialState = "0";
   push(&stack, initialState);

   //printing the trace table header
   printf("%-50s %-50s %-50s\n","Stack","Input","Action");
   for(int i = 0; i<50; i++){
    printf("---");
   }
   printf("\n");
   
   //action varial and loop conditions
   char action[10];
   bool runLoop = true;



   //loop that will iterate until the input is completely parsed or revealed false
   while(runLoop){

    //getting the next token from the queue
    char token[5];
    strncpy(token, peekQ(&input), sizeof(token) - 1);
    token[sizeof(token) - 1] = '\0';
    
    //getting the last item on the stack
    char stackTop[5];
    strncpy(stackTop, peekS(&stack), sizeof(stackTop)-1);
    stackTop[sizeof(stackTop) - 1] = '\0';
    int actionCol = -1;
    
    //iterating through the header row of the actionTable until finding corresponding token
    for(int i = 0; i<aCols; i++ ){
     char tmp[10];
     strncpy(tmp, actionTable[0][i], sizeof(tmp) - 1);
     if(strcmp(token, tmp) == 0){
         actionCol = i;
         break;
     }
    }
    
    //if token is not found in actionTable, alerting the user of a syntax error and terminating the program
    if(actionCol==-1){
     printf("\nThe token \"%s\" has not been found in the action table.", token);
     printf( "Please ensure the provided input is correct. The program will be terminated. \n");
     exit(1);
    }
 
    //retrieving the action from the action table
    strncpy(action, actionTable[atoi(stackTop) + 1][actionCol], sizeof(action)-1);
    
    
    switch(action[0]){

        //if the action is a SHIFT action, the input token and the action number a pushed onto the stack, and
        //the input token is removed from the queue.
        //the token is also added as a leaf in the parsing tree
        case 's':{ 

            Node* leaf = newNode(token, 0);
            pushT(leaf); 

            push(&stack, peekQ(&input));
            push(&stack, &action[1]);

            printStack(&stack);
            printQueue(&input);
            printf("Shift %c\n\n",action[1]);
            dequeue(&input);
            break;
        }
        //if the action is a REDUCE action, retrieving the corresponding grammar rule, reducing the stack accordingly
        //and changing the action number according to the GOTO table
        case 'r':{

            int ruleNumber = action[1] - '0' - 1;
            int ruleSize = grammarTable[ruleNumber].lhsSize;
            int popNum = ruleSize * 2;

            Node* children[10];  
            
            //pop the RHS rule, to assign the lhs node as their parent by creating a subtree
            for (int i = ruleSize - 1; i >= 0; i--) {
                children[i] = popT();  
            }
            
            //poping the rhs from the stack
            for(int i = 0; i < popNum; i++){
                pop(&stack);
            }
            int goToRow = atoi(peekS(&stack)) + 1;
            int goToCol;
            for(int i = 0; i<goCols; i++){
                char* a = goToTable[0][i];
                char bstr[2] = {grammarTable[action[1]- '0' - 1].lhs, '\0'};
                if(strcmp(goToTable[0][i], &bstr) == 0){
                    goToCol = i;
                    break;
                }
            }
            //pushing the lhs on the stack
            char lhs[2] = {grammarTable[action[1] - '0' - 1].lhs, '\0'};
            push(&stack, &lhs);
            push(&stack, goToTable[goToRow][goToCol]);

            //rebuilding the subtree with LHS as the parent and RHS as the children
            Node* parent = newNode(lhs, ruleSize);
            for (int i = 0; i < ruleSize; i++) {
                parent->children[i] = children[i];
            }
            pushT(parent);
            
            printStack(&stack);
            printQueue(&input);
            printf("Reduce %c (GOTO [%i, %c]\n\n",action[1], goToRow - 1, lhs[0]);

            break;

        }
        //in case a syntax error happens
        case '-':
        runLoop = false;
        printf("\nSYNTAX ERROR\n");
        break;
        //when the input is accepted
        case 'a':
            runLoop = false;
            break;
        default:
            printf("An error occured. The program will be terminated.");
            exit(1);
    }

   }

    for(int i = 0; i<50; i++){
        printf("---");
    }
    printf("\nParse Tree:\n");
    printTree(topT());

    return 0;
}




//function to read from files and store the input into a 2D dynamic string array (implemented as 3D dynamic char array)
char*** readFile(char file[MAX_SIZE], int* rows, int* cols){
    FILE *fileptr;
    
    fileptr = fopen(file,"r" );
    
    //checking the file opens properly
    if(fileptr == NULL)
    {
        printf("The %s file could not be opened. The program will terminate.", file);
        exit(1);

    }
    //calculating the dimensions of the table
    char line[MAX_LINE_LENGTH];
    *rows = 0;
    *cols = 0;
    while(fgets(line, sizeof(line), fileptr)){
        if(*rows == 0){
            char* token = strtok((line), " \n");
            while(token){
                (*cols)++;
                token = strtok(NULL, " \n");
            }
        }
        (*rows)++;    
           
    }
    //allocating memory for the 2D array
    char*** table = malloc(*rows * sizeof(char**));

    for(int i = 0; i<*rows; i++){
        table[i] = malloc(*cols * sizeof(char*));
    }

    rewind(fileptr);

    //allocating memory for each string, and copying the file content into the array
    int row = 0;
    while(fgets(line, sizeof(line), fileptr)){

        int col = 0;
        char* token = strtok((line), " \n");
        while(token && col < *cols){

            table[row][col] = malloc(strlen(token) +1);
            strcpy(table[row][col], token);
            token = strtok(NULL, " \n");
            col++;
        }
        row++;
    }
    
    

    fclose(fileptr);

    return table;





}

//function storing the grammar rules from an external file
Grammar* readGrammar(char file[MAX_SIZE]){
    FILE *fileptr;
    
    fileptr = fopen(file,"r" );
    
    //checking the file opens properly
    if(fileptr == NULL)
    {
        printf("The %s file could not be opened. The program will terminate.", file);
        exit(1);

    }
    //calculating dimensions (number of rules)
    char line[MAX_LINE_LENGTH];
    int rows = 0;
    while(fgets(line, sizeof(line), fileptr)){
        rows++;
           
    }
    //allocating memory for an array of grammar structs, and copying data
    Grammar* grammarTable = malloc(rows * sizeof(Grammar));
    int i = 0;
    rewind(fileptr);
    while(fgets(line, sizeof(line), fileptr)){
        int size = 0;
        char* token = strtok((line), " \n");
        grammarTable[i].ruleNumber= atoi(token);
        token = strtok(NULL, " \n");
        grammarTable[i].lhs= token[0];
        token = strtok(NULL, " \n");
        token = strtok(NULL, " \n");
        while(token){
            grammarTable[i].rhs[size] = token[0];
            size++;
            token = strtok(NULL, " \n");
        }
        grammarTable[i].lhsSize = size;
        i++;

         
           
    }
    fclose(fileptr);

    return grammarTable;


}
//function to store the input into a queue from external file
Queue getInput(char file[MAX_SIZE]){
    //queue initialization
    Queue input;
    initializeQueue(&input);
    char inpString[MAX_SIZE];

    FILE *fileptr;
        
        fileptr = fopen(file,"r" );
        
        //checking the file opens properly
        if(fileptr == NULL)
        {
            printf("The input file %s could not be opened. The program will terminate.", file);
            exit(1);

        }
    fgets(inpString, sizeof(inpString), fileptr);
    //tokenizing the input and enqueing it 
    char* tokenizedInput = strtok((inpString), " \n");
    while(tokenizedInput){
        enqueue(&input, tokenizedInput);
        tokenizedInput = strtok(NULL, " \n");

    }
    return input;
}