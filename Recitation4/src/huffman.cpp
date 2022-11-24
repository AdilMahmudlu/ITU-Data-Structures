/* @Author
Student Name: Adil Mahmudlu
Student ID : 150200915
Date: 06.12.2021 */

#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

//added constructor
Node::Node() {
    this->left = NULL;
    this->right = NULL;
    this->next = NULL;
}

int Huffman::findindex(Token *arr, string elem){
    for (int i = 0; i < token_count; i++) {
        if (arr[i].symbol == elem) {
            return i;
        }
    }
    return -1;
}

void Huffman::find_frequencies()
{
    int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);
        index = findindex(token_array, s);
        if (index == -1) {
            Token t;
            t.symbol = s;
            t.count = 1;
            token_array[token_count] = t;
            token_count++;
        }
        else {
            token_array[index].count++;
        }
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}
/*push doesn't push nodes to the beginning, but rather pushes
them in sorted manner*/
void PriorityQueue::push(Node *newnode)
{
	if (head == NULL) {
        head = newnode;
        return;
    }
    else {
        Node* t = head;
        //if newnode should be added to beginning
        if (t->token.count > newnode->token.count) {
            newnode->next = t;
            head = newnode;
            return;
        }
        //if newnode should be added inbetween nodes
        while (t->next != NULL && t->next->token.count <= newnode->token.count) {
            t = t->next;
        }
        newnode->next = t->next;
        t->next = newnode;
        return;
    }
}

Node* PriorityQueue::pop()
{
    if (head == NULL) {
        return NULL;
    }
    else {
        Node* t = head;
        head = head->next;
        t->next = NULL; //we won't need next pointer anymore
        return t;
    }
}

void Huffman::get_priority_queue()
{
    for (int i = 0; i < token_count; i ++) {
        Node* t = new Node();
        t->token = token_array[i];
        priority_queue.push(t);
        priority_queue.token_count++;
    } 
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    Node * p = new Node();
    p->token.count = node1->token.count + node2->token.count;
    p->token.symbol = node1->token.symbol + node2->token.symbol;
    p->left = node1;
    p->right = node2;
    return p;
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    while (priority_queue.token_count > 1) {
        /*according to my research, in C++ we can't know the
        order of evaluation of parameters, so the below function's
        inputs can be both merge(X, Y) and merge (Y, X)
        Node* t = huffman_binary_tree.merge(priority_queue.pop(), priority_queue.pop());
        on  my computer, inputs were always like merge(Y, X), but 
        to make it guaranteed that the function inputs will
        be in order, as in the case merge (X, Y), I have to write this */
        Node* a = priority_queue.pop();
        Node* b = priority_queue.pop();
        Node* t = huffman_binary_tree.merge(a, b);
        priority_queue.push(t);
        priority_queue.token_count--;
    }
    huffman_binary_tree.root = priority_queue.head;
}

void Huffman::get_codes(Node *traversal,string codepart)
{
    if (traversal->left != NULL) {
        codepart.append("0");
        traversal->left->token.code.append(codepart);
        get_codes(traversal->left, codepart);
        codepart.pop_back();
    }
    if (traversal->right != NULL) {
        codepart.append("1");
        traversal->right->token.code.append(codepart);
        get_codes(traversal->right, codepart);
        codepart.pop_back();
    }
    if (traversal->left == NULL && traversal->right == NULL) {
        token_array[findindex(token_array, traversal->token.symbol)].code = traversal->token.code;
    }
    return;
}

string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}