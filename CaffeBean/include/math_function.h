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
}

#endif //CAFFEBEAN_MATH_FUNCTION_H
