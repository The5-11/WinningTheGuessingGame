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

// should alreday work...
int getRandomRange() {
    std::cout << "Die erzeugten Zufallszahlen beim Ratespiel liegen im Bereich von (inklusive): \n";
    int min;
    std::cin >> min;
    std::cout << "...bis (inklusive): \n";
    int max;
    std::cin >> max;

    std::cout << "Es gibt also " << (max - min + 1) << " Möglichkeiten.\n";
    return (max - min + 1);
}

void printFazit(int range, int smaller, int larger) {
    /* You have to add 1 to both, because they tell the number of attempts needed so that there is only 1 possibilty >left<.
     * so you have to make the "final" attempt
     */
    ++smaller;
    ++larger;

    std::cout << "\nFazit:\n";
    if (larger > smaller) {
        std::cout << "\tBei einer Bereichsgröße von " << range <<
                  " braucht man mit der Methode 'Mittig halbieren' \n\t"
                  "im schlechtesten Fall zwischen " << smaller << " und " << larger <<
                  " Versuchen um garantiert zu gewinnen.";
    }
    if (larger == smaller) {
        std::cout << "\tBei einer Bereichsgröße von " << range <<
                  " braucht man mit der Methode 'Mittig halbieren' \n\t"
                  "im schlechtesten Fall " << larger <<
                  " Versuche um garantiert zu gewinnen.";
    }
    if (smaller > larger) {
        std::cout << "Fehler in 'printFazit()'! 'smaller' ist größer als 'larger'!";
    }

}

int main() {

    int range = getRandomRange();
    int largerRange{range};
    int smallerRange{range};
    int guessCount{0};
    std::cout << "\n";

    do {
        if (largerRange % 2 == 1) {

            //caused by the integer division this line returns the larger of the 2 parts
            largerRange = largerRange - (largerRange / 2);
            ++guessCount;
        } else {
            largerRange /= 2;
            ++guessCount;
        }

        if (largerRange <= 1) {
            std::cout << "Nach dem " << guessCount << ". Versuch bleibt nur noch " << largerRange << " Möglichkeit.\n";
            break;
        }

        std::cout << "Nach dem " << guessCount << ". Versuch bleiben maximal noch " << largerRange
                  << " Möglichkeiten.\n";


    } while (largerRange >= 1);

    int largerGuessCount = guessCount;
    guessCount = 0;

    std::cout << "\nEine Wiederholung des Durchlaufs mit der Annahme, dass bei ungerader Bereichsgröße "
                 "immer der kleinere Bereich die zu erratende Zahl enthält:\n\n";
    do {
        smallerRange /= 2;
        ++guessCount;

        if (smallerRange <= 1) {
            std::cout << "Nach dem " << guessCount << ". Versuch bleibt nur noch " << smallerRange << " Möglichkeit.\n";
            break;
        }

        std::cout << "Nach dem " << guessCount << ". Versuch bleiben im \"besseren\" Fall noch " << smallerRange
                  << " Möglichkeiten.\n";


    } while (smallerRange >= 1);

    printFazit(range, guessCount, largerGuessCount);

    return 0;
}