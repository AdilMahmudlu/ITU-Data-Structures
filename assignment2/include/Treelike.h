
#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

class City {
    public:
        int index; //index on the array
        string name;
        City* left;
        City* right;
        int leftdur;
        int rightdur;
        City(string, int);
};

class Map {
    public:
        int cur_city_count;
        vector<string> cities; //vector of cities
        City* root;
        vector<int> durations; //vector of durations
        Map();
        void construct_treelike(string);
        void prune_tree(City*);
        int city_index(string); //getting index of a city by name (needed in main.cpp)
        City* get_city(string, City*); //getting city by name
        string print_tree(City*, string);
};

#endif