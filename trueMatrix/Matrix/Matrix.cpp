#include "Matrix.h"
#include <iostream>
#include <locale.h>
#include <iomanip>

namespace mathTools
{
    bool Matrix::debug = false;
    settings* settings::uniqueInstance = nullptr;
    settings* Matrix::setting = settings::create();
    int Matrix::num = 0; //начальное кол-во объектов класса

    /*инициализация (создание дубликата матрицы)*/
    void Matrix::init(int rows, int cols, double** matrix) {
        this->numObj = ++this->num;

        if (rows * cols == 0) {
            this->rows = this->cols = 0;
            matrix = nullptr;
            return;
        }

        this->rows = rows; this->cols = cols;

        double**& mtx = this->matrix = new double* [rows];
        for (int i = 0; i < rows; i++) mtx[i] = new double[cols]();

        if (matrix == nullptr) return;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                mtx[i][j] = matrix[i][j];
    }

    /*копирование объекта матрица*/
    void Matrix::copy(const Matrix& other){

        if (this->matrix != nullptr) {
            for (int i = 0; i < this->rows; i++)
                delete[] this->matrix[i];
            delete[] this->matrix;
        }

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
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 1)" << std::endl;
    }

    /*принимает матрицу с размерами rows cols*/
    Matrix::Matrix(int rows, int cols, double** matrix) {
        init(rows, cols, matrix);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 2)" << std::endl;
    }

    /*матрица размеров rows cols заполненная нулями*/
    Matrix::Matrix(int rows, int cols) {
        init(rows, cols, nullptr);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 3)" << std::endl;
    }

    /*принимает квадратную матрицу*/
    Matrix::Matrix(int square, double** matrix) {
        init(square, square, matrix);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 4)" << std::endl;
    }

    /*матрица размера square^2 заполненная нулями*/
    Matrix::Matrix(int square) {
        init(square , square, nullptr);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 5)" << std::endl;
    }

    /*конструктор копирования*/
    Matrix::Matrix(Matrix& other) {
        this->matrix = nullptr;
        this->numObj = ++this->num;
        copy(other);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор копирования)" << std::endl;
    }

    /*деструктор*/
    Matrix::~Matrix() {
        /*выкидываем за собой мусор*/
        for (int i = 0; i < this->rows; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "деструтор)" << std::endl;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator=(const Matrix& other) 
    {
        // Проверка на самоприсваивание
        if (this != &other) copy(other);
        //delete &other;
        return *this;
    }

    /*подмена понятий (перегрузка)*/
    double*& Matrix::operator[](const int index){
       return this->matrix[index];//TODO сделать проверку индексов
    }

    const double* Matrix::operator[](const int index) const
    {
        return this->matrix[index];//TODO сделать проверку индексов
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator+=(const Matrix& other) {
        if (this->isSum(other) == false)
            throw "Вычитание невозможно"; 
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                this->matrix[i][j] = this->matrix[i][j] + other[i][j];

        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator*=(double k) {
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                this->matrix[i][j] *= k;
        return *this;
    }

    Matrix& Matrix::operator*=(const Matrix& other) {
        if (this->isMultiply(other) == false) 
            throw "Вычитание невозможно";
        double** newMatrix = new double* [this->rows];
        for (int i = 0; i < this->rows; i++) 
            newMatrix[i] = new double[other.cols];
        

        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++) {
                newMatrix[i][j] = 0.0;
                for (int k = 0; k < this->cols; k++) {
                    newMatrix[i][j] += (this->matrix[i][k] * other[k][j]);
                }
            }
        for (int i = 0; i < this->rows; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;
        this->cols = other.getCols();
        matrix = newMatrix;

        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator-=(const Matrix& other) {
        if (this->isSum(other) == false) 
            throw "Вычитание невозможно";
     
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                this->matrix[i][j] -= other[i][j];
        
        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix Matrix::operator+(const Matrix& other) {
        Matrix res(*this);
        res += other;
        return res;
    }

    /*подмена понятий (перегрузка)*/
    Matrix Matrix::operator-(const Matrix& other) {
        Matrix res(*this);
        res -= other;
        return res;
    }

    /*подмена понятий (перегрузка)*/
    Matrix Matrix::operator*(const Matrix& other) {
        Matrix res(*this);
        res *= other;
        return res;
    }

    /*подмена понятий (перегрузка)*/
    Matrix Matrix::operator*(double k) {
        Matrix res(*this);
        res *= k;
        return res;
    }    

    int Matrix::getCols() const{//узнать кол-во столбцов
        return this->cols;
    }

    int Matrix::getRows() const{//узнать кол-во рядов
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

    bool Matrix::isMultiply(const Matrix& other) {
        return (this->matrix != nullptr && other.matrix != nullptr && this->cols == other.rows) ? true : false;
    }

    bool Matrix::isSum(const Matrix& other) {
        return ((this->cols == other.getCols()) && (this->rows == other.getRows()) && (other.matrix != nullptr)) ? true : false;
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

    settings* Matrix::settings() {
        return Matrix::setting;
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

    std::ostream& operator<< (std::ostream& os, const Matrix& matrix) {
        //return os << "__" << std::endl;
        for (int i = 0; i < matrix.getRows(); i++) {
            for (int j = 0; j < matrix.getCols(); j++) {
                os << std::setw(matrix.setting->getSetw()) << std::setprecision(matrix.setting->getPrecision()) << matrix[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    settings::settings() {
        this->setw = 8;
        this->precision = 3;
    }

    settings* settings::create() {
        if (settings::uniqueInstance == nullptr) {//пофиксить при многопоточности
            settings::uniqueInstance = new settings();
        }
        return settings::uniqueInstance;
    }

    void settings::setSetw(int s)
    {
        this->setw = s;
    }

    void settings::setPrecision(int p)
    {
        this->precision = p;
    }

    int settings::getSetw()
    {
        return this->setw;
    }

    int settings::getPrecision()
    {
        return this->precision;
    }
}

