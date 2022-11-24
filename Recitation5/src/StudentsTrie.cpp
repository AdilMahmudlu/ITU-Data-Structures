/* @Author
Student Name: Adil Mahmudlu
Student ID : 150200915
Date: 20.12.2021 */

#include <fstream>
#include <iostream>

#include "StudentsTrie.h"

using namespace std;

TrieNode::TrieNode (const char& digit){
   this->digit = digit;
   for(int i=0; i<MAX_CHILDREN; children[i++] = NULL); 
};
/*
//deleting all children before deleting itself
TrieNode::~TrieNode() {
   for (int i = 0; i < MAX_CHILDREN; i++) {
      if (children[i]) {
         delete children[i];
      }
   }
   return;
}
*/
// Construct a StudentsTrie using the records in 'file_name' 
StudentsTrie::StudentsTrie ( const string& file_name  ) { 
    ifstream student_ids_file ( file_name );   // ifstream object for input file
    string current_student_id;

    root = new TrieNode('r');

    if( student_ids_file.is_open() ) {
        for(int i=1; student_ids_file >> current_student_id; i++ ) {
           insert_id(current_student_id); // YOU HAVE TO IMPLEMENT insert_id() METHOD BELOW
        }
        student_ids_file.close();
    }
    else {
        cout << "File: " << file_name << " could NOT be opened!!";
        exit(1);
    }

    student_ids_file.close();
};

// Insert a student ID into the StudentsTrie 
void StudentsTrie::insert_id ( const string& student_id ) {
   TrieNode* temp = root;
   for (int i = 0; i < 9; i++) {
      int num = (int)student_id[i]-48; //turn char to int
      if (temp->children[num] == NULL) { //if parent doesn't have child with this num, create new
         TrieNode* newNode = new TrieNode(num);
         temp->children[num] = newNode;
      }
      temp = temp->children[num];
   }
};

// Check existence of a student ID in the StudentsTrie
bool StudentsTrie::in_the_trie ( const string& student_id ) {
   TrieNode* temp = root; 
   for (int i = 0; i < 9; i++) {
      int num = (int)student_id[i]-48;
      if (temp->children[num] != NULL) {
         temp = temp->children[num];
      }
      else {
         return false;
      }
   }
   return true;
}; 

// StudentsTrie Destructor
StudentsTrie::~StudentsTrie() {
   for (int i=0; i < MAX_CHILDREN; i++){
      if( root->children[i] ) delete root->children[i];
   };
};

