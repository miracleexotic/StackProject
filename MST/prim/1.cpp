#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct ch
{
    char c;
    int w;
    struct ch *next;
}child;

typedef struct nd
{
    char c;
    struct ch *nextCh;
    struct nd *nextNd; 
}node;

// Node and Child
node *headNode = NULL;
node *tailNode = NULL;
int cNode = 0;

void appendChild(char p, char ch, int w) {
    child *n = (child*) malloc(sizeof(child));
    n->next = NULL;
    node *currentNd;
    currentNd = headNode;
    while(currentNd != NULL and currentNd->c != p) {
        currentNd = currentNd->nextNd;
    }
    if(currentNd->c == p) {
        if(currentNd->nextCh == NULL) {
            currentNd->nextCh = n;
            n->c = ch;
            n->w = w;
        } else {
            n->next = currentNd->nextCh;
            currentNd->nextCh = n;
            n->c = ch;
            n->w = w;
        }
    } else {
        printf("don't have node %c", p);
    }
    child *n1 = (child*) malloc(sizeof(child));
    n1->next = NULL;
    currentNd = headNode;
    while(currentNd != NULL and currentNd->c != ch) {
        currentNd = currentNd->nextNd;
    }
    if(currentNd->c == ch) {
        if(currentNd->nextCh == NULL) {
            currentNd->nextCh = n1;
            n1->c = p; //
            n1->w = w;
        } else {
            n1->next = currentNd->nextCh;
            currentNd->nextCh = n1;
            n1->c = p; //
            n1->w = w;
        }
    } else {
        printf("don't have node %c", ch);
    }
}

void appendNode(char ch) { //add at tail
    node *n = (node*) malloc(sizeof(node));
    n->nextNd = NULL;
    n->nextCh = NULL;
    if(headNode == NULL) {
        headNode = n;
    } else {
        tailNode->nextNd = n;
    }
    tailNode = n;
    n->c = ch;
    cNode++;
}

void printNode() {
    node *current;
    current = headNode;
    while(current != NULL) {
        printf("%c ", current->c);
        current = current->nextNd;
    }
}

void printChild(char ch) {
    node *current;
    current = headNode;
    while(current != NULL && current->c != ch) {
        current = current->nextNd;
    }
    if(current->c == ch) {
        child *cur;
        cur = current->nextCh;
        printf("%c: [", ch);
        while(cur != NULL) {
            printf("%c: %d", cur->c, cur->w);
            printf(cur->next == NULL ? "" : ", ");
            cur = cur->next;
        }
        printf("]");
    } else {
        printf("don't have node %c", ch);
    }
}

void printAll() {
    node *current;
    current = headNode;
    printf("Internal node: [Leaf Node: Weight, ...], ...\n");
    printf("{");
    while(current != NULL) {
        printChild(current->c);
        printf(current->nextNd == NULL ? "" : ",\n ");
        current = current->nextNd;
    }
    printf("}");
}

char getChildNode(char ch, int n) {
    int i = 0;
    node *current;
    current = headNode;
    while(current != NULL && current->c != ch) {
        current = current->nextNd;
    }
    if(current->c == ch) {
        child *cur;
        cur = current->nextCh;
        while(i<n) {
            cur = cur->next;
            i++;
        }
        return cur->c;
    }
    return NULL;
}

int countChild(char ch) {
    int count = 0;
    node *current;
    current = headNode;
    while(current != NULL && current->c != ch) {
        current = current->nextNd;
    }
    if(current->c == ch) {
        child *cur;
        cur = current->nextCh;
        while(cur != NULL) {
            cur = cur->next;
            count++;
        }
    }
    return count;
}

int getChildWeight(char ch, int n) {
    int i = 0;
    node *current;
    current = headNode;
    while(current != NULL && current->c != ch) {
        current = current->nextNd;
    }
    if(current->c == ch) {
        child *cur;
        cur = current->nextCh;
        while(i<n) {
            cur = cur->next;
            i++;
        }
        return cur->w;
    }
    return NULL;
}


// dist
child *headDist = NULL;
child *tailDist = NULL;
int cDist = 0;

