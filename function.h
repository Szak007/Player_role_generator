/**@file*/

/*
Player_role_generator
*/

#pragma once

//header file import 
#include "struct.h"

//import library
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

//File that have definition of functions

/** Function that takes parameters in the main function
* @param num numerber of parameters
* @param params parameters from file
* @param file_trees tree file
* @param file_data dane file
* @author Jacek
* @date 2024-02-21
* @return return 0 if file dont work, return 1 if file work
*/
bool download_parameters(int num, char* params[], std::string& file_trees, std::string& file_data);



/** Function that load data from tree file
* @param f_tree path to the tree file
* @author Jacek
* @date 2024-02-21
* @return std::map<int, Node> map of tree nodes loaded from file
*/
std::map<int, Node> load_tree(const std::string& f_tree);

/** Function that load data from dane file
* @param f_data path to the dane file
* @author Jacek
* @date 2024-02-21
* @return std::vector<Player> vector of players loaded from file
*/
std::vector<Player> load_players(const std::string& f_data);

/** Function to assign position for player
* @param player player to assign position
* @param tree tree structure with position rules
* @author Jacek
* @date 2024-02-21
* @return std::string assigned position for the player
*/
std::string assign_positions(const Player& player, const std::map<int, Node>& tree);

/** Function to create file
* @param players vector of players
* @param tree tree structure with position rules
* @author Jacek
* @date 2024-02-21
* @return void
*/
void create_file(const std::vector<Player>& players, const std::map<int, Node>& tree);



