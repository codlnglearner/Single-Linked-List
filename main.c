#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct linked_list_node{
    int value;
    struct linked_list_node* next;
} Node;

typedef Node* List;

int Exist(List p, int value)
{
    // judge whether linked list p contains the value
    // you should visit each node of the linked list one by one, and check whether it is equal to the value
    // if you find it then return 1, otherwise return 0
    while(p!=NULL)
    {
        if(p->value==value) return 1;
        p = p->next;
    }
    return 0;
}

void Print(List p)
{
    // print all integers from the head of linked list in one line(separated by a space), in other words, you should firstly print the integer p points to
    // to be more specific, print p->value and then move p to the next node p->next recursively, until p points to NULL
    while(p!=NULL)
    {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

int Num(List p){
    int num = 0;

    while(p!=NULL)
    {
        num = num + 1;
        p = p->next;
    }

    return num;
}

int MiddleIndex(List p){
    int mid;
    mid= (Num(p)+1)/2;
    return mid;
}
List Insert(List p, int value)
{
    struct linked_list_node* new_node = NULL;
    int exist;
    new_node = (struct linked_list_node*)malloc(sizeof(struct linked_list_node));
    exist = Exist(p,value);

    if(exist==0){
    new_node->value=value;
    new_node->next=p;
    p=new_node;
    }
    return p;
}

List Delete_a(List p){
    struct linked_list_node *toDelete;
    toDelete=p;
    p=p->next;
    free(toDelete);
    return p;
}

List Delete_b(List p){
    struct linked_list_node *toDelete, *seclastNode;
    toDelete=p;
    seclastNode=p;
    while(toDelete->next!=NULL){
        seclastNode=toDelete;
        toDelete=toDelete->next;
    }
    if(toDelete==p){
        p=NULL;
    }else{
        seclastNode->next=NULL;
    }
    free(toDelete);
    return p;
}

List Delete_c(List p){
    struct linked_list_node *toDelete, *prevNode;
    toDelete=p;
    prevNode=p;
    int mid = MiddleIndex(p);
    for(int i=2;i<=mid;i++){
        prevNode=toDelete;
        toDelete=toDelete->next;
    }
    if(toDelete!=NULL){
        if(toDelete==p){
            p=p->next;
        }
        prevNode->next=toDelete->next;
        toDelete->next=NULL;
        free(toDelete);
    }
    return p;
}

List Delete_d(List p, int value_min, int value_max){
    struct linked_list_node *cur, *prevNode;
    int todelete = 0;
    while(p->value>=value_min && p->value<=value_max){
        prevNode=p;
        p=p->next;
        free(prevNode);
        todelete++;
    }
    prevNode=NULL;
    cur=p;
    while(cur!=NULL){
        if(cur->value>=value_min&&cur->value<=value_max){
            if(prevNode!=NULL){
                prevNode->next=cur->next;
            }
            free(cur);
            cur=prevNode->next;
            todelete++;
        }
        else{
            prevNode=cur;
            cur=cur->next;
        }
    }
    return p;
}

void sortList(List p){
    struct linked_list_node *current = p, *index=NULL;
    int temp;
    while(current!=NULL){
        index=current->next;
        while(index!=NULL){
            if(current->value>index->value){
                temp=current->value;
                current->value=index->value;
                index->value=temp;
            }
            index=index->next;
        }
        current=current->next;
    }

}


int main()
{
    List p = NULL;
    int n, m;
    int value, value_min, value_max;

    printf("List initialization: \n");
    printf("How many integers in list initially: ");
    scanf("%d", &n);
    printf("What are the integers: ");
    for(int i=0; i<n; i++)
    {
        int value;
        scanf("%d", &value);
        p = Insert(p, value);
    }
    sortList(p);
    printf("Delete a value from head\n");
	p = Delete_a(p);
    Print(p);

	printf("Delete a value from end\n");
	p = Delete_b(p);
    Print(p);

	printf("Delete a value from middle\n");
	p = Delete_c(p);
    Print(p);

	scanf("%d%d", &value_min, &value_max);
    p = Delete_d(p, value_min, value_max);
    Print(p);
}
