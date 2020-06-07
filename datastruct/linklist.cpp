/*
 *  LinkList 展示链表的操作
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node{
    ElemType data;
    Node* next; 
}Node;

typedef struct LinkList{
    Node* head;
}LinkList;

bool Init(LinkList* list){
    if (list == NULL) return false;
    list->head = (Node*) malloc(sizeof(Node));
    list->head->next = NULL;

    return true;
}

bool Insert(LinkList* list, ElemType e){
    if (list == NULL) return false;

    // create new node
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;

    // find the tail of list
    Node* p = list->head;
    while(p->next != NULL) p = p->next;

    // append to list
    p->next = node;

    return true;
}

// delete all nodes that data == e
void Delete(LinkList* list, ElemType e){
    if (list == NULL || list->head == NULL) return;

    Node* p = list->head;
    while(p->next != NULL) {

        if (p->next->data == e){
            // delete this node
            Node* d = p->next; // record this node for free memory
            p->next = p->next->next; // delete from list

            free(d);
        }else{
            p = p->next;
        }
    }
}

void Display(LinkList list){
    if (list.head == NULL) return;
    Node* p = list.head->next;;
    while(p != NULL) {
        printf("%d\n", p->data);
        p = p->next;
    }
}

// Merge list1 and list2
// list1, list2 有序递增，合并成有序递增
LinkList* Merge(LinkList list1, LinkList list2){
    LinkList* list3 = (LinkList*) malloc(sizeof(LinkList));
    Init(list3);

    Node *p1 = list1.head;
    Node *p2 = list2.head;

    // 同时遍历两个list，比较
    while(p1->next != NULL && p2->next != NULL){
        if(p1->next->data < p2->next->data ){
            Insert(list3, p1->next->data);
            p1 = p1->next;
        }

        else if(p1->next->data == p2->next->data){
            Insert(list3, p1->next->data);
            p1 = p1->next;
            p2 = p2->next;
        }

        else{
            Insert(list3, p2->next->data);
            p2 = p2->next;
        }
    }

    // 将剩下的直接加入到list3
    Node* p = NULL;
    if(p1->next == NULL) { // list1 已遍历完
        p = p2->next;
    }else{
        p = p1->next;
    }

    while(p != NULL) { 
        Insert(list3, p->data);
        p = p->next;
    }

    return list3;
}

int main()
{
    LinkList list1,list2;
    Init(&list1);
    Init(&list2);


    for (int i=0; i<10; i += 2)  Insert(&list1, i);
    for (int i=0; i<10; i += 3)  Insert(&list2, i);
   
    Display(list1);printf("---\n");
    Display(list2);printf("---\n");

    Delete(&list1,4);
    Display(list1);printf("---\n");

    LinkList* list3 = Merge(list1, list2);
    Display(*list3);printf("---\n");

    return 0;
}
