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

void append_list(char ch) {
    node *n = (node*) malloc(sizeof(node));
    n->next = NULL;
    if(head == NULL) {
        head = n;
    } else {
        tail->next = n;
    }
    tail = n;
    n->c = ch;
    count_list++;
}

void print_list() {
    node *current;
    current = head;
    while(current != NULL) {
        printf("%c", current->c);
        current = current->next;
    }
}

void delete_node(char ch) {
    node *current;
    node *prev;
    current = head;
    if(head->c == ch) {
        head = head->next;
    } else {
        while ((current != NULL) && (current->c != ch)) {
            prev = current;
            current = current->next;
        }
        if(current->c == ch) {
            if(tail->c == ch) {
                tail = prev;
            }
            prev->next = current->next;
            current->next = NULL;
        }
    }
    if(current->c == ch) {
        count_list--;
    } else {
        printf("%c is not in the list\n", ch);
    }
    free(current);
}

node *head_output = NULL;
node *tail_output = NULL;
int count_output = 0;

void append_output(char ch) {
    node *n = (node*) malloc(sizeof(node));
    n->next = NULL;
    if(head_output == NULL) {
        head_output = n;
    } else {
        tail_output->next = n;
    }
    tail_output = n;
    n->c = ch;
    count_output++;
}

void print_output() {
    node *current;
    current = head_output;
    while(current != NULL) {
        printf("%c", current->c);
        current = current->next;
    }
}

void delete_output() {
    node *prev;
    prev = head_output;
    while(prev->next != tail_output) {
        prev = prev->next;
    }
    node *current;
    current = tail_output;
    tail_output = prev;
    free(current);
}

node *top = NULL;
int up = 1;

void push(char x) {
    node *n = (node*) malloc(sizeof(node));
    n->next = top;
    top = n;
    n->c = x;
}

char pop() {
    char p;
    node *n;
    n = top;
    top = top->next;
    p = n->c;
    free(n);
    return p;
}

char stacktop() {
    if(top == NULL) {
        return NULL;
    } else {
        return top->c;
    }
}

int checkpr(char temp) {
    int pr;
    if(temp == '(') {
        pr = 2;
    } else if(temp == ')' ) {
        pr = 2;
    } else if(temp == '^') {
        pr = 5;
    } else if(temp == '*' || temp == '/') {
        pr = 4;
    } else {
        pr = 3;
    }
    return pr;
}

void checkoper(char ck) {
    if(ck == '(') {
        up += 3;
    }
    if(stacktop() == NULL) {
        push(ck);
        append_list(ck);
        print_list();
    } else if(ck == ')') {
        while(stacktop() != '(') {
            append_output(stacktop());
            delete_node(pop());
        }
        delete_node(pop());
        print_list();
    } else {
        if(checkpr(ck) * up <= checkpr(stacktop()) * up && ck != '(') {
            while ((checkpr(ck) * up <= checkpr(stacktop()) * up) && (stacktop() != NULL) && stacktop() != '(') {
                // printf("%c ", pop()); // append list
                append_output(stacktop());
                delete_node(pop());
                // pop();
                // print_list();
            }
        }
        push(ck);
        append_list(ck);
        print_list();
    }
}

int main() {
    int c, count = 0;
    do
    {
        if(count == 0) {
            printf("Infix: ");
        }
        c = getchar();
        if(c != '\n') {
            if(count == 0) {
                printf("------------------------------------------\n");
                printf(" Step\tSymbol\tStack\tOutput\n");
                printf("------------------------------------------\n");
                count = 1;
            }
            if(isdigit(c) || isalpha(c)) {
                printf("%4d\t%3c\t", count++, c);
                print_list();
                printf("\t");
                // printf("%c ", c);
                append_output(c);
                print_output();
                printf("\n");
            } else {
                printf("%4d\t%3c\t", count++, c);
                checkoper(c); // print list
                printf("\t");
                print_output();
                printf("\n");
            }
        }
    } while(c!='\n');
    printf("%4d\t\t\t",count);
    print_output();
    while(stacktop() != NULL) {
        printf("%c", pop());
    }
    printf("\n------------------------------------------\n");
    return 0;
}