void appendDist(char ch, int weight) {
    child *n = (child*) malloc(sizeof(child));
    n->next = NULL;
    if(headDist == NULL) {
        headDist = n;
        tailDist = n;
        n->c = ch;
        n->w = weight;
        cDist++;
    } else {
        child *current;
        current = headDist;
        while(current != NULL && current->c != ch) {
            current = current->next;
        }
        if(current == NULL) {
            tailDist->next = n;
            tailDist = n;
            n->c = ch;
            n->w = weight;
            cDist++;
        } else if(current->c == ch) {
            current->w = weight;
        } else {
            tailDist->next = n;
            tailDist = n;
            n->c = ch;
            n->w = weight;
            cDist++;
        }
    }
}

int getDistWeight(char ch) {
    child *current;
    current = headDist;
    while(current != NULL && current->c != ch) {
        current = current->next;
    }
    if(current->c == ch) {
        return current->w;
    } else {
        return NULL;
    }
}

int getDefault(char ch, int n) {
    child *current;
    current = headDist;
    while(current != NULL && current->c != ch) {
        current = current->next;
    }
    if(current == NULL) {
        return n;
    } else if(current->c == ch) {
        return current->w;
    } else {
        return n;
    }
}

char findDist(int n) {
    int i = 0;
    child *current;
    current = headDist;
    while(i<n) {
        current = current->next;
        i++;
    }

    return current->c;
}

void printDist() {
    child *current;
    current = headDist;
    printf("{");
    while(current != NULL) {
        printf("%c: %d", current->c, current->w);
        printf(current->next == NULL ? "" : ", ");
        current = current->next;
    }
    printf("}");
}


// Known
node *headKnown = NULL;
node *tailKnown = NULL;
int cKnown = 0;

void appendKnown(char ch) {
    node *n = (node*) malloc(sizeof(node));
    n->nextNd = NULL;
    n->nextCh = NULL;
    if(headKnown == NULL) {
        headKnown = n;
    } else {
        tailKnown->nextNd = n;
    }
    tailKnown = n;
    n->c = ch;
    cKnown++;
}

bool findKnown(char ch) {
    node *current;
    current = headKnown;
    while(current != NULL && current->c != ch) {
        current = current->nextNd;
    }
    if(current == NULL) {
        return false;
    } else if(current->c == ch) {
        return true;
    } else {
        return false;
    }
}


// path
child *headPath = NULL;
child *tailPath = NULL;
int cPath = 0;

void appendPath(char nodeNext, char selfNode) {
    child *n = (child*) malloc(sizeof(child));
    n->next = NULL;
    if(headPath == NULL) {
        headPath = n;
    } else {
        tailPath->next = n;
    }
    tailPath = n;
    n->c = nodeNext;
    n->w = selfNode;
    cPath++;
}


// prim
void prim(char s) {
    appendDist(s, 0);
    appendPath(s, 0);
    int mini;
    char u;

    while(true) {
        if(cKnown == cNode - 1) {
            break;
        }
        mini = 100000;
        for(int i = 0; i<cDist; i++) {
            if(!(findKnown(findDist(i))) && (getDistWeight(findDist(i)) < mini)) {
                mini = getDistWeight(findDist(i));
                u = findDist(i);
            }
        }
        appendKnown(u);
        int count = countChild(u);
        for(int i = 0; i<count; i++) {
            if(!(findKnown(getChildNode(u, i)))) {
                if((getChildWeight(u, i)) < (getDefault(getChildNode(u, i), 100000))) {
                    appendDist(getChildNode(u, i), getChildWeight(u, i));
                    appendPath(getChildNode(u, i), u);
                }
            }
        }
    }
    printDist();
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
    printf("--------------------------------------------\n");

    for(int i = 0; i<m; i++) {
        char addNode, addChild;
        int weight;
        printf("Edge %d: ", i+1);
        scanf(" %c", &addNode);
        scanf(" %c", &addChild);
        scanf(" %d", &weight);
        appendChild(addNode, addChild, weight);
    }
    printf("--------------------------------------------\n");

    // printNode();
    // printf("\n");
    // printChild('A');
    // printf("\n");
    // printChild('B');
    // printf("\n");
    // printChild('G');
    // printf("\n");
    printAll();
    printf("\n--------------------------------------------\n");
    printf("Starting Node = ");
    char startNode;
    scanf(" %c", &startNode);
    printf("Shortest Path -> ");
    prim(startNode);
    printf("\n");

    return 0;
}





