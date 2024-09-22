/**@file*/

/*
Player_role_generator
*/

#pragma once

//import library
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

/** Structure that describe Player with name, surname and skills
*/
struct Player {
	std::string name=""; ///<Name of player
	std::string surname=""; ///<Surename of player
	std::vector <int> skills; ///<Skill of player
};

/** Structure that describe node with id, skills, requirement, value, left, right
*/

struct Node {
	int id = 0; ///<Id of node
	std::string skill = ""; ///<Skill in node
	std::string condition = ""; ///<Requirement of node
	int value = 0; ///<Value of node
	std::string left = ""; ///<Left turn in node
	std::string right = ""; ///<Right turn in node

};