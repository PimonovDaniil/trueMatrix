
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
    Matrix::debug = false; //отображать конструкторы/деструкторы

    /*настройка формата вывода матрицы*/
    Matrix::setting->setPrecision(3); //устанавливает точность
    Matrix::setting->setSetw(8); //Устанавливает ширину поля

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
}