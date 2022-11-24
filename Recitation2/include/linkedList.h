/* @Author
Student Name: Adil Mahmudlu
Student ID : 150200915
Date: 01.11.2021 */

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

class Node{
    public:
        char letter;
        Node* next;
};


class LinkedList{

    Node* head;
    Node* tail;

    public:
        //added constructor and addNode function
        LinkedList();
        void addNode(char);
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
};

#endif