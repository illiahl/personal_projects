#ifndef ADDITIVE_FACTOR_GROUP_OF_ZMODN_H
#define ADDITIVE_FACTOR_GROUP_OF_ZMODN_H

#include "Additive_Group_of_Zmodn.h"

class Additive_Factor_Group : public Additive_Group_of_Zmodn
{
    int factoringElement;
    list<list<int>> setOfCosets;

public:

    Additive_Factor_Group(int, int);
    ~Additive_Factor_Group();
    Additive_Factor_Group(const Additive_Factor_Group&);
    inline int getFactoringElement() const;
    Additive_Factor_Group& setFactoringElement(int);
    void print() const;
    void info() const;
};

#endif /* ADDITIVE_FACTOR_GROUP_OF_ZMODN_H */