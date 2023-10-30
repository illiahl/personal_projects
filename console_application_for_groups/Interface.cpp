#include "Interface.h"

template <typename T>
int Permutation<T>::countOfPermutations = 0;
void Interface::viewMenu()
{
    while(true){
        cout << "~~~MENU~~~" << endl;
        cout << "Choose Class: " << endl;
        cout << "1 - Additive Group of Z mod n" << endl;
        cout << "2 - Multiplicative Group of Z mod n" << endl;
        cout << "3 - Permutation" << endl;
        cout << "0 - Exit program!" << endl;
        int ansClass;
        cin >> ansClass;
        if (ansClass == 1){
            int number;
            while (true)
            {
                cout << "Enter n: ";
                cin >> number;
                if (number > 0) break;
                else cout << "Invalid input data!" << endl;            
            }
            Additive_Group_of_Zmodn group1(number);
            while (true)
            {
                cout << "/--Additive Group of Z mod n Menu--/" << endl;
                cout << "Choose action:" << endl;
                cout << "1 - View n" << endl;
                cout << "2 - Set n" << endl;
                cout << "3 - Get coset of element" << endl;
                cout << "4 - Get cyclic subgroup of element" << endl;
                cout << "5 - Get order of element" << endl;
                cout << "6 - Get iverse elemtnt" << endl;
                cout << "7 - find all homomorphisms between Z_n and Z_m" << endl;
                cout << "8 - Factorize group by cyclic subgroup" << endl;
                cout << "9 - Print set of elements" << endl;
                cout << "0 - Go back to class selection menu!" << endl;
                int ans1;
                cin >> ans1;
                if (ans1 == 1){
                    cout << "N of this group = " << group1.getN() << endl;
                }
                else if (ans1 == 2){
                    cout << "Enter new n: ";
                    int num;
                    cin >> num;
                    group1.setN(num);
                }
                else if (ans1 == 3){
                    cout << "Enter element: ";
                    int element;
                    cin >> element;
                    list<int> coset = group1.getCoset(element);
                    cout << "Coset: {";
                    for (list<int>::const_iterator i = coset.begin(), j = coset.end(); i != j; i++){
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
                else if (ans1 == 4){
                    cout << "Enter element: ";
                    int element;
                    cin >> element;
                    list<int> cyclic_subgroup = group1.getCyclicSubgroup(element);
                    cout << "Cyclic subgroup: {";
                    for (list<int>::const_iterator i = cyclic_subgroup.begin(), j = cyclic_subgroup.end(); i != j; i++){
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
                else if (ans1 == 5){
                    cout << "Enter element: ";
                    int element;
                    cin >> element;
                    cout << "Order of " << element <<" = " << group1.getOrder(element) << endl;
                }
                else if (ans1 == 6){
                    cout << "Enter element: ";
                    int element;
                    cin >> element;
                    cout << "Inverse element of " << element << " = " << group1.getInverse(element) << endl;
                }
                else if (ans1 == 7){
                    cout << "Enter first group`s order: ";
                    int ord1;
                    cin >> ord1;
                    cout << "Enter second group`s order: ";
                    int ord2;
                    cin >> ord2;
                    Additive_Group_of_Zmodn a(ord1);
                    Additive_Group_of_Zmodn b(ord2);
                    findAllHomomorphisms(a, b);
                }
                else if (ans1 == 8){
                    int factorel;
                    while (true)
                    {
                        cout << "Enter factoring element: ";
                        cin >> factorel;
                        if (number > 0 && factorel >= 0 && factorel <= number-1) break;
                        else cout << "Invalid input data!" << endl;            
                    }
                    Additive_Factor_Group group3(number, factorel);
                    while (true)
                    {
                        cout << "/--Additive Factor-Group of Z mod n Menu--/" << endl;
                        cout << "Choose action:" << endl;
                        cout << "1 - View factoring element" << endl;
                        cout << "2 - Set factoring element" << endl;
                        cout << "3 - Print set of cosets of factor-group" << endl;
                        cout << "0 - Go back to additive group menu!" << endl;
                        int ans3;
                        cin >> ans3;
                        if (ans3 == 1){
                            cout << "Factoring element of this factor-group = " << group3.getFactoringElement() << endl;
                        }
                        else if (ans3 == 2){
                            cout << "Enter new factoring element: ";
                            int fact;
                            cin >> fact;
                            group3.setFactoringElement(fact);
                        }
                        else if (ans3 == 3) group3.print();
                        else if (ans3 == 0) break;
                        else cout << "You have chosen incorrect variant!" << endl;
                    }
                }
                else if (ans1 == 9) group1.print();
                else if (ans1 == 0) break;
                else cout << "You have chosen incorrect variant!" << endl;            
            }
        }
        if (ansClass == 2){
            int number;
            while (true)
            {
                cout << "Enter n: ";
                cin >> number;
                if (number > 1) break;
                else cout << "Invalid input data!" << endl;            
            }
            Multiplicative_Group_of_Zmodn group2(number);
            while (true)
            {
                cout << "/--Multiplicative Group of Z mod n Menu--/" << endl;
                cout << "Choose action:" << endl;
                cout << "1 - View n" << endl;
                cout << "2 - Set n" << endl;
                cout << "3 - Get coset of element" << endl;
                cout << "4 - Get cyclic subgroup of element" << endl;
                cout << "5 - Get order of element" << endl;
                cout << "6 - Get iverse elemtnt" << endl;
                cout << "7 - Factorize group by cyclic subgroup" << endl;
                cout << "8 - Print set of elements" << endl;
                cout << "0 - Go back to class selection menu!" << endl;
                int ans2;
                cin >> ans2;
                if (ans2 == 1){
                    cout << "N of this group = " << group2.getN() << endl;
                }
                else if (ans2 == 2){
                    cout << "Enter new n: ";
                    int num;
                    cin >> num;
                    group2.setN(num);
                }
                else if (ans2 == 3){
                    cout << "Enter element: ";
                    int element;
                    cin >> element;
                    list<int> coset = group2.getCoset(element);
                    cout << "Coset: {";
                    for (list<int>::const_iterator i = coset.begin(), j = coset.end(); i != j; i++){
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
                else if (ans2 == 4){
                    cout << "Enter element: ";
                    int element;
                    cin >> element;
                    list<int> cyclic_subgroup = group2.getCyclicSubgroup(element);
                    cout << "Cyclic subgroup: {";
                    for (list<int>::const_iterator i = cyclic_subgroup.begin(), j = cyclic_subgroup.end(); i != j; i++){
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
                else if (ans2 == 5){
                    cout << "Enter element: ";
                    int element;
                    cin >> element;
                    cout << "Order of " << element <<" = " << group2.getOrder(element) << endl;
                }
                else if (ans2 == 6){
                    cout << "Enter element: ";
                    int element;
                    cin >> element;
                    cout << "Inverse element of " << element << " = " << group2.getInverse(element) << endl;
                }
                else if (ans2 == 7){
                    int factorel;
                    while (true)
                    {
                        cout << "Enter factoring element: ";
                        cin >> factorel;
                        if (factorel >= 1 && factorel <= number-1 && __gcd(number, factorel) == 1) break;
                        else cout << "Invalid input data!" << endl;            
                    }
                    Multiplicative_Factor_Group group4(number, factorel);
                    while (true)
                    {
                        cout << "/--Multiplicative Factor-Group of Z mod n Menu--/" << endl;
                        cout << "Choose action:" << endl;
                        cout << "1 - View factoring element" << endl;
                        cout << "2 - Set factoring element" << endl;
                        cout << "3 - Print set of cosets of factor-group" << endl;
                        cout << "0 - Go back to multiplicative group menu!" << endl;
                        int ans4;
                        cin >> ans4;
                        if (ans4 == 1){
                            cout << "Factoring element of this factor-group = " << group4.getFactoringElement() << endl;
                        }
                        else if (ans4 == 2){
                            cout << "Enter new factoring element: ";
                            int fact;
                            cin >> fact;
                            group4.setFactoringElement(fact);
                        }
                        else if (ans4 == 3) group4.print();
                        else if (ans4 == 0) break;
                        else cout << "You have chosen incorrect variant!" << endl;
                    }
                }
                else if (ans2 == 8) group2.print();
                else if (ans2 == 0) break;
                else cout << "You have chosen incorrect variant!" << endl;            
            }
        }
        else if (ansClass == 3){
            int anstype;
            while(true)
            {
                cout << "Choose type:"<< endl;
                cout << "1 - int" << endl;
                cout << "2 - char" << endl;
                cin >> anstype;
                if(anstype == 1 || anstype == 2) break;
                else cout << "You have chosen incorrect variant!" << endl;
            }
            if(anstype == 1)
            {
                int len;
                while (true)
                {
                    cout << "Enter lenght of permutation: ";
                    cin >> len;
                    if (len > 0) break;
                    else cout << "Invalid input data!" << endl;            
                }
                Permutation<int> perm(len);
                while (true)
                {
                    cout << "/--Permutation Menu--/" << endl;
                    cout << "Choose action:" << endl;
                    cout << "1 - Get cycle decomposition" << endl;
                    cout << "2 - Get order of permutation" << endl;
                    cout << "3 - Get sign of permutation" << endl;
                    cout << "4 - Get inverse permutation" << endl;
                    cout << "5 - Get mapping of element" << endl;
                    cout << "6 - Compute composition of two permutations" << endl;
                    cout << "7 - Print permutation" << endl;
                    cout << "0 - Go back to class selection menu!" << endl;
                    int ans5;
                    cin >> ans5;
                    if (ans5 == 1){
                        list<list<int>> cycle_decomposition = perm.getCycleDecomposition();
                        cout << "Cycle Decomposition: ";
                        for (list<list<int>>::const_iterator i = cycle_decomposition.begin(), j = cycle_decomposition.end(); i != j; i++)
                        {
                            list<int> cycle = *i;
                            cout << "(";
                            for (list<int>::const_iterator k = cycle.begin(), l = cycle.end(); k != l; k++)
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
                                cout << ")";
                            }
                            else {
                                i--;
                                cout << ") o ";
                            }
                        }
                        cout << endl;
                        continue;
                    }
                    else if (ans5 == 2){
                        cout << "Order of permutation = " << perm.getOrder() << endl;
                        continue;
                    }
                    else if (ans5 == 3){
                        cout << "Sign of permutation = " << perm.getSign() << endl;
                        continue;
                    }
                    else if (ans5 == 4){
                        Permutation<int> a(perm.getInverse());
                        cout << "Inverse ";
                        a.print();
                        continue;
                    }
                    else if (ans5 == 5){
                        int element;
                        while (true)
                        {   
                            cout << "Enter element:";
                            cin >> element;
                            if (element >= 1 && element <= perm.getLength()) break;
                            else cout << "Wrong input data!" << endl;
                        }
                        cout << element << " maps to " << perm[element-1] << endl;
                        continue;
                    }
                    else if (ans5 == 6){
                        cout << "Enter lenghts of permutations: ";
                        int lens;
                        cin >> lens;
                        cout << "Enter first permutation:" << endl;
                        Permutation<int> p1(lens);
                        cout << "Enter second permutation:" << endl;
                        Permutation<int> p2(lens);
                        Permutation<int> p3(p2);
                        p3 = p1*p2;
                        cout << "(Result of composition) ";
                        p3.print();
                        continue;
                    }
                    else if (ans5 == 7){ 
                        perm.print();
                        continue;
                    }
                    else if (ans5 == 0) break;
                    else cout << "You have chosen incorrect variant!" << endl;
                    int ans3;
                    cin >> ans3;
                }
            }
            else if (anstype == 2)
            {
                int len;
                while (true)
                {
                    cout << "Enter lenght of permutation: ";
                    cin >> len;
                    if (len > 0) break;
                    else cout << "Invalid input data!" << endl;            
                }
                Permutation<char> perm(len);
                while (true)
                {
                    cout << "/--Permutation Menu--/" << endl;
                    cout << "Choose action:" << endl;
                    cout << "1 - Get cycle decomposition" << endl;
                    cout << "2 - Get order of permutation" << endl;
                    cout << "3 - Get sign of permutation" << endl;
                    cout << "4 - Get inverse permutation" << endl;
                    cout << "5 - Get mapping of element" << endl;
                    cout << "6 - Compute composition of two permutations" << endl;
                    cout << "7 - Print permutation" << endl;
                    cout << "0 - Go back to class selection menu!" << endl;
                    int ans5;
                    cin >> ans5;
                    if (ans5 == 1){
                        list<list<int>> cycle_decomposition = perm.getCycleDecomposition();
                        cout << "Cycle Decomposition: ";
                        for (list<list<int>>::const_iterator i = cycle_decomposition.begin(), j = cycle_decomposition.end(); i != j; i++)
                        {
                            list<int> cycle = *i;
                            cout << "(";
                            for (list<int>::const_iterator k = cycle.begin(), l = cycle.end(); k != l; k++)
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
                                cout << ")";
                            }
                            else {
                                i--;
                                cout << ") o ";
                            }
                        }
                        cout << endl;
                        continue;
                    }
                    else if (ans5 == 2){
                        cout << "Order of permutation = " << perm.getOrder() << endl;
                        continue;
                    }
                    else if (ans5 == 3){
                        cout << "Sign of permutation = " << perm.getSign() << endl;
                        continue;
                    }
                    else if (ans5 == 4){
                        Permutation<char> a(perm.getInverse());
                        cout << "Inverse ";
                        a.print();
                        continue;
                    }
                    else if (ans5 == 5){
                        int element;
                        while (true)
                        {   
                            cout << "Enter element:";
                            cin >> element;
                            if (element >= 1 && element <= perm.getLength()) break;
                            else cout << "Wrong input data!" << endl;
                        }
                        cout << element << " maps to " << perm[element-1] << endl;
                        continue;
                    }
                    else if (ans5 == 6){
                        cout << "Enter lenghts of permutations: ";
                        int lens;
                        cin >> lens;
                        cout << "Enter first permutation:" << endl;
                        Permutation<char> p1(lens);
                        cout << "Enter second permutation:" << endl;
                        Permutation<char> p2(lens);
                        Permutation<char> p3(p2);
                        p3 = p1*p2;
                        cout << "(Result of composition) ";
                        p3.print();
                        continue;
                    }
                    else if (ans5 == 7){
                        perm.print();
                        continue;
                    }
                    else if (ans5 == 0) break;
                    else cout << "You have chosen incorrect variant!" << endl;
                    int ans3;
                    cin >> ans3;
                }
            }
        }
        else if (ansClass == 0) {
            cout << endl << "/" << Permutation<int>::getCountOfPermutations() << " integer permutations were created!/" << endl;
            break;
        }
        else cout << "You have chosen incorrect variant!" << endl;
    }
}