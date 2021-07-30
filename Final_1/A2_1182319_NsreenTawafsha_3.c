#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Student: Nsreen Tawafsha 1182319
Instructor: Dr.Radi Jarrar
The Sorting application, is a simple application that reads an unspecified number of strings file,
and then sort it using radix sort after checking many condtions.
*/

//structs definition and the protype for the functions
struct node{
    char str[15];
    struct node* Next;
};
typedef struct node strNode;

//---------------------------------
// functions used in the program
void menu();
int readFromFile(char fileName[], strNode* HEAD);
void addNode(strNode* HEAD , strNode* newNode);
void printList(strNode* HEAD, char fileName[], int chose2, int chose4, int who);
void radixSortOfStrings(strNode* HEAD);
int map(char ch);
strNode* returnNodeForRadixSort(strNode* list);
void prepareForNewIteration(strNode* A[], strNode* HEAD);
void deletePocket(strNode* A[]);
void deleteList(strNode* HEAD);
//----------------------------------

int main(){
    //Creating the header for strings list
    strNode* HEAD = (strNode*) malloc(sizeof(strNode));
    if(HEAD == NULL) // to check if the head take a place in the memory
        printf("Out of space!\n");
    HEAD->Next = NULL;
    printf("\t\t\t\t\tWelcome To The Sorting System\t\t\t\t\t\n\n");
    printf("Before start using the system, please do what you are asked for in the following sentences.\n\n");
    char ch2;
    int ch;
    int chose2 = 0;
    int chose4 = 0;
    int flag = 0; // to check if reading process done
    int sort = 0; // to check if the file has been sorted
    int read = 0; // to check if the file has been read
    do{
        menu(); // chose what you want to do
        scanf(" %c", &ch2);
        ch = ch2 - 48;
        switch(ch){
            case 1: {
                char fileName[20]; // getting the name of the file from which to read data
                if(read == 0){
                    printf("\nEnter file name to read strings, please add (.txt) at the end of its name\n");
                    scanf(" %s" , fileName);
                    flag = readFromFile(fileName , HEAD);
                    while(flag==0){ // if the file is not exists
                        printf("Please re-enter file name, add (.txt) at the end of its name\n");
                        scanf("%s", fileName);
                        flag = readFromFile(fileName, HEAD);
                        }
                    if(flag == 1) read = 1;
                    break;
                    }
                else if(read == 1){ // if chose read file option two times
                    printf("You have already read a file ... if you want to read the same file that you entered before please enter (1)\n");
                    printf("If you want to read different one please enter (0)\n");
                    scanf("%d" , &read);
                    printf("\n");
                    if(read == 0){
                        ch = 1;
                        sort = 0;
                    }
                    break;
                }
            }
            case 2: {
                if(flag==0){ // if you chose option 2 before reading the file
                    printf("Please read the input file before doing this choice(choose number one)\n\n");
                    break;
                }
                if(HEAD->Next == NULL){ // if there is nothing to read in the file (Empty file)
                    printf("Please check your file, There is nothing inside (Empty File)\n\n");
                    flag=0;
                    break;
                }
                char notSortedFile[20]; // getting file name to print not sorted strings in
                chose2 = 1;
                if(chose4==1){
                        printf("Please enter (1) If you want to store the not sorted strings in the same file that contain sorted one\n");
                        printf("If you want to store them in different file, Please enter (0)\n");
                        scanf(" %d", &chose4);
                        }
                if(chose4==0){
                        printf("Enter the name of file you want to store the reading strings in, please add (.txt) at the end of its name.\n");
                        scanf(" %s" , notSortedFile);
                        printList(HEAD, notSortedFile, chose2, chose4 , 0);
                        printf("END PRINTING WITHOUT SORTING ^-^\n\n");
                        break;
                }
                else{  // if you want to store them in the same file that contain sorted strings(after choosing number 4)
                        printf("Please re-enter the name of file that contain sorted strings\n");
                        scanf(" %s" , notSortedFile);
                        printList(HEAD, notSortedFile, chose2, chose4 , 0);
                        printf("END PRINTING THE SORTED SORTINGS ^-^\n\n");
                        break;
                }

            }
            case 3: {
                if(flag==0){ // if you chose option 3 before reading the file
                    printf("Please read the input file before doing this choice(choose number one)\n\n");
                    break;
                }
                radixSortOfStrings(HEAD); // call radix sort function
                printf("END SORTING ^-^\n\n");
                sort = 1;
                break;
            }
            case 4: {
                if(flag==0){ // if you chose option 4 before reading the file
                    printf("Please read the input file before doing this choice(choose number one)\n\n");
                    break;
                }
                if(sort==0){ // if the strings that have been read are not sorted
                    printf("Please sort the strings read before doing this choice(choose number three)\n\n");
                    break;
                }
                char sortedFile[20]; // getting file name to print sorted strings in
                chose4 = 1;
                if(chose2==1){
                    printf("Please enter (1) If you want to store the sorted strings in the same file that contain not sorted one\n");
                    printf("If you want to store them in different file, Please enter (0)\n");
                    scanf(" %d", &chose2);
                }
                if(chose2==0){
                    printf("Enter the name of file you want to display the sorted strings in, please add (.txt) at the end of its name.\n");
                    scanf(" %s" , sortedFile);
                    printList(HEAD, sortedFile, chose2, chose4, 1);
                    printf("END PRINTING THE SORTED STRINGS ^-^\n\n");
                    break;
                }
                else{
                    printf("Please re-enter the name of file that contain not sorted strings\n");
                    scanf(" %s" , sortedFile);
                    printList(HEAD, sortedFile, chose2, chose4, 1);
                    printf("END PRINTING THE SORTED STRINGS ^-^\n\n");
                    break;
                }
            }
            default:
                continue;
        }
    }while(ch != 5); // stop when enter 5
    //free the allocated memory for the linked list
    deleteList(HEAD);
    printf("HAVE A NICE DAY!, THANKS FOR DOING WHAT YOU ASKED FOR ^-^\n\n");
    exit(0);
}

