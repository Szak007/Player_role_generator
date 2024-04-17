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
struct Zawodnik {
	std::string imie=""; ///<Name of player
	std::string nazwisko=""; ///<Surename of player
	std::vector <int> skills; ///<Skill of player
};

/** Structure that describe node with id, skills, requirement, value, left, right
*/

struct Wezel {
	int id = 0; ///<Id of node
	std::string umiejetnosc = ""; ///<Skill in node
	std::string warunek = ""; ///<Requirement of node
	int wartosc = 0; ///<Value of node
	std::string lewo = ""; ///<Left turn in node
	std::string prawo = ""; ///<Right turn in node

};