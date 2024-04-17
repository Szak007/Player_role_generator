/**@file*/

/*
Player_role_generator
*/

//header file import 
#include "struct.h"
#include "function.h"

//import library
#include <iostream>

/** Main function managing
* @param num number of initial parameters
* @param params parameters
*/
int main(int num, char* params[])
{
    // Variables for storing paths to the data files
    std::string p_drzewo; ///< hold path to drzewo.txt file
    std::string p_dane; ///< hold path to dane.txt file

    // Attempt to retrieve the file paths from provided parameters
     if (!pobieranie_parametrow(num, params, p_drzewo, p_dane)) {
        std::cout << "pobieranie parametrow sie nie powiodlo\n";
        return 0;

    }

     // Load the tree structure from the 'drzewo' file
     auto drzewo = wczytaj_drzewo(p_drzewo); 

     // Load player data from the 'dane' file
     auto zawodnicy = wczytaj_zawodnikow(p_dane);

     // Create the output file with assigned player roles
     tworzenie_pliku(zawodnicy, drzewo);

     return 0;
}

//wyczyścić kod i opisać całość w doxywizard