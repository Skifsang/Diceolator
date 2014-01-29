#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
public:
    Character(const int strength, const int dexterity, const int constitution, const int intelligence,
              const int wisdom, const int charisma);

private:
    const int strength;
    const int dexterity;
    const int constitution;
    const int intelligence;
    const int wisdom;
    const int charisma;
};

#endif // CHARACTER_H
