#include "oper.h"

#include <iostream>

MATRIX::MATRIX()
{
    n = m = 0;
    M = nullptr;
}

// ����������� � ����� �����������
MATRIX::MATRIX(int _m, int _n)
{
    m = _m;
    n = _n;

    // �������� ������ ��� �������
    // �������� ���'��� ��� ������� ����������
    M = (int**) new int*[m]; // ���������� �����, ���������� ����������

    // �������� ������ ��� ������� ���������
    for (int i = 0; i < m; i++)
        M[i] = (int*)new int[n];

    // ��������� ������ M ������
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = 0;
}

// ����������� ����������� - ������������
MATRIX::MATRIX(const MATRIX& _M)
{
    // ��������� ����� ������ ��� �������� ���������� ������
    // ����������� ������ *this <= _M
    m = _M.m;
    n = _M.n;

    // �������� ������ ��� M
    M = (int**) new int*[m]; // ���������� �����, ���������� ����������

    for (int i = 0; i < m; i++)
        M[i] = (int*) new int[n];

    // ��������� ����������
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = _M.M[i][j];
}

// ������ �������
int MATRIX::GetMij(int i, int j)
{
    if ((m > 0) && (n > 0))
        return M[i][j];
    else
        return 0;
}

void MATRIX::SetMij(int i, int j, int value)
{
    if ((i < 0) || (i >= m))
        return;
    if ((j < 0) || (j >= n))
        return;
    M[i][j] = value;
}

// �����, ��������� �������
void MATRIX::Print(const char* ObjName)
{
    std::cout << "Object: " << ObjName << std::endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout << M[i][j] << "\t";
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl << std::endl;
}

// �������� ����������� - ������������
MATRIX MATRIX::operator=(const MATRIX& _M)
{
    if (n > 0)
    {
        // ���������� ������, ���������� ����� ��� ������� *this
        for (int i = 0; i < m; i++)
            delete[] M[i];
    }

    if (m > 0)
    {
        delete[] M;
    }

    // ����������� ������ M <= _M
    m = _M.m;
    n = _M.n;

    // �������� ������ ��� M �����
    M = (int**) new int*[m]; // ���������� �����, ���������� ����������
    for (int i = 0; i < m; i++)
        M[i] = (int*) new int[n];

    // ��������� ����������
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = _M.M[i][j];
    return *this;
}

// ���������� - ����������� ������, ���������� ��� �������
MATRIX::~MATRIX()
{
    if (n > 0)
    {
        // ���������� ���������� ������ ��� ������ ������
        for (int i = 0; i < m; i++)
            delete[] M[i];
    }

    if (m > 0)
        delete[] M;
}

// ����������������
MATRIX MATRIX::transpose()
{
    MATRIX T(n, m);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            T.M[j][i] = M[i][j];

    return T;
}

// ��������� �� �������
MATRIX MATRIX::multiply(MATRIX B)
{
    MATRIX C(m, B.n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < B.n; j++)
        {
            C.M[i][j] = 0;
            for (int k = 0; k < n; k++)
                C.M[i][j] += M[i][k] * B.M[k][j];
        }

    return C;
}

// ��������
MATRIX MATRIX::sum(MATRIX B)
{
    MATRIX C(m, n);

    if (B.m != m || B.n != n)
        return {};

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C.M[i][j] += M[i][j] + B.M[i][j];

    return C;
}

// ���������
MATRIX MATRIX::sub(MATRIX B)
{
    MATRIX C(m, n);

    if (B.m != m || B.n != n)
        return {};

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C.M[i][j] += M[i][j] - B.M[i][j];

    return C;
}

// ��������� �� �����
MATRIX MATRIX::multiply(int k)
{
    MATRIX K(m, n);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            K.M[i][j] = M[i][j] * k;

    return K;
}