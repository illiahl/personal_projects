#ifndef PERMUTATION
#define PERMUTATION

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

template <typename T>
class Permutation 
{
    int length;
    map<int, T> alphabet; 
    vector<int> matrix;
    static int countOfPermutations;

public:

    Permutation(int);
    Permutation(const Permutation&);
    Permutation(vector<int>);
    ~Permutation();
    operator vector<int>();
    inline int getLength() const;
    list<list<int>> getCycleDecomposition() const;
    int getOrder() const;
    int getSign() const;
    Permutation<T> getInverse() const;
    Permutation<T> operator*(const Permutation&);
    Permutation<T>& operator=(const Permutation&);
    int operator[](int);
    void print() const;
    void info() const;
    inline static int getCountOfPermutations();
};

#endif /* PERMUTATION */