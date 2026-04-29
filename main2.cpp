#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *prev;

    Node(int d)
    {
        data = d;
        next = NULL;
        prev = NULL;
    }
};

void insertathead(Node *&head, Node *&tail, int data)
{
    Node *newnode = new Node(data);

    if (head == NULL)
    {
        head = tail = newnode;
        return;
    }
    newnode->next = head;
    head->prev = newnode;
    head = newnode;
}
void insertattail(Node *&head, Node *&tail, int data)
{
    Node *newnode = new Node(data);

    if (tail == NULL)
    {
        head = tail = newnode;
        return;
    }
    tail->next = newnode;
    newnode -> prev = tail;
    tail = newnode;
}

void insertAtPosition(Node* &head, Node* &tail , int data, int Position){
    if (position == 1)
    {
        insertathead(head, tail, data);
        return;
    }
    Node *temp = head;
    int count = 1;
    while (count < Position - 1 && temp != NULL)
    {
        temp = temp->next;
        count++;
    }
    if (temp->next == NULL)
    {
        insertattail(head, tail, data);
        return;
    }
    Node *newnode = new Node(data);

    newnode->next = temp->next;
    temp->next->prev = newnode;
    temp->next = newnode;
    newnode->prev = temp;
}

void printforward(Node* head){
    Node *temp = head;
    while (temp)
    {
        cout << temp->data << "<-->";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
void deletehead(Node* &head , Node* &tail){
    if(head==NULL) return;
    Node* temp=head;
    head=head->next;
    if(head!=NULL){
        head->prev=NULL;
    }
    else{
        tail=NULL;
    }
    delete temp;
}
void deletetail(Node* &head , Node* &tail){
    if(tail==NULL) return;
    Node* temp=tail;
    tail=tail->prev;
    if(tail!=NULL){
        tail->next=NULL;
    }
    else{
        head=NULL;
    }
    delete temp;
}
void deleteatPosition(Node* &head, Node* &tail , int position){
    if(position==1){
        deletehead(head,tail);
        return;
    }
    Node* curr=head;
    int count=1;
    while(count<position && curr!=NULL){
        curr=curr->next;
        count++;
    }
    if(curr==tail){
        deletetail(head,tail);
        return;
    }
    curr->prev->next=curr->next;
    curr->next->prev=curr->prev;
    delete curr;
}
int main2(){
    Node *head = NULL;
    Node *tail = NULL;
    printforward(head);
    insertathead(head, tail, 10);
    printforward(head);
    insertattail(head, tail, 20);
    printforward(head);
    insertattail(head, tail, 30);
    printforward(head);
    insertattail(head, tail, 40);
    printforward(head);
    insertAtPosition(head, tail, 50, 5);
    printforward(head);
    insertAtPosition(head, tail, 0, 1);
    printforward(head);
}