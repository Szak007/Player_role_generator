
#pragma once

#include "struct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

bool pobieranie_parametrow(int num, char* params[], std::string& plik_drzewa, std::string& plik_danych);
std::map<int, Wezel> wczytaj_drzewo(const std::string& p_drzewo);
std::vector<Zawodnik> wczytaj_zawodnikow(const std::string& p_dane);

std::string przypisz_pozycje(const Zawodnik& zawodnik, const std::map<int, Wezel>& drzewo);
void tworzenie_pliku(const std::vector<Zawodnik>& zawodnicy, const std::map<int, Wezel>& drzewo);


