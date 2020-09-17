#include "Matrix.h"
#include <iostream>
#include <locale.h>

namespace mathTools
{
    /*инициализация (создание дубликата матрицы)*/
    void Matrix::init(int rows, int cols, double** matrix) {
        this->rows = rows; this->cols = cols;
        if ((rows > 0) && (cols > 0)) {
            double** newMatrix = new double* [rows];
            for (int i = 0; i < rows; i++) {
                newMatrix[i] = new double[cols];
            }
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    if (matrix != nullptr) {
                        newMatrix[i][j] = matrix[i][j];
                    }
                    else {
                        newMatrix[i][j] = 0;
                    }

            this->matrix = newMatrix;
        }
        else {
            this->matrix = nullptr;
        }
    }

    /*копирование объекта матрица*/
    void Matrix::copy(Matrix& other) {
        /*выкидываем за собой мусор*/
        /*for (int i = 0; i < this->rows; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;*/
        this->cols = other.cols;
        this->rows = other.rows;

        this->matrix = new double* [this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->matrix[i] = new double[this->cols];
        }
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                this->matrix[i][j] = other[i][j];
    }

    /*конструктор  без параметров*/
    Matrix::Matrix() {
        init(0, 0, nullptr);
    }

    /*принимает матрицу с размерами rows cols*/
    Matrix::Matrix(int rows, int cols, double** matrix) {
        init(rows, cols, matrix);
    }

    /*матрица размеров rows cols заполненная нулями*/
    Matrix::Matrix(int rows, int cols) {
        init(rows, cols, nullptr);
    }

    /*принимает квадратную матрицу*/
    Matrix::Matrix(int square, double** matrix) {
        init(square, square, matrix);
    }

    /*матрица размера square^2 заполненная нулями*/
    Matrix::Matrix(int square) {
        init(square, square, nullptr);
    }

    /*конструктор копирования*/
    Matrix::Matrix(Matrix& other) {
        copy(other);
    }

    /*деструктор*/
    Matrix::~Matrix() {
        /*выкидываем за собой мусор*/
        for (int i = 0; i < this->rows; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator=(Matrix& other)
    {
        // Проверка на самоприсваивание
        if (this != &other) copy(other);
        return *this;
    }

    /*подмена понятий (перегрузка)*/
    double*& Matrix::operator[](int index) {
        return this->matrix[index];//TODO сделать проверку индексов
    }

    /*подмена понятий (перегрузка)*/
    void Matrix::operator+=(Matrix& other) {
        if (this->isSum(other)) {
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    this->matrix[i][j] += other[i][j];
        }
        else {
            throw "Вычитание невозможно";
        }
    }

    void Matrix::operator*=(Matrix& other) {
        if (this->isMultiply(other)) {
            double** newMatrix = new double* [other.getRows()];
            for (int i = 0; i < other.getRows(); i++) {
                newMatrix[i] = new double[this->cols];
            }
            
            for (int i = 0; i < other.getRows(); i++)
                for (int j = 0; j < this->cols; j++) {
                    double c = 0.0;
                    for (int k = 0; k < this->cols; k++) {
                        c += this->matrix[k][j] * other[i][k];
                    }
                    newMatrix[i][j] = c;
                }

            for (int i = 0; i < this->rows; i++)
                delete[] this->matrix[i];
            delete[] this->matrix;
            this->rows = other.getRows();
            matrix = newMatrix;
        }
        else {
            throw "Вычитание невозможно";
        }
    }

    /*подмена понятий (перегрузка)*/
    void Matrix::operator-=(Matrix& other) {
        if (this->isSum(other)) {
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    this->matrix[i][j] -= other[i][j];
        }
        else {
            throw "Вычитание невозможно";
        }
    }

    int Matrix::getCols() {//узнать кол-во столбцов
        return this->cols;
    }

    int Matrix::getRows() {//узнать кол-во рядов
        return this->rows;
    }

    /*Изменяет размер матрицы. Работает как и в сторону увеличения, так
    и в сторону уменьшения вплоть до удаления при пареметрах (0, 0).
    При уменьшении размеров матрицы лишние элементы удаляются, при увиличерии
    заполняются нулями. */
    void Matrix::setLength(int rows, int cols) {
        if ((rows == 0) || (cols == 0)) {
            /*выкидываем за собой мусор*/
            for (int i = 0; i < this->rows; i++)
                delete[] this->matrix[i];
            delete[] this->matrix;

            this->matrix = nullptr;
            this->rows = rows;
            this->cols = cols;
        }
        else if ((rows < 0) || (cols < 0)) {
            throw "Размер матрицы не может быть отрицательным";
        }
        else if (!((this->rows == rows) && (this->cols == cols))) {
            /*инициализируем новую матрицу*/
            double** newMatrix = new double* [rows];
            for (int i = 0; i < rows; i++) {
                newMatrix[i] = new double[cols];
            }

            /*переносим данные*/
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    if ((i < this->rows) && (j < this->cols)) {
                        newMatrix[i][j] = this->matrix[i][j];
                    }
                    else {
                        newMatrix[i][j] = 0;
                    }

            /*выкидываем за собой мусор*/
            for (int i = 0; i < this->rows; i++)
                delete[] this->matrix[i];
            delete[] this->matrix;

            this->matrix = newMatrix;
            this->cols = cols;
            this->rows = rows;
        }
    }

    bool Matrix::isMultiply(Matrix other) {
        return (this->rows == other.getCols()) ? true : false;
    }

    bool Matrix::isSum(Matrix other) {
        return ((this->cols == other.getCols()) && (this->rows == other.getRows())) ? true : false;
    }

    double Matrix::getMax() {
        if ((this->rows > 0) && (this->cols > 0)) {
            double max = matrix[0][0];
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    if (matrix[i][j] > max)
                        max = matrix[i][j];
            return max;
        }
        else {
            throw "Матрица пустая";
        }
    }

    double Matrix::getMin() {
        if ((this->rows > 0) && (this->cols > 0)) {
            double min = matrix[0][0];
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    if (matrix[i][j] < min)
                        min = matrix[i][j];
            return min;
        }
        else {
            throw "Матрица пустая";
        }
    }

    void Matrix::print() { //TODO добавить перегрузку оператора <<
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++)
                printf("%lf ", this->matrix[i][j]);
            printf("\n");
        }
    }
}
