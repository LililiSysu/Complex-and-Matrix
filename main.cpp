#include"matrix_head.h"
using namespace std;

#define Type double

int main_complex/**/()
{
	//testing complex.
	Complex c0(9, 6);
	Complex c1(1, 0);
	Complex c2(4, -4);
	cout << c2 + c0 + c1 << endl;
	cout << Complex(4, 2) << endl;
	cout << type(Complex(4, 3)) << endl;

	cout << conj(c0) << endl;
	cout << rotate(c1, pi / 4) << endl;

	cout << 1 / c2 << endl;
	cout << inverse(c2) << endl;

	Complex c3 = sqrt(c2);
	cout << c3 << endl;
	cout << pow(c3, 2) << endl;

	Complex c4 = exp(c2);
	cout << c4 << endl;
	cout << log(c4) << endl;
	cout << log(c4) - 2 * pi*J << endl;

	cout << pow(J, 4) << endl;
	cout << pow(4, J) << endl;
	cout << pow(J, J) << endl;

	cout << log(5, J) << endl;
	cout << log(J, 5) << endl;
	cout << log(J, J) << endl;

	cout << J << endl;
	cout << -J << endl;

	cout << "__________________" << endl;
	cout << sin(J) << endl;
	cout << cos(J) << endl;
	cout << tan(J) << endl;
	cout << cot(J) << endl;
	cout << sec(J) << endl;
	cout << asin(J) << endl;
	cout << acos(J) << endl;
	cout << atan(J + 1) << endl;

	cout << "__________________" << endl << endl;
	cout << "c0=" << c0 << endl;
	cout << "c1=" << c1 << endl;
	cout << "c2=" << c2 << endl;
	cout << "c3=" << c3 << endl << endl;

	c3 = c2;
	c2 = c2 + 1 + c4;
	c1 = Complex(4, 2);
	Complex c5(c0);

	cout << "c1=" << c1 << endl;
	cout << "c2=" << c2 << endl;
	cout << "c3=" << c3 << endl;
	cout << "c5=" << c0 << endl << endl;

	c1 = c2 = c3 = c5;
	cout << "c1=" << c1 << endl;
	cout << "c2=" << c2 << endl;
	cout << "c3=" << c3 << endl;
	cout << "c5=" << c0 << endl;

	printf("c1=%14.4e", c1); printf("\n");

	end(); return 0;
}

int main_matrix/**/()
{
	//testing Matrix
	Type val[] = {
		3,4,3,
		4,6,2,
		3,2,10
	};

	//check inv, isSymmetric, isPositiveDefinite
	Matrix<Type> A(3, 3, val);
	cout << "A=" << A;
	cout << "inv(A)=" << inv(A);
	cout << "A * inv(A)=" << A * inv(A);
	cout << "A.isSymmetric()=" << A.isSymmetric() << endl;
	cout << "A.isPositiveDefinite()=" << A.isPositiveDefinite() << endl;
	cout << "eig_val(A)="<<eig_val(A);
	cout << "A.condition_num()=" << A.condition_num() << endl;

	//check QR
	Matrix<Type> Q, R;
	QR(A, Q, R);
	cout << "Q=" << Q;
	cout << "R=" << R;
	cout << "QR=" <<Q*R;
	cout << "inv(Q)=" << inv(Q);
	cout << "Q * inv(Q)=" << Q * inv(Q);

	//check eigen_val
	Matrix<Type> eig_Vals = eig_val(A);
	cout << "eig_Vals=" << eig_Vals;
	//check eig
	Matrix<Type> eig_Vecs;
	eig(A, eig_Vals, eig_Vecs);
	cout << "eig_Vals=" << eig_Vals;
	cout << "eig_Vecs=" << eig_Vecs;

	//check svd
	Type val2[] = {
		3,10,6,
		5,1,6
	};
	Matrix<Type> B(2, 3, val2);
	cout << "B=" << B;
	Matrix<Type> U, Sigma, V_T;
	svd(B, U, Sigma, V_T);
	cout << "U=" << U;
	cout << "Sigma=" << Sigma;
	cout << "V_T=" << V_T;
	cout << "U_Sigma_VT=" << U * Sigma * V_T;
	cout << "B.condition_num()=" << B.condition_num() << endl;

	//check norm_1, norm_2, norm_infinity, det, rank, single
	cout << "B.norm_1()= " << B.norm_1() << endl;
	cout << "B.norm_2()= " << B.norm_2() << endl;
	cout << "B.norm_infinity()= " << B.norm_infinity() << endl;
	cout << "A.det()= " << A.det() << endl;
	cout << "B.rank()=" << B.rank() << endl;
	cout << "A.rank()=" << A.rank() << endl;

	Type val3[] = {
		3,10,6,
		9,30,18
	};
	Matrix<Type> C(2, 3, val3);
	cout << "C.rank()=" << C.rank() << endl;
	cout << "C.isSingle()=" << C.isSingle() << endl;

	//check print_file, print_file_science
	U.print_file("A.txt");
	U.print_file_science("A_s.txt");
	
	//check read file.
	cout << endl << "_______check read file._______" << endl << endl;
	Matrix<double> U2(2, 2, 'u');
	U2.print_file("U.txt");
	U2.print_file("U.dat");	// default:write in letter; if file type is "dat", write in binary.
	Matrix<double> U2_read;
	U2_read.read_file("U.dat"); // default:read in binary; if file type is "txt", read in letter.
	cout << "U2" << U2;
	cout << "U2_read" << U2_read;
	cout << "(U2==U2_read) = " << (U2 == U2_read) << endl;
	cout << "U2 - U2_read" << U2 - U2_read;
	
	//check extend block
	Matrix<Type> M = A * A;
	cout << "A=" << A;
	cout << "M=" << M;
	cout << "A-M=" << extend_block(A, M);
	end(); return 0;
}

