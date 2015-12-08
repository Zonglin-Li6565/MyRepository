/*
 * ComplexNumber.h
 *
 *  Created on: Nov 3, 2015
 *      Author: Zonglin Li
 */
#include <sstream>
#include <locale>
#include <stdexcept>
#include <stdlib.h>
#include <cmath>

#ifndef COMPLEXNUMBER_H_
#define COMPLEXNUMBER_H_

namespace std {

class ComplexNumber {
public:
	double real;
	double imaginary;
	ComplexNumber();
	ComplexNumber(double real);
	ComplexNumber(const string expression);
	ComplexNumber(double realpart, double imaginarypart);
	ComplexNumber(const ComplexNumber& complexnumber);
	static double getimaginary(const ComplexNumber& complexnumber);
	static double getreal(const ComplexNumber& complexnumber);
	static ComplexNumber subtract(const ComplexNumber& first,
			const ComplexNumber& second);
	void add(double real);
	void add(double real, double imaginary);
	void add(const ComplexNumber& first);
	double getreal();
	double getimaginary();
	double angle();
	string toString();
	virtual ~ComplexNumber();
	ComplexNumber& operator=(const ComplexNumber& newone);				//assign
	ComplexNumber& operator=(const string expression);
};

bool operator==(const ComplexNumber& first, const ComplexNumber& second);
bool operator!=(const ComplexNumber& first, const ComplexNumber& second);
ComplexNumber operator+(const ComplexNumber& first,
		const ComplexNumber& second);	//add
ComplexNumber operator-(const ComplexNumber& first,
		const ComplexNumber& second);	//Subtract
ComplexNumber operator-(const ComplexNumber& first);				//negative
ComplexNumber operator*(const ComplexNumber& first,
		const ComplexNumber& second);	//multiply
ComplexNumber operator/(const ComplexNumber& first,
		const ComplexNumber& second);	//divide
ComplexNumber operator^(ComplexNumber& first, double power);			//power
ComplexNumber operator~(const ComplexNumber& complex);			//convergence
double parsedouble(string expression, int& start, int end);
int parsesign(string expression, int& start, int const end);
} /* namespace std */

#endif /* COMPLEXNUMBER_H_ */
