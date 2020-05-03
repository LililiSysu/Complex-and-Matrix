#pragma once
#include<functional>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<ctime>
#include<string>
#include<fstream>

using namespace std;
#define pi 3.14159265358979323846

void end() {
	cout << endl << "___________________________________"
		<< endl << "press enter to continue...";
	getchar();
}

//rand functions
template<class T> T rand_num(unsigned int seed)
{
	//produce a rand number uniformly from 0 to 1.
	static unsigned int h = seed;
	h = (38131 + 3321 * h) % 65521;
	return T(h / 65521.0);
}
template<class T> T rand_num_pn(unsigned int seed)
{
	//produce a rand number uniformly from -1 to 1.
	return T(1 - 2 * rand_num<double>(seed));
}
template<class T> T rand_num_ga(unsigned int seed)
{
	//produce a rand number of normal gaussian distribution
	unsigned int seed2 = seed * seed + 152;	//seed2
	return T(sqrt(-2 * log(rand_num<double>(seed)))*cos(2 * pi*rand_num<double>(seed2)));	//return guassian random varible.
}
template<class T> T rand_num_01(unsigned int seed)
{
	//random number 0 or 1
	return T(rand_num<T>(seed) > 0.5 ? 1 : 0);
}
template<class T> T rand_num_pn1(unsigned int seed)
{
	//random number -1 or 1
	return T(rand_num<double>(seed) > 0.5 ? 1 : -1);
}
template<class T> T rand_num_09(unsigned int seed)
{
	//random interger number from 0 to 9
	return T(int(rand_num<double>(seed) * 10));
}

//type functions for complex.

char type(const char& a) {
	return 'c';
}
char type(const bool& a) {
	return 'b';
}
char type(const int& a) {
	return 'i';
}
char type(const long& a) {
	return 'l';
}
char type(const float& a) {
	return 'f';
}
char type(const double& a) {
	return 'd';
}

char conj(const char& a) {
	return a;
}
bool conj(const bool& a) {
	return a;
}
int conj(const int& a) {
	return a;
}
long conj(const long& a) {
	return a;
}
float conj(const float& a) {
	return a;
}
double conj(const double& a) {
	return a;
}

char get_x(const char& a) {
	return a;
}
bool get_x(const bool& a) {
	return a;
}
int get_x(const int& a) {
	return a;
}
long get_x(const long& a) {
	return a;
}
float get_x(const float& a) {
	return a;
}
double get_x(const double& a) {
	return a;
}

char get_y(const char& a) {
	return a;
}
bool get_y(const bool& a) {
	return a;
}
int get_y(const int& a) {
	return a;
}
long get_y(const long& a) {
	return a;
}
float get_y(const float& a) {
	return a;
}
double get_y(const double& a) {
	return a;
}

//other functions
string file_type(const string& file_name) {	//return the type of file
	string ans = "";
	for (int k = file_name.find('.') + 1; file_name[k] != '\0'; k++)
		ans = ans + file_name[k];
	return ans;
}

//Complex class
template<class T> T arg(T ang) {
	if (ang > pi) {
		do {
			ang -= 2 * pi;
		} while (ang > pi);
	}
	else if (ang <= -pi) {
		do {
			ang += 2 * pi;
		} while (ang <= -pi);
	}
	return ang;
};

class Complex
{
	// the angle range from (-pi, pi]
private:
	double x;
	double y;
	bool isFA_form; //0: Real-Imaginary. 1: Fabs-Angle.

public:
	Complex(double X = 0, double Y = 0, bool isFA = false) :x(X), y(Y), isFA_form(isFA) {	//default: Real-Imaginary type.
		if (isFA_form == true) y = arg(y);
	}
	Complex(const Complex& c) {
		x = c.x;
		y = c.y;
		isFA_form = c.isFA_form;
	}
	Complex operator = (const Complex& c) {
		x = c.x;
		y = c.y;
		isFA_form = c.isFA_form;
		return c;
	}
	~Complex() {}

	double get_x() const {
		return x;
	}
	double get_y() const {
		return y;
	}
	friend double get_x(const Complex& c) {
		return c.x;
	}
	friend double get_y(const Complex& c) {
		return c.y;
	}
	double real() const	{
		if (isFA_form)
			return x * cos(y);
		else
			return x;
	}
	double imag() const	{
		if (isFA_form)
			return x * sin(y);
		else
			return y;
	}
	double fab() const {
		if (isFA_form)
			return x;
		else
			return sqrt(x * x + y * y);
	}
	double angle() const {
		if (isFA_form)
			return y;
		else
			if (x > 0)
				return atan(y / x);
			else if (x < 0 && y >= 0)
				return atan(y / x) + pi;
			else if (x < 0 && y < 0)
				return atan(y / x) - pi;
			else if (x == 0 && y != 0)
				return (y > 0)*pi / 2;
			else
				return 0;	//set the angle of (0 + 0j) be 0
	}
	bool isFA() const {
		return isFA_form;
	}
	bool isRI() const {
		return !isFA_form;
	}
	bool form() const {
		return isFA_form; //0: Real-Imaginary. 1: Fabs-Angle.
	}
	bool isZero() const {
		if (isFA_form)
			return x == 0;
		else
			return (x == 0 && y == 0);
	}
	void set(double X, double Y) {
		x = X;
		y = Y;
		if (isFA_form == true) y = arg(y);
	}
	void set(double X, double Y, bool isFA) {
		x = X;
		y = Y;
		isFA_form = isFA;
		if (isFA_form == true) y = arg(y);
	}
	void set_x(double X) {
		x = X;
	}
	void set_y(double Y) {
		y = Y;
		if (isFA_form == true) y = arg(y);
	}
	void set_form(bool isFA) {
		isFA_form = isFA;
		if (isFA_form == true) y = arg(y);
	}
	void turn_RI() {
		if (isFA_form)
			set(x * cos(y), x * sin(y), false);
		else;
	}
	void turn_FA() {
		if (isFA_form);
		else
			set(sqrt(x * x + y * y), angle(), true);
	}

	void print() const {
		if (isFA_form)
			cout << x << " e^(" << y << "j)" << endl;
		else
			if (y >= 0)
				cout << x << " +" << fabs(y) << 'j' << endl;
			else
				cout << x << ' ' << y << 'j' << endl;
	}
	void input(bool isFA = false) {	//default: Real-Imaginary type.
		isFA_form = isFA;
		cin >> x >> y;
	}
	friend void printf(const char* setting, const Complex& c) {
		if (c.isFA_form) {
			printf(setting, c.x); printf((c.y >= 0 ? " e^( j%.4e )" : " e^( -j%.4e )"), fabs(c.y));
		}
		else {
			printf(setting, c.x); printf((c.y >= 0 ? " + j%.4e" : " - j%.4e"), fabs(c.y));
		}

	}
	friend void fprintf(FILE *const file,const char* setting, const Complex& c) {
		if (c.isFA_form) {
			fprintf(file, setting, c.x); fprintf(file, (c.y >= 0 ? " e^( j%.4e )" : " e^( -j%.4e )"), fabs(c.y));
		}
		else {
			fprintf(file, setting, c.x); fprintf(file, (c.y >= 0 ? " + j%.4e" : " - j%.4e"), fabs(c.y));
		}

	}
	friend ostream& operator << (ostream& out, const Complex& c) {
		if (c.isFA_form)
			out << c.x << "e^(" << c.y << "j)";
		else
			if (c.y >= 0)
				out << c.x << " +" << fabs(c.y) << 'j';
			else
				out << c.x << ' ' << c.y << 'j';
		return out;
	}
	friend istream& operator >> (istream& in, Complex& c) {
		in >> c.x >> c.y;
		c.isFA_form = false;	// default case is real-imaginary input
		return in;
	}
	friend char type(const Complex& c) {
		return 'C';
	}

	//the following answer form is same with the [c1/c] form.
	friend Complex operator + (const Complex& c1, const Complex& c2) {
		if (c1.isFA_form) {
			Complex ans(c1.x * cos(c1.y) + c2.real(), c1.x * sin(c1.y) + c2.imag());
			ans.turn_FA();
			return ans;
		}
		else
			return Complex(c1.x + c2.real(), c1.y + c2.imag());
	}
	friend Complex operator + (double num, const Complex& c) {
		if (c.isFA_form) {
			Complex ans(c.x * cos(c.y) + num, c.x * sin(c.y));
			ans.turn_FA();
			return ans;
		}
		else
			return Complex(c.x + num, c.y);
	}
	friend Complex operator + (const Complex& c, double num) {
		return num + c;
	}
	friend Complex operator - (const Complex& c1, const Complex& c2) {
		if (c1.isFA_form) {
			Complex ans(c1.x * cos(c1.y) - c2.real(), c1.x * sin(c1.y) - c2.imag());
			ans.turn_FA();
			return ans;
		}
		else
			return Complex(c1.x - c2.real(), c1.y - c2.imag());
	}
	friend Complex operator - (double num, const Complex& c) {
		return num + (-c);
	}
	friend Complex operator - (const Complex& c, double num) {
		return -num + c;
	}
	friend Complex operator * (const Complex& c1, const Complex& c2) {
		if (c1.isFA_form)
			return Complex(c1.x * c2.fab(), arg(c1.y + c2.angle()), true);
		else
			return Complex(c1.x * c2.real() - c1.y * c2.imag(), c1.x * c2.imag() + c1.y * c2.real());
	}
	friend Complex operator * (double num, const Complex& c) {
		if (c.isFA_form)
			if (num > 0)
				return Complex(c.x * num, c.y, true);
			else
				return Complex(c.x * (-num), arg(c.y + pi), true);
		else
			return Complex(c.x * num, c.y * num);
	}
	friend Complex operator * (const Complex& c, double num) {
		return num * c;
	}
	friend Complex operator / (const Complex& c1, const Complex& c2) {
		if (c1.isFA_form)
			return Complex(c1.x / c2.fab(), arg(c1.y - c2.angle()), true);
		else {
			double temp = c2.real() * c2.real() + c2.imag() * c2.imag();
			return Complex((c1.x * c2.real() + c1.y * c2.imag()) / temp, (c1.y * c2.real() - c1.x * c2.imag()) / temp);
		}
	}
	friend Complex operator / (double num, const Complex& c) {
		if (c.isFA_form)
			if (num > 0)
				return Complex(num / c.x, ((c.y == pi) ? c.y : -c.y), true);
			else
				return Complex((-num) / c.x, arg(((c.y == pi) ? c.y : -c.y) + pi), true);
		else {
			double temp = c.x * c.x + c.y * c.y;
			return Complex(c.x * num / temp, -c.y * num / temp);
		}
	}
	friend Complex operator / (const Complex& c, double num) {
		return 1 / num * c;
	}

