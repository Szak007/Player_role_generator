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
    std::string f_tree; ///< hold path to tree.txt file
    std::string f_data; ///< hold path to dane.txt file

    // Attempt to retrieve the file paths from provided parameters
     if (!download_parameters(num, params, f_tree, f_data)) {
        std::cout << "pobieranie parametrow sie nie powiodlo\n";
        return 0;

    }

     // Load the tree structure from the 'tree' file
     auto tree = load_tree(f_tree); 

     // Load player data from the 'dane' file
     auto players = load_players(f_data);

     // Create the output file with assigned player roles
     create_file(players, tree);

     return 0;
}

