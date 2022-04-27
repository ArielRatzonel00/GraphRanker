///////////////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: Ariel Ratzonel
// PROJECT:         Final project of Algorithms and  Principles of Computer Science
//                  Graph Ranker
///////////////////////////////////////////////////////////////////////////////////////////////




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX 500000

//Data Structures
typedef struct node {
    struct node* next;
    struct node* prec;
    int index;
    int load;
} node;
typedef struct list {
    node* head;
    node* last;
} List;

int dimNode = 0;
int dimRank = 0;
int indexNewGraph = 0;
List* list;
char* token;
int* costMatrix;
int* distances;
bool* visited;





void parseInput(char* line );
void newGraph();
void handleGraphInput(const char* line, int contMatrix, int*matrix);
int dijkstraAlgorithm(const int* matrix);
int minDistance();
int personalAtoi(int length);
void personalStrtok(const char* line);
void insertGraphInTheList(int indexGraph, int loadGraph);
void insertNode(int indexGraph, int loadGraph);
void insertNode1(int indexGraph, int loadGraph);



//Custom Strtok function
void personalStrtok(const char* line){
    int i = 0;
    int j = 0;
    while (line[i] != ' ') {
        token[j] = line[i];
        j++;
        i++;
    }
    dimNode = personalAtoi(j-1);
    i++;
    j = 0;
    while (line[i] != '\n'){
        token[j] = line[i];
        j++;
        i++;
    }
    dimRank = personalAtoi( j-1);
}


void handleGraphInput(const char* line, int contMatrix, int*matrix){
    int i = 0;
    int j = 0;
    for (int c = 0; c < dimNode; c++) {
        while (line[i] != ',' && line[i] != '\n') {
            token[j] = line[i];
            j++;
            i++;
        }
        i++;
        matrix[contMatrix] = personalAtoi(j - 1);
        contMatrix++;
        j=0;
    }
}

// Custom Atoi function
int personalAtoi( int length){
    int n = 0;
    int p = 1;
    for (int i = 0; i <= length;i++){
        for (int c = 0; c<length-i;c++){
            p*=10;
        }
        n += (token[i]-48) * p;
        p = 1;
    }
    return n;
}

//Parsing input
void parseInput(char* line){
    if (line[0] == 'T') {
        node* temp = list->head;
        if(temp == NULL){
            printf("\n");
        }
        while (temp!= NULL){
            if(temp!= list->last) {
                printf("%d ", temp->index);
                temp = temp->next;
            } else{
                printf("%d\n", temp->index);
                temp = NULL;
            }

        }

    }
    else if (line[0] == 'A'){
        newGraph();
    }
    else{
        personalStrtok(line);
    }
}

//Calculating min distances from nodes, function used in Dijkstra algorithm
int minDistance(){
    int min = 2147483647;
    int minVector = 0;
    for (int i = 0; i < dimNode; ++i) {
        if(visited[i] == false && distances[i] <= min){
            min = distances[i];
            minVector = i;
        }
    }
    return minVector;
}

//Dijkstra algorithm

int dijkstraAlgorithm(const int* matrix){
    int sum = 0;

    for (int i = 0; i< dimNode;i++){
        visited[i] = false;
        distances[i] = 2147483647;
    }
    distances[0] = 0;

    for (int cont = 0; cont < dimNode-1; ++cont) {
        int j = minDistance();
        visited[j] = true;
        for (int c = 0; c < dimNode; ++c) {
            if(!visited[c] && distances[j] != 2147483647 && (distances[j] + matrix[j*dimNode + c] < distances[c])){
                if(matrix[j*dimNode + c] != 0){
                    distances[c] = distances[j] + matrix[j * dimNode + c];
                }
            }
        }
    }
    for (int i = 0; i < dimNode; ++i) {
        if(distances[i] == 2147483647){
            distances[i] = 0;
        }
        sum += distances[i];
    }
    return sum;
}

//Function for inserting the first node in the list
void insertNode1(int indexGraph, int loadGraph){
    node* newnode = malloc(sizeof(node));
    node* temp = NULL;
    node* temp2 = NULL;
    newnode->index = indexGraph;
    newnode->load = loadGraph;
    if(loadGraph >= list->last->load){
        temp = list->last;
        list->last->next = newnode;
        newnode->prec = temp;
        list->last = newnode;
        list->last->next = NULL;
    } else {
        temp = list->head;
        while (temp->load <= loadGraph) {
            temp = temp->next;
        }
        if(temp == list->head){
            newnode->next = list->head;
            list->head->prec = newnode;
            list->head = newnode;
            list->head->prec = NULL;
        }
        else {
            temp2 = temp->prec;
            temp2->next = newnode;
            newnode->prec = temp2;
            newnode->next = temp;
            temp->prec = newnode;
        }
    }
}

//Function for inserting the a node in the list

void insertNode(int indexGraph, int loadGraph) {
    node *temp = list->head;
    node *temp2 = NULL;
    node *temp3 = NULL;
    if (loadGraph >= list->last->prec->load) {
        list->last->index = indexGraph;
        list->last->load = loadGraph;
    } else {
        while (temp->load <= loadGraph) {
            temp = temp->next;
        }
        list->last->index = indexGraph;
        list->last->load = loadGraph;

        if (temp == list->head) {
            temp3 = list->last->prec;
            list->last->next = list->head;
            list->head->prec = list->last;
            list->last->prec = NULL;
            list->head = list->last;
            list->last = temp3;
        } else {
            temp2 = temp->prec;
            temp3 = list->last->prec;
            temp2->next = list->last;
            list->last->prec = temp2;
            list->last->next = temp;
            temp->prec = list->last;
            list->last = temp3;
            list->last->next = NULL;
        }
    }
}

//Adding a new graph on the rank
void insertGraphInTheList(int indexGraph, int loadGraph){
    if(indexGraph == 0){
        node* node0 = malloc(sizeof (node));
        node0->index = indexGraph;
        node0->load = loadGraph;
        list->head = node0;
        list->last = node0;
        list->head->prec = NULL;
        list->last->next = NULL;
    }else if(indexGraph <= dimRank-1){
        insertNode1(indexGraph, loadGraph);

    } else if (indexGraph >= dimRank) {
        if (loadGraph < list->last->load) {
            insertNode(indexGraph, loadGraph);
        }
    }
}

void newGraph(){
    int sumLoads;
    for (int i = 0; i < dimNode; ++i) {
        char row[MAX];
        if(fgets(row, MAX, stdin)) {
            handleGraphInput(row, i * dimNode, costMatrix);
        }
    }
    sumLoads = dijkstraAlgorithm(costMatrix);
    insertGraphInTheList(indexNewGraph, sumLoads);
    indexNewGraph++;
}

//Main
int main() {
    list = malloc(sizeof(struct list));
    char input[MAX];
    token = malloc(MAX);
    if(fgets(input,MAX,stdin) != NULL) {
        personalStrtok(input);
        costMatrix = malloc(sizeof(int) *dimNode*dimNode);
        distances = malloc(sizeof(int) * dimNode);
        visited = malloc(sizeof(bool) * dimNode);

    }
    while (fgets(input,MAX,stdin) != NULL){
        parseInput(input);
    }
    return 0;
}

