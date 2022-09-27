// ConsoleAppCour27-09.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//<>fichier pris, ''fichier a nous
#include <iostream>
#include <string>

using namespace std;

struct Toto
{
    float x = 0.555f;
};

int main()
{
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
    }
};
