#ifndef __MATRIX__
#define __MATRIX__

class Mat3
{
public:
    double A[3][3];
    Mat3();
    Mat3&       operator*= (const Mat3& B);
    Mat3&       operator+= (const Mat3& B);
    Mat3&       operator-= (const Mat3& B);
    Mat3&       operator*= (double c);
    Mat3&       operator/= (double c);
    
    Mat3 inverse() const;
    static Mat3 rotate_x(double phi);
    static Mat3 rotate_y(double phi);
    static Mat3 rotate_z(double phi);
};


Mat3 operator* (const Mat3& A, const Mat3& B);
Mat3 operator* (const Mat3& A, double c);
Mat3 operator* (double c, const Mat3& A);
Vec3 operator* (const Mat3& A, const Vec3& b);  

#endif
