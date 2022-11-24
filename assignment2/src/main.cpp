#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "Treelike.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Map map1;
    Map map2;
    //map1.construct_treelike(argv[1]);
    //map2.construct_treelike(argv[2]);
    map1.construct_treelike("../Include/map1_friend1.txt"); //used these for testing
    map2.construct_treelike("../Include/map1_friend2.txt");
    map1.prune_tree(map1.root);
    map2.prune_tree(map2.root);
    //using MAP data structure would be more efficient but we haven't learned that yet
    int min_dur = 0;
    string meeting_point;
    for (int i = 0; i < map1.cur_city_count; i++) {
        int index;
        if ((index = map2.city_index(map1.cities[i])) == -1) {
            continue;
        }
        if (min_dur == 0 || min_dur > map1.durations[i] + map2.durations[index]) {
            min_dur = map1.durations[i] + map2.durations[index];
            meeting_point = map1.cities[i];
        }
    }
    string s1 = "", s2 = "";
    cout << "FRIEND-1:" << map1.print_tree(map1.root, s1) << endl;
    cout << "FRIEND-2:" << map2.print_tree(map2.root, s2) << endl; 
    cout << "MEETING POINT: " << meeting_point << endl;
    cout << "TOTAL DURATION COST: " << min_dur << endl;
    return 0;
}
