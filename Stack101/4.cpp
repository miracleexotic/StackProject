#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct nd
{
    char c;
    struct nd *next; 
}node;

node *head = NULL;
node *tail = NULL;
int count_list = 0;

int main() {
    
    node *a = (node*) malloc(sizeof(node));
    a->next = NULL;
    node *b = (node*) malloc(sizeof(node));
    b->next = a;
    printf("%d", b->next == NULL);

    return 0;
}