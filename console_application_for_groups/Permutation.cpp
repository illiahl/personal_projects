#include "Permutation.h"

template <typename T>
Permutation<T>::Permutation(int len)
{
    length = len;
    cout << "Enter set:" << endl;
    for (int i = 0; i < length; i++){
        T element;
        cout << "Enter " << i+1 << " element: ";
        cin >> element;
        alphabet.insert(typename map<int, T>::value_type(i, element));
    }
    cout << "Enter permutation:" << endl;
    for (int i = 0; i < length; i++){
        cout << i+1 << " -> ";
        while(true){
            int k;
            cin >> k;
            if (k >= 1 && k <= length){
                int p = 0;
                for (int j = 0; j < length; j++)
                    if (!matrix.empty() && matrix[j] == k) p = 1;
                if (p == 0){
                    matrix.push_back(k);
                    break;
                }
                else cout << "Invalid input data" << endl;
            }
            else cout << "Invalid input data" << endl;
        }
    }
    countOfPermutations++;
    cout << endl;
}

template <typename T>
Permutation<T>::Permutation(const Permutation<T>& perm)
{
    length = perm.length;
    if(!matrix.empty()) matrix.clear();
    for (int i = 0; i < length; i++)
        matrix.push_back(perm.matrix[i]);
    if(!alphabet.empty()) alphabet.clear();
    alphabet = perm.alphabet;
}

template <typename T>
Permutation<T>::Permutation(vector<int> mat)
{
    length = mat.size();
    matrix = mat;
    cout << "Enter set:" << endl;
    for (int i = 0; i < length; i++){
        T element;
        cout << "Enter " << i+1 << " element: ";
        cin >> element;
        alphabet.insert(typename map<int, T>::value_type(i, element));
    }
}

template<>
Permutation<int>::Permutation(vector<int> mat)
{
    length = mat.size();
    matrix = mat;
    for (int i = 0; i < length; i++)
        alphabet.insert(pair<int, int>(i, i+1));
}

template <typename T>
Permutation<T>::~Permutation()
{
    if(!matrix.empty()) matrix.clear();
    if(!alphabet.empty()) alphabet.clear();
}

template <typename T>
Permutation<T>::operator vector<int>()
{
    return matrix;
}

template <typename T>
inline int Permutation<T>::getLength() const
{
    return length;
}

template <typename T>
list<list<int>> Permutation<T>::getCycleDecomposition() const
{
    list<list<int>> cycle_decomposition;
    list<int> cycle;
    for(int i = 1; i <= length; i++){
        int p = 0;
        for (list<list<int>>::const_iterator f = cycle_decomposition.begin(), g = cycle_decomposition.end(); f != g; f++)
            for(list<int>::const_iterator q = (*f).begin(), r = (*f).end(); q != r; q++)
                if (i == *q) p = 1;
        if (p == 0){
            int k = i;
            cycle.push_back(k);
            k = matrix[k-1];
            while(k != i){
                cycle.push_back(k);
                k = matrix[k-1];
            }
            cycle_decomposition.push_back(cycle);
            cycle.clear();
        }
    }
    return cycle_decomposition;
}

template <typename T>
int Permutation<T>::getOrder() const
{
    list<list<int>> cycle_decomposition = getCycleDecomposition();
    vector<int> cycle_lengths;
    for (list<list<int>>::const_iterator i = cycle_decomposition.begin(), j = cycle_decomposition.end(); i != j; i++){
        int k = 0;
        for (list<int>::const_iterator p = (*i).begin(), q = (*i).end(); p != q; p++)
            k++;
        cycle_lengths.push_back(k);
    }
    int m;
    if(cycle_lengths.size() == 1) m = cycle_lengths[0];
    if(cycle_lengths.size() >= 2){
        m = (cycle_lengths[0]*cycle_lengths[1])/__gcd(cycle_lengths[0], cycle_lengths[1]);
        for(int i = 2; i < cycle_lengths.size(); i++)
        m = (m*cycle_lengths[i])/__gcd(m, cycle_lengths[i]);
    }
    return m;
}

template <typename T>
int Permutation<T>::getSign() const
{
    list<list<int>> cycle_decomposition = getCycleDecomposition();
    vector<int> cycle_lengths;
    for (list<list<int>>::const_iterator i = cycle_decomposition.begin(), j = cycle_decomposition.end(); i != j; i++){
        int k = 0;
        for (list<int>::const_iterator p = (*i).begin(), q = (*i).end(); p != q; p++)
            k++;
        cycle_lengths.push_back(k);
    }
    int m;
    if(cycle_lengths.size() == 1){
        m = (cycle_lengths[0]%2 + 1)%2;
    }
    if(cycle_lengths.size() >= 2){
        m = ((cycle_lengths[0]%2 + 1)%2 + (cycle_lengths[1]%2 + 1)%2)%2;
        for(int i = 2; i < cycle_lengths.size(); i++)
        m = (m + (cycle_lengths[i]%2 + 1)%2)%2;
    }
    return m;
}

template <typename T>
Permutation<T> Permutation<T>::getInverse() const
{
    Permutation<T> inv(*this);
    inv.matrix.clear();
    for (int i = 0; i < length; i++)
        for (int j = 0; j < length; j++)
            if (matrix[j] == i+1) inv.matrix.push_back(j+1);
    return inv;
}

template <typename T>
Permutation<T> Permutation<T>::operator*(const Permutation<T>& perm2)
{
    if (length == perm2.length && length != 0 && alphabet == perm2.alphabet){
        Permutation<T> perm(*this);
        perm.matrix.clear();
        for (int i = 0; i < perm.length; i++)
            perm.matrix.push_back(matrix[perm2.matrix[i] - 1]);
        return perm;
    }
    else{
        cout << "Invalid input data" << endl;
        exit(0);
    }
}

template <typename T>
Permutation<T>& Permutation<T>::operator=(const Permutation<T>& perm)
{
    length = perm.length;
    if(!matrix.empty()) matrix.clear();
    for (int i = 0; i < length; i++)
        matrix.push_back(perm.matrix[i]);
    if(!alphabet.empty()) alphabet.clear();
    alphabet = perm.alphabet;
    return *this;
}

template <typename T>
int Permutation<T>::operator[](int index)
{
    return matrix[index];
}

template <typename T>
void Permutation<T>::print() const
{
    cout << "Permutation:" << endl;
    for (int i = 0; i < length; i++)
        cout << alphabet.at(i) << " -> " << alphabet.at(matrix[i] - 1) << endl;
    cout << endl;
}

template <typename T>
inline int Permutation<T>::getCountOfPermutations()
{
    return countOfPermutations;
}

template <typename T>
void Permutation<T>::info() const 
{
    cout << "Element of S_" << length << endl;
}