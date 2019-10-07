#include<bits/stdc++.h>
using namespace std;

struct node
{
int data;
node *next;
};

class LinkedList
{
private:
    node *head, *tail;
public:
    LinkedList();
    void insert(int data);
    void display();

};

LinkedList::LinkedList():head(NULL),tail(NULL){}

void LinkedList::insert(int data)
{
    node *temp = new node;
    temp->data = data;
    temp->next = NULL;

    if(head==NULL)
    {
        head=temp;
        tail=temp;
        temp=NULL;
    }
    else
    {
        tail->next=temp;
        tail=temp;
    }
}

void LinkedList::display()
{
    node *temp = this->head;

    while (temp!=NULL)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
}