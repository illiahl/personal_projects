#include "Multiplicative_Group_of_Zmodn.h"

Multiplicative_Group_of_Zmodn::Multiplicative_Group_of_Zmodn(int number = 2) : Additive_Group_of_Zmodn(number)
{   
    for (int i = 0; i < number; i++)
        if(__gcd(number, i) != 1) set.remove(i);
}

Multiplicative_Group_of_Zmodn::~Multiplicative_Group_of_Zmodn()
{
    if(!set.empty()) set.clear();
}

Multiplicative_Group_of_Zmodn::Multiplicative_Group_of_Zmodn(const Multiplicative_Group_of_Zmodn& group) : Additive_Group_of_Zmodn(group) {}

Multiplicative_Group_of_Zmodn&::Multiplicative_Group_of_Zmodn::setN(int number)
{
    n = number;
    if(!set.empty()) set.clear();
    for(int i = 0; i < n; i++)
        if(__gcd(n,i) == 1) set.push_back(i);
    return *this;
}

list<int> Multiplicative_Group_of_Zmodn::getCoset(int number) const
{
    if (number >= 1 && number <= n-1 && __gcd(n, number) == 1){
        list<int> coset;
        for (list<int>::const_iterator i = set.begin(), j = set.end(); i != j; i++)
            coset.push_back((number*(*i))%n);
        return coset;
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

list<int> Multiplicative_Group_of_Zmodn::getCyclicSubgroup(int number) const
{
    if (number >= 1 && number <= n-1 && __gcd(n, number) == 1){
        list<int> cyclicsubgroup;
        int power = 1;
        for (list<int>::const_iterator i = set.begin(), j = set.end(); i != j; i++, power++)
        {
            int k = pow(number,power);
            cyclicsubgroup.push_back(k%n);
            if(k%n == 1) break;
        }
        return cyclicsubgroup;
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

int Multiplicative_Group_of_Zmodn::getOrder(int number) const
{
    if (number >= 1 && number <= n-1 && __gcd(n, number) == 1){
        list<int> cyclicsubgroup = getCyclicSubgroup(number);
        int order = 0;
        for (list<int>::const_iterator i = cyclicsubgroup.begin(), j = cyclicsubgroup.end(); i != j; i++)
        {
            order++;
            if(*i == 1) break;
        }
        return order;
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

int Multiplicative_Group_of_Zmodn::getInverse(int number) const
{
    if (number >= 1 && number <= n-1 && __gcd(n, number) == 1){
        list<int> cyclicsubgroup = getCyclicSubgroup(number);
        for (list<int>::const_iterator i = cyclicsubgroup.begin(), j = cyclicsubgroup.end(); i != j; i++)
            if(*i == 1) {
                i--;
                return *i;
            }
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

void Multiplicative_Group_of_Zmodn::info() const 
{
    cout << "Z*_" << n << endl;
}