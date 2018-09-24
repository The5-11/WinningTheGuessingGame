#include <iostream>

/* by Simon Blankenburg
 * started at 09/19/2018
 * finished at 09/24/2018
 *
 * The initial idea is to check how many guesses are maximum needed to win the game.
 * This program additionally evaluates the chance to win a hi-lo guessing game
 * (such the one at https://www.learncpp.com/cpp-tutorial/5-x-chapter-5-comprehensive-quiz/ )
 * based on the guessing times and the number range.
 *
 * Used Method is simple: Enter the median number of the range and check, if the Number to be guessed is higher or lower
 */

int getRandomRange() {

    bool noGoodValuesAvailable{true};
    int startrange{0};
    do {
        std::cout
            << "Die erzeugten Zufallszahlen beim Ratespiel liegen im Bereich von (inklusive): \n";

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
            std::cout << "Es gibt also " << startrange << " Möglichkeiten.\n"
                                                          "(Die Wahrscheinlichkeit, die gesuchte Zahl bei der 1. Nachfrage direkt zu erraten beträgt "
                      << (100.0 / startrange) << "%.)\n\n";
            noGoodValuesAvailable = false;
        } else if (startrange == 1) {
            std::cout << "Es gibt nur " << startrange << " Möglichkeit.\n\n";
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
              guessCount << " Nachfrage(n) um garantiert zu gewinnen.\n";
}

int doItRecursive(int range, int tempGuessCount) {
    if (range < 0) {
        std::cout << "range ist kleiner als 0.\n";
    } else if (range == 0) {
        std::cout << "Somit errät man die gesuchte Zahl (spätestens) beim " << tempGuessCount << ". Mal.\n";
        return tempGuessCount;
    } else if (tempGuessCount == 0) {
        return doItRecursive(range / 2, ++tempGuessCount);
    } else {
        std::cout << "Nach der " << tempGuessCount << ". Nachfrage bleiben maximal noch " << range
                  << " Möglichkeit(en).\n"
                     "(Die Wahrscheinlichkeit, die gesuchte Zahl bei der " << (tempGuessCount + 1)
                  << ". Nachfrage direkt zu erraten beträgt " << (100.0 / range) << "%.)\n\n";

        return doItRecursive(range / 2, ++tempGuessCount);
    }
    return 0; //should never be reached
}


int main() {

    std::cout << "[Rekursive Variante]\n\n";
    int startrange = getRandomRange();
    int range{startrange};

    printConclusion(startrange, doItRecursive(range, 0));

    return 0;
}
