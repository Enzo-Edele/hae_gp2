// ConsoleAppCour27-09.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//<>fichier pris, ''fichier a nous
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct Toto
{
    float x = 0.555f;
};

int main()
{
    struct Test
    {
        float y = 0.4444f;
    };
    {
        //std::cout << "Hello World!\n";
        printf("12345\n");
        printf("0\n");
        std::string zero = "0";
        char zeroC[] = "0";

        std::cout << zeroC << " c++ style \n";
        //console.print(zeroC)
        printf("%s c style\n", zeroC);
        printf("%0.2f \n", 0.666666f);

        float half = 0.5f;
        //afficher ca en c style avec chaine de format %f
        printf("%0.1f \n", half);
        //
        //et en c++ style avec std::to_string()
        std::cout << std::to_string(half) << "\n";
    }

    {
        int val = 123456789123456789; //sup a 2 milliard donc plus de 32bits
        printf("%i\n", val);
        cout << std::to_string(val) << "\n";

        uint64_t val64 = 123456789123456789;
        printf("%lld\n", val64);
        cout << to_string(val64) << "\n";
    }

    {
        Toto toto;
        cout << to_string(toto.x) << "\n";

        Test test;
        cout << to_string(test.y) << "\n";
    }

    {
        std::unordered_map<int, std::string> t;
        t[0] = "toto";
        cout << t[0] << "\n";

        for (std::unordered_map<int, std::string>::iterator iter = t.begin(); iter != t.end(); iter++) { //recup iterateur
            auto& p = *iter;  //esperluette pour faire reference en utilisant l'étoile qui demande le contenu
            cout << p.first << "=" << p.second << "\n";
        }

        for (std::pair<const int, std::string>& p : t) {
            cout << p.first << "=" << p.second << "\n";
        }
    }

    {
        int c = 0;
        int tab[] = { 0, 1 ,2 ,3 ,4 };
        int* d = &tab[0]; //d a l'adresse de tab[0] et modifier d modifie l'adresse contenue dans d(donc ce qu'il reference)
        d++;
        *d = 666;
        int* e0 = nullptr;
        int* e1 = NULL;
        int* e2 = 0;
        int here = 0;
    }
    {
        int c = 0;
        int& d = c; //d reference c modifier d va modifier c, d reference c
        d++;
        int here = 0;
    }
    {
        int tab[] = { 66, 1, 2 ,3 };
        int* c = & tab[0];
        *c = 0;
        *c++;
        *++c;
        c++;
    }
}

template<typename T>
class Array {

};
