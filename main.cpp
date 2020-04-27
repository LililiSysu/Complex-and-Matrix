#include"matrix_head.h"
using namespace std;
#define Type double

int main1()
{
	//testing complex.
	Complex c0(9, 6);
	Complex c1(1, 0);
	Complex c2(4, -4);

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

int main()
{
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

	end(); return 0;
}