# Player Role Generator

## Overview

The **Player Role Generator** is a C++ application designed to randomly assign roles to players in a game. The application efficiently manages player data using a binary tree structure and allows for reading and writing player information to text files. The project leverages the **Standard Template Library (STL)** for sorting and managing data.

## Features

- Random assignment of roles to players.
- Efficient data storage using **binary trees**.
- File operations for saving and loading player data.
- Data sorting and searching using **STL algorithms**.

## Technologies

- **Programming Language**: C++
- **Data Structures**: Binary Tree
- **Libraries**: Standard Template Library (STL - vector, map)
- **File Operations**: Read and write from text files

## Installation and Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/Szak007/Player_role_generator.git
   ```
2. Compile the project using your favorite C++ compiler:
   ```bash
   g++ -o player_role_generator main.cpp
   ```
3. Run the program:
   ```bash
   ./player_role_generator
   ```
4. Run the program with the required parameters:
   ```bash
   ./player_role_generator -t tree.txt -d data.txt
   ```

## Project Structure

- **main.cpp**: The main entry point of the application.
- **player.cpp**: File containing the Player class and its methods.
- **binary_tree.cpp**: File with the implementation of the binary tree structure.
- **data.txt**: Sample text file with player data.

## Skills Demonstrated

- Management of data structures (**binary tree**).
- Handling **file operations** for reading and writing data.
- Implementation of **sorting** and **search** mechanisms using **STL**.

## Future Improvements

- Extend the program to support more complex game mechanics.
- Add a graphical interface using a framework like **Qt**.
