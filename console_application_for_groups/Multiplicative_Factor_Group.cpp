#include "Multiplicative_Factor_Group.h"

Multiplicative_Factor_Group::Multiplicative_Factor_Group(int number = 2, int element = 1) : Multiplicative_Group_of_Zmodn(number)
{
    if (element >= 1 && element <= n-1 && __gcd(n, element) == 1){
        factoringElement = element;
        list<int> cyclic_subgroup = getCyclicSubgroup(factoringElement);
        for (list<int>::const_iterator i = set.begin(), j = set.end(); i != j; i++){
            list<int> coset;
            for (list<int>::const_iterator k = cyclic_subgroup.begin(), l = cyclic_subgroup.end(); k != l; k++){
                coset.push_back(((*i)*(*k))%n);
            }
            int p = 0;
            coset.sort();
            for (list<list<int>>::const_iterator f = setOfCosets.begin(), g = setOfCosets.end(); f != g; f++){
                if(coset == *f) p = 1;
            }
            if (p == 0){
                setOfCosets.push_back(coset);
                coset.clear();
            }
            else {
                p = 0;
                coset.clear();
            }
        }
        setOfCosets.unique();
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

Multiplicative_Factor_Group::~Multiplicative_Factor_Group()
{
    if(!set.empty()) set.clear();
    if(!setOfCosets.empty()) setOfCosets.clear();
}

Multiplicative_Factor_Group::Multiplicative_Factor_Group(const Multiplicative_Factor_Group& group) : Multiplicative_Group_of_Zmodn(group)
{
    factoringElement = group.factoringElement;
    for (list<list<int>>::const_iterator i = group.setOfCosets.begin(), j = group.setOfCosets.end(); i != j; i++)
        setOfCosets.push_back(*i);
}

inline int Multiplicative_Factor_Group::getFactoringElement() const
{
    return factoringElement;
}

Multiplicative_Factor_Group& Multiplicative_Factor_Group::setFactoringElement(int element)
{
    if (element >= 0 && element <= n-1 && __gcd(n, element) == 1){
        if(!setOfCosets.empty()) setOfCosets.clear();
        factoringElement = element;
        list<int> cyclic_subgroup = getCyclicSubgroup(factoringElement);
        for (list<int>::const_iterator i = set.begin(), j = set.end(); i != j; i++){
            list<int> coset;
            for (list<int>::const_iterator k = cyclic_subgroup.begin(), l = cyclic_subgroup.end(); k != l; k++){
                coset.push_back(((*i)*(*k))%n);
            }
            int p = 0;
            for (list<list<int>>::const_iterator f = setOfCosets.begin(), g = setOfCosets.end(); f != g; f++){
                if(coset == *f) p = 1;
            }
            if (p == 0){
                coset.sort();
                setOfCosets.push_back(coset);
                coset.clear();
            }
            else {
                p = 0;
                coset.clear();
            }
        }
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

void Multiplicative_Factor_Group::print() const
{
    cout << "Set of cosets:" << endl << "{";
    for (list<list<int>>::const_iterator i = setOfCosets.begin(), j = setOfCosets.end(); i != j; i++)
    {
        list<int> coset = *i;
        cout << "{";
        for (list<int>::const_iterator k = coset.begin(), l = coset.end(); k != l; k++)
        {
            k++;
            if(k == l) {
                k--;
                cout << *k;
            }
            else {
                k--;
                cout << *k << ", ";
            }
        }
        i++;
        if(i == j) {
            i--;
            cout << "}";
        }
        else {
            i--;
            cout << "}, ";
        }
    }
    cout << "}" << endl;
}

void Multiplicative_Factor_Group::info() const
{
    cout << "Z*_" << n << "/[" << factoringElement << "]" << endl;
}