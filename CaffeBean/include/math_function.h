//
// Created by Kaiyu Xie on 2020/2/5.
//

#ifndef CAFFEBEAN_MATH_FUNCTION_H
#define CAFFEBEAN_MATH_FUNCTION_H

#include <../../lib/Eigen/Dense>
#include "common.h"

using namespace Eigen;

inline void Eigen_test() {
    Matrix3d m = Matrix3d::Random();
    m = (m + Matrix3d::Constant(1.2)) * 50;
    std::cout << "m =" << std::endl << m << std::endl;
    Vector3d v(1, 2, 3);
    std::cout << "m * v =" << std::endl << m * v << std::endl;

    float *a = new float[20];
    for (int i = 0; i < 20; ++i) {
        a[i] = i;
    }
    Map<Matrix<float, 4, 5, RowMajor> > staMat(a);
    std::cout << "a =\n" << staMat << std::endl;
    auto b = staMat.transpose();
    std::cout << "b =\n" << b << std::endl;
    auto c = staMat * b;
    std::cout << "c =\n" << c << std::endl;
    auto d = staMat.squaredNorm();
    std::cout << "d =\n" << d << std::endl;
}

inline void display_matrix(std::string name, float *m, int row, int col) {
    auto matrix = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(m, row, col);
    std::cout << name << " =\n" << matrix << std::endl;
}

inline void matrix_add(float *a, float *b, float *c, int row, int col) {
    auto dym_mat_a = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(a, row, col);
    auto dym_mat_b = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(b, row, col);
    auto dym_mat_c = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(c, row, col);
    dym_mat_c = dym_mat_a + dym_mat_b;
}

inline void matrix_multiply(float *a, float *b, float *c, int a_row, int a_col, int b_row, int b_col) {
    CAFFEBEAN_ASSERT(a_col == b_row, "a_col should be equal to b_row");
    auto dym_mat_a = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(a, a_row, a_col);
    auto dym_mat_b = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(b, b_row, b_col);
    auto dym_mat_c = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(c, a_row, b_col);
    dym_mat_c = dym_mat_a * dym_mat_b;
}

#endif //CAFFEBEAN_MATH_FUNCTION_H
