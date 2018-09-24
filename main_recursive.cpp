#include <iostream>

int guessCount{0}; //see below

int getRandomRange() {

    bool noGoodValuesAvailable{true};
    int startrange{0};
    do {
        std::cout << "Die erzeugten Zufallszahlen beim Ratespiel liegen im Bereich von (inklusive): \n";

        int min;
        std::cin >> min;

        if (!std::cin.fail()) {
            std::cout << "...bis (inklusive): \n";
        }

        int max;
        std::cin >> max;

        if (std::cin.fail()) {
            std::cout << "Fehlerhafte Eingabe.\n\n";
            std::cin.clear(); //back in 'normal' operation mode
            std::cin.ignore(32767, '\n'); //remove bad input
            noGoodValuesAvailable = true;
            continue;
        }

        startrange = max - min + 1;

        if (startrange > 1) {
            std::cout << "Es gibt also " << startrange << " Möglichkeiten.\n\n";
            noGoodValuesAvailable = false;
        } else if (startrange == 1) {
            std::cout << "Es gibt also nur " << startrange << " Möglichkeit.\n\n";
            noGoodValuesAvailable = false;
        } else {
            std::cout << "FEHLER in 'getRandomRange()'. Wahrscheinlich wurden die Bereichsgrenzen vertauscht\n"
                         "oder die eingegebenen Zahlen sind zu groß. \nBitte erneut eingeben.\n\n";
            noGoodValuesAvailable = true;

        }
    } while (noGoodValuesAvailable);


    return (startrange);
}


void printConclusion(int startrange, int guessCount) {
    std::cout << "\nFazit:\n";
    std::cout << "\tBei einer Bereichsgröße von " << startrange <<
              " braucht man mit der Methode 'Mittig halbieren' \n\t"
              "maximal (falls die gesuchte Zahl nicht schon früher direkt erraten wird)\n\t" <<
              guessCount << " Nachfragen um garantiert zu gewinnen.\n";
}

//I have to think about a better function name
void doItRecursive(int range, int tempGuessCount) {
    if (range < 0) {
        std::cout << "range ist kleiner als 0.\n";
    } else if (range == 0) {
        std::cout << "Somit errät man die gesuchte Zahl (spätestens) beim " << tempGuessCount << ". Mal.\n";
    } else if (tempGuessCount == 0) {
        doItRecursive(range / 2, ++tempGuessCount);
    } else {
        std::cout << "Nach der " << tempGuessCount << ". Nachfrage bleiben maximal noch " << range
                  << " Möglichkeiten.\n";
        doItRecursive(range / 2, ++tempGuessCount);
        ++guessCount; //not perfect, but I didn't know how to use tempGuessCount also in the main function
    }
}


int main() {

    int startrange = getRandomRange();

    int range{startrange};
    int tempGuessCount{0};

    doItRecursive(range, tempGuessCount);

    printConclusion(startrange, ++guessCount);

    return 0;
}