// options function for user
void menu(){
    printf("1-Read the input file\n");
    printf("2-Print the strings that have been read before sorting\n");
    printf("3-Sort the strings that have been read\n");
    printf("4-Print the strings that have been sorted\n");
    printf("5-End your journey\n");
    printf("-------------------------------------------\n");
    printf("Please make a choice: \n");
}

// function to read the input file
int readFromFile(char fileName[], strNode* HEAD){
    char line[15];

    strNode* newNode;
    FILE* in = fopen(fileName , "r");
    if(in == NULL){ // if the file doesn't exist
        printf("WRONG FILE NAME !\n");
        return(0);
    }
    while(fgets(line, sizeof(line), in)){
        newNode = (strNode*) malloc(sizeof(strNode));

        char *token = strtok(line, "  \n");
        strncpy((newNode->str), token, 15);
        newNode->Next=NULL;
        addNode(HEAD, newNode);
    }
    fclose(in);
    printf("END READING ^-^\n\n");
    return (1);
}

// function that add new node to linked list
void addNode(strNode* HEAD , strNode* newNode){
    strNode* p = HEAD->Next;
    if(p==NULL)
        HEAD->Next = newNode;
    else{
        while(p->Next != NULL)
            p = p->Next;
        p->Next = newNode;
    }
}

// function to display list at any case
void printList(strNode* HEAD, char fileName[], int chose2, int chose4, int who){
    FILE* out;
    if(chose2==1 && chose4==1){ // print in the same file for both cases
        out = fopen(fileName, "a");
        fputs("\n\n-------------------------------------------\n\n", out);
        if(who==1)
            fputs("The Strings after sorting\n", out);
        else
            fputs("The Strings before sorting\n" , out);
    }
    else if(chose2==1){
        out = fopen(fileName, "w");
        fputs("The Strings before sorting\n" , out);
    }
    else{
        out = fopen(fileName, "w");
        fputs("The Strings after sorting\n", out);
    }
    strNode* p = HEAD->Next;
    while(p != NULL){
        fputs(p->str, out);
        fprintf(out, "\n");
        p = p->Next;
    }
    fclose(out);
}

///////// RADIX SORT function(DONE)
void radixSortOfStrings(strNode* HEAD){
    if(HEAD->Next->Next == NULL) // if the linked list have just one string then there is no need for sorting
        return;
    strNode* p;
    strNode* temp;
    strNode* A[37]; // make a pocket to use in sorting
    int i;
    int j;
    int index;
    for(i=0; i<37; i++){
        A[i] =(strNode*) malloc(sizeof(strNode));
        if(A[i] == NULL) printf("Out of space!\n ");
        A[i]->Next = NULL;
    }

    for(j=15; j>0; j--){ // to pass through all 15 characters in 15 iterations
        p = returnNodeForRadixSort(HEAD); // node taken from radix sort
        p->Next = NULL;
        while(p != NULL){
            index = map(p->str[j-1]); // return index of array (pocket) to put returned node after
            if((A[index]->Next) == NULL)
                A[index]->Next = p;
            else {
                    temp = A[index];
                    while(temp->Next != NULL)
                        temp = temp->Next;
                    temp->Next = p;
            }
            p = returnNodeForRadixSort(HEAD);
        }
        prepareForNewIteration(A, HEAD); //head sorted after the 15 iterations
    }
    deletePocket(A); // delete the pocket from memory
}

// function to return the index of array(pocket)
int map(char ch){
    if(ch >= 97){
        ch = ch-32;
        return(ch-55);
    }
    else if(ch >= 65)
        return(ch-55);
    else if(ch >= 48)
        return(ch-48);
    else
        return(36);
}

// function to return the node from linked list to radix sort
strNode* returnNodeForRadixSort(strNode* list){
    strNode* temp = NULL;
    if(list->Next != NULL){
            temp = list->Next;
            list->Next = list->Next->Next;
            temp->Next = NULL;
    }
    return temp;
}


//function to return all contents of pockets to the empty linked list preparing to the next iteration
void prepareForNewIteration(strNode* A[], strNode* HEAD){
    strNode* temp;
    strNode* p;
    int i;
    for(i=0 ; i<37; i++){
        if(A[i]->Next == NULL)
            continue;
        else{
            temp = A[i]->Next;
            while(temp != NULL){
                A[i]->Next = temp->Next;
                temp->Next = NULL;
                p = temp;
                addNode(HEAD, p);
                temp = A[i]->Next;
            }
        }
    }
}

// function to delete pocket from memory using free() function
void deletePocket(strNode* A[]){
    int i;
    strNode* p;
    for(i=0; i<37; i++){
        p = A[i]->Next;
        while(p != NULL){
            A[i]->Next = p->Next;
            free(p);
            p = A[i]->Next;
        }
    }
}

// function to delete list from memory after ending the program
void deleteList(strNode* HEAD){
    strNode* p = HEAD->Next;;
    while(HEAD->Next != NULL){
        HEAD->Next = p->Next;
        free(p);
        p = HEAD->Next;
    }
}
