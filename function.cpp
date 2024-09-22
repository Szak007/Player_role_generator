/**@file*/

/*
Player_role_generator
*/

//header file import 
#include "function.h"
#include "struct.h"

//import library
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

//Get parameters
bool download_parameters(int num, char* params[], std::string& f_tree, std::string& f_data) {
    std::cout << params[0] << "\n";
    if (num < 5) {
        std::cout << "incorrect number of parameters\n";
        return 0;
    }
    for (int i = 1; i < num; i += 2) {
        if ((std::string)params[i] == "-t") {
            std::ifstream f_one(params[i + 1]);
            f_tree = params[i + 1];
            if (!f_one) {
                std::cout << "does not work file one - tree\n";
                return 0;
            }
        }
        else if ((std::string)params[i] == "-d") {
            std::ifstream f_two(params[i + 1]);
            f_data = params[i + 1];
            if (!f_two) {
                std::cout << "does not work file two - data\n";
                return 0;
            }
        }
        else {
            std::cout << "wrong parameters\n";
            return 0;
        }
    }
    return 1;
}


//Load data from tree file
std::map<int, Node> load_tree(const std::string& f_tree) {
    std::map<int, Node> tree;
    std::ifstream file(f_tree);
    std::string line;

    while (getline(file, line)) {
        std::istringstream iss(line);
        int id, value;
        std::string skill, condition, left, right;
        

        iss >> id;
        if (iss >> skill >> condition >> value >> left >> right) { 
            tree[id] = Node{ id, skill, condition, value, left, right };
        }
        else { 
            tree[id] = Node{ id, "", "", 0, skill, "" };
        }
    }

    return tree;
}


//Load data from dane file
std::vector<Player> load_players(const std::string& f_data) {
    std::vector<Player> players;
    std::ifstream file(f_data);
    std::string line;
    
    std::getline(file, line);

    while (std::getline(file, line)) {
        
        if (line.empty() || line[0] == '%') continue;

        std::istringstream iss(line);
        std::string name;
        std::string surname;
        int control;
        int speed;
        int stamina;
        int kick;
        int guard;

        
        size_t commentIndex = line.find('%'); 
        if (commentIndex != std::string::npos) {
            line = line.substr(0, commentIndex);
            iss.str(line);
            iss.clear();
        }

        if (iss >> name >> surname >> control >> speed >> stamina >> kick >> guard) {
            
            Player New_Player;
            New_Player.name = name;
            New_Player.surname = surname;
            
            New_Player.skills.push_back(control);
            New_Player.skills.push_back(speed);
            New_Player.skills.push_back(stamina);
            New_Player.skills.push_back(kick);
            New_Player.skills.push_back(guard);

            players.push_back(New_Player);
        }
        else {
            std::cout << "Error loading data for the player: " << line << std::endl;
        }
    }

    return players;
}

//Asign possition for player
std::string assign_positions(const Player& player, const std::map<int, Node>& tree) {
    int id_node = 0;
    while (true) {
        const Node& w = tree.at(id_node);

        
        if (w.skill.empty() || w.condition.empty()) {
            return w.left; 
        }

        
        int index_utilities = -1;
        if (w.skill == "Control") index_utilities = 0;
        else if (w.skill == "Speed") index_utilities = 1;
        else if (w.skill == "Stamina") index_utilities = 2;
        else if (w.skill == "Kick") index_utilities = 3;
        else if (w.skill == "Guard") index_utilities = 4;

        int attribute_value = (index_utilities != -1) ? player.skills.at(index_utilities) : 0;

        bool passage = (w.condition == "<=") ? (attribute_value <= w.value) : (attribute_value > w.value);

        
        std::string next_step = passage ? w.left : w.right;
        std::stringstream ss(next_step);

        if (!(ss >> id_node)) {
            return next_step; 
        }
    }
}

//Create file
void create_file(const std::vector<Player>& players, const std::map<int, Node>& tree) {
    std::ofstream file_wyjsciowy("pozycje_graczy.txt");
    for (const auto& i : players) {
        std::string pozycja = assign_positions(i, tree);
        std::cout << i.name << " " << i.surname << ": " << pozycja << std::endl; 
        file_wyjsciowy << i.name << " " << i.surname << ": " << pozycja << std::endl; 
    }
}

