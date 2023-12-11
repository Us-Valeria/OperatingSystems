#include <stdio.h>
#include <stdlib.h>


struct Node;


struct Node* createNode(int data);

void append(struct Node** head, int data);

void removeNode(struct Node** head, int data);

void printList(struct Node* head);
int size(struct Node* head);

int contains(struct Node* head, int data);

int get(struct Node* head, int index);

int Enter();

void freeList(struct Node* head);

void printMenu();



void menu()
{   
    struct Node* head = NULL;
    while(1)
    {
        printMenu();
        int n;
        scanf("%d", &n);

        switch(n)
        {
            case 1: 
            {
                
                append(&head, Enter());
                break;
            }
            case 2:
            {
                removeNode(&head, Enter());
                break;
            }
            case 3:
            {
                printf("%d\n", size(head));
                break;
            }
            case 4:
            {
                printf("Check value: %s\n", contains(head, Enter()) ? "Yes" : "No");
                break;
            }
            case 5:
            {
                printf("%d\n", get(head, Enter()));
                break;
            }
            case 6:
            {
                printList(head);
                break;
            }
            default:
                exit(1);    
            
        }
    }
    freeList(head);

}

int main() 
{    
    menu();
    return 0;
}