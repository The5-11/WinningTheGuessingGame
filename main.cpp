#include <iostream>

using guessrange_t = long long; //just change this data type to change all of guessrange_t

/* by Simon Blankenburg
 * started at 09/19/2018
 * finished at --/09/2018
 *
 * This program evaluates the chance to win a hi-lo guessing game
 * (such the one at https://www.learncpp.com/cpp-tutorial/5-x-chapter-5-comprehensive-quiz/ )
 * based on the guessing times and the number range.
 *
 * The idea is to check how many guesses are maximum needed to win the game.
 *
 * Used Method is simple: Enter the median number of the range and check, if the guessing Number is higher or lower
 */

// This should work fine...
guessrange_t getRandomRange() {

    bool noGoodValuesAvailable{true};
    guessrange_t startrange{0};
    do {
        std::cout << "Die erzeugten Zufallszahlen beim Ratespiel liegen im Bereich von (inklusive): \n";

        guessrange_t min;
        std::cin >> min;

        std::cout << "...bis (inklusive): \n";

        guessrange_t max;
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


void printFazit(guessrange_t startrange, guessrange_t guessCount) {
    std::cout << "\nFazit:\n";
    std::cout << "\tBei einer Bereichsgröße von " << startrange <<
              " braucht man mit der Methode 'Mittig halbieren' \n\t"
              "maximal (falls die gesuchte Zahl nicht schon früher direkt erraten wird)\n\t" <<
              guessCount << " Nachfragen um garantiert zu gewinnen.\n";
}


int main() {

    guessrange_t startrange = getRandomRange();

    //short quit, if range is only 1
    if (startrange == 1) {
        std::cout << "Somit errät man die gesuchte Zahl beim 1. Mal.\n";
        return 0;
    }

    guessrange_t range{startrange};
    guessrange_t guessCount{0};
    do {
        //the integer division fits for both (range is even/uneven) cases, because the median number is >not< included in the new range!
        if (range > 1) {
            range /= 2;
            ++guessCount;
        }

        if (range <= 1) {
            if (guessCount > 0) {
                std::cout << "Nach der " << guessCount << ". Nachfrage bleibt maximal noch " << range
                          << " Möglichkeit.\n";
            }

            std::cout << "Somit errät man die gesuchte Zahl spätestens beim " << ++guessCount << ". Mal.\n";
            break;
        }
        std::cout << "Nach der " << guessCount << ". Nachfrage bleiben maximal noch " << range
                  << " Möglichkeiten.\n";
    } while (range >= 1);

    printFazit(startrange, guessCount);

    return 0;
}




/*std::cout << "\nEine Wiederholung des Durchlaufs mit der Annahme, dass bei einer Nachfrage\n"
                 "die gesuchte Zahl immer in dem (wenn möglich) kleineren Bereich ist,\n"
                 "die Zahl aber nicht bereits \"unterwegs\" erraten wird:\n\n";

    int smallerRange{range};
    do {
        //with decrementing smallerRange, the integer division fits also in this situation (smaller range) for both cases!
        // e.g. (6-1)/2=2, (5-1)/2=2
        --smallerRange /= 2;
        ++guessCount;

        if (smallerRange == 1) {
            std::cout << "Nach der " << guessCount << ". Nachfrage bleibt im besseren Fall nur noch " << smallerRange
                      << " Möglichkeit.\n";
            break;
        } else if (smallerRange <= 0) {
            std::cout << "Somit errät man die gesuchte Zahl im besseren Fall beim " << guessCount << ". Mal.\n";
            break;
        }

        std::cout << "Nach der " << guessCount << ". Nachfrage bleiben im \"besseren\" Fall noch " << smallerRange
                  << " Möglichkeiten.\n";


    } while (smallerRange >= 1);*/