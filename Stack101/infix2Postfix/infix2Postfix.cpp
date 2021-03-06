#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct nd
{
    char c;
    struct nd *next; 
}node;


//linklist contain stack to print
node *head = NULL;
node *tail = NULL;
int count_list = 0;

void append_list(char ch) { //add at tail
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
    int count = 0; 
    node *current;
    current = head;
    while(current != NULL) {
        count++;
        printf("%c", current->c);
        current = current->next;
    }
    printf(count >= 8 ? "" : "\t");
}

void delete_lnode() {
    node *current;
    node *prev;
    prev = head;
    if(head == NULL) { // 0 node
        printf("don't have node");
    }
    if(head->next == NULL) { // 1 node
        free(head);
        head = NULL;
    } else { // >= 2 node
        while(prev->next->next != NULL) {
            prev = prev->next;
        }
        free(tail);
        prev->next = NULL;
        tail = prev;
    }
    
}

void destroy_stack() {
    node *current;
    current = head;
    while(head != NULL) {
        head = head->next;
        free(current);
        current = head;
    }
    tail = NULL;
}

// linklist contain output to print
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

void destroy_output() {
    node *current;
    current = head_output;
    while(head_output != NULL) {
        head_output = head_output->next;
        free(current);
        current = head_output;
    }
    tail_output = NULL;
}

// stack
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
    if(temp == '^') {
        pr = 3;
    } else if(temp == '*' || temp == '/') {
        pr = 2;
    } else {
        pr = 1;
    }
    return pr;
}

void checkoper(char ck) {
    if((stacktop() == NULL) || (ck == '(') || (ck == '[') || (ck == '{')) {
        push(ck);
        append_list(ck);
        print_list();
    } else if(ck == ')') {
        while(stacktop() != '(') {
            append_output(stacktop());
            pop();
            delete_lnode();
        }
        pop();
        delete_lnode();
        print_list();
    } else if(ck == ']') {
        while(stacktop() != '[') {
            append_output(stacktop());
            pop();
            delete_lnode();
        }
        pop();
        delete_lnode();
        print_list();
    } else if(ck == '}') {
        while(stacktop() != '{') {
            append_output(stacktop());
            pop();
            delete_lnode();
        }
        pop();
        delete_lnode();
        print_list();
    } else {
        if(checkpr(ck) <= checkpr(stacktop()) && ((stacktop() != '(') && (stacktop() != '[') && (stacktop() != '{'))) {
            while ((checkpr(ck) <= checkpr(stacktop())) && (stacktop() != NULL) && (stacktop() != '(') && (stacktop() != '[') && (stacktop() != '{')) {
                // printf("%c ", pop()); // append list
                append_output(stacktop());
                pop();
                delete_lnode();
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
    printf("+========== Infix to postfix converter ==========+\n");
    printf("|-The converter supports : + , - , * , / and ^.  |\n");
    printf("|-Parenthesis : (), [], {}.                      |\n");
    printf("|-Stack can contain 16 char to smooth interface. |\n");
    printf("+================================================+\n");
    char opt;
    while(true) 
    {
        char c;
        int count = 0;
        do
        {
            if(count == 0) {
                printf("|\n| Input processing...\n|\n+-> ");
                printf("Infix: ");
            }
            c = getchar();
            if(c != '\n') {
                if(count == 0) {
                    printf("--------------------------------------------------\n");
                    printf(" Step\tSymbol\tStack\t\tOutput\n");
                    printf("--------------------------------------------------\n");
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
        printf("%4d\t\t\t\t",count);
        print_output();
        while(stacktop() != NULL) {
            char c = pop();
            printf("%c", c);
            append_output(c);
        }
        printf("\n+-------------------------------------------------\n");
        printf("|-> Postfix : ");
        print_output();
        printf("\n+-------------------------------------------------\n");
        printf("\nPress enter button to do it again or [Q/q]uit : ");
        scanf("%c", &opt);
        if(opt == 'Q' || opt == 'q') {
            printf("\n=================== Thank you!! ==================\n");
            break;
        } else {
            /*
            destroy any thing;
            */
            printf("|\n| Destroy processing...\n");
            destroy_stack();
            destroy_output();
        }
    }
    return 0;
}


