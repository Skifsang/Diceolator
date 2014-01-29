#ifndef DICE_H
#define DICE_H

class Dice
{
public:
    Dice(const int numberOfEdges);

    int throwDice (const int numberOfTrows, const int modifier) const;

private:
    const int numberOfEdges;
};

#endif // DICE_H
