#include "Dice.h"
#include <QtGlobal>

Dice::Dice(const int numberOfEdges) :
    numberOfEdges(numberOfEdges)
{
}

int Dice::throwDice(const int numberOfTrows, const int modifier) const
{
    int sum = 0;
    for (int i = 0; i < numberOfTrows; i++){
        sum += (qrand() % numberOfEdges) + 1 + modifier;
    }
    return sum;
}
