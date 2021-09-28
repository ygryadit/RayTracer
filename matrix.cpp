#include "vector.h"
#include "matrix.h"
#include <cmath>

Mat3:: Mat3()
{
    A[0][0] = A[1][1] = A[2][2] = 1.0; 
    A[1][0] = A[0][1] = A[1][2] = A[2][0] = A[2][1] = A[0][2] = 0.0;
}

Mat3 Mat3::inverse() const
{
    Mat3 R;
    double det = A[0][0] * (A[1][1] * A[2][2] - A[2][1] * A[1][2])
               - A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0])
               + A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]); 
    R.A[0][0] = A[1][1] * A[2][2] - A[1][2] * A[2][1];
	R.A[0][1] = A[0][2] * A[2][1] - A[0][1] * A[2][2];
	R.A[0][2] = A[0][1] * A[1][2] - A[0][2] * A[1][1];
	R.A[1][0] = A[1][2] * A[2][0] - A[2][2] * A[1][0];
	R.A[1][1] = A[0][0] * A[2][2] - A[0][2] * A[2][0];
	R.A[1][2] = A[0][2] * A[1][0] - A[0][0] * A[1][2];
	R.A[2][0] = A[1][0] * A[2][1] - A[1][1] * A[2][0];
	R.A[2][1] = A[0][1] * A[2][0] - A[0][0] * A[2][1];
	R.A[2][2] = A[0][0] * A[1][1] - A[0][1] * A[1][0];       
    return R /= det;
}

Mat3 Mat3::rotate_x(double phi)
{
    Mat3 R;

    R.A[1][1] = cos(phi);
    R.A[1][2] = sin(phi);
    R.A[2][1] = -sin(phi);
    R.A[2][2] = cos(phi);
    return R;
}

Mat3 Mat3::rotate_y(double phi)
{
    Mat3 R;

    R.A[0][0] = cos(phi);
    R.A[2][0] = sin(phi);
    R.A[0][2] = -sin(phi);
    R.A[2][2] = cos(phi);
    return R;
}

Mat3 Mat3::rotate_z(double phi)
{
    Mat3 R;

    R.A[0][0] = cos(phi);
    R.A[0][1] = sin(phi);
    R.A[1][0] = -sin(phi);
    R.A[1][1] = cos(phi);
    return R;
}

Mat3& Mat3:: operator*= (const Mat3& B)
{
	return *this = *this * B;
}

Mat3& Mat3:: operator/= (double c)
{
    A[0][0] /= c;
	A[0][1] /= c;
	A[0][2] /= c;
	A[1][0] /= c;
	A[1][1] /= c;
	A[1][2] /= c;
	A[2][0] /= c;
	A[2][1] /= c;
	A[2][2] /= c;

    return *this; 
}

Mat3& Mat3:: operator*= (double c)
{
    A[0][0] *= c;
	A[0][1] *= c;
	A[0][2] *= c;
	A[1][0] *= c;
	A[1][1] *= c;
	A[1][2] *= c;
	A[2][0] *= c;
	A[2][1] *= c;
	A[2][2] *= c;

    return *this; 
}

Mat3 operator* (const Mat3& A, const Mat3& B)
{
    Mat3 R;

    R.A[0][0] = A.A[0][0] * B.A[0][0] + A.A[0][1] * B.A[1][0] + A.A[0][2] * B.A[2][0];
    R.A[0][1] = A.A[0][0] * B.A[0][1] + A.A[0][1] * B.A[1][1] + A.A[0][2] * B.A[2][1];
    R.A[0][2] = A.A[0][0] * B.A[0][2] + A.A[0][1] * B.A[1][2] + A.A[0][2] * B.A[2][2];
    R.A[1][0] = A.A[1][0] * B.A[0][0] + A.A[1][1] * B.A[1][0] + A.A[1][2] * B.A[2][0];
    R.A[1][1] = A.A[1][0] * B.A[0][1] + A.A[1][1] * B.A[1][1] + A.A[1][2] * B.A[2][1];
    R.A[1][2] = A.A[1][0] * B.A[0][2] + A.A[1][1] * B.A[1][2] + A.A[1][2] * B.A[2][2];
    R.A[2][0] = A.A[2][0] * B.A[0][0] + A.A[2][1] * B.A[1][0] + A.A[2][2] * B.A[2][0];
    R.A[2][1] = A.A[2][0] * B.A[0][1] + A.A[2][1] * B.A[1][1] + A.A[2][2] * B.A[2][1];
    R.A[2][2] = A.A[2][0] * B.A[0][2] + A.A[2][1] * B.A[1][2] + A.A[2][2] * B.A[2][2];

    return R;
}

Mat3 operator* (const Mat3& A, double c)
{
    Mat3 R = A;
    return R *= c;
}

Mat3 operator* (double c, const Mat3& A)
{
    Mat3 R = A;
    return R *= c;
}

Vec3 operator* (const Mat3& A, const Vec3& b)
{
    Vec3 r;
    r.x[0] = A.A[0][0] * b.x[0] + A.A[0][1] * b.x[1] + A.A[0][2] * b.x[2];
	r.x[1] = A.A[1][0] * b.x[0] + A.A[1][1] * b.x[1] + A.A[1][2] * b.x[2];
	r.x[2] = A.A[2][0] * b.x[0] + A.A[2][1] * b.x[1] + A.A[2][2] * b.x[2];
	return r;
}
