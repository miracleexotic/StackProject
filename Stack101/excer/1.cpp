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

void append_beforeTail(int c) {
    node *n = (node*) malloc(sizeof(node));
    n->next = NULL;
    if(head == NULL) {
        head = n;
        tail = n;
    } else {
        node *prev;
        node *current;
        current = head;
        while(current->next != NULL) {
            prev = current;
            current = current->next;
        }
        if(head != tail) {
            prev->next = n;
        }
        n->next = current;
        if(head == tail) {
            head = n;
        }
    }
    n->c = c;
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

    append_beforeTail(1);
    append_beforeTail(2);
    append_beforeTail(3);
    append_beforeTail(4);
    append_beforeTail(5);
    append_beforeTail(6);
    append_beforeTail(7);
    append_beforeTail(8);
    append_beforeTail(9);
    append_beforeTail(10);

    printAll();

    return 0;
}


























