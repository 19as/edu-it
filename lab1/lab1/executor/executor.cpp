#include <iostream>
#include <oper.h>

void main()
{
    MATRIX M(2, 3);

    int i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            M.SetMij(i, j, i + j);

    M.Print("A");
    
    MATRIX T;
    T = M.transpose();

    T.Print("A^T");

    MATRIX C;

    C = M.multiply(T);
    C.Print("C=A*A^T");

    MATRIX C1;

    C1 = M.sum(M);
    C1.Print("C=A+A");


    MATRIX C2;

    C2 = M.multiply(2);
    C2.Print("C=A*2");
}