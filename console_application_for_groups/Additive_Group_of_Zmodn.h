#ifndef ADDITIVE_GROUP_OF_ZMODN_H
#define ADDITIVE_GROUP_OF_ZMODN_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class Additive_Group_of_Zmodn
{
protected:

    int n;
    list<int> set;

public:

    Additive_Group_of_Zmodn(int);
    virtual ~Additive_Group_of_Zmodn();
    Additive_Group_of_Zmodn(const Additive_Group_of_Zmodn&);
    Additive_Group_of_Zmodn& setN(int);
    inline int getN() const;
    inline list<int> getSet() const;
    list<int> getCoset(int) const;
    list<int> getCyclicSubgroup(int) const;
    int getOrder(int) const;
    int getInverse(int) const;
    bool operator<(const Additive_Group_of_Zmodn&);
    bool operator>(const Additive_Group_of_Zmodn&);
    bool operator==(const Additive_Group_of_Zmodn&);
    bool operator!=(const Additive_Group_of_Zmodn&);
    friend istream& operator>>(istream&, Additive_Group_of_Zmodn&);
    friend ostream& operator<<(ostream&, Additive_Group_of_Zmodn&);
    void print() const;
    virtual void info() const;

private:

    friend void findAllHomomorphisms(const Additive_Group_of_Zmodn&, const Additive_Group_of_Zmodn&);
};

#endif /* ADDITIVE_GROUP_OF_ZMODN_H */