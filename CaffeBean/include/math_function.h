//
// Created by Kaiyu Xie on 2020/2/5.
//

#ifndef CAFFEBEAN_MATH_FUNCTION_H
#define CAFFEBEAN_MATH_FUNCTION_H

#include <../../lib/Eigen/Dense>

using namespace Eigen;
using namespace std;

inline void Eigen_test() {
    Matrix3d m = Matrix3d::Random();
    m = (m + Matrix3d::Constant(1.2)) * 50;
    cout << "m =" << endl << m << endl;
    Vector3d v(1, 2, 3);
    cout << "m * v =" << endl << m * v << endl;

    float *a = new float[20];
    for (int i = 0; i < 20; ++i) {
        a[i] = i;
    }
    Map<Matrix<float, 4, 5, RowMajor> > staMat(a);
    cout << "a =\n" << staMat << endl;
    auto b = staMat.transpose();
    cout << "b =\n" << b << endl;
    auto c = staMat * b;
    cout << "c =\n" << c << endl;
    auto d = staMat.squaredNorm();
    cout << "d =\n" << d << endl;
}

#endif //CAFFEBEAN_MATH_FUNCTION_H
