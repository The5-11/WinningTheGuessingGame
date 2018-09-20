#include <iostream>

/* by Simon Blankenburg
 * started at 09/19/2018
 * finished at --/09/2018
 *
 * This program evaluates the chance to win a hi-lo guessing game
 * (such the one at https://www.learncpp.com/cpp-tutorial/5-x-chapter-5-comprehensive-quiz/ )
 * based on the guessing times and the number range.
 *
 * The idea is to check if it's possible to win the game every time when guessing times
 * is high in relation to the number range.
 *
 * Used Method is simple: enter the medean number in between the range and check, if it is higher or lower and so on
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


int main() {

    int range = getRandomRange();
    int guessCount{0};

    do {
        if (range % 2 == 1) {

            //caused by the integer division this line returns the larger of the 2 parts
            range = range - (range / 2);
            ++guessCount;
        } else {
            range /= 2;
            ++guessCount;
        }

        if (range <= 1) {
            std::cout << "Nach dem " << guessCount << ". Versuch bleibt nur noch " << range << " Möglichkeit.\n";
            break;
        }

        std::cout << "Nach dem " << guessCount << ". Versuch bleiben maximal noch " << range << " Möglichkeiten.\n";


    } while (range >= 1);
    return 0;
}