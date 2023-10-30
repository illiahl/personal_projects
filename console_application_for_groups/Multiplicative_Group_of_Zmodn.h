#ifndef MULTIPLICATIVE_GROUP_OF_ZMODN_H
#define MULTIPLICATIVE_GROUP_OF_ZMODN_H

#include "Additive_Group_of_Zmodn.h"
#include <cmath>

class Multiplicative_Group_of_Zmodn : public Additive_Group_of_Zmodn
{

public:

    Multiplicative_Group_of_Zmodn(int);
    virtual ~Multiplicative_Group_of_Zmodn();
    Multiplicative_Group_of_Zmodn(const Multiplicative_Group_of_Zmodn&);
    Multiplicative_Group_of_Zmodn& setN(int);
    list<int> getCoset(int) const;
    list<int> getCyclicSubgroup(int) const;
    int getOrder(int) const;
    int getInverse(int) const;
    void info() const;
};

#endif /* MULTIPLICATIVE_GROUP_OF_ZMODN_H */