	friend Complex operator - (const Complex& c) {
		if (c.isFA_form) {
			return Complex(c.x, arg(c.y + pi), true);
		}
		else {
			return Complex(-c.x, -c.y);
		}
	}
	friend bool operator == (const Complex& c1, const Complex& c2) {
		return ((c1.isFA_form == c2.isFA_form) ? (c1.x == c2.x && c1.y == c2.y) : (c1.real() == c2.real() && c1.imag() == c2.imag()));
	}
	friend bool operator == (double num, const Complex& c2) {
		return (c2.y == 0 && c2.x == num);
	}
	friend bool operator == (const Complex& c2, double num) {
		return (c2.y == 0 && c2.x == num);
	}
	friend bool operator != (const Complex& c1, const Complex& c2) {
		return !(c1 == c2);
	}
	friend bool operator != (double num, const Complex& c2) {
		return (c2.y != 0 || c2.x != num);
	}
	friend bool operator != (const Complex& c2, double num) {
		return (c2.y != 0 || c2.x != num);
	}
	friend bool operator > (const Complex& c1, const Complex& c2) {
		if (c1.y == 0 && c2.y == 0) {
			return c1.x > c2.x;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator > (const Complex& c, double num) {
		if (c.y == 0) {
			return c.x > num;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator > (double num, const Complex& c) {
		if (c.y == 0) {
			return num > c.x;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator < (const Complex& c1, const Complex& c2) {
		if (c1.y == 0 && c2.y == 0) {
			return c1.x < c2.x;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator < (const Complex& c, double num) {
		if (c.y == 0) {
			return c.x < num;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator < (double num, const Complex& c) {
		if (c.y == 0) {
			return num < c.x;

		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator >= (const Complex& c1, const Complex& c2) {
		if (c1.y == 0 && c2.y == 0) {
			return c1.x >= c2.x;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator >= (const Complex& c, double num) {
		if (c.y == 0) {
			return c.x >= num;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator >= (double num, const Complex& c) {
		if (c.y == 0) {
			return num >= c.x;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator <= (const Complex& c1, const Complex& c2) {
		if (c1.y == 0 && c2.y == 0) {
			return c1.x <= c2.x;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator <= (const Complex& c, double num) {
		if (c.y == 0) {
			return c.x <= num;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}
	friend bool operator <= (double num, const Complex& c) {
		if (c.y == 0) {
			return num <= c.x;
		}
		else {
			cout << "error compare" << endl;
			return false;
		}
	}

	friend double fabs(const Complex& c) {
		if (c.isFA_form)
			return fabs(c.x);
		else
			return sqrt(c.x * c.x + c.y * c.y);
	}
	friend Complex sqrt(const Complex& c) {
		if (c.isFA_form)
			return Complex(sqrt(c.x), c.y / 2, true);
		else {
			Complex ans(sqrt(c.fab()), c.angle() / 2, true);
			ans.turn_RI();
			return ans;
		}
	}
	friend Complex conj(const Complex& c) {
		return Complex(c.x,((c.isFA_form && c.y == pi) ? c.y : -c.y), c.isFA_form);
	}
	
	friend Complex rotate(const Complex& c, double theta) {
		if (c.isFA_form)
			return Complex(c.x, arg(c.y + theta), true);
		else {
			Complex ans(c);
			ans.turn_FA();
			ans = rotate(ans, theta);
			ans.turn_RI();
			return ans;
		}
	}
	friend Complex inverse(const Complex& c) {
		if (c.isFA_form)
			return Complex(1 / c.x, (c.y == pi ? c.y : -c.y), true);
		else {
			double temp = c.x * c.x + c.y * c.y;
			return Complex(c.x / temp, -c.y / temp);
		}
	}
	friend Complex exp(const Complex& c) {
		if (c.isFA_form)
			return Complex(exp(c.x * cos(c.y)), arg(c.x * sin(c.y)), true);
		else
			return Complex(exp(c.x)*cos(c.y), exp(c.x)*sin(c.y));
	}
	friend Complex pow(const Complex& c, double num) {
		if (c.isFA_form)
			return Complex(pow(c.x, num), arg(c.y * num), true);
		else {
			Complex ans(c);
			ans.turn_FA();
			ans = pow(ans, num);
			ans.turn_RI();
			return ans;

		}
	}
	friend Complex pow(double num, const Complex& c) {
		if (c.isFA_form) {
			Complex ans(c.x * cos(c.y), c.x * sin(c.y));
			ans.set(pow(num, ans.x), ans.y * log(num), true);
			return ans;
		}
		else {
			Complex ans(pow(num, c.x), c.y * log(num), true);
			ans.turn_RI();
			return ans;
		}
	}
	friend Complex log(const Complex& c) {
		if (c.isFA_form) {
			Complex ans(log(c.x), c.y);
			ans.turn_FA();
			return ans;
		}
		else {
			Complex ans(log(sqrt(c.x * c.x + c.y * c.y)), c.angle());
			return ans;
		}
	}
	friend Complex log(double num, const Complex& c) {
		return 1 / log(num)*log(c);
	}
	friend Complex log(const Complex& c, double num) {
		return 1 / log(c)*log(num);
	}
	friend Complex pow(const Complex& c1, const Complex& c2) {
		Complex temp(c2);
		double c2_fabs = temp.fab();
		temp.turn_RI();
		Complex J(0, 1);
		return pow(c1, temp.x) * exp(temp.y * J * log(c1));
	}
	friend Complex log(const Complex& c1, const Complex& c2) {
		return 1 / log(c1) * log(c2);
	}

	friend Complex sin(const Complex& c) {
		Complex J(0, 1);
		return (exp(c * J) - exp(-c * J)) / (2 * J);
	}
	friend Complex cos(const Complex& c) {
		Complex J(0, 1);
		return (exp(c * J) + exp(-c * J)) / 2;
	}
	friend Complex tan(const Complex& c) {
		Complex J(0, 1);
		return (exp(c * J) - exp(-c * J)) / (exp(c * J) + exp(-c * J)) / J;
	}
	friend Complex cot(const Complex& c) {
		Complex J(0, 1);
		return (exp(c * J) + exp(-c * J)) * J / (exp(c * J) - exp(-c * J));
	}
	friend Complex sec(const Complex& c) {
		Complex J(0, 1);
		return 2 / (exp(c * J) + exp(-c * J));
	}
	friend Complex asin(const Complex& c) {
		Complex J(0, 1);
		return log(c * J + sqrt(1 - c * c)) * (-J);
	}
	friend Complex acos(const Complex& c) {
		Complex J(0, 1);
		return log(c + sqrt(1 - c * c) * J) * (-J);
	}
	friend Complex atan(const Complex& c) {
		Complex J(0, 1);
		return log((-c + J) / (c + J)) / (2 * J);
	}
	friend Complex sinh(const Complex& c) {
		return (exp(c) - exp(-c)) / 2;
	}
	friend Complex cosh(const Complex& c) {
		return (exp(c) + exp(-c)) / 2;
	}
	friend Complex tanh(const Complex& c) {
		return (exp(c) + exp(-c)) / (exp(c) - exp(-c));
	}
	friend Complex asinh(const Complex& c) {
		return log(c + sqrt(c*c + 1));
	}
	friend Complex acosh(const Complex& c) {
		return log(c + sqrt(c*c - 1));
	}
	friend Complex atanh(const Complex& c) {
		return log((1 + c) / (1 - c)) / 2;
	}
};

Complex J(0, 1);
Complex J2(1, pi / 2, 1);

//Matrix class
template<class T> class Matrix
{
protected:
	int r;
	int c;
	T* e;
public:

	//constructors and destructor
	Matrix() {
		r = 0;
		c = 0;
		e = NULL;
	}
	Matrix(int row, int column, T *element) :r(row), c(column) {
		e = new T[r*c];
		for (int i = 0; i < r*c; i++)
			e[i] = element[i];
	}
	Matrix(int row, int column) :r(row), c(column) {
		e = new T[r*c];
	}
	Matrix(int row, int column, char type) :r(row), c(column) {
		e = new T[r*c];
		if (type == '0' /* zero */) {
			for (int i = 0; i < r*c; i++)
				e[i] = T(0);
		}
		else if (type == '1' /* one */) {
			for (int i = 0; i < r*c; i++)
				e[i] = T(1);
		}
		else if (type == 'i' /* identity */) {
			for (int i = 0; i < r; i++)
				for (int j = 0; j < c; j++)
					if (i == j)
						e[i*c + j] = T(1);
					else
						e[i*c + j] = T(0);
		}
		else if (type == 'u' /* uniformly from 0 to 1 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num<T>((unsigned int)time(0));
		}
		else if (type == 'U' /* Uniformly from -1 to 1 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_pn<T>((unsigned int)time(0));
		}
		else if (type == 'g' /* gaussian normally */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_ga<T>((unsigned int)time(0));
		}
		else if (type == 'b' /* binary of 0 and 1 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_01<T>((unsigned int)time(0));
		}
		else if (type == 'B' /* Binary of -1 and 1 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_pn1<T>((unsigned int)time(0));
		}
		else if (type == 'n' /* natrual uniformly from 0 to 9 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_09<T>((unsigned int)time(0));
		}
		else if (type == 'N' /* Natrual number in sequence start from 0 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = T(i);
		}
	}
	Matrix(int size, T *element) :r(size), c(size) {
		e = new T[r*c];
		for (int i = 0; i < r*c; i++)
			e[i] = element[i];
	}
	Matrix(int size) :r(size), c(size) {
		e = new T[r*c];
	}
	Matrix(int size, char type) :r(size), c(size) {
		e = new T[r*c];
		if (type == '0' /* zero */) {
			for (int i = 0; i < r*c; i++)
				e[i] = T(0);
		}
		else if (type == '1' /* one */) {
			for (int i = 0; i < r*c; i++)
				e[i] = T(1);
		}
		else if (type == 'i' /* identity */) {
			for (int i = 0; i < r; i++)
				for (int j = 0; j < c; j++)
					if (i == j)
						e[i*c + j] = T(1);
					else
						e[i*c + j] = T(0);
		}
		else if (type == 'u' /* uniformly from 0 to 1 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num<T>((unsigned int)time(0));
		}
		else if (type == 'U' /* Uniformly from -1 to 1 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_pn<T>((unsigned int)time(0));
		}
		else if (type == 'g' /* gaussian normally */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_ga<T>((unsigned int)time(0));
		}
		else if (type == 'b' /* binary of 0 and 1 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_01<T>((unsigned int)time(0));
		}
		else if (type == 'B' /* Binary of -1 and 1 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_pn1<T>((unsigned int)time(0));
		}
		else if (type == 'n' /* natrual uniformly from 0 to 9 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = rand_num_09<T>((unsigned int)time(0));
		}
		else if (type == 'N' /* Natrual number in sequence start from 0 */) {
			for (int i = 0; i < r*c; i++)
				e[i] = T(i);
		}
	}
	Matrix(const Matrix<T>& A) {
		r = A.r;
		c = A.c;
		e = new T[r*c];
		for (int i = 0; i < r*c; i++)
			e[i] = A.e[i];
	}
	Matrix<T> operator = (const Matrix<T>& A) {
		T *temp = e;
		r = A.r;
		c = A.c;
		e = new T[r*c];
		delete[] temp;
		for (int i = 0; i < r*c; i++)
			e[i] = A.e[i];
		return A;
	}
	~Matrix() {
		delete[] e;
	}
	void clear() {
		r = 0;
		c = 0;
		delete[] e;
	}

	//fetch functions
	int row() const {
		return r;	// return the number of row
	}
	int col() const {
		return c;	// return the number of column
	}
	int pos_ind(int row, int column) const {
		return row * c + column;
	}
	T ele(int pos) const {
		return e[pos - 1];	//return the element in positon (pos)
	}
	T ele(int row, int column) const {
		return e[(row - 1) * c + column - 1];	//return the element in positon (row, column)
	}
	T ele_ind(int pos) const {
		return e[pos];	//return the element in positon (pos)
	}
	T ele_ind(int row, int column) const {
		return e[row * c + column];	//return the element in positon (row, column)
	}
	Matrix<T> get_row(int row) const {	//return the row vector in row (row)
		Matrix<T> result(1, c);
		row--;
		for (int j = 0; j < c; j++)
			result.set_e_ind(j, e[row * c + j]);
		return result;
	}
	Matrix<T> get_col(int column) const {	//return the column vector in column (column)
		Matrix<T> result(r, 1);
		column--;
		for (int i = 0; i < r; i++)
			result.set_e_ind(i, e[i * c + column]);
		return result;
	}
	Matrix<T> flat(bool to_row = 1) const {	//return the [row/column] vector of all elements
		if (to_row)
			return Matrix<T>(1, r * c, e);
		else
			return Matrix<T>(r * c, 1, e);
	}
	Matrix<T> get_part(int row_start, int row_end, int column_start, int column_end) const {
		//return the matrix in a certain part (row_start to row_end, column_start to column_end)

		row_start--;
		column_start--;
		Matrix<T> result(row_end - row_start, column_end - column_start);
		int k = 0;
		for (int i = row_start; i < row_end; i++)
			for (int j = column_start; j < column_end; j++) {
				result.set_e_ind(k, e[i*c + j]);
				k++;
			}
		return result;
	}
	Matrix<T> get_diag() const {	//return the row vector of diagonal elements
		if (r <= c) {
			Matrix<T> result(1, r);
			for (int i = 0; i < r; i++)
				result.set_e_ind(i, e[i * c + i]);
			return result;
		}
		else {
			Matrix<T> result(1, c);
			for (int j = 0; j < c; j++)
				result.set_e_ind(j, e[j * c + j]);
			return result;
		}
	}

	Matrix<T> get_row_ind(int row) const {	//return the row vector in row (row)
		Matrix<T> result(1, c);
		for (int j = 0; j < c; j++)
			result.set_e_ind(j, e[row * c + j]);
		return result;
	}
	Matrix<T> get_col_ind(int column) const {	//return the column vector in column (column)
		Matrix<T> result(r, 1);
		for (int i = 0; i < r; i++)
			result.set_e_ind(i, e[i * c + column]);
		return result;
	}

	//the next 14 functions return the element with [max/min] [fabs] value
	T max_ele() const {	//return the max element in matrix
		T max = e[0];
		double max_fabs = fabs(max);
		double temp_fabs;
		for (int j = 0; j < r *c; j++) {
			temp_fabs = fabs(e[j]);
			if (max_fabs < temp_fabs) {
				max = e[j];
				max_fabs = temp_fabs;
			}
		}
		return max;
	}
	T max_ele(int &position) const {	//return the max element and its position (position) in matrix
		T max = e[0];
		double max_fabs = fabs(max);
		double temp_fabs;
		position = 1;
		for (int j = 0; j < r*c; j++) {
			temp_fabs = fabs(e[j]);
			if (max_fabs < temp_fabs) {
				max = e[j];
				max_fabs = temp_fabs;
				position = j + 1;
			}
		}
		return max;
	}
	T max_ele(int &row, int &column) const {	//return the max element and its position (row, column) in matrix
		T max = e[0];
		double max_fabs = fabs(max);
		double temp_fabs;
		row = 1;
		column = 1;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++) {
				temp_fabs = fabs(e[i * c + j]);
				if (max_fabs < temp_fabs) {
					max = e[i * c + j];
					max_fabs = temp_fabs;
					row = i + 1;
					column = j + 1;
				}
			}
		return max;
	}
	T min_ele() const {	//return the min element in matrix
		T min = e[0];
		double min_fabs = fabs(min);
		double temp_fabs;
		for (int j = 0; j < r*c; j++) {
			temp_fabs = fabs(e[j]);
			if (min_fabs > temp_fabs) {
				min = e[j];
				min_fabs = temp_fabs;
			}
		}
		return min;
	}
	T min_ele(int &position) const {	//return the min element and its position (position) in matrix
		T min = e[0];
		double min_fabs = fabs(min);
		double temp_fabs;
		position = 1;
		for (int j = 0; j < r*c; j++) {
			temp_fabs = fabs(e[j]);
			if (min_fabs > temp_fabs) {
				min = e[j];
				min_fabs = temp_fabs;
				position = j + 1;
			}
		}
		return min;
	}
	T min_ele(int &row, int &column) const {	//return the min element and its position (row, column) in matrix
		T min = e[0];
		double min_fabs = fabs(min);
		double temp_fabs;
		row = 1;
		column = 1;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++) {
				temp_fabs = fabs(e[i * c + j]);
				if (min_fabs > temp_fabs) {
					min = e[i * c + j];
					min_fabs = temp_fabs;
					row = i + 1;
					column = j + 1;
				}
			}
		return min;
	}
	T max_row_ele(int row) const {
		row--;
		T max = e[row * c];
		double max_fabs = fabs(max);
		double temp_fabs;
		for (int j = 1; j < c; j++) {
			temp_fabs = fabs(e[row * c + j]);
			if (max_fabs < temp_fabs) {
				max = e[row * c + j];
				max_fabs = temp_fabs;
			}
		}
		return max;
	}
	T max_row_ele(int row, int &position) const {
		row--;
		T max = e[row * c];
		double max_fabs = fabs(max);
		double temp_fabs;
		position = 1;
		for (int j = 1; j < c; j++) {
			temp_fabs = fabs(e[row * c + j]);
			if (max_fabs < temp_fabs) {
				max = e[row * c + j];
				max_fabs = temp_fabs;
				position = j;
			}
		}
		return max;
	}
	T min_row_ele(int row) const {
		row--;
		T min = e[row * c];
		double min_fabs = fabs(min);
		double temp_fabs;
		for (int j = 1; j < c; j++) {
			temp_fabs = fabs(e[row * c + j]);
			if (min_fabs > temp_fabs) {
				min = e[row * c + j];
				min_fabs = temp_fabs;
			}
		}
		return min;
	}
	T min_row_ele(int row, int &position) const {
		row--;
		T min = e[row * c];
		double min_fabs = fabs(min);
		double temp_fabs;
		position = 1;
		for (int j = 1; j < c; j++) {
			temp_fabs = fabs(e[row * c + j]);
			if (min_fabs > temp_fabs) {
				min = e[row * c + j];
				min_fabs = temp_fabs;
				position = j;
			}
		}
		return min;
	}
	T max_col_ele(int column) const {
		column--;
		T max = e[column];
		double max_fabs = fabs(max);
		double temp_fabs;
		for (int i = 1; i < r; i++) {
			temp_fabs = fabs(e[i * c + column]);
			if (max_fabs < temp_fabs) {
				max = e[i * c + column];
				max_fabs = temp_fabs;
			}
		}
		return max;
	}
	T max_col_ele(int column, int &position) const {
		column--;
		T max = e[column];
		double max_fabs = fabs(max);
		double temp_fabs;
		position = 1;
		for (int i = 1; i < r; i++) {
			temp_fabs = fabs(e[i * c + column]);
			if (max_fabs < temp_fabs) {
				max = e[i * c + column];
				max_fabs = temp_fabs;
				position = i;
			}
		}
		return max;
	}
	T min_col_ele(int column) const {
		column--;
		T min = e[column];
		double min_fabs = fabs(min);
		double temp_fabs;
		for (int i = 1; i < r; i++) {
			temp_fabs = fabs(e[i * c + column]);
			if (min_fabs > temp_fabs) {
				min = e[i * c + column];
				min_fabs = temp_fabs;
			}
		}
		return min;
	}
	T min_col_ele(int column, int &position) const {
		column--;
		T min = e[column];
		double min_fabs = fabs(min);
		double temp_fabs;
		position = 1;
		for (int i = 1; i < r; i++) {
			temp_fabs = fabs(e[i * c + column]);
			if (min_fabs > temp_fabs) {
				min = e[i * c + column];
				min_fabs = temp_fabs;
				position = i;
			}
		}
		return min;
	}

	T max_ele_ind(int &position) const {	//return the max element and its position (position) in matrix
		T max = e[0];
		double max_fabs = fabs(max);
		double temp_fabs;
		position = 0;
		for (int j = 0; j < r*c; j++) {
			temp_fabs = fabs(e[j]);
			if (max_fabs < temp_fabs) {
				max = e[j];
				max_fabs = temp_fabs;
				position = j;
			}
		}
		return max;
	}
	T max_ele_start_from_ind(int start_position,int &position) const {
		/* return the max element and its position (position) in matrix
		   start from the element with positoin (start_position) */
		T max = e[start_position];
		double max_fabs = fabs(max);
		double temp_fabs;
		position = start_position;

		for (int j = start_position + 1; j < r*c; j++) {
			temp_fabs = fabs(e[j]);
			if (max_fabs < temp_fabs) {
				max = e[j];
				max_fabs = temp_fabs;
				position = j;
			}
		}
		return max;
	}
	T max_col_ele_start_from_ind(int column, int row_start, int& position) const {
		int start_pos = row_start * c + column;
		T max = e[start_pos];
		double max_fabs = fabs(max);
		double temp_fabs;
		position = row_start;
		for (int i = row_start + 1; i < r; i++) {
			start_pos += c;
			temp_fabs = fabs(e[start_pos]);
			if (max_fabs < temp_fabs) {
				max = e[start_pos];
				max_fabs = temp_fabs;
				position = i;
			}
		}
		return max;
	}

	//judge functions
	bool isEmpty() const {
		return (r == 0 || c == 0);
	}
	bool isZero() const {
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (e[i*c + j] == T(0));
				else
					return false;
		return true;

	}
	bool isSquared() const {
		return (r == c);
	}
	bool isThin() const {
		return (r > c);
	}
	bool isFat() const {
		return (r < c);
	}
	bool isIdentity() const {
		if (r == c) {
			for (int i = 0; i < r; i++)
				for (int j = 0; j < c; j++)
					if (i == j)
						if (e[i*c + j] != T(1)) return false;
						else;
					else
						if (e[i*c + j] != T(0))return false;
						else;
		}
		else
			return false;
		return true;
	}
	bool isDiagonal() const {
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (i != j)
					if (e[i*c + j] != T(0))return false;
		return true;
	}
	bool isUpper() const {
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (i > j)
					if (e[i*c + j] != T(0))return false;
		return true;
	}
	bool isLower() const {
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (i < j)
					if (e[i*c + j] != T(0))return false;
		return true;
	}
	bool isSymmetric() const {
		if (r == c) {
			for (int i = 0; i < r; i++)
				for (int j = i + 1; j < c; j++)
					if (e[i*c + j] != e[j*c + i])return false;
			return true;
		}
		else
			return false;
	}
	bool isHermitian() const {
		if (T != Complex)
			return isSymmetric();
		else {
			if (r == c) {
				for (int i = 0; i < r; i++)
					for (int j = i + 1; j < c; j++)
						if (e[i*c + j] != conj(e[j*c + i]))return false;
				return true;
			}
			else
				return false;
		}
	}
	bool isVector() const {
		return (r == 1 || c == 1);
	}
	bool isSingle() const {
		int ran = rank();
		return (ran != r && ran != c);
	}
	bool isPositiveDefinite() const {
		if (r != c)return false;
		Matrix<T> U, Sigma, V_T;
		svd((*this), U, Sigma, V_T);
		int diag_pos = 0;
		if (r <= c)
			for (int i = 0; i < r; i++) {
				if (Sigma.ele_ind(diag_pos) <= 0) return false;
				diag_pos += (c + 1);
			}
		else
			for (int j = 0; j < c; j++) {
				if (Sigma.ele_ind(diag_pos) <= 0) return false;
				diag_pos += (c + 1);
			}
		return true;
	}
	bool isSemiPositiveDefinite() const {
		if (r != c)return false;
		Matrix<T> U, Sigma, V_T;
		svd((*this), U, Sigma, V_T);
		int diag_pos = 0;
		if (r <= c)
			for (int i = 0; i < r; i++) {
				if (Sigma.ele_ind(diag_pos) < 0) return false;
				diag_pos += (c + 1);
			}
		else
			for (int j = 0; j < c; j++) {
				if (Sigma.ele_ind(diag_pos) < 0) return false;
				diag_pos += (c + 1);
			}
		return true;
	}

	//set function(change the matrix)
	void set_r(int row) {
		r = row;
	}
	void set_c(int column) {
		c = column;
	}
	void set_size(int row, int column) {
		change_size(row, column);
	}
	void set_e(int pos, T element) {
		e[pos - 1] = element;
	}
	void set_e(int row, int column, T element) {
		e[(row - 1) * c + column - 1] = element;
	}
	void set_e_ind(int pos, T element) {
		e[pos] = element;
	}
	void set_e_ind(int row, int column, T element) {
		e[row * c + column] = element;
	}	
	void set_e_ind(int pos, const Matrix<T>& elements) {
		int size_all = elements.row() * elements.col();
		if (pos + size_all > r*c) {
			cout << "size error, set_e_ind failed" << endl;
			return;
		}
		for (int i = 0; i < size_all; i++)
			e[pos + i] = elements.ele_ind(i);
	}
	void set_e(const Matrix<T>& elements) {
		int count = r * c;
		for (int i = 0; i < count; i++)
			e[i] = elements.ele_ind(i);
	}
	void set_diag(const Matrix<T>& elements) {
		int diag_pos = 0;
		if (r <= c)
			for (int i = 0; i < r; i++) {
				e[diag_pos] = elements.ele_ind(i);
				diag_pos += (c + 1);
			}
		else
			for (int j = 0; j < c; j++) {
				e[diag_pos] = elements.ele_ind(j);
				diag_pos += (c + 1);
			}
	}
	void add(T element) {	// a matrix add a number
		int size_all = r * c;
		for (int i = 0; i < size_all; i++)
			e[i] = e[i] + element;
	}
	void scale(T element) {	// a number times a matrix
		int size_all = r * c;
		for (int i = 0; i < size_all; i++)
			e[i] = e[i] * element;
	}
	void add_diag(T element) {
		int diag_pos = 0;
		if (r <= c)
			for (int i = 0; i < r; i++) {
				e[diag_pos] = e[diag_pos] + element;
				diag_pos += (c + 1);
			}
		else
			for (int j = 0; j < c; j++) {
				e[diag_pos] = e[diag_pos] + element;
				diag_pos += (c + 1);
			}
	}
	void scale_diag(T element) {
		int diag_pos = 0;
		if (r <= c)
			for (int i = 0; i < r; i++) {
				e[diag_pos] = e[diag_pos] * element;
				diag_pos += (c + 1);
			}
		else
			for (int j = 0; j < c; j++) {
				e[diag_pos] = e[diag_pos] * element;
				diag_pos += (c + 1);
			}
	}
	void switch_ele(int position_1, int position_2) {
		if (position_1 == position_2) return;
		position_1--;
		position_2--;
		T temp = e[position_1];
		e[position_1] = e[position_2];
		e[position_2] = temp;
	}
	void switch_ele(int row_1, int column_1, int row_2, int column_2) {
		row_1 = (row_1 - 1)* c + column_1 - 1;		// row_1 is position_1
		row_2 = (row_2 - 1)* c + column_2 - 1;		// row_2 is position_2
		T temp = e[row_1];
		e[row_1] = e[row_2];
		e[row_2] = temp;
	}
	void switch_row(int row_1, int row_2) {
		if (row_1 == row_2) return;
		T temp;
		row_1 = (row_1 - 1)*c;
		row_2 = (row_2 - 1)*c;
		for (int j = 0; j < c; j++) {
			temp = e[row_1];
			e[row_1] = e[row_2];
			e[row_2] = temp;
			row_1++;
			row_2++;
		}
	}
	void switch_col(int column_1, int column_2) {
		if (column_1 == column_2) return;
		column_1--;
		column_2--;
		T temp;
		for (int i = 0; i < r; i++) {
			temp = e[column_1];
			e[column_1] = e[column_2];
			e[column_2] = temp;
			column_1 += c;
			column_2 += c;
		}
	}
	void change_row(int row, const Matrix<T>& elements) {
		row = (row - 1)*c;
		for (int j = 0; j < c; j++)
			e[row++] = elements.ele_ind(j);
	}
	void change_col(int column, const Matrix<T>& elements) {
		column--;
		for (int i = 0; i < r; i++) {
			e[column] = elements.ele_ind(i);
			column += c;
		}
	}
	friend Matrix<T> arrange_row(const Matrix<T>& A, const Matrix<int>& permutation) {	//permutation is vector
		Matrix<T> ans(A.r,A.c);
		int row_pos;
		int row_pos2;
		for (int i = 0; i < A.r; i++) {
			row_pos = i * A.c;
			row_pos2 = (permutation.ele_ind(i) - 1) * A.c;
			for (int j = 0; j < A.c; j++)
				ans.e[row_pos + j] = A.e[row_pos2 + j];
		}
		return ans;
	}
	friend Matrix<T> arrange_col(const Matrix<T>& A, const Matrix<int>& permutation) {	//permutation is vector
		Matrix<T> ans(A.r, A.c);
		int col_pos;
		int col_pos2;
		for (int i = 0; i < A.r; i++) {
			col_pos = i;
			col_pos2 = permutation.ele_ind(i) - 1;
			for (int j = 0; j < A.c; j++) {
				ans.e[col_pos] = A.e[col_pos2];
				col_pos += A.c;
				col_pos2 += A.c;
			}				
		}
		return ans;
	}
	void append_ele(T element) {
		if (r == 1 || r == 0) {
			T *temp = e;
			e = new T[c + 1];
			for (int i = 0; i < c; i++)
				e[i] = temp[i];
			e[c] = element;
			c++;
			delete[]temp;
		}
		else if (c == 1) {
			T *temp = e;
			e = new T[r + 1];
			for (int j = 0; j < r; j++)
				e[j] = temp[j];
			e[r] = element;
			r++;
			delete[]temp;
		}
		else
			cout << "size error, append failed" << endl;
	}
	void append_row(const Matrix<T>& elements) {
		if (elements.get_col() != c) {
			cout << "size error, append failed" << endl;
			return;
		}
		T *temp = e;
		e = new T[r*c + c];
		int row_pos;
		for (int i = 0; i <= r; i++) {
			row_pos = i * c;
			if (i != r)
				for (int j = 0; j < c; j++)
					e[row_pos + j] = temp[row_pos + j];
			else
				for (int j = 0; j < c; j++)
					e[row_pos + j] = elements.ele_ind(j);
		}
		r++;
		delete[]temp;
	}
	void append_col(const Matrix<T>& elements) {
		if (elements.get_row() != r) {
			cout << "size error, append failed" << endl;
			return;
		}
		T *temp = e;
		e = new T[r*c + r];
		int row_pos;
		for (int i = 0; i < r; i++) {
			row_pos = i * c;
			for (int j = 0; j <= c; j++)
				if (j != c)
					e[row_pos + j + i] = temp[row_pos + j];
				else
					e[row_pos + j] = elements.ele_ind(i);
		}
		c++;
		delete[]temp;
	}
	void unitize() {
		int size_all = r * c;
		double sum_fabs_2 = 0;
		for (int i = 0; i < size_all; i++)
			sum_fabs_2 += fabs(e[i])*fabs(e[i]);
		if (sum_fabs_2 == 0)return;
		sum_fabs_2 = sqrt(sum_fabs_2);
		for (int i = 0; i < size_all; i++)
			e[i] = e[i] / sum_fabs_2;
	}
	void unitize_row(int row) {
		row = (row - 1)*c;
		double sum_fabs_2 = 0;
		for (int i = 0; i < c; i++)
			sum_fabs_2 += fabs(e[row + i])*fabs(e[row + i]);
		if (sum_fabs_2 == 0)return;
		for (int i = 0; i < c; i++)
			e[row + i] = e[row + i] / sum_fabs_2;
	}
	void unitize_col(int column) {
		column--;
		int temp_col = column;
		double sum_fabs_2 = 0;
		for (int j = 0; j < r; j++) {
			sum_fabs_2 += fabs(e[temp_col])*fabs(e[temp_col]);
			temp_col += c;
		}
		if (sum_fabs_2 == 0)return;
		for (int j = 0; j < r; j++) {
			e[column] = e[column] / sum_fabs_2;
			column += c;
		}
	}
	void change_size(int row, int column) {
		if (r * c == row * column) {
			r = row;
			c = column;
		}
		else
			cout << "change size fail" << endl;
	}
	void cut(int row, int column) {
		if (row < r && column < c) {
			T *temp = e;
			e = new T[row*column];
			int row_pos;
			for (int i = 0; i < row; i++) {
				row_pos = i * column;
				for (int j = 0; i < column; i++)
					e[row_pos + j] = temp[row_pos + j];
			}
			delete[] temp;
			r = row;
			c = column;
		}
		else
			cout << "cut fail" << endl;
	}
	
	void switch_ele_ind(int position_1, int position_2) {
		if (position_1 == position_2) return;
		T temp = e[position_1];
		e[position_1] = e[position_2];
		e[position_2] = temp;
	}
	void change_row_ind(int row, const Matrix<T>& elements) {
		row = row * c;
		for (int j = 0; j < c; j++)
			e[row++] = elements.ele_ind(j);
	}
	void change_col_ind(int column, const Matrix<T>& elements) {
		for (int i = 0; i < r; i++) {
			e[column] = elements.ele_ind(i);
			column += c;
		}
	}
	void switch_row_ind(int row_1, int row_2) {
		if (row_1 == row_2) return;
		T temp;
		row_1 = row_1 * c;
		row_2 = row_2 * c;
		for (int j = 0; j < c; j++) {
			temp = e[row_1];
			e[row_1] = e[row_2];
			e[row_2] = temp;
			row_1++;
			row_2++;
		}
	}
	void switch_col_ind(int column_1, int column_2) {
		if (column_1 == column_2) return;
		T temp;
		for (int i = 0; i < r; i++) {
			temp = e[column_1];
			e[column_1] = e[column_2];
			e[column_2] = temp;
			column_1 += c;
			column_2 += c;
		}
	}
	friend Matrix<T> arrange_col_ind(const Matrix<T>& A, const Matrix<int>& permutation) {	//permutation is vector
		Matrix<T> ans(A.r, A.c);
		int col_pos;
		int col_pos2;
		for (int i = 0; i < A.r; i++) {
			col_pos = i;
			col_pos2 = permutation.ele_ind(i);
			for (int j = 0; j < A.c; j++) {
				ans.e[col_pos] = A.e[col_pos2];
				col_pos += A.c;
				col_pos2 += A.c;
			}
		}
		return ans;
	}
	friend Matrix<T> arrange_row_ind(const Matrix<T>& A, const Matrix<int>& permutation) {	//permutation is vector
		Matrix<T> ans(A.r, A.c);
		int row_pos;
		int row_pos2;
		for (int i = 0; i < A.r; i++) {
			row_pos = i * A.c;
			row_pos2 = permutation.ele_ind(i) * A.c;
			for (int j = 0; j < A.c; j++)
				ans.e[row_pos + j] = A.e[row_pos2 + j];
		}
		return ans;
	}

	//input and output(\)
	void print() const {
		cout << setprecision(4);
		int row_pos;
		for (int i = 0; i < r; i++) {
			row_pos = i * c;
			for (int j = 0; j < c; j++) {
				cout << setw(14) << e[row_pos + j];
			}
			cout << endl;
		}
	}
	void print_science() const {
		int row_pos;
		for (int i = 0; i < r; i++) {
			row_pos = i * c;
			for (int j = 0; j < c; j++) {
				printf("%14.4e", e[row_pos + j]);
			}
			printf("\n");
		}
	}
	void input() {
		T *temp = e;
		T *e = new T *[1000];		//element max is 1000, can change
		delete[]temp;
		char c;
		T num;
		int column1;

		//input process
		int row1 = 0;
		int row_pos = 0;
		do {
			column1 = 0;
			while ((c = getchar()) != '\n' && c != ']')
			{
				ungetc(c, stdin);
				cin >> num;
				e[row_pos + column1] = num;
				column1++;
			}
			row_pos += column1;
			row1++;
		} while (c != ']');
		getchar();		//eliminate the enter type
		cut(row1, column1);
	}
	friend ostream& operator << (ostream& out,const Matrix<T>& A) {
		out << endl;
		out << setprecision(4);
		int row_pos;
		for (int i = 0; i < A.r; i++) {
			row_pos = i * A.c;
			for (int j = 0; j < A.c; j++) {
				out << setw(14) << A.e[row_pos + j];
			}
			out << endl;
		}
		return out;
	}
	friend istream& operator >> (istream& in, Matrix<T> A) {
		T *temp = A.e;
		A.e = new T[1000];		//element max is 1000, can change
		delete[]temp;
		char c;
		T num;
		int column1;

		//input process
		int row1 = 0;
		int row_pos = 0;
		do {
			column1 = 0;
			while ((c = getchar()) != '\n' && c != ']')
			{
				ungetc(c, stdin);
				in >> num;
				A.e[row_pos + column1] = num;
				column1++;
			}
			row_pos += column1;
			row1++;
		} while (c != ']');
		getchar();		//eliminate the enter type
		A.cut(row1, column1);
		return in;
	}
	void print_file(string file_name,int mode=ios::out) const {	//ios::app [append]. ios::binary [in binary form]

		//if file type is "dat", write in binary.
		string f_type = file_type(file_name);
		if (f_type == "dat")	mode = ios::binary;	/**/

		ofstream fout;
		fout.open(file_name, mode);
		int row_pos;

		if (mode == ios::binary) {
			fout << r << ' ' << c << endl;
			int size_all = r * c;
			if (type(e[0]) == 'C')
				for (int i = 0; i < size_all; i++) {
					fout << get_x(e[i]) << ' ' << get_y(e[i])<<' ';
				}

			else
				for (int i = 0; i < size_all; i++)
					fout << e[i] << ' ';
			fout.close();
		}
		else {
			fout << r << ' ' << c << endl;
			fout << setprecision(4);
			for (int i = 0; i < r; i++) {
				row_pos = i * c;
				for (int j = 0; j < c; j++) {
					fout << setw(14) << e[row_pos + j];
				}
				fout << endl;
			}
			fout.close();
		}
	}
	void print_file_science(const char* file_name,const char* mode="w") const {	//"a" [append to the file].
		FILE *fp = fopen(file_name, mode);
		
		int row_pos;
		fprintf(fp, "%d %d\n", r, c);
		for (int i = 0; i < r; i++) {
			row_pos = i * c;
			for (int j = 0; j < c; j++) {
				fprintf(fp, "%14.4e", e[row_pos + j]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	void read_file(string file_name, int mode = ios::binary) { // ios::in [in text form] (can be transformed)
		
		//if file type is "txt"; read in letter.
		string f_type = file_type(file_name);
		if (f_type == "txt")	mode = ios::in;	/**/

		ifstream fin;
		fin.open(file_name);
		if (!fin.is_open()) {
			cout << "can't open file: " << file_name << endl;
			return;
		}

		clear();
		fin >> r >> c;
		int size_all = r * c;
		e = new T[size_all];
		for (int i = 0; i < size_all; i++)
			fin >> e[i];			
	}

	//compute functions(return a new matrix if can)
	T norm_1() const {
		if (isVector()) {
			int size_all = r * c;
			T sum_fabs = T(0);
			for (int i = 0; i < size_all; i++)
				sum_fabs = sum_fabs + fabs(e[i]);
			return sum_fabs;
		}
		else {
			T ans = T(0);
			T sum;
			int col_pos;
			for (int j = 0; j < c; j++) {
				sum = T(0);
				col_pos = j;
				for (int i = 0; i < r; i++) {
					sum = sum + fabs(e[col_pos]);
					col_pos += c;
				}
				if (sum > ans)
					ans = sum;
			}
			return ans;
		}		
	}
	T norm_2() const {
		if (isVector()) {
			int size_all = r * c;
			T sum_fabs_2 = T(0);
			for (int i = 0; i < size_all; i++)
				sum_fabs_2 = sum_fabs_2 + fabs(e[i])*fabs(e[i]);
			return sqrt(sum_fabs_2);
		}
		else {
			Matrix<T> U, Sigma, V_T;
			svd((*this), U, Sigma, V_T);
			return fabs(Sigma.ele_ind(0));
		}
	}
	T norm_infinity() const {
		if (isVector())
			return max_ele();
		else {
			T ans = T(0);
			T sum;
			int row_pos;
			for (int i = 0; i < r; i++) {
				sum = T(0);
				row_pos = i * c;
				for (int j = 0; j < c; j++)
					sum = sum + fabs(e[row_pos + j]);
				if (sum > ans)
					ans = sum;
			}
			return ans;
		}
	}
	T det() const {
		if (isSquared()) {
			Matrix<int> P;
			Matrix<T> L, U;
			bool sign=LU((*this), P, L, U);
			int diag_pos = 0;
			T ans = T(1);
			for (int i = 0; i < r; i++) {
				ans = ans * U.ele_ind(diag_pos);
				diag_pos += (c + 1);
			}
			return (sign ? -ans : ans);
		}
		else {
			cout << "size error, [det] failed" << endl;
			return T(0);
		}
	}
	int rank() const {
		int ans = 0;
		Matrix<T> Q, R;
		QR((*this), Q, R);
		int diag_pos = 0;
		for (int i = 0; i < c; i++) {
			if (R.ele_ind(diag_pos) > 1e-12)ans++;
			diag_pos += (c + 1);
		}
		return ans;
	}
	T condition_num() const {
		if (r==c) {
			Matrix<T> lambda = eig_val((*this));
			return fabs(lambda.ele_ind(0) / lambda.ele_ind(r-1));
		}
		else {
			Matrix<T> U, Sigma, V_T;
			svd((*this), U, Sigma, V_T);
			return fabs(Sigma.ele_ind(0) / Sigma.ele_ind(((r > c) ? ((c - 1)*c + c - 1) : ((r - 1)*c + r - 1))));
		}
	}
	friend Matrix<T> operator + (const Matrix<T>& A, const Matrix<T>& B) {
		if (A.r == B.r && A.c == B.c) {
			Matrix<T> ans(A.r, A.c);
			for (int i = 0; i < A.r* A.c; i++)
				ans.e[i] = A.e[i] + B.e[i];
			return ans;
		}
		else {
			cout << "size error, add failed" << endl;
			return Matrix<T>();
		}
	}
	friend Matrix<T> operator + (T num, const Matrix<T>& A) {
		Matrix<T> ans(A.r, A.c);
		for (int i = 0; i < A.r* A.c; i++)
			ans.e[i] = A.e[i] + num;
		return ans;
	}
	friend Matrix<T> operator + (const Matrix<T>& A, T num) {
		return num + A;
	}
	friend Matrix<T> operator - (const Matrix<T>& A, const Matrix<T>& B) {
		if (A.r == B.r && A.c == B.c) {
			Matrix<T> ans(A.r, A.c);
			for (int i = 0; i < A.r* A.c; i++)
				ans.e[i] = A.e[i] - B.e[i];
			return ans;
		}
		else {
			cout << "size error, minus failed" << endl;
			return Matrix<T>();
		}
	}
	friend Matrix<T> operator - (T num, const Matrix<T>& A) {
		Matrix<T> ans(A.r, A.c);
		for (int i = 0; i < A.r* A.c; i++)
			ans.e[i] = num - A.e[i];
		return ans;
	}
	friend Matrix<T> operator - (const Matrix<T>& A, T num) {
		return -num + A;
	}
	friend Matrix<T> operator * (const Matrix<T>& A, const Matrix<T>& B) {
		if (A.c == B.r) {
			Matrix<T> ans(A.r, B.c);
			int row_pos;
			int row_pos2;
			int temp_j;
			for (int i = 0; i < A.r; i++) {
				row_pos2 = i * A.c;
				row_pos = i * B.c;
				for (int j = 0; j < B.c; j++) {
					ans.e[row_pos + j] = T(0);
					temp_j = j;
					for (int t = 0; t < A.c; t++) {
						ans.e[row_pos + j] = ans.e[row_pos + j] + A.e[row_pos2 + t] * B.e[temp_j];
						temp_j += B.c;
					}
				}
			}
			return ans;
		}
		else {
			cout << "size error, multiply failed" << endl;
			return Matrix<T>();
		}
	}
	friend Matrix<T> operator * (T num, const Matrix<T>& A) {
		Matrix<T> ans(A.r, A.c);
		for (int i = 0; i < A.r* A.c; i++)
			ans.e[i] = A.e[i] * num;
		return ans;
	}
	friend Matrix<T> operator * (const Matrix<T>& A, T num) {
		return num * A;
	}
	friend T dot_product(const Matrix<T>& A, const Matrix<T>& B) {
		int size_all = A.r * A.c;
		T ans = T(0);
		if (size_all == B.r * B.c) {
			for (int i = 0; i < size_all; i++)
				ans = ans + conj(A.e[i]) * B.e[i];
			return ans;
		}
		else {
			cout << "size error, dot_product failed" << endl;
			return ans;
		}
	}
	friend Matrix<T> dot_time(const Matrix<T>& A, const Matrix<T>& B) {
		int size_all = A.r * A.c;
		if (size_all == B.r * B.c) {
			Matrix<T> ans(A.r, A.c);
			for (int i = 0; i < size_all; i++)
				ans.e[i] = A.e[i] * B.e[i];
			return ans;
		}
		else {
			cout << "size error, dot_time failed" << endl;
			return Matrix<T>();
		}
	}
	friend int diff_num(const Matrix<T>& A, const Matrix<T>& B) {
		//the function return the number of different elements of the 2 matrices
		int size_all = A.r * A.c;
		if (size_all == B.r * B.c) {
			int ans = 0;
			for (int i = 0; i < size_all; i++)
				if (A.e[i] != B.e[i])
					ans++;
			return ans;
		}
		else {
			cout << "size error, [diff_num] failed" << endl;
			return 0;
		}
	}

	friend Matrix<T> L_inv(const Matrix<T>& L) {
		if (L.r == L.c) {
			Matrix<T> D(1, L.r, '1');	//diagonal
			int row_pos;
			for (int i = 0; i < L.r; i++) {
				row_pos = i * L.c;
				if (L.e[row_pos + i] == T(1))continue;
				D.e[i] = 1 / L.e[row_pos + i];
				for (int j = 0; j <= i; j++)
					L.e[row_pos + j] = L.e[row_pos + j] * D.e[i];	//row scaling
			}

			Matrix<T> ans(L.r, L.c, 'i');
			int col_pos;
			for (int i = 1; i < L.r; i++)
				for (int t = 0; t < L.r - i; t++) {
					// operation on ans.e[(t+i) * L.c+t]
					row_pos = (t + i) * L.c + t;
					col_pos = t * L.c + t;
					T sum = T(0);
					for (int j = 1; j < i; j++) {
						col_pos += L.c;
						sum = sum + L.e[row_pos + j] * ans.e[col_pos];
					}
					
					ans.e[row_pos] = -L.e[row_pos] - sum;
				}

			//column scaling back
			for (int z = 0; z < L.r; z++) {
				if (D.e[z] == T(1))continue;
				col_pos = z * L.c + z;
				for (int k = z; k < L.c; k++) {
					ans.e[col_pos] = ans.e[col_pos] * D.e[z];
					col_pos += L.c;
				}
			}
			return ans;
		}
		else {
			cout << "size error, L_inv failed" << endl;
			return Matrix<T>();
		}

	}
	friend Matrix<T> U_inv(const Matrix<T>& U) {
		Matrix<T> ans;
		ans =transpose(U);	//U^T
		ans = L_inv(ans);	//(U^T)^(-1)
		return transpose(ans);	//(U^T)^(-1)^T
	}
	friend bool LU(const Matrix<T>& A, Matrix<int>& P, Matrix<T>& L, Matrix<T>& U) {	//return if the times of permutation is odd
		if (A.r == A.c) {
			P = Matrix<int>(1, A.r, 'N');
			L = Matrix<T>(A.r, A.c, 'i');
			U = A;
			int permute;
			int col_pos;
			int col_pos2;
			bool ans = false;
			T temp;
			for (int i = 0; i < A.c; i++) {
				temp = U.max_col_ele_start_from_ind(i, i, permute);
				if (temp == T(0)) {
					cout << "warning: singular" << endl;
					continue;
				}
				P.switch_ele_ind(i, permute);
				U.switch_row_ind(i, permute);
				if (i != permute)ans = !ans;
				//arrange L
				col_pos = i * U.c;
				for (int t = 0; t < i; t++) {
					L.switch_ele_ind(col_pos + t, permute * U.c + t);
				}
				col_pos = col_pos + i;
				col_pos2 = col_pos;
				for (int j = i + 1; j < U.r; j++) {
					col_pos2 += U.c;
					temp = U.e[col_pos2] / U.e[col_pos];
					L.e[col_pos2] = temp;
					U.change_row_ind(j, U.get_row_ind(j) + U.get_row_ind(i) * (-temp));				
				}
			}
			return ans;
		}
		else {
			cout << "size error, LU failed" << endl;
			return false;
		}
	}
	friend Matrix<T> inv(const Matrix<T>& A) {
		Matrix<int> P;
		Matrix<T> L, U, ans;
		LU(A, P, L, U);
		ans = U_inv(U) * L_inv(L);

		//changing P to column arrange number
		Matrix<int> P_copy(P);
		for (int i = 0; i < P.col(); i++) {
			P.set_e_ind(P_copy.ele_ind(i), i);
		}

		return arrange_col_ind(ans, P);
	}

	friend Matrix<T> operator / (const Matrix<T>& A, const Matrix<T>& B) {
		return A * inv(B);
	}
	friend Matrix<T> operator / (double num, const Matrix<T>& A) {
		return num * inv(A);
	}
	friend Matrix<T> operator / (const Matrix<T>& A, double num) {
		return 1 / num * A;
	}
	friend Matrix<T> operator - (const Matrix<T>& A) {
		return -1 * A;
	}
	friend bool operator == (const Matrix<T>& A, const Matrix<T>& B) {
		if (A.r == B.r && A.c == B.c) {
			int size_all = A.r * A.c;
			for (int i = 0; i < size_all; i++)
				if (A.e[i] != B.e[i])
					return false;
			return true;
		}
		else
			return false;
	}
	friend bool operator != (const Matrix<T>& A, const Matrix<T>& B) {
		return !(A == B);
	}

	friend void QR(const Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R) {
		Q = A;
		R = Matrix<T>(A.c, A.c, '0');
		int row_pos;
		for (int i = 0; i < A.c; i++) {
			row_pos = i * R.c;
			Matrix<T> temp0 = Q.get_col_ind(i);
			R.e[row_pos + i] = temp0.norm_2();	//get R[i][i]

			temp0.scale(1 / R.e[row_pos + i]);
			Q.change_col_ind(i, temp0);
			for (int l = i + 1; l < A.c; l++) {
				Matrix<T> temp3 = Q.get_col_ind(i);	//q[i]
				Matrix<T> temp4 = Q.get_col_ind(l);	//q[l]
				R.e[row_pos + l] = dot_product(temp3, temp4);	//R[i][l]=q[i]^T*q[l]

				temp3.scale(R.e[row_pos + l]);
				temp4 = temp4 - temp3;
				Q.change_col_ind(l, temp4);	//q[l]=q[l]-R[i][l] * q[i]
			}
		}
	}
	friend Matrix<T> eig_val(Matrix<T> A, int iteration=15) {
		// perform QR iteration
		if (A.r == A.c) {
			T shift;
			Matrix<T> Q, R;
			for (int i = 0; i < iteration; i++) {
				shift = A.e[A.r*A.c - 1] + T(0.01);
				A.add_diag(-shift);
				QR(A, Q, R);
				A = R * Q;
				A.add_diag(shift);
			}
			Matrix<T> ans = A.get_diag();

			// arrange the eigen_Values
			int pos;
			for (int j = 0; j < A.r; j++) {
				ans.max_ele_start_from_ind(j, pos);
				ans.switch_ele_ind(j, pos);
			}
			return ans;
		}
		else {
			cout << "size error, get eigen_val failed" << endl;
			return Matrix<T>();
		}

		
	}
	friend void eig_shift_inv(Matrix<T> A, T shift, T& eigen_value, Matrix<T>& eigen_Vector,int iter=50) {
		//the function perform shift inverse iteration to find the eigenvalue and eigenvector
		
		if (A.r == A.c) {
			A.add_diag(-shift);

			A = inv(A);	//inverse of A
			eigen_Vector = Matrix<T>(A.r, 1, 'u');	//initial starting eigen vetor
			for (int i = 0; i < iter; i++) {
				eigen_Vector = A * eigen_Vector;
				eigen_Vector.scale(1 / eigen_Vector.max_ele());	//set vector max element to 1
			}
			
			//compute the eigen_value
			A = A * eigen_Vector;
			eigen_value = dot_product(eigen_Vector, eigen_Vector) / dot_product(eigen_Vector, A) + shift;
		}
		else
			cout << "size error, [eig_shift_inv] failed" << endl;
	}
	friend void eig(const Matrix<T>& A, Matrix<T>& eigen_Values, Matrix<T>& eigen_Vectors) {
		//the output eigenvectors are listed by column.

		if (A.r == A.c) {
			eigen_Values = eig_val(A, 5);
			eigen_Vectors = Matrix<T>(A.r, A.c);
			Matrix<T> temp;
			for (int i = 0; i < A.r; i++) {
				eig_shift_inv(A, eigen_Values.e[i] + 0.01, eigen_Values.e[i], temp, 10);
				temp.unitize();
				eigen_Vectors.change_col_ind(i, temp);
			}
		}
		else
			cout << "size error, [eig] failed" << endl;
	}
	friend void svd(const Matrix<T>& A, Matrix<T>& U, Matrix<T>& Sigma, Matrix<T>& V_T) {
		if (A.r == A.c) {
			Matrix<T> eig_Vals;
			Sigma = Matrix(A.r, A.c, '0');
			eig(A, eig_Vals, U);
			Sigma.set_diag(eig_Vals);
			if (A.isSymmetric())
				V_T = transpose(U);
			else
				V_T = inv(U);
		}
		else {
			Matrix<T> AT_A = Hermit(A);	//AT now
			Matrix<T> A_AT = A * AT_A;
			AT_A = AT_A * A;	//AT_A now

			Matrix<T> Sigma1;
			eig(A_AT, Sigma1, U);

			Matrix<T> Sigma2;
			eig(AT_A, Sigma2, V_T);

			Sigma = Matrix(A.r, A.c, '0');

			//computing Sigma
			int row_pos;
			for (int i = 0; i < A.r; i++) {
				row_pos = i * A.c;
				for (int j = 0; j < A.c; j++) {
					if (i == j) {
						Sigma.e[row_pos + j] = dot_product(A.get_row_ind(0), V_T.get_col_ind(i)) / U.e[i];
					}
				}
			}
			V_T = Hermit(V_T);
		}
	}
	//failed to find the complex eigenvalues. (eig_val, eig_shift_inv, eig, svd)

	//extend functions (return a new matrix)
	friend Matrix<T> transpose(const Matrix<T>& A) {
		Matrix<T> ans(A.c, A.r);
		int row_pos;
		int col_pos;
		for (int i = 0; i < A.r; i++) {
			row_pos = i * A.c;
			col_pos = i;
			for (int j = 0; j < A.c; j++) {
				ans.e[col_pos] = A.e[row_pos + j];
				col_pos += ans.c;
			}
		}
		return ans;
	}
	friend Matrix<T> Hermit(const Matrix<T>& A) {
		if (type(A.e[0]) == 'C') {
			Matrix<T> ans(A.c, A.r);
			int row_pos;
			int col_pos;
				for (int i = 0; i < A.r; i++) {
					row_pos = i * A.c;
					col_pos = i;
					for (int j = 0; j < A.c; j++) {
						ans.e[col_pos] = ((i == j) ? A.e[row_pos + j] : conj(A.e[row_pos + j]));
						col_pos += ans.c;
					}
				}
			return ans;
		}
		else
			return transpose(A);
	}
	friend Matrix<T> extend_block(const Matrix<T>& A, const Matrix<T>& B) {
		int row_all = A.r + B.r;
		int column_all = A.c + B.c;
		int row_pos;
		Matrix<T> ans(row_all, column_all);
		for (int i = 0; i < row_all; i++) {
			row_pos = i * column_all;
			for (int j = 0; j < column_all; j++) {
				if (i < A.r && j < A.c)
					ans.e[row_pos + j] = A.e[i * A.c + j];
				else if (i >= A.r && j >= A.c)
					ans.e[row_pos + j] = B.e[(i - A.r) * B.c + j - A.c];
				else
					ans.e[row_pos + j] = T(0);
			}
		}
		return ans;
	}
	friend Matrix<T> combine(const Matrix<T>& A, const Matrix<T>& B, const Matrix<T>& C, const Matrix<T>& D) {
		if (A.r == B.r && A.c == C.c && B.c == D.c && C.r == D.r) {
			int row_all = A.r + C.r;
			int column_all = A.c + B.c;
			int row_pos;
			Matrix<T> ans(row_all, column_all);
			for (int i = 0; i < row_all; i++) {
				row_pos = i * column_all;
				for (int j = 0; j < column_all; j++) {
					if (i < A.r && j < A.c)
						ans.e[row_pos + j] = A.e[i * A.c + j];
					else if (i < A.r && j >= A.c)
						ans.e[row_pos + j] = B.e[i * B.c + j - A.c];
					else if (i >= A.r && j < A.c)
						ans.e[row_pos + j] = C.e[(i - A.r) * C.c + j];
					else if (i >= A.r && j >= A.c)
						ans.e[row_pos + j] = D.e[(i - A.r) * D.c + j - A.c];
				}
			}
			return ans;
		}
		else {
			cout << "size error, combine failed" << endl;
			return Matrix<T>();
		}		
	}
	friend Matrix<T> extend_row_copy(const Matrix<T>& A, int number_of_copies) {
		//return a matrix with a number of copied rows.
		if (number_of_copies == 1)return A;
		int size_all = A.r * A.c;
		int col_pos = 0;
		Matrix<T> ans(number_of_copies, size_all);
		for (int i = 0; i < number_of_copies; i++) {
			ans.set_e_ind(col_pos, A);
			col_pos += size_all;
		}
		return ans;
	}
	friend Matrix<T> ReLu(const Matrix<T>& A,T shift=0) {
		//return a matrix after ReLu function.
		int size_all = A.r * A.c;
		Matrix<T> ans(A.r, A.c);
		for (int i = 0; i < size_all; i++)
			ans.e[i] = (A.e[i] > shift ? A.e[i] : 0);
		return ans;
	}
};

enum Error_code { success, underflow, overflow, outOfRange };
const int max_tensor = 10;

template <class T> class Tensor
{
public:
	// methods of the Tensor ADT 
	Tensor() {	//constructor
		count = 0;
	};
	Tensor(Matrix<T> *val, int size) {
		count = size;
		for (int i = 0; i < count; i++)
			entry[i] = val[i];
	}
	Tensor(const Tensor<T>& X) {
		count = X.count;
		for (int i = 0; i < count; i++)
			entry[i] = X.entry[i];
	}
	Tensor<T> operator = (const Tensor<T>& X) {
		count = X.count;
		for (int i = 0; i < count; i++)
			entry[i] = X.entry[i];
		return X;
	}
	int size() const {
		return count;
	}
	bool full() const {
		return count == max_tensor;
	}
	bool empty() const {
		return count == 0;
	}
	void clear() {
		count = 0;
	}
	void traverse(void(*visit)(Matrix<T>& A)) {
		for (int i = 0; i < count; i++)
		{
			(*visit)(entry[i]);
		}
	}
	Error_code retrieve(int position, Matrix<T>& A) const {
		if (count == 0) return underflow;
		if (position<1 || position>count) return outOfRange;
		A = entry[position - 1];
		return success;
	}
	Error_code replace(int position, const Matrix<T>& A) {
		if (count == 0) return underflow;
		if (position<1 || position>count) return outOfRange;
		entry[position - 1] = A;
		return success;
	}
	Error_code remove(int position, Matrix<T>& A) {
		if (count == 0) return underflow;
		if (position<1 || position>count) return outOfRange;
		A = entry[position - 1];
		for (int j = position - 1; j < count - 1; j++)
		{
			entry[j] = entry[j + 1];
		}
		count--;
		return success;
	}
	Error_code insert(int position, const Matrix<T>& A) {
		if (count == max_tensor) return overflow;
		if (position<1 || position>count + 1) return outOfRange;
		for (int j = count - 1; j >= position - 1; j--)
		{
			entry[j + 1] = entry[j];
		}
		count++;
		entry[position - 1] = A;
		return success;
	}
	Error_code append(const Matrix<T>& A) {
		if (count == max_tensor) return overflow;
		entry[count] = A;
		count++;
		return success;
	}
	Matrix<T> get_entry_ind(int position) const {
		if (count == 0 || position < 0 || position >= count) {
			cout << "size or position error, get_entry_ind failed" << endl;
			return Matrix<T>();
		}		
		return entry[position];
	}
	void print() const {
		cout << endl << endl << "//" << endl;
		cout << setprecision(4);
		int row_pos;
		for (int k = 0; k < count; k++) {
			for (int i = 0; i < entry[k].row(); i++) {
				row_pos = i * entry[k].col();
				for (int j = 0; j < entry[k].col(); j++) {
					cout << setw(14) << entry[k].ele_ind(row_pos + j);
				}
				cout << endl;
			}
			cout << "//" << endl;
		}
		cout << endl;
	}
	friend ostream& operator << (ostream& out,const Tensor<T>& X) {
		out << endl << endl << "//" << endl;
		out << setprecision(4);
		int row_pos;
		for (int k = 0; k < X.count; k++) {
			for (int i = 0; i < X.entry[k].row(); i++) {
				row_pos = i *X. entry[k].col();
				for (int j = 0; j < X.entry[k].col(); j++) {
					out <<  setw(14) << X.entry[k].ele_ind(row_pos + j);
				}
				out << endl;
			}
			out << "//" << endl;
		}
		out << endl;
		return out;
	}
protected:
	// data members for a contiguous list implementation 
	int count;
	Matrix<T> entry[max_tensor];
};

template <class T> class net
{
protected:
	Tensor<T> weight;
	Tensor<T> bias;
	Matrix<T> input;
	Matrix<T> desired_output;
public:
	net() {}
	net(int *shape, int shape_size, char type = 'g') {
		for (int i = 1; i < shape_size; i++) {
			weight.append(Matrix<T>(shape[i - 1], shape[i], type));
			bias.append(Matrix<T>(1, shape[i], type));
		}
	}
	net(const net<T>& N) {
		weight = N.weight;
		bias = N.bias;
	}
	net operator = (const net<T>& N) {
		weight = N.weight;
		bias = N.bias;
		return N;
	}
	~net() {}

	void set_input(const Matrix<T>& Input) {
		input = Input;
	}
	void set_desired_output(const Matrix<T>& desired_Output) {
		desired_output = desired_Output;
	}
	void set_put(const Matrix<T>& Input, const Matrix<T>& desired_Output) {
		input = Input;
		desired_output = desired_Output;
	}
	Matrix<T> forward_propagation() const {
		int shape_size = weight.size();
		Tensor<T> biases;
		for(int i=0;i<bias.size();i++)
			biases.append(extend_row_copy(bias.get_entry_ind(i), input.row()));
		Matrix<T> ans(input);
		for (int i = 0; i < shape_size; i++)
			ans = ReLu(ans * weight.get_entry_ind(i) + biases.get_entry_ind(i)); // use ReLu
		return ans;
	}
	Matrix<T> cost_fun() const {
		//waiting for
		return Matrix<T>();
	}
	void backward_propagation(Tensor<T>& d_weight, Tensor<T>& d_bias) {
		//waiting for

	}

	void print() const {
		cout << endl << setw(28) << "<------" << endl;
		cout << "weight =" << weight;
		cout << "bias =" << bias;
		cout << setw(28) << "------>" << endl;
	}
	friend ostream& operator << (ostream& out, const net<T>& N) {
		out << endl << setw(28) << "<------" << endl;
		out << "weight =" << N.weight;
		out << "bias =" << N.bias;
		out << setw(28) << "------>" << endl;
		return out;
	}
};
