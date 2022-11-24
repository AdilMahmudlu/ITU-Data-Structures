/* @Author
Student Name: Adil Mahmudlu
Student ID : 150200915
Date: 04.01.2022 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>

using namespace std;

string file_path;
ifstream inFile;

bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();



int main(int argc, char* argv[])
{
    bool end = false;
    char choice;
    

    file_path = argv[1];
    //file_path = "orders.txt";
    inFile.open(file_path,ios::in);
    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
        return EXIT_FAILURE;
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    
    inFile.close();
    return EXIT_SUCCESS;


}


void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List 5 products with the highest revenue for total" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        break;
    case 'E':
    case 'e':
        terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts() {
    cout << "5 products with the highest revenue for total are:\n"; 
    string product;
    double price;
    int quantity;
    string day;
    int count;
    map <string, double> revenue;
    multimap <double, string> revenue_list;
    map <string, double>::iterator it;
    multimap <double, string>::reverse_iterator revit;

    inFile >> product >> product >> product >> product; //getting rid of first line;
    
    while (inFile >> product >> price >> quantity >> day) {
        if (revenue.count(product)) {
            revenue[product] += price*quantity;
        }
        else {
            revenue[product] = price*quantity;
        }
    }
    
    for (it = revenue.begin(); it != revenue.end(); it++) {
        revenue_list.insert(make_pair(it->second, it->first));
    }
    
    for (revit = revenue_list.rbegin(), count = 0; revit != revenue_list.rend(), count <5; revit++, count++) {
        cout << revit->second << ' ' << fixed << setprecision(2) << revit->first << '\n';
    }
}

