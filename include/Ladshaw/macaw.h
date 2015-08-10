//----------------------------------------
//  Created by Austin Ladshaw on 1/7/14
//  Copyright (c) 2014
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#ifndef MACAW_HPP_
#define MACAW_HPP_

#include <stdio.h>				//Line to allow cout functionality
#include <math.h>               //Line added to allow usage of the pow (e, x) function
#include <iostream>				//Line to allow for read/write to the console using cpp functions
#include <fstream>				//Line to allow for read/write to and from .txt files
#include <stdlib.h>				//Line need to convert strings to doubles
#include <vector>				//Line needed to use dynamic arrays called vectors
#include <time.h>				//Line needed to display program runtime
#include <float.h>				//Line to allow use of machine precision constants
#include <string>				//Line to allow use of strings as a data type
//#include <unordered_map>        //Line to allow use of unordered_map structure
#include <exception>            //Line to allow use of try-catch statements
#include "error.h"

//Matrix Class
class Matrix
{
public:

	//Generalized Matrix Operations
	Matrix(int rows, int columns);
	double& operator()(int i, int j);
	double operator()(int i, int j) const;
	Matrix(const Matrix& M);
	Matrix& operator=(const Matrix& M);
	Matrix();
    ~Matrix();
	void set_size(int i, int j);
    void zeros();
    void edit(int i, int j, double value);
    int rows();
    int columns();
	double determinate();
    double norm();
	double sum();
    double inner_product(const Matrix& x);
	Matrix& cofactor(const Matrix& M);
	Matrix operator+(const Matrix& M);
	Matrix operator-(const Matrix& M);
	Matrix operator*(const double);
	Matrix operator/(const double);
	Matrix operator*(const Matrix& M);
	Matrix& transpose(const Matrix& M);
    Matrix& transpose_multiply(const Matrix& MT, const Matrix& v);
	Matrix& adjoint(const Matrix &M);
	Matrix& inverse(const Matrix &M);
	void Display(const std::string Name);

	//Specialized Matrix Operations for 1-D FDM
	Matrix& tridiagonalSolve(const Matrix& A, const Matrix& b);
	Matrix& ladshawSolve(const Matrix& A, const Matrix& d);
	Matrix& tridiagonalFill(const double A, const double B, const double C, bool Spherical);
    Matrix& naturalLaplacian3D(int m);
	Matrix& sphericalBCFill(int node, const double coeff, double variable);
	Matrix& ConstantICFill(const double IC);

	//Specialized Matrix Operations for SKIMMER
	Matrix& SolnTransform(const Matrix& A, bool Forward);
	double sphericalAvg(double radius, double dr, double bound, bool Dirichlet);
	double IntegralAvg(double radius, double dr, double bound, bool Dirichlet);
	double IntegralTotal(double dr, double bound, bool Dirichlet);
	
	//Specialized Matrix Operations for 1-D Conservation Laws
	Matrix& tridiagonalVectorFill(const std::vector<double> &A, const std::vector<double> &B, const std::vector<double> &C);
	Matrix& columnVectorFill(const std::vector<double> &A);
	Matrix& columnProjection(const Matrix& b, const Matrix& b_old, const double dt, const double dt_old);
	Matrix& dirichletBCFill(int node, const double coeff, double variable);
    
    //Matrix operations for functions focused on Krylov, GMRES, and PJFNK methods
  	Matrix& diagonalSolve(const Matrix& D, const Matrix& v);
    Matrix& upperTriangularSolve(const Matrix& U, const Matrix& v);
    Matrix& lowerTriangularSolve(const Matrix& L, const Matrix& v);
    Matrix& upperHessenberg2Triangular(Matrix& b);
    Matrix& lowerHessenberg2Triangular(Matrix& b);
    Matrix& upperHessenbergSolve(const Matrix& H, const Matrix& v);
    Matrix& lowerHessenbergSolve(const Matrix& H, const Matrix& v);
    Matrix& columnExtract(int j, const Matrix& M);
    Matrix& rowExtract(int i, const Matrix& M);
    Matrix& columnReplace(int j, const Matrix& v);
    Matrix& rowReplace(int i, const Matrix& v);
    void rowShrink();
    void columnShrink();
    void rowExtend(const Matrix& v);
    void columnExtend(const Matrix& v);
    

protected:
    int num_rows;
	int num_cols;
	std::vector<double> Data;
};

//Start of an inherited class for handling Sparse Matrices
/*
class SparseMatrix : Matrix
{
public:
  	//Generalized SparseMatrix Operations
    SparseMatrix();
    ~SparseMatrix();
  	SparseMatrix(int rows, int columns);
    double& operator()(int i, int j);
  	double operator()(int i, int j) const;
    SparseMatrix& operator=(const Matrix& M);
    SparseMatrix(const Matrix& M);
    SparseMatrix& operator=(const SparseMatrix& SM);
    SparseMatrix(const SparseMatrix& SM);
  	void set_size(int i, int j);
  	void remove(int i, int j);
  	void remove_all();
    void edit(int i, int j, double value);
  	double norm();
  	double inner_product(const Matrix& x);
  	double inner_product(const SparseMatrix& sx);
    SparseMatrix operator+(const Matrix& M);
    SparseMatrix operator+(const SparseMatrix& SM);
    SparseMatrix operator-(const Matrix& M);
    SparseMatrix operator-(const SparseMatrix& SM);
    SparseMatrix operator*(const double);
    SparseMatrix operator*(const Matrix& M);
    SparseMatrix operator*(const SparseMatrix& SM);
  	SparseMatrix& transpose(const Matrix& M);
  	SparseMatrix& transpose(const SparseMatrix& SM);
  	SparseMatrix& transpose_multiply(const Matrix& MT, const Matrix& v);
  	SparseMatrix& transpose_multiply(const SparseMatrix& MT, const Matrix& v);
  	SparseMatrix& transpose_multiply(const Matrix& MT, const SparseMatrix& v);
  	SparseMatrix& transpose_multiply(const SparseMatrix& MT, const SparseMatrix& v);
    void Display(const std::string Name);
  
  	//Specialized SparseMatrix Operations for 1-D Conservation Law PDEs
  	SparseMatrix& ladshawSolve(const Matrix& A, const Matrix& d);
  	SparseMatrix& ladshawSolve(const SparseMatrix& A, const Matrix& d);
  	SparseMatrix& ladshawSolve(const Matrix& A, const SparseMatrix& d);
  	SparseMatrix& ladshawSolve(const SparseMatrix& A, const SparseMatrix& d);
  	SparseMatrix& tridiagonalFill(const double A, const double B, const double C, bool Spherical);
  	SparseMatrix& ConstantICFill(const double IC);
  	SparseMatrix& tridiagonalVectorFill(const std::vector<double> &A, const std::vector<double> &B, const std::vector<double> &C);
  	SparseMatrix& columnVectorFill(const std::vector<double> &A);
  	SparseMatrix& columnProjection(const Matrix& b, const Matrix& b_old, const double dt, const double dt_old);
  	SparseMatrix& columnProjection(const SparseMatrix& b, const Matrix& b_old, const double dt, const double dt_old);
  	SparseMatrix& columnProjection(const Matrix& b, const SparseMatrix& b_old, const double dt, const double dt_old);
  	SparseMatrix& columnProjection(const SparseMatrix& b, const SparseMatrix& b_old, const double dt, const double dt_old);
  	SparseMatrix& dirichletBCFill(int node, const double coeff, double variable);
  
protected:
    std::unordered_map<int, double> Key;
  	int nz;
    double zero[1];
};
 */

int MACAW_TESTS();


#endif /* MACAW_HPP_ */
