#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct nd {
    int c;
    struct nd *next;
}node;
node *head = NULL;
node *tail = NULL;
int count = 0;

void append_before3Tail(int c) {
    node *n = (node*) malloc(sizeof(node));
    n->c = c;
    n->next = NULL;
    if(count == 0) {
        head = n;
        tail = n;
    } else if(count == 1) {
        tail = n;
        head->next = n;
    } else if(count == 2) {
        n->next = head;
        head = n;
    } else {
        node *prev;
        node *current;
        current = head;
        while(current->next != tail) {
            prev = current;
            current = current->next;
        }
        prev->next = n;
        n->next = current;
    }
    count++;
}

void printAll() {
    node *current;
    current = head;
    while (current != NULL) {
        printf("%d ", current->c);
        current = current->next;
    }
}



int main() {

    append_before3Tail(1);
    append_before3Tail(2);
    append_before3Tail(3);
    append_before3Tail(4);
    append_before3Tail(5);
    append_before3Tail(6);
    append_before3Tail(7);
    append_before3Tail(8);
    append_before3Tail(9);
    append_before3Tail(10);

    printAll();

    return 0;
}


























