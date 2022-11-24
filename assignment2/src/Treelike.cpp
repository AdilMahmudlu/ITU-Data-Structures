#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include "Treelike.h"

using namespace std;

City::City(string name, int index) {
    this->index = index;
    this->name = name;
    this->left = NULL;
    this->right = NULL;
    this->leftdur = 0;
    this->rightdur = 0;
}

Map::Map() {
    this->cur_city_count = 0;
    this->root = NULL;
}

int Map::city_index(string name) {
    for (int i = 0; i < cur_city_count; i++) {
        if (cities[i] == name) {
            return i;
        }
    }
    return -1; //so i can check if a city is on a map
}

City* Map::get_city(string n, City* c) {
    if (c == NULL) {
        return NULL;
    }
    if (c->name == n) {
        return c;
    }
    if (c->left != NULL) {
        if (get_city(n, c->left) != NULL) {
            return get_city(n, c->left);
        };
    }
    if (c->right != NULL) {
        if (get_city(n, c->right) != NULL) {
            return get_city(n, c->right);
        };
    }
    return NULL;
}

void Map::construct_treelike(string file_name) {
    ifstream file(file_name);
    string s1, s2;
    int d;
    City* c1;
    City* c2;
    while (file >> s1 >> s2 >> d) {
        if (root == NULL) {
            c1 = new City(s1, cur_city_count);
            cities.push_back(s1);
            cur_city_count++;
            root = c1;
            durations.push_back(0); 
        }
        else {
            c1 = get_city(s1, root);
        }
        
        if ((c2 = get_city(s2, root)) == NULL) {
            c2 = new City(s2, cur_city_count);
            cities.push_back(s2);
            cur_city_count++;
            durations.push_back(durations[c1->index] + d);
        }

        if (c1->left == NULL) {
            c1->left = c2;
            c1->leftdur = d;
        }
        else {
            c1->right = c2;
            c1->rightdur = d;
        }
        if (durations[c2->index] > durations[c1->index] + d) {
            durations[c2->index] = durations[c1->index] + d; //already setting durations to minimum
        }
    }
}

void Map::prune_tree(City* c) {
    int i1 = c->index;
    if (c->left != NULL) {
        int i2 = c->left->index;
        if (durations[i2] == durations[i1] + c->leftdur) { //if the duration is the minimum, continue
            prune_tree(c->left);
        }
        else { //else, delete the connection
            c->left = NULL;
            c->leftdur = 0;
        }
        //this might keep 2 or more connections if they have the same duration
    }
    if (c->right != NULL) {
        int i2 = c->right->index;
        if (durations[i2] == durations[i1] + c->rightdur) {
            prune_tree(c->right);
        }
        else {
            c->right = NULL;
            c->rightdur = 0;
        }
    }
    return;
}

string Map::print_tree(City* c, string s) {
    s.append(" ");
    s.append(c->name);
    if (c->left != NULL) {
        s = print_tree(c->left, s);
    }
    if (c->right != NULL) {
        s = print_tree(c->right, s);
    }
    return s;
}