int main_image/**/()
{
	string file_name = "white.bmp";
	ifstream fin;
	fin.open(file_name, ios::binary);
	if (!fin.is_open()) {
		cout << "can't open file: " << file_name << endl;
	}
	
	unsigned char c;
	int i = 0;
	while (!fin.eof()) {
		fin >> c;
		cout << int(c) << '\t';
		i++;
	}
	cout << i << endl;

	end(); return 0;
}

int main_tensor/**/()
{
	const int size = 6;
	Matrix<Type> val[] = {
		Matrix<Type>(3, 3, 'i'),Matrix<Type>(3, 6, 'g'),Matrix<Type>(6, 3, 'N'),
		Matrix<Type>(2, 3, '0'),Matrix<Type>(2, 1, '1'),Matrix<Type>(1, 3, 'U')
	};
	Tensor<Type> tensor(val, size);
	cout << "tensor =" << tensor;

	end(); return 0;
}

int main/*_net/**/()
{
	const int shape_size = 4;
	int _shape[] = {
		3,4,3,4
	};
	net<Type> N(Matrix<int>(1,shape_size,_shape));

	cout << "shape" << N.get_shape();
	cout << "N:" << N;

	N.set_input(Matrix<Type>(2, 3, 'u'));
	N.set_desired_output(Matrix<int>(2, 1, 'N'));
	cout << "N.get_desired_output()=" << N.get_desired_output();
	N.set_hypara(0.02, 0.002, 0.01);

	N.forward_prop();
	cout << "N.get_midput()" << N.get_midput();
	cout << "N.output=" << N.get_output();
	cout << "N.cost_fun()=" << N.cost_fun();

	N.backward_prop();
	N.forward_prop();
	cout << "N.get_midput()=" << N.get_midput();
	cout << "N.output=" << N.get_output();
	cout << "N.cost_fun()=" << N.cost_fun();
	

	for (int i = 0; i < 100; i++) {
		N.backward_prop();
		N.forward_prop();
		cout << "N.output=" << N.get_output();
		cout << "N.cost_fun()=" << N.cost_fun();
	}
	cout << "N.get_input()=" << N.get_input() << endl;
	cout << "N:" << N << endl;

	end(); return 0;
}

int main_test/**/()
{
	cout << rand_num_ga<double>((unsigned int)time(0)) << endl;
	cout << rand_num_ga<double>((unsigned int)time(0)) << endl;
	cout << rand_num_ga<double>((unsigned int)time(0)) << endl;
	cout << rand_num_ga<double>((unsigned int)time(0)) << endl;
	cout << rand_num_ga<double>((unsigned int)time(0)) << endl;
	cout << rand_num_ga<double>((unsigned int)time(0)) << endl;

	end(); return 0;
}
