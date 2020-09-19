﻿
// trueMatrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <locale.h>
#include <iostream>
#include "Matrix/Matrix.h"
using namespace mathTools;
using namespace std;


int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    Matrix::debug = false;
    /*инициализируем новую матрицу*/
    double** a1 = new double* [3];
    for (int i = 0; i < 3; i++) {
        a1[i] = new double[3];
    }
    a1[0][0] = 4; a1[0][1] = 1.405340503460; a1[0][2] = 0;
    a1[1][0] = 3; a1[1][1] = 2; a1[1][2] = 1;
    a1[2][0] = 0; a1[2][1] = 1; a1[2][2] = 0;

    Matrix a(3, 3, a1);
    a.setLength(2, 2);
    cout << a << endl;

    /*инициализируем новую матрицу*/
    double** b1 = new double* [2];
    for (int i = 0; i < 2; i++) {
        b1[i] = new double[3];
    }
    b1[0][0] = 2; b1[0][1] = 0;  b1[0][2] = -1;
    b1[1][0] = 0; b1[1][1] = -2; b1[1][2] = 2;

    Matrix b(2, 3, b1);
    b.setLength(2, 2);
    cout << b << endl;

    Matrix c;
    c =  a * 2;
    Matrix x(b);
    cout << c << endl << a << endl << b;
    

    //for (int i = 0; i <= 10; i++) {
    //    std::cout << a + b << std::endl;
    //}

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   ++3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
