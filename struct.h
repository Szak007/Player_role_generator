#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

struct Zawodnik {
	std::string imie="";
	std::string nazwisko="";
	std::vector <int> skills;
	/*int control=0;
	int speed=0;
	int stamina=0;
	int kick=0;
	int guard=0;*/
};

struct Wezel {
	int id = 0;
	std::string umiejetnosc = "";
	std::string warunek = ""; // <=
	int wartosc = 0;
	std::string lewo = "";
	std::string prawo = "";

};