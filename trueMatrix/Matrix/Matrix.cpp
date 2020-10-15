﻿#include "Matrix.h"
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
    void Matrix::init(int rows, int cols, double* matrix) {
        
        this->numObj = ++this->num;

        if (rows * cols == 0) {
            this->rows = this->cols = 0;
            matrix = nullptr;
            return;
        }

        this->rows = rows; this->cols = cols;

        this->matrix = new double[rows*cols];

        if (matrix == nullptr) return;

        for (int i = 0; i < this->rows* this->cols; i++)
            this->matrix[i] = matrix[i];
    }

    /*копирование объекта матрица*/
    void Matrix::copy(const Matrix& other){

        if (this->matrix != nullptr) {
            delete[] this->matrix;
        }

        this->cols = other.cols;
        this->rows = other.rows;

        this->matrix = new double [this->rows * this->cols];

        for (int i = 0; i < this->rows * this->cols; i++)
                this->matrix[i] = other.matrix[i];
                
    }

    /*конструктор  без параметров*/
    Matrix::Matrix() {
        init(0, 0, nullptr);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 1)" << std::endl;
    }

    /*принимает матрицу с размерами rows cols*/
    Matrix::Matrix(int rows, int cols, double* matrix) {
        init(rows, cols, matrix);
        
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 2)" << std::endl;
    }

    /*матрица размеров rows cols заполненная нулями*/
    Matrix::Matrix(int rows, int cols) {
        init(rows, cols, nullptr);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 3)" << std::endl;
    }

    /*принимает квадратную матрицу*/
    Matrix::Matrix(int square, double* matrix) {
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
    Matrix::MatrixRow Matrix::operator[](const int index){
        return MatrixRow(this, index);//TODO сделать проверку индексов
    }

    //const double* Matrix::operator[](const int index) const
    //{
    //    return this->matrix[index];//TODO сделать проверку индексов
    //}

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator+=(const Matrix& other) {
        if (this->isSum(other) == false)
            throw "Вычитание невозможно"; 
        for (int i = 0; i < this->rows * this->cols; i++)
                this->matrix[i] += other.matrix[i];

        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator*=(double k) {
        for (int i = 0; i < this->rows * this->cols; i++)
                this->matrix[i] *= k;
        return *this;
    }

    //this->m_r * this->m_owner->cols + r
    Matrix& Matrix::operator*=(const Matrix& other) {
        if (this->isMultiply(other) == false) 
            throw "Вычитание невозможно";
        double* newMatrix = new double [this->rows * other.cols];

        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++) {
                newMatrix[/*i][j*/i * this->cols + j] = 0.0;
                for (int k = 0; k < this->cols; k++) {
                    newMatrix[/*i][j*/ i * this->cols + j] += (this->matrix[/*i][k*/ i * this->cols + j] * other.matrix[/*k][j*/ k * this->cols + j]);
                }
            }
        delete[] this->matrix;
        this->cols = other.getCols();
        matrix = newMatrix;

        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator-=(const Matrix& other) {
        if (this->isSum(other) == false) 
            throw "Вычитание невозможно";
     
        for (int i = 0; i < this->rows * this->cols; i++)
            this->matrix[i] -= other.matrix[i];
        
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

    bool Matrix::isMultiply(const Matrix& other) {
        return (this->matrix != nullptr && other.matrix != nullptr && this->cols == other.rows) ? true : false;
    }

    bool Matrix::isSum(const Matrix& other) {
        return ((this->cols == other.getCols()) && (this->rows == other.getRows()) && (other.matrix != nullptr)) ? true : false;
    }

    double Matrix::getMax() {
        if ((this->rows > 0) && (this->cols > 0)) {
            double max = matrix[0];
            for (int i = 0; i < this->rows * this->cols; i++)
                    if (matrix[i] > max)
                        max = matrix[i];
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
            double min = matrix[0];
            for (int i = 0; i < this->rows * this->cols; i++)
                for (int j = 0; j < this->cols; j++)
                    if (matrix[i] < min)
                        min = matrix[i];
            return min;
        }
        else {
            throw "Матрица пустая";
        }
    }

    //std::ostream& operator<< (std::ostream& os, const Matrix& matrix) {
    //    //return os << "__" << std::endl;
    //    for (int i = 0; i < matrix.getRows(); i++) {
    //        for (int j = 0; j < matrix.getCols(); j++) {
    //            os << std::setw(matrix.setting->getSetw()) << std::setprecision(matrix.setting->getPrecision()) << matrix[i][j] << " ";
    //        }
    //        os << std::endl;
    //    }
    //    return os;
    //}

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
    Matrix::MatrixRow::MatrixRow(const Matrix* owner, unsigned r)
    {
        this->m_owner = owner;
        this->m_r = r;
    }
   
    double Matrix::MatrixRow::operator[](unsigned r) const
    {
        return this->m_owner->matrix[this->m_r * this->m_owner->cols + r];
    }

    double& Matrix::MatrixRow::operator[](unsigned r)
    {
        return this->m_owner->matrix[this->m_r * this->m_owner->cols + r];
    }
}

