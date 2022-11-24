#include "../include/team.h"

using namespace std;

Team::Team(){};
string Team::getName() { return name; };
int Team::getCurrentSize() { return current_size; };
int Team::getId() { return id; };
int Team::getCapacity() { return capacity; };
Player *Team::getPlayer(int number)
{
    for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return &player_list[i];
    }
    return nullptr;
};
Player *Team::getPlayerList()
{
    return player_list;
};
void Team::setName(string new_name) { name = new_name; };
void Team::setId(int newId) { id = newId; };
void Team::listPlayers()
{
    cout << "Number"
         << " Name"
         << " Age"
         << " #Goals"
         << " #Assists"
         << " #Matches" << endl;
    ;
    for (int i = 0; i < current_size; i++)
    {
        cout << player_list[i].getNumber() << " - ";
        cout << player_list[i].getName() << " - ";
        cout << player_list[i].getAge() << " - ";
        cout << player_list[i].getGoalNumber() << " - ";
        cout << player_list[i].getAssistNumber() << " - ";
        cout << player_list[i].getMatchNumber() << endl;
    }
};
void Team::addPlayer(int number, string name, int age, int goals, int assists, int matches)
{
    if (capacity <= current_size) {
        if (capacity == 0) {
            capacity = 3;
            /*in this case, team is newly created so
            player_list should be initialized*/
            player_list = new Player[capacity];
        } else {
            /*in this case, capacity is increased so
            a new array is created and all the players
            are copied over, old array is deleted*/
            int new_cap = capacity * 2;
            Player* temp = new Player[new_cap];
            for (int i = 0; i < capacity; i++) {
                *(temp + i) = *(player_list + i);
            }
            delete [] player_list;
            player_list = temp;
            capacity = new_cap;
        }
    }
    player_list[current_size].setNumber(number);
    player_list[current_size].setName(name);
    player_list[current_size].setAge(age);
    player_list[current_size].setGoalNumber(goals);
    player_list[current_size].setAssistNumber(assists);
    player_list[current_size].setMatchNumber(matches);
    current_size++;
};

bool Team::checkNumber(int number)
{
    for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return true;
    }
    return false;
}
void Team::removePlayer(int number)
{
    int player_index; //index of the player to be removed
    int offset = 0;
    int new_cap;
    for (int i = 0; i < current_size; i++) {
        if (player_list[i].getNumber() == number) {
            player_index = i;
            break;
        }
    }
    if (capacity > 1 && capacity >= current_size*2) {
        new_cap = capacity/2;
    }
    else {
        new_cap = capacity;
    }
    /*new array is created and all the players are
    copied over except the one to be removed*/
    Player* temp = new Player[new_cap];
    for (int i = 0; i < current_size; i++) {
        if (i == player_index) {
            offset = 1;
            continue;
        }
        *(temp+i-offset) = *(player_list+i);
    }
    current_size--;
    capacity = new_cap;
    delete [] player_list;
    player_list = temp;
};