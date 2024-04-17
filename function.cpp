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
bool pobieranie_parametrow(int num, char* params[], std::string& p_drzewo, std::string& p_dane) {
    std::cout << params[0] << "\n";
    if (num < 5) {
        std::cout << "nie poprawna ilosc parametrow\n";
        return 0;
    }
    for (int i = 1; i < num; i += 2) {
        if ((std::string)params[i] == "-t") {
            std::ifstream p_jeden(params[i + 1]);
            p_drzewo = params[i + 1];
            if (!p_jeden) {
                std::cout << "nie dziala plik jeden - drzewo\n";
                return 0;
            }
        }
        else if ((std::string)params[i] == "-d") {
            std::ifstream p_dwa(params[i + 1]);
            p_dane = params[i + 1];
            if (!p_dwa) {
                std::cout << "nie dziala plik dwa - dane\n";
                return 0;
            }
        }
        else {
            std::cout << "zle parametry\n";
            return 0;
        }
    }
    return 1;
}


//Load data from drzewo file
std::map<int, Wezel> wczytaj_drzewo(const std::string& p_drzewo) {
    std::map<int, Wezel> drzewo;
    std::ifstream plik(p_drzewo);
    std::string linia;

    while (getline(plik, linia)) {
        std::istringstream iss(linia);
        int id, wartosc;
        std::string umiejetnosc, warunek, lewo, prawo;
        

        iss >> id;
        if (iss >> umiejetnosc >> warunek >> wartosc >> lewo >> prawo) { // Wêze³ decyzyjny
            drzewo[id] = Wezel{ id, umiejetnosc, warunek, wartosc, lewo, prawo };
        }
        else { 
            drzewo[id] = Wezel{ id, "", "", 0, umiejetnosc, "" };
        }
    }

    return drzewo;
}


//Load data from dane file
std::vector<Zawodnik> wczytaj_zawodnikow(const std::string& p_dane) {
    std::vector<Zawodnik> zawodnicy;
    std::ifstream plik(p_dane);
    std::string linia;
    
    std::getline(plik, linia);

    while (std::getline(plik, linia)) {
        
        if (linia.empty() || linia[0] == '%') continue;

        std::istringstream iss(linia);
        std::string imie;
        std::string nazwisko;
        int control;
        int speed;
        int stamina;
        int kick;
        int guard;

        
        size_t commentIndex = linia.find('%'); 
        if (commentIndex != std::string::npos) {
            linia = linia.substr(0, commentIndex);
            iss.str(linia);
            iss.clear();
        }

        if (iss >> imie >> nazwisko >> control >> speed >> stamina >> kick >> guard) {
            
            Zawodnik nowyZawodnik;
            nowyZawodnik.imie = imie;
            nowyZawodnik.nazwisko = nazwisko;
            
            nowyZawodnik.skills.push_back(control);
            nowyZawodnik.skills.push_back(speed);
            nowyZawodnik.skills.push_back(stamina);
            nowyZawodnik.skills.push_back(kick);
            nowyZawodnik.skills.push_back(guard);

            zawodnicy.push_back(nowyZawodnik);
        }
        else {
            std::cout << "Blad wczytywania danych dla zawodnika: " << linia << std::endl;
        }
    }

    return zawodnicy;
}

//Asign possition for player
std::string przypisz_pozycje(const Zawodnik& zawodnik, const std::map<int, Wezel>& drzewo) {
    int id_wezla = 0;
    while (true) {
        const Wezel& w = drzewo.at(id_wezla);

        
        if (w.umiejetnosc.empty() || w.warunek.empty()) {
            return w.lewo; 
        }

        
        int indeksUmiejetnosci = -1;
        if (w.umiejetnosc == "Control") indeksUmiejetnosci = 0;
        else if (w.umiejetnosc == "Speed") indeksUmiejetnosci = 1;
        else if (w.umiejetnosc == "Stamina") indeksUmiejetnosci = 2;
        else if (w.umiejetnosc == "Kick") indeksUmiejetnosci = 3;
        else if (w.umiejetnosc == "Guard") indeksUmiejetnosci = 4;

        int wartosc_atrybutu = (indeksUmiejetnosci != -1) ? zawodnik.skills.at(indeksUmiejetnosci) : 0;

        bool przejscie = (w.warunek == "<=") ? (wartosc_atrybutu <= w.wartosc) : (wartosc_atrybutu > w.wartosc);

        
        std::string nastepny_krok = przejscie ? w.lewo : w.prawo;
        std::stringstream ss(nastepny_krok);

        if (!(ss >> id_wezla)) {
            return nastepny_krok; 
        }
    }
}

//Create file
void tworzenie_pliku(const std::vector<Zawodnik>& zawodnicy, const std::map<int, Wezel>& drzewo) {
    std::ofstream plik_wyjsciowy("pozycje_graczy.txt");
    for (const auto& i : zawodnicy) {
        std::string pozycja = przypisz_pozycje(i, drzewo);
        std::cout << i.imie << " " << i.nazwisko << ": " << pozycja << std::endl; 
        plik_wyjsciowy << i.imie << " " << i.nazwisko << ": " << pozycja << std::endl; 
    }
}

