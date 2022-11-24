/* @Author
Student Name: Adil Mahmudlu
Student ID : 150200915
Date: 16.11.2021 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

void infix_to_postfix(string,string&);
bool higher_priority(char,char);
double eval_prefix(string);
double evaluate(double,double,char);
void infix_to_prefix(string,string&);
void str_reverse(string&);

int main(){
    string infix;
    string prefix;
    bool is_exit = false;

    while(!is_exit)
    {

        cout<<"Input the expression in infix: ";
        cin>>infix;

        if (infix == "E" || infix == "e") 
            is_exit = true;

        else
        {
            infix_to_prefix(infix, prefix);
            cout<<prefix<<endl;
            cout<<setprecision(2)<<fixed<<eval_prefix(prefix)<<endl;
        }

        cin.clear();
        cin.ignore();
        infix.clear();
        prefix.clear();
    }
    
    return EXIT_SUCCESS;
}

void infix_to_postfix(string infix,string& postfix)
{
    stack<char> s;
    for (char c: infix) {
        if (c>=48 && c<=57) {
            postfix.push_back(c);
        }
        else if ((c == '+' || c == '-' || c == '*' || c == '/') && !s.empty()) {
            if (!higher_priority(s.top(), c)) {
                s.push(c);
            }
            else {
                while (!s.empty() && higher_priority(s.top(), c)) {
                    postfix.push_back(s.top());
                    s.pop();
                }
                s.push(c);
            }
        }
        else if ((c == '+' || c == '-' || c == '*' || c == '/') && s.empty()) {
            s.push(c);
        }
    }
    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }

}

void infix_to_prefix(string infix,string& prefix)
{
    str_reverse(infix);
    infix_to_postfix(infix, prefix);
    str_reverse(prefix);
}

void str_reverse(string& s)
{
    reverse(s.begin(), s.end()); 
}



bool higher_priority(char first,char second){
    if( (first == '*' || first == '/') && (second == '+' || second == '-') )
        return true;
    else return false;
}

double eval_prefix(string expr){
    stack<double> s;
    double first, second;

    for (int i = expr.size()-1; i >= 0; i--) {
        if (expr[i] >=48 && expr[i] <= 57) {
            s.push(expr[i]-48);
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            first = s.top();
            s.pop();
            second = s.top();
            s.pop();
            s.push(evaluate(first, second, expr[i]));
        }
    }
    return s.top();
}

double evaluate(double first,double second,char c){
    switch(c){
        case '*':
            return first*second;
        case '+':
            return first+second;
        case '-':
            return first-second;
        case '/':
            return first/second;
        default:
            return 0;
    }
}
