#include "Additive_Group_of_Zmodn.h"

Additive_Group_of_Zmodn::Additive_Group_of_Zmodn(int number = 1)
{
    n = number;
    for(int i = 0; i < n; i++)
        set.push_back(i);
}

Additive_Group_of_Zmodn::~Additive_Group_of_Zmodn()
{
    if(!set.empty()) set.clear();
}

Additive_Group_of_Zmodn::Additive_Group_of_Zmodn(const Additive_Group_of_Zmodn& group)
{
    n = group.n;
    for (list<int>::const_iterator i = group.set.begin(), j = group.set.end(); i != j; i++)
        set.push_back(*i);
}

Additive_Group_of_Zmodn& Additive_Group_of_Zmodn::setN(int number)
{
    n = number;
    if(!set.empty()) set.clear();
    for(int i = 0; i < n; i++)
        set.push_back(i);
    return *this;
}

inline int Additive_Group_of_Zmodn::getN() const
{
    return n;
}

inline list<int> Additive_Group_of_Zmodn::getSet() const
{
    return set;
}

list<int> Additive_Group_of_Zmodn::getCoset(int number) const
{
    if (number >= 0 && number <= n-1){
        list<int> coset;
        for (list<int>::const_iterator i = set.begin(), j = set.end(); i != j; i++)
            coset.push_back((number+(*i))%n);
        return coset;
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

list<int> Additive_Group_of_Zmodn::getCyclicSubgroup(int number) const
{
    if (number >= 0 && number <= n-1){
        list<int> cyclicsubgroup;
        int power = 1;
        for (list<int>::const_iterator i = set.begin(), j = set.end(); i != j; i++, power++)
        {
            cyclicsubgroup.push_back((number*power)%n);
            if((number*power)%n == 0) break;
        }
        return cyclicsubgroup;
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

int Additive_Group_of_Zmodn::getOrder(int number) const
{
    if (number >= 0 && number <= n-1){
        list<int> cyclicsubgroup = getCyclicSubgroup(number);
        int order = 0;
        for (list<int>::const_iterator i = cyclicsubgroup.begin(), j = cyclicsubgroup.end(); i != j; i++)
        {
            order++;
            if(*i == 0) break;
        }
        return order;
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

int Additive_Group_of_Zmodn::getInverse(int number) const
{
    if (number >= 0 && number <= n-1) return n-number;
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

bool Additive_Group_of_Zmodn::operator<(const Additive_Group_of_Zmodn& gr2)
{
    return n < gr2.n;
}

bool Additive_Group_of_Zmodn::operator>(const Additive_Group_of_Zmodn& gr2)
{
    return n > gr2.n;
}

bool Additive_Group_of_Zmodn::operator==(const Additive_Group_of_Zmodn& gr2)
{
    return n == gr2.n;
}

bool Additive_Group_of_Zmodn::operator!=(const Additive_Group_of_Zmodn& gr2)
{
    return !(*this == gr2);
}

istream& operator>>(istream& istrm, Additive_Group_of_Zmodn& group)
{
    istrm >> group.n;
    if(!group.set.empty()) group.set.clear();
    for(int i = 0; i < group.n; i++)
        group.set.push_back(i);
    return istrm;
}

ostream& operator<<(ostream& ostrm, Additive_Group_of_Zmodn& group)
{
    ostrm << "Set:" << endl << "{";
    for (list<int>::const_iterator i = group.set.begin(), j = group.set.end(); i != j; i++)
    {
        i++;
        if(i == j) {
            i--;
            ostrm << *i;
        }
        else {
            i--;
            ostrm << *i << ", ";
        }
    }
    ostrm << "}" << endl;
}

void Additive_Group_of_Zmodn::print() const
{
    cout << "Set:" << endl << "{";
    for (list<int>::const_iterator i = set.begin(), j = set.end(); i != j; i++)
    {
        i++;
        if(i == j) {
            i--;
            cout << *i;
        }
        else {
            i--;
            cout << *i << ", ";
        }
    }
    cout << "}" << endl;
}

void Additive_Group_of_Zmodn::info() const
{
    cout << "Z_" << n << endl;
}

void findAllHomomorphisms(const Additive_Group_of_Zmodn& gr1, const Additive_Group_of_Zmodn& gr2)
{
    int n, m, m1;
    n = gr1.n;
    m = gr2.n;
    m1 = m/(__gcd(n, m));
    vector<vector<int>> homomorphisms;
    vector<int> homomorphism;
    for (int k = 0; k < __gcd(n,m); k++)
    {
        for(int i = 0; i < n; i++)
            homomorphism.push_back((i*(k*m1))%m);
        homomorphisms.push_back(homomorphism);
        homomorphism.clear();
    }

    cout << "~~~Possible homomorphisms from Z_" << n << " to Z_" << m << "~~~" << endl;
    for (int k = 0; k < __gcd(n,m); k++)
    {
        cout << "f" << k*m1 << ":" << endl;
        for(int i = 0; i < n; i++)
            cout << i << " -> " << homomorphisms[k][i] << endl;
        cout << endl;
    }
}