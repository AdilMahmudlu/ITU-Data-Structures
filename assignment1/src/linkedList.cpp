/* @Author 
Student Name: Adil Mahmudlu
Student ID : 150200915 
Date: 08.11.2021 */

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../include/linkedList.h"

using namespace std;

void Train::create(){
    head = NULL;
    tail = NULL;
}; 

void Train::addMaterial(char material, int weight){
    if (head == NULL) {
        addWagon();
    }
    wagonNode* tempW = head;
    /*if a wagon hasMaterial of type ID, we add to it and don't
    look for other material nodes. if it doesn't, we create new 
    material node of type ID and add to it*/
    bool hasMaterial = false;

    while (true) {
        materialNode* tempM = tempW->material;
        hasMaterial = false;
        while (tempM != NULL) {
            /*if there is ID type material node, and it's not full,
            we add to it*/
            if (tempM->id == material && tempM->weight < 2000) {
                //if there is enough room
                if ((2000 - tempM->weight) >= weight) {
                    tempM->weight += weight;
                    return;
                }
                else {
                    weight -= (2000 - tempM->weight);
                    tempM->weight = 2000;
                    hasMaterial = true;
                    break;
                }
            }
            //if it is full
            else if (tempM->id == material && tempM->weight == 2000) {
                hasMaterial = true;
                break;
            }
            tempM = tempM->next;
        }
        //if wagon doesn't have ID type material block
        if (!hasMaterial) {
            tempM = tempW->material;
            //we add the new node alphabetically
            if (tempM != NULL && tempM->id < material) {
                while (tempM->next != NULL && tempM->next->id < material) {
                    tempM = tempM->next;
                }
                materialNode* newMaterial = new materialNode;
                newMaterial->id = material;
                newMaterial->next = tempM->next;
                tempM->next = newMaterial;
                if (weight > 2000) {
                    newMaterial->weight = 2000;
                    weight -= 2000;
                } 
                else {
                    newMaterial->weight = weight;
                    return;
                }
            }
            //if the node we are adding is the first node on linked list
            else {
                materialNode* newMaterial = new materialNode;
                newMaterial->id = material;
                newMaterial->next = tempW->material;
                tempW->material = newMaterial;
                if (weight > 2000) {
                    newMaterial->weight = 2000;
                    weight -= 2000;
                } 
                else {
                    newMaterial->weight = weight;
                    return;
                }
            }
        }
        //if we are not done and we need a  new wagon
        if (tempW->next == NULL) {
            addWagon();
        }
        tempW = tempW->next;
    }
}; 


void Train::deleteFromWagon(char material, int weight){
    wagonNode* tempW = head;
    wagonNode* rightLimit = tail->next;
    /*the right limit goes from right to left once every cycle
    tempW goes from left to right until rightLimit every cycle
    */
    while (true) {
        while (tempW->next != rightLimit) {
            tempW = tempW->next;
        }
        materialNode* tempM = tempW->material;
        while (tempM != NULL) {
            //if there is enough amount we need
            if (tempM->id == material && tempM->weight >= weight) {
                tempM->weight -= weight;
                //if the material node is 0, we delete it.
                if (tempM->weight == 0) {
                    removeMaterialNode(material, tempW);
                }
                //we remove all the wagons that is empty
                removeWagon();
                return;
            }
            //if we don't have enough in this wagon
            else if (tempM->id == material && tempM->weight < weight) {
                weight -= tempM->weight;
                tempM->weight = 0;
                /*we depleted this wagon's material node so we delete it
                in case this wagon is now empty, we will delete it at the end
                when we are done*/
                removeMaterialNode(material, tempW);
                break;
            }
            else {
                tempM = tempM->next;
            }
        }
        rightLimit = tempW;
        tempW = head;
        if (rightLimit == head) {
            return;
        }
    }
};  


void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 

void Train::addWagon() {
    if(head == NULL) {
        wagonNode* newWagon = new wagonNode;
        newWagon->wagonId = 1;
        newWagon->next = NULL;
        newWagon->material = NULL;
        head = newWagon;
        tail = newWagon;
    }
    else {
        wagonNode* newWagon = new wagonNode;
        newWagon->wagonId = tail->wagonId + 1;
        newWagon->next = NULL;
        newWagon->material = NULL;
        tail->next = newWagon;
        tail = newWagon;
    }
};

void Train::removeWagon() {
    //if there is no wagon to be deleted
    if(head == NULL) {
        return;
    }
    //if the last wagon is not empty (then there is no empty wagons)
    if(tail->material != NULL ) {
        return;
    }
    //while last wagon is empty, we delete it and previous wagon is not tail
    while (tail->material == NULL) {
        wagonNode* temp = head;
        if (temp == tail) {
            delete temp;
            head = NULL;
            tail = NULL;
            return;
        }
        while (temp->next != tail) {
            temp = temp->next;
        }
        temp->next = NULL;
        delete tail;
        tail = temp;
    }
};

void Train::removeMaterialNode(char material, wagonNode* wagon) {
    materialNode* temp = wagon->material;
    materialNode* pretemp = temp;
    while (temp != NULL) {
        if (temp->id == material) {
            //if material node is not empty
            if (temp->weight > 0) {
                return;
            }
            else {
                //if material node is head (first node)
                if (temp == wagon->material) {
                    wagon->material = temp->next;
                    delete temp;
                    return;
                }
                else {
                    pretemp->next = temp->next;
                    delete temp;
                    return;
                }
            }
        }
        pretemp = temp;
        temp = temp->next;
    }
};