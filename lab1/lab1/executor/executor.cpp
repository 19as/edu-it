#include <iostream>
#include <oper.h>

void main()
{
    MATRIX<int> M(2, 3);

    int i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            M.SetMij(i, j, i + j);

    M.Print("A");
    
    MATRIX<int> T;
    T = M.transpose();

    T.Print("A^T");

    MATRIX<int> C;

    C = M.multiply(T);
    C.Print("C=A*A^T");

    MATRIX<int> C1;

    C1 = M.sum(M);
    C1.Print("C=A+A");


    MATRIX<int> C2;

    C2 = M.multiply<int>(2);
    C2.Print("C=A*2");
}