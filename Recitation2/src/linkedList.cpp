/* @Author
Student Name: Adil Mahmudlu
Student ID : 150200915
Date: 01.11.2021 */

#include <iostream>
#include <stdio.h>

#include "linkedList.h"

using namespace std;

LinkedList::LinkedList() {
    head = NULL;
    tail = NULL;
}

void LinkedList::addNode(char s) {
    Node* newNode = new Node;
    newNode->letter = s;
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    newNode->next = head;
}

void LinkedList::reorderList(){
    int ordered = 0; //number of changes in full circle
    bool done = false;
    Node* p = tail;
    Node* c = head;
    Node* n = head->next;
    while(!done) {
        //bubble sort
        if ((c->letter)-(n->letter) > 0) {
            p->next = n;
            c->next = n->next;
            n->next = c;
            if (n == tail) {
                tail = c;
            }
            if (c == head) {
                head = n;
            }
            ordered++;
            //shift one node right
            p = n;
            n = c->next;
        }
        else {
            p = c;
            c = n;
            n = n->next;
        }
        if (c == tail) {
            /*if the node we are comparing is at the end, we don't want to
            compare it to first node. if the number of changes during
            one full circle is zero, there isn't anything left to reorder, so we are done*/
            if (ordered == 0) {
                done = true;
            }
            ordered = 0;
            p = c;
            c = n;
            n = n->next;
        }
    }
};

void LinkedList::removeDublicates(){
    Node* p = head;
    while (p != tail) {
        /*if current letter and next letter are same, delete next node
        if next node was a tail, then tail is current node*/
        if (p->letter == p->next->letter) {
            Node* temp = p->next;
            p->next = p->next->next;
            if (temp == tail) {
                tail = p;
            }
            delete temp;
        }
        else {
            p = p->next;
        }
    }
};

void LinkedList::reverseList(){
    /*self-explanatory*/
    Node* p = head;
    Node* c = head->next;
    Node* n = c->next;

    c->next = p;
    p = c;
    c = n;
    n = n->next;

    while (p != head) {
        c->next = p;
        p = c;
        c = n;
        n = n->next;
    }
    tail = head;
    head = tail->next;
};

void LinkedList::printList(){
    Node* temp = head;
    while(true){
        cout<<temp->letter<<" ";
        temp = temp->next;
        if(temp == head)
            break;
    }
    cout<<endl;
};