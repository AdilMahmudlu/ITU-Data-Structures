/* @Author
Student Name: Adil Mahmudlu
Student ID : 150200915
Date: 01.11.2021 */

#include <iostream> 
#include <stdlib.h>
//for file handling
#include <fstream>

#include "linkedList.h"

using namespace std;

int main(int argc, char* argv[]) {
	system("clear");
	//system("cls");

    LinkedList newLinkedList;

    char letter;
    ifstream inputFile(argv[1]);
    while (inputFile.get(letter)) {
        if (letter != '\n'){
            newLinkedList.addNode(letter);
        }
    };
    inputFile.close();

    cout << "Readed letters in Circular Linked List: ";
    newLinkedList.printList();
    
    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();

    newLinkedList.reverseList();
    cout<<"Reversed Circular list: ";
    newLinkedList.printList();

    return EXIT_SUCCESS;
}