#include <iostream>

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
int getRandomRange() {
    std::cout << "Die erzeugten Zufallszahlen beim Ratespiel liegen im Bereich von (inklusive): \n";
    int min;
    std::cin >> min;
    std::cout << "...bis (inklusive): \n";
    int max;
    std::cin >> max;
    int startrange = max - min + 1;
    if (startrange > 1) {
        std::cout << "Es gibt also " << startrange << " Möglichkeiten.\n";
    } else if (startrange == 1) {
        std::cout << "Es gibt also nur " << startrange << " Möglichkeit.\n";
    } else {
        std::cout << "FEHLER in 'getRandomRange()'. Wahrscheinlich wurden die Bereichsgrenzen vertauscht.\n"
                     "Die Ausführung wird mit getauschten Bereichsgrenzen fortgesetzt.";
        return (min - max + 1);
    }

    return (startrange);
}


void printFazit(int range, int smaller, int larger) {

    std::cout << "\nFazit:\n";
    if (larger > smaller) {
        std::cout << "\tBei einer Bereichsgröße von " << range << " braucht man mit der Methode 'Mittig halbieren' \n\t"
                                                                  "maximal (falls die gesuchte Zahl nicht schon früher direkt erraten wird)\n\t"
                                                                  "(zwischen " << smaller << " und) " << larger
                  << " Nachfragen um garantiert zu gewinnen.";
    }
    if (larger == smaller) {
        std::cout << "\tBei einer Bereichsgröße von " << range <<
                  " braucht man mit der Methode 'Mittig halbieren' \n\t"
                  "maximal (falls die gesuchte Zahl nicht schon früher direkt erraten wird)\n\t" <<
                  larger << " Nachfragen um garantiert zu gewinnen.";
    }
    if (smaller > larger) {
        std::cout << "FEHLER in 'printFazit()'. 'smaller' > 'larger'!";
    }

}


int main() {

    int range = getRandomRange();

    if (range == 1) {
        std::cout << "Somit errät man die gesuchte Zahl beim 1. Mal.";
        return 0;
    }

    int guessCount{0};
    std::cout << "\n";


    int largerRange{range};
    do {
        //the integer division fits for both (range is even/uneven) cases, because the median number is not included in the new range!
        if (largerRange > 1) {
            largerRange /= 2;
            ++guessCount;
        }

        if (largerRange <= 1) {
            if (guessCount > 0) {
                std::cout << "Nach der " << guessCount << ". Nachfrage bleibt maximal noch " << largerRange
                          << " Möglichkeit.\n";
            }

            std::cout << "Somit errät man die gesuchte Zahl spätestens beim " << ++guessCount << ". Mal.\n";
            break;
        }
        std::cout << "Nach der " << guessCount << ". Nachfrage bleiben maximal noch " << largerRange
                  << " Möglichkeiten.\n";
    } while (largerRange >= 1);

    int largerGuessCount = guessCount;
    guessCount = 0;

    std::cout << "\nEine Wiederholung des Durchlaufs mit der Annahme, dass bei einer Nachfrage\n"
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


    } while (smallerRange >= 1);

    printFazit(range, guessCount, largerGuessCount);

    return 0;
}