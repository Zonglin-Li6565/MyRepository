//============================================================================
// Name        : ComplexNumber.cpp
// Author      : Zonglin Li
//============================================================================

#include <iostream>
#include "ComplexNumber.h"
using namespace std;

int main() {							//example codes.
	ComplexNumber a;					//using empty constructor
	ComplexNumber b(4);					//pass in the real part
	ComplexNumber c(3, 6);				//create a complete complex number
	ComplexNumber z;					//using empty constructor
	z = "  5.09  -   7.3i  ";			//assign from string
	ComplexNumber t;					//using empty constructor
	t = " -  5.09 + 4.23i ";			//assign from string
	cout << ComplexNumber::getimaginary(c) << endl;
	cout << b.getreal() << endl;
	a.add(b);							//add b to a
	cout << "a = " << a.toString() << endl;
	ComplexNumber d = ComplexNumber::subtract(b, c);	//subtract c from b
	cout << "d = " << d.toString() << endl;
	double e = 4;
	c.add(e);							//add e to real part of c
	cout << "c = " << c.toString() << endl;
	cout << "z = " << z.toString() << endl << "t = " << t.toString() << endl;
	ComplexNumber x = z + t;			//create a new complex number and assign the value of z + t
	cout << "x = " << x.toString() << endl;
	ComplexNumber conjugatex = ~x;		//conjugate of x
	cout << "conjugates of x = " << conjugatex.toString() << endl;
	ComplexNumber o;
	o = "3 + 4i";						//assign value for o
	ComplexNumber r;
	r = o ^ 0.5;						//o to 0.5(square root of o)
	ComplexNumber p;
	p = o ^ 2;							//o to 2(square of o)
	cout << "root of 3 + 4i = " << r.toString() << endl;
	cout << "square of 3 + 4i = " << p.toString() << endl;
	return 0;
}

namespace std {

ComplexNumber::ComplexNumber() {
	real = 0;
	imaginary = 0;
}

ComplexNumber::ComplexNumber(double rel) {
	real = rel;
	imaginary = 0;
}

ComplexNumber::ComplexNumber(double realpart, double imaginarypart) {
	real = realpart;
	imaginary = imaginarypart;
}

ComplexNumber::ComplexNumber(const string expression) {
	ostringstream exception;
	int size = expression.size(), i = 0, signr, signi;
	signr = parsesign(expression, i, size);
	this->real = parsedouble(expression, i, size) * signr;
	signi = parsesign(expression, i, size);
	this->imaginary = parsedouble(expression, i, size) * signi;
	if (expression[i] != 'i' && i != size) {
		exception << "for input: " << expression << " illegal expression at "
				<< i;
		throw runtime_error(exception.str());
	}
}

int parsesign(string expression, int& start, int const end) {
	ostringstream exception;
	char c = expression[start];
	for (; start < end; c = expression[++start]) {
		if (c == ' ')
			continue;
		if (isdigit(c))
			break;
		if (c == '+' || c == '-') {
			start++;
			return 44 - c;
		}
		exception << "illegal expression at " << start;
		throw runtime_error(exception.str());
	}
	return 1;
}

double parsedouble(string expression, int& start, int const end) {
	ostringstream s, exception;
	char c = expression[start];
	bool hasdot = false;
	for (; start < end; c = expression[++start]) {
		if (c == ' ')
			continue;
		if (isdigit(c)) {
			for (; start < end && (isdigit(c = expression[start]) || c == '.');
					start++) {
				if (c == '.' && hasdot) {
					exception << "for input: " << expression
							<< " multiple dots at " << start;
					throw runtime_error(exception.str());
				} else
					hasdot = c == '.' ? true : hasdot;
				s << c;
			}
			break;
		}
		exception << "for input: " << expression << " illegal expression at "
				<< start;
		throw runtime_error(exception.str());
	}
	return atof(s.str().c_str());
}

ComplexNumber::ComplexNumber(const ComplexNumber& complexnumber) {
	real = complexnumber.real;
	imaginary = complexnumber.imaginary;
}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber& newone) {
	if (this == &newone)
		return *this;
	this->real = newone.real;
	this->imaginary = newone.imaginary;
	return *this;
}

ComplexNumber& ComplexNumber::operator=(const string expression) {
	ComplexNumber c(expression);
	this->real = c.real;
	this->imaginary = c.imaginary;
	return *this;
}

double ComplexNumber::getimaginary(const ComplexNumber& complexnumber) {
	return complexnumber.imaginary;
}

double ComplexNumber::getreal(const ComplexNumber& complexnumber) {
	return complexnumber.real;
}

double ComplexNumber::getreal() {
	return real;
}

double ComplexNumber::getimaginary() {
	return imaginary;
}

double ComplexNumber::angle() {
	return atan(imaginary / real);
}

ComplexNumber ComplexNumber::subtract(const ComplexNumber& first,
		const ComplexNumber& second) {
	ComplexNumber c(first.real - second.real,
			first.imaginary - second.imaginary);
	return c;
}

void ComplexNumber::add(double real) {
	this->real += real;
}

void ComplexNumber::add(double real, double imaginary) {
	this->real += real;
	this->imaginary += imaginary;
}

void ComplexNumber::add(const ComplexNumber& first) {
	this->real += first.real;
	this->imaginary += first.imaginary;
}

bool operator==(const ComplexNumber& first, const ComplexNumber& second) {
	return first.real == second.real && first.imaginary == second.imaginary;
}

bool operator!=(const ComplexNumber& first, const ComplexNumber& second) {
	return !(first == second);
}

ComplexNumber operator+(const ComplexNumber& first,
		const ComplexNumber& second) {
	return ComplexNumber(first.real + second.real,
			first.imaginary + second.imaginary);
}

ComplexNumber operator-(const ComplexNumber& first,
		const ComplexNumber& second) {
	return ComplexNumber(first.real - second.real,
			first.imaginary - second.imaginary);
}

ComplexNumber operator-(const ComplexNumber& first) {
	return ComplexNumber(-first.real, -first.imaginary);
}

ComplexNumber operator*(const ComplexNumber& first,
		const ComplexNumber& second) {
	double a = first.real, b = first.imaginary, c = second.real, d =
			second.imaginary;
	return ComplexNumber(a * c - b * d, a * d + b * c);
}

ComplexNumber operator~(const ComplexNumber& complex) {
	return ComplexNumber(complex.real, -complex.imaginary);
}

ComplexNumber operator/(const ComplexNumber& first,
		const ComplexNumber& second) {
	if (second.imaginary == 0) {
		return ComplexNumber(first.real / second.real,
				first.imaginary / second.real);
	} else {
		return first * (~second) / ((~second) * second);
	}
}

ComplexNumber operator^(ComplexNumber& first, double power) {
	double r = pow(sqrt((first * (~first)).real), power);
	double theta = first.angle() * power;
	ComplexNumber c(r * cos(theta), r * sin(theta));
	return c;
}

string ComplexNumber::toString() {
	ostringstream s;
	s << real;
	if (imaginary >= 0)
		s << " + ";
	else
		s << " - ";
	s << abs(imaginary) << "i ";
	return s.str();
}

ComplexNumber::~ComplexNumber() {
}

} /* namespace std */
