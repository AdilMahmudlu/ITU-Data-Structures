/* @Author 
Student Name: Adil Mahmudlu
Student ID : 150200915 
Date: 08.11.2021 */

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        char id;
        int weight;
        materialNode* next;
};

class wagonNode{
    public:
        int wagonId;
        materialNode* material;
        wagonNode* next;
};

class Train{  

    wagonNode* head;
    wagonNode* tail;
    
    public:
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
        void addWagon();
        void removeWagon();
        void removeMaterialNode(char, wagonNode*);
};

#endif