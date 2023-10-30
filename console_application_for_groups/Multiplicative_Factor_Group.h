#ifndef MULTIPLICATIVE_FACTOR_GROUP_OF_ZMODN_H
#define MULTIPLICATIVE_FACTOR_GROUP_OF_ZMODN_H

#include "Multiplicative_Group_of_Zmodn.h"

class Multiplicative_Factor_Group : public Multiplicative_Group_of_Zmodn
{
    int factoringElement;
    list<list<int>> setOfCosets;
    
public:

    Multiplicative_Factor_Group(int, int);
    ~Multiplicative_Factor_Group();
    Multiplicative_Factor_Group(const Multiplicative_Factor_Group&);
    inline int getFactoringElement() const;
    Multiplicative_Factor_Group& setFactoringElement(int);
    void print() const;
    void info() const;
};

#endif /* MULTIPLICATIVE_FACTOR_GROUP_OF_ZMODN_H */