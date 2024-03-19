#include "struct.h"
#include "function.h"
#include <iostream>
//Zadanie polega na stworzeniu algorytmu który będzie przyporządkowywać zawodników do odpowiedniej pozycji na boisku. 
//Zalozmy ze będziemy oceniać ich po 5 cechach. Na początku trzeba sobie rozpisać drzewo- bo w oparciu o taki algorytm to rozwiążemy.
//Rozpisz dowolnie na podstawie tych 5 cech jak chciałbyś przyporządkowywać tych zawodników. 
int main(int num, char* params[])
{
    std::string p_drzewo;
    std::string p_dane;

     if (!pobieranie_parametrow(num, params, p_drzewo, p_dane)) {
        std::cout << "pobieranie parametrow sie nie powiodlo\n";
        return 0;

    }

     auto drzewo = wczytaj_drzewo(p_drzewo); 
     auto zawodnicy = wczytaj_zawodnikow(p_dane);

     /*for (auto i : drzewo) {
         std::cout << i.first << "\t" << i.second.id << "\n";

     }*/

     for (const auto& i : zawodnicy) {
         std::string pozycja = przypisz_pozycje(i, drzewo);
         std::cout << i.imie << " " << i.nazwisko << ": " << pozycja << std::endl;
     }
     tworzenie_pliku(zawodnicy, drzewo);
     return 0;
}

//wyczyścić kod i opisać całość w doxywizard