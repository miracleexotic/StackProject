#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct ed
{
    char n1;
    char n2;
    int w;
    struct ed *next;
}edge;

typedef struct nd
{
    char c;
    struct nd *nextCh;
    struct nd *nextNd; 
}node;


// Edges
edge *headEdge = NULL;
edge *tailEdge = NULL;
int cEdge = 0;

void appendEdge(char n1, char n2, int w) {
    edge *n = (edge*) malloc(sizeof(edge));
    n->n1 = n1;
    n->n2 = n2;
    n->w = w;
    n->next = NULL;
    edge *prev = (edge*) malloc(sizeof(edge));;
    prev->w = -1;
    edge *current;
    current = headEdge;
    while(true) {
        if(prev->w == -1 && current == NULL) {
            headEdge = n;
            tailEdge = n;
            cEdge++;
            break;
        } else if(prev->w == -1 && current->w > w) {
            n->next = current;
            headEdge = n;
            cEdge++;
            break;
        } else if(prev->w < w && current == NULL) {
            prev->next = n;
            tailEdge = n;
            cEdge++;
            break;
        } else if(prev->w <= w && current->w > w) {
            prev->next = n;
            n->next = current;
            cEdge++;
            break;
        } 
        prev = current;
        current = current->next;
    }
}

edge *popEdge() { // แค่ดึงออก แต่ยังไม่ได้คืน memory
    edge *current;
    current = headEdge;
    headEdge = headEdge->next;
    cEdge--;
    return current;
}

void printEdge() {
    edge *current;
    current = headEdge;
    while(current != NULL) {
        printf("[%c,%c,%d]", current->n1, current->n2, current->w);
        printf(current->next == NULL ? "" : ", ");
        current = current->next;
    }
}


// Node
node *headNode = NULL;
node *tailNode = NULL;
int cNode = 0;

void appendNode(char c) { // add at tail
    node *n = (node*) malloc(sizeof(node));
    n->nextCh = NULL;
    n->nextNd = NULL;
    if(headNode == NULL) {
        headNode = n;
    } else {
        tailNode->nextNd = n;
    }
    tailNode = n;
    n->c = c;
    cNode++;
}

int countNodeNd() {
    int count = 0;
    node *current;
    current = headNode;
    while(current != NULL) {
        current = current->nextNd;
        count++;
    }

    return count;
}

int found = 0;
void search(node *current, char ch) {
    if(current == NULL) {
        found += 0;
    } else if(current->c == ch) {
        found = 1;
    } else {
        search(current->nextCh, ch); // ลงไปทางซ้ายก่อน
        search(current->nextNd, ch); // ตามด้วยทางขวา
    }
}

bool foundNode(int n, char ch) {
    int i = 0;
    found = 0;
    node *current;
    current = headNode;
    while(i<n) {
        current = current->nextNd;
        i++;
    }
    if(current->c == ch) {
        return true;
    } else {
        node *cur;
        cur = current->nextCh;
        search(cur, ch);
        if(found == 1) {
            return true;
        } else {
            return false;
        }
    }
}

void updateNode(char cUp, char cIn) {
    node *currentUp;
    currentUp = headNode;
    while(currentUp->c != cUp) {
        currentUp = currentUp->nextNd;
    }
    node *currentIn;
    node *prev;
    currentIn = headNode;
    while(currentIn->c != cIn) {
        prev = currentIn;
        currentIn = currentIn->nextNd;
    }
    if(currentIn == headNode) {
        headNode = currentIn->nextNd;
    } else if(currentIn == tailNode) {
        tailNode = prev;
        prev->nextNd = NULL;
    } else {
        prev->nextNd = currentIn->nextNd; // -- 
    }
    currentIn->nextNd = currentUp->nextCh; // --
    currentUp->nextCh = currentIn;
    cNode--;
    
}

char findNode(int n) {
    int i = 0;
    node *current;
    current = headNode;
    while(i<n) {
        current = current->nextNd;
        i++;
    }
    return current->c;
}

void printNode() {
    node *current;
    current = headNode;
    printf("{");
    while(current != NULL) {
        printf("[%c", current->c);
        node *cur;
        cur = current->nextCh;
        while(cur != NULL) {
            printf(", %c", cur->c);
            cur = cur->nextCh;
        }
        printf("]");
        printf(current->nextNd == NULL ? "" : ", ");
        current = current->nextNd;
    }
    printf("}");
}


// krusk
void krusk() {
    while(true) {
        if(countNodeNd() == 1) {
            break;
        }
        edge *x = popEdge();
        int i, j;
        for(i = 0; i<cNode; i++) {
            if(foundNode(i, x->n1)) {
                break;
            }
        }
        for(j = 0; j<cNode; j++) {
            if(foundNode(j, x->n2)) {
                if(i == j) {
                    break;
                }
                updateNode(findNode(j), findNode(i));
                printf("[%c, %c, %d]", x->n1, x->n2, x->w);
                printf(cNode == 1 ? "" : ", ");
                break;
            }
        }

    }
}


int main() {
    int n, m;
    printf("Node, Edge = ");
    scanf(" %d", &n);
    scanf(" %d", &m);

    printf("--------------------------------------------\n");
    printf("Node Name: ");
    for(int i = 0; i<n; i++) {
        char addNode;
        scanf(" %c", &addNode);
        appendNode(addNode);
    }
    printNode();
    printf(" -> %d", countNodeNd());
    printf("\n--------------------------------------------\n");

    for(int i = 0; i<m; i++) {
        char addNode, addChild;
        int weight;
        printf("Edge %d: ", i+1);
        scanf(" %c", &addNode);
        scanf(" %c", &addChild);
        scanf(" %d", &weight);
        appendEdge(addNode, addChild, weight);
    }
    printf("--------------------------------------------\n");
    printf("All Edges = {");
    printEdge();
    printf("}");
    printf("\n--------------------------------------------\n");
    printf("Shortest Edges -> ");
    krusk();
    printf("\n--------------------------------------------\n");

    return 0;
}







