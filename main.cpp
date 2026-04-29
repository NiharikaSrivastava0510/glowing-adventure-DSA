// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int d)
    {
        data = d;
        next = NULL;
    }
};

void insertathead(Node *&head, Node *&tail, int data)
{
    Node *NewNode = new Node(data);
    if (head == NULL)
    {
        head = tail = NewNode;
        return;
    }
    // newnode =7;
    // 1 -> 2 ->3 -> 4 -> 5
    NewNode->next = head;
    // 7-> 1->2->3-> 4 ->5
    head - NewNode;
}

void insertattail(Node *&head, Node *&tail, int data)
{
    Node *NewNode = new Node(data);
    if (tail == NULL)
    {
        head = tail = NewNode;
        return;
    }
    tail->next = NewNode;
    tail = NewNode;
}
void gettail(Node *&head)
{
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    cout << "value of tail Node is: " << temp->data;
}
void insertatPosition(Node *&head, Node *&tail, int position, int data)
{
    Node *NewNode = new Node(data);

    if (position == 1) // insert at head
    {
        insertathead(head, tail, data);

        return;
    }
    Node *temp = head;

    int count = 1;
    while (count < position - 1)
    {

        temp = temp->next;

        count++;
    }
    if (temp->next == NULL) // if temp is tail then its next 1s NULL
    {
        insertattail(head, tail, data);

        return;
    }
    NewNode->next = temp->next;

    temp->next = NewNode;
}
void printlist(Node *&head)
{
    Node *temp = head;
    while (temp)
    {
        cout << temp->data << "-->";
        temp = temp->next;
    }
    return;
}

void deleteathead(Node *&head, Node *&tail)
{
    if (head == NULL)
        return;
    Node *temp = head;
    head = head->next;
    if (head == NULL) // single node check
        tail = NULL;
    delete temp;
}
void deleteattail(Node *&head, Node *&tail)
{
    if (head == NULL)
        return; // no list present
    Node *temp = head;
    if (head == tail)
    { // single node deleted both head and tail
        delete head;
        head = tail = NULL;
        return;
        // proper Lengthy linked list Node *temp = head;
        while (temp->next != tail)
        {
            temp = temp->next;
        }
        delete tail;
        temp->next = NULL;
        tail = temp;
    }
}

void deleteatposition(Node *&head, Node *&tail, int position)
{
    if (position == 1)
    {
        deleteathead(head, tail);
        return;
    }
    Node *prev = NULL;
    Node *curr = head;
    int count = 1;
    while (count < position && curr != NULL)
    {
        prev - curr;
        curr = curr->next;
        count++;
    }

    if (curr = tail)
    {
        deleteattail(head, tail);
        return;
    }
    prev->next = curr->next;

    delete curr;
}
int main()
{
    // Write C++ code here
    // std::cout << "Try programiz.pro";

    // return 0;

    // Node* temp= new Node(1);
    // cout<<temp->data;
    // cout<<endl;
    // cout<<temp->next;
    // cout<<endl;
    // Node* temp2= new Node(3);
    // cout<<temp2->data;
    // cout<<endl;
    // cout<<temp2->next;
    // temp->next=temp2;
    // cout<<endl;
    // cout<<temp->next;

    Node *head = NULL;
    Node *tail = NULL;
    insertathead(head, tail, 10);
    printlist(head);
    cout << endl;
    insertattail(head, tail, 20);
    printlist(head);
    cout << endl;
    cout << tail->data << endl;
    cout << head->data << endl;
    insertattail(head, tail, 30);
    printlist(head);
    cout << endl;
    insertattail(head, tail, 40);
    printlist(head);
    cout << endl;
    insertatPosition(head, tail, 3, 25);
    printlist(head);
    cout << endl;
    insertatPosition(head, tail, 1, 5);
    printlist(head);
    cout << endl;
    cout << head->data << endl;
};