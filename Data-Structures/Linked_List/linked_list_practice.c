
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void push_front(struct Node **head, int data) { //나 그냥 이런 type 받을게라는 선언
    struct Node * new_node = malloc(sizeof(struct Node)); 
        new_node->data = data;
        new_node->next = *head;
        *head = new_node; 
    };

int main() {
    struct Node *head = NULL; //헤드는 노드를 가리키는 포인터
    push_front(&head, 10); //
    push_front(&head, 20);

    struct Node *current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }


};
// int main() {
//     struct Node a = {10, NULL};
//     struct Node b = {20, NULL};

//     a.next = &b;

// }