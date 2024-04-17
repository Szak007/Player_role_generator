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
* @param plik_drzewa drzewo file
* @param plik_danych dane file
* @author Jacek
* @date 2024-02-21
* @return return 0 if file dont work, return 1 if file work
*/
bool pobieranie_parametrow(int num, char* params[], std::string& plik_drzewa, std::string& plik_danych);



/** Function that load data from drzewo file
* @param p_drzewo path to the drzewo file
* @author Jacek
* @date 2024-02-21
* @return std::map<int, Wezel> map of tree nodes loaded from file
*/
std::map<int, Wezel> wczytaj_drzewo(const std::string& p_drzewo);

/** Function that load data from dane file
* @param p_dane path to the dane file
* @author Jacek
* @date 2024-02-21
* @return std::vector<Zawodnik> vector of players loaded from file
*/
std::vector<Zawodnik> wczytaj_zawodnikow(const std::string& p_dane);

/** Function to assign position for player
* @param zawodnik player to assign position
* @param drzewo tree structure with position rules
* @author Jacek
* @date 2024-02-21
* @return std::string assigned position for the player
*/
std::string przypisz_pozycje(const Zawodnik& zawodnik, const std::map<int, Wezel>& drzewo);

/** Function to create file
* @param zawodnicy vector of players
* @param drzewo tree structure with position rules
* @author Jacek
* @date 2024-02-21
* @return void
*/
void tworzenie_pliku(const std::vector<Zawodnik>& zawodnicy, const std::map<int, Wezel>& drzewo);



