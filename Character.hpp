
#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
public:
    Character(int n);
    ~Character();
    void set_nValue(int n);
    int get_nValue();

private:
    int nValue;
};

#endif