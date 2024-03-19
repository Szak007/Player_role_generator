
#include "function.h"
#include "struct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

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


//std::map<int, Wezel> wczytaj_drzewo(const std::string& p_drzewo) {
//    std::map<int, Wezel> drzewo;
//    std::cout << p_drzewo; //debug
//    std::ifstream plik(p_drzewo);
//    int id;
//    int wartosc;
//    std::string umiejetnosc;
//    std::string lewo;
//    std::string prawo;
//    char warunek;
//
//    while (plik >> id >> umiejetnosc >> warunek >> wartosc >> lewo >> prawo) {
//        drzewo[id] = { id, umiejetnosc, warunek, wartosc, lewo, prawo };
//    }
//    
//    return drzewo;
//}

//std::map<int, Wezel> wczytaj_drzewo(const std::string& p_drzewo) {
//    std::map<int, Wezel> drzewo;
//    std::ifstream plik(p_drzewo);
//    std::string linia;
//
//    while (getline(plik, linia)) {
//        std::istringstream iss(linia);
//        int id;
//        std::string umiejetnosc, warunek;
//        int wartosc;
//        std::string lewo, prawo;
//
//        iss >> id;
//
//        if (iss >> umiejetnosc >> warunek >> wartosc >> lewo >> prawo) { // Wêze³ decyzyjny
//            drzewo[id] = Wezel{ id, umiejetnosc, warunek, wartosc, lewo, prawo };
//        }
//        else { // Liœæ (pozycja)
//            drzewo[id] = Wezel{ id, umiejetnosc, "", 0, "", "" };
//        }
//    }
//
//    return drzewo;
//}

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

        
        size_t commentIndex = linia.find('%'); //z geeksforgeeks 
        if (commentIndex != std::string::npos) {
            linia = linia.substr(0, commentIndex);
            iss.str(linia);
            iss.clear();
        }

        if (iss >> imie >> nazwisko >> control >> speed >> stamina >> kick >> guard) {
            /*zawodnicy.push_back({ imie, nazwisko, control, speed, stamina, kick, guard });*/ //to mi nie dzia³a³o
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
void tworzenie_pliku(const std::vector<Zawodnik>& zawodnicy, const std::map<int, Wezel>& drzewo) {
    std::ofstream plik_wyjsciowy("pozycje_graczy.txt");
    for (const auto& i : zawodnicy) {
        std::string pozycja = przypisz_pozycje(i, drzewo);
        std::cout << i.imie << " " << i.nazwisko << ": " << pozycja << std::endl; 
        plik_wyjsciowy << i.imie << " " << i.nazwisko << ": " << pozycja << std::endl; 
    }
}


//void tworzenie_pliku(const Zawodnik& zawodnicy, const std::map<int, Wezel>& drzewo, std::string& p_drzewo, std::string& p_dane) {
//    std::ofstream plikWyjsciowy("pozycje_graczy.txt");
//    for (auto& i : zawodnicy) {
//        std::string pozycja = przypisz_pozycje(i, drzewo);
//        std::cout << i.imie << " " << i.nazwisko << ": " << pozycja << std::endl; 
//        plikWyjsciowy << i.imie << " " << i.nazwisko << ": " << pozycja << std::endl; 
//    }
//}

//int wartosc(const std::string& umiejetnosc, const Zawodnik& zawodnik) {
//    if (umiejetnosc == "Control") return zawodnik.control;
//    else if (umiejetnosc == "Speed") return zawodnik.speed;
//    else if (umiejetnosc == "Stamina") return zawodnik.stamina;
//    else if (umiejetnosc == "Kick") return zawodnik.kick;
//    else if (umiejetnosc == "Guard") return zawodnik.guard;
//    return 0; 
//}




//std::string przypisz_pozycje(const Zawodnik& zawodnik, const std::map<int, Wezel>& drzewo) {
//    int id_wezla = 0;
//    std::string nastepny_krok;
//    while (true) {
//        const Wezel& w = drzewo.at(id_wezla);
//        int wartosc_atrybutu = wartosc(w.umiejetnosc, zawodnik);
//        bool przejscie = (w.warunek == '<=') ? (wartosc_atrybutu <= w.wartosc) : (wartosc_atrybutu > w.wartosc);
//
//        nastepny_krok = przejscie ? w.lewo : w.prawo;
//
//        std::stringstream ss(nastepny_krok);
//        
//
//        if (ss >> id_wezla) {
//            
//        }
//        else {
//            break;
//        }
//
//    }
//    return nastepny_krok;
//}

//metoda w ktorej bedzie for i bedzie przechodzil po vector z zawodnikami i bedzie dla kazdego uruchamial przypisz pozycje 

//wypisuje zawodnikow i pozycje do pliku

//sprawdzaæ czy to dzia³a
//poprawiæ vector 



