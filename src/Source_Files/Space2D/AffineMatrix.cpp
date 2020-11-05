#include "include.h"
#include "AngularType.h"
#include <vector>
#include <cmath>
#include "SFML/Graphics.hpp"
#include "Vec2.h"
#include "Point2.h"
#include "NormalizedVec2.h"
#include "Rect2.h"
#include "Poly2.h"
#include "Dimension2.h"

using namespace Space2D;

using Dimension = Dimension2;
using Vec = Vec2;
using Point = Point2;
using Poly = Poly2;
using NormalVec = NormalizedVec2;
using Rectangle = Rect2;

AffineMatrix::AffineMatrix() noexcept : matrix{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f } {}

AffineMatrix::AffineMatrix(const float& fill_value) noexcept : matrix{
    fill_value, fill_value, fill_value,
    fill_value, fill_value, fill_value,
    fill_value, fill_value, fill_value
} {}

AffineMatrix::AffineMatrix(
    const float& a00, const float& a01, const float& a02,
    const float& a10, const float& a11, const float& a12,
    const float& a20, const float& a21, const float& a22
) noexcept : matrix{ a00, a10, a20, a01, a11, a21, a02, a12, a22 } {}

Point AffineMatrix::transformPoint(const Point& p) const noexcept {
    return Point(
        matrix[0] * p.x + matrix[3] * p.y + matrix[6],
        matrix[1] * p.x + matrix[4] * p.y + matrix[7]
    );
}

Vec AffineMatrix::transformVec(const Vec& v) const noexcept {
    return Vec(
        matrix[0] * v.x + matrix[3] * v.y,
        matrix[1] * v.x + matrix[4] * v.y
    );
}

NormalVec AffineMatrix::transformNormalVec(const NormalVec& v) const noexcept {
    return NormalVec(
        matrix[0] * v.x + matrix[3] * v.y,
        matrix[1] * v.x + matrix[4] * v.y
    );
}

Dimension AffineMatrix::transformDim(const Dimension& d) const noexcept {
    return Dimension(
        matrix[0] * d.x + matrix[3] * d.y,
        matrix[1] * d.x + matrix[4] * d.y
    );
}

Rectangle AffineMatrix::transformRect(const Rectangle& r) {
    return Rectangle(
        transformPoint(r.min),
        transformPoint(r.max)
    );
}

Poly AffineMatrix::transformPoly(const Poly& to_transform) const noexcept {
    std::vector<Point> polypoints(0);
    auto polylen = to_transform.size();
    polypoints.reserve(polylen);

    for (size_t i = 0; i < polylen; i++) {
        polypoints.push_back(transformPoint(to_transform[i]));
    }

    return Poly(polypoints, transformPoint(to_transform.cent));

}


AffineMatrix AffineMatrix::getInverse() const noexcept {

    float determinant = matrix[0] * (matrix[4] * matrix[8] - matrix[7] * matrix[5])
        - matrix[3] * (matrix[1] * matrix[8] - matrix[7] * matrix[2])
        + matrix[6] * (matrix[1] * matrix[5] - matrix[4] * matrix[2]);


    if (determinant != 0.0f)
    {
        //[0 3 6]
        //[1 4 7]
        //[2 5 8]

        //[0 1 2]
        //[3 4 5]
        //[6 7 8]

        return AffineMatrix(
            (matrix[4] * matrix[8] - matrix[5] * matrix[7]) / determinant,
            -(matrix[3] * matrix[8] - matrix[5] * matrix[6]) / determinant,
            (matrix[3] * matrix[7] - matrix[4] * matrix[6]) / determinant,

            -(matrix[1] * matrix[8] - matrix[2] * matrix[7]) / determinant,
            (matrix[0] * matrix[8] - matrix[2] * matrix[6]) / determinant,
            -(matrix[0] * matrix[7] - matrix[1] * matrix[6]) / determinant,

            (matrix[1] * matrix[5] - matrix[2] * matrix[4]) / determinant,
            -(matrix[0] * matrix[5] - matrix[2] * matrix[3]) / determinant,
            (matrix[0] * matrix[4] - matrix[1] * matrix[3]) / determinant
        );
    }
    else
    {
        return AffineMatrix();
    }
}

AffineMatrix AffineMatrix::operator*(const AffineMatrix& rhs) const noexcept {

    //[0 3 6]
    //[1 4 7]
    //[2 5 8]

    return AffineMatrix(
        (matrix[0] * rhs.matrix[0] + matrix[3] * rhs.matrix[1] + matrix[6] * rhs.matrix[2]),
        (matrix[0] * rhs.matrix[3] + matrix[3] * rhs.matrix[4] + matrix[6] * rhs.matrix[5]),
        (matrix[0] * rhs.matrix[6] + matrix[3] * rhs.matrix[7] + matrix[6] * rhs.matrix[8]),

        (matrix[1] * rhs.matrix[0] + matrix[4] * rhs.matrix[1] + matrix[7] * rhs.matrix[2]),
        (matrix[1] * rhs.matrix[3] + matrix[4] * rhs.matrix[4] + matrix[7] * rhs.matrix[5]),
        (matrix[1] * rhs.matrix[6] + matrix[4] * rhs.matrix[7] + matrix[7] * rhs.matrix[8]),

        (matrix[2] * rhs.matrix[0] + matrix[5] * rhs.matrix[1] + matrix[8] * rhs.matrix[2]),
        (matrix[2] * rhs.matrix[3] + matrix[5] * rhs.matrix[4] + matrix[8] * rhs.matrix[5]),
        (matrix[2] * rhs.matrix[6] + matrix[5] * rhs.matrix[7] + matrix[8] * rhs.matrix[8])
    );
}

AffineMatrix& AffineMatrix::operator*=(const AffineMatrix& rhs) noexcept {

    //[0 3 6]
    //[1 4 7]
    //[2 5 8]

    (*this) = AffineMatrix(
        (matrix[0] * rhs.matrix[0] + matrix[3] * rhs.matrix[1] + matrix[6] * rhs.matrix[2]),
        (matrix[0] * rhs.matrix[3] + matrix[3] * rhs.matrix[4] + matrix[6] * rhs.matrix[5]),
        (matrix[0] * rhs.matrix[6] + matrix[3] * rhs.matrix[7] + matrix[6] * rhs.matrix[8]),

        (matrix[1] * rhs.matrix[0] + matrix[4] * rhs.matrix[1] + matrix[7] * rhs.matrix[2]),
        (matrix[1] * rhs.matrix[3] + matrix[4] * rhs.matrix[4] + matrix[7] * rhs.matrix[5]),
        (matrix[1] * rhs.matrix[6] + matrix[4] * rhs.matrix[7] + matrix[7] * rhs.matrix[8]),

        (matrix[2] * rhs.matrix[0] + matrix[5] * rhs.matrix[1] + matrix[8] * rhs.matrix[2]),
        (matrix[2] * rhs.matrix[3] + matrix[5] * rhs.matrix[4] + matrix[8] * rhs.matrix[5]),
        (matrix[2] * rhs.matrix[6] + matrix[5] * rhs.matrix[7] + matrix[8] * rhs.matrix[8])
    );
    return *this;
}

AffineMatrix& AffineMatrix::translate(const Vec& translation_vec) noexcept {

    auto trans_vec_inv = this->getInverse().transformVec(translation_vec);

    return ((*this) *= AffineMatrix(
        1, 0, trans_vec_inv.x,
        0, 1, trans_vec_inv.y,
        0, 0, 1
    ));
}

AffineMatrix& AffineMatrix::rotate(const Radians& rad) noexcept {
    auto val = rad.get();

    float cosval = static_cast<float>(cos(val));
    float sinval = static_cast<float>(sin(val));

    return ((*this) *= AffineMatrix(
        cosval, sinval, 0,
        -sinval, cosval, 0
    ));
}

AffineMatrix& AffineMatrix::rotate(const Radians& rad, Point center) noexcept {

    auto val = rad.get();

    auto cosval = cos(val);
    auto sinval = sin(val);



    return ((*this) *= AffineMatrix(
        cosval, sinval, center.x * (1 - cosval) - center.y * sinval,
        -sinval, cosval, center.y * (1 - cosval) + center.x * sinval
    ));
}

AffineMatrix& AffineMatrix::scale(const Percent& scale_x, const Percent& scale_y) noexcept {

    auto sx = (float)scale_x.get();
    auto sy = (float)scale_x.get();

    float x = sx;
    float y = sy;

    return ((*this) *= AffineMatrix(
        x, 0, 0,
        0, y, 0
    ));
}

AffineMatrix& AffineMatrix::scale(const float& x_factor, const float& y_factor) noexcept {

    float x = x_factor;
    float y = y_factor;

    return ((*this) *= AffineMatrix(
        x, 0, 0,
        0, y, 0
    ));
}

AffineMatrix& AffineMatrix::scale(const Percent& scale_x, const Percent& scale_y, const Point& center) noexcept {

    float x = static_cast<float>(scale_x.get());
    float y = static_cast<float>(scale_y.get());

    return((*this) *= AffineMatrix(
        x, 0, center.x * (1 - x),
        0, y, center.y * (1 - y)
    ));
}

AffineMatrix& AffineMatrix::scale(const float& scale_x, const float& scale_y, const Point& center) noexcept {

    float x = scale_x;
    float y = scale_y;

    return((*this) *= AffineMatrix(
        x, 0, center.x * (1 - x),
        0, y, center.y * (1 - y)
    ));
}

AffineMatrix& AffineMatrix::shear(const float& shear_factor_X, const float& shear_factor_Y) noexcept {
    return((*this) *= AffineMatrix(
        1, shear_factor_X, 0,
        shear_factor_Y, 1, 0
    ));
}

AffineMatrix& AffineMatrix::shear(const float& shear_factor_X, const float& shear_factor_Y, Point center) noexcept {

    center *= -1;

    float sx = shear_factor_X;
    float sy = shear_factor_Y;

    return((*this) *= AffineMatrix(
        1, sx, -(center.y * sx),
        sy, 1, center.x * sy
    ));
}

AffineMatrix& AffineMatrix::reflectX() noexcept {
    return linearReflection(Vec(1, 0));
}

AffineMatrix& AffineMatrix::reflectY() noexcept {
    return linearReflection(Vec(0, 1));
}

AffineMatrix& AffineMatrix::linearReflection(const Vec& line_slope) noexcept {
    auto a = -line_slope.y;
    auto b = line_slope.x;

    (*this) *= (AffineMatrix(
        b * b - a * a, -2 * a * b, 0,
        -2 * a * b, a * a - b * b, 0
    ) * (1 / line_slope.MagSquared()));


    return *this;
}

AffineMatrix& AffineMatrix::linearReflection(const Vec& line_slope, const Point& intercept) noexcept {
    auto a = -line_slope.y;
    auto b = line_slope.x;
    float c; //the y intercept
    if (intercept.y == 0) {
        c = intercept.x;
    }
    else {
        auto m = a / b;
        auto x1 = intercept.x;
        auto y1 = intercept.y;
        c = (-y1 / m) + x1;
    }


    (*this) *= (AffineMatrix(
        b * b - a * a, -2 * a * b, -2 * a * c,
        -2 * a * b, a * a - b * b, -2 * b * c
    ) * (1 / line_slope.MagSquared()));


    return *this;
}

AffineMatrix& AffineMatrix::orthagonalProjection(const Vec& line_slope) noexcept {

    NormalVec a = line_slope.Normalize();

    (*this) *= (AffineMatrix(
        a.x * a.x, a.x * a.y, 0,
        a.x * a.y, a.y * a.y, 0
    ));
    return *this;
}

AffineMatrix& AffineMatrix::orthagonalProjection(const Vec& line_slope, const Point& intercept) noexcept {
    NormalVec v = line_slope.Normalize();

    auto a = -line_slope.y;
    auto b = line_slope.x;
    float c; //the y intercept
    if (intercept.y == 0) {
        c = intercept.x;
    }
    else {
        auto m = a / b;
        auto x1 = intercept.x;
        auto y1 = intercept.y;
        c = (-y1 / m) + x1;
    }

    auto d = abs(a * intercept.x + b * intercept.y + c) / sqrt(a * a + b * b);

    auto trans_val = line_slope.unitNormal() * d;

    if (c > 0) {
        trans_val *= -1;
    }

    (*this) *= (AffineMatrix(
        v.x * v.x, v.x * v.y, trans_val.x,
        v.x * v.y, v.y * v.y, trans_val.y
    ));
    return *this;
}

AffineMatrix& AffineMatrix::operator*=(const float& factor) noexcept {

    matrix[0] *= factor;
    matrix[1] *= factor;

    matrix[3] *= factor;
    matrix[4] *= factor;

    matrix[6] *= factor;
    matrix[7] *= factor;

    return *this;
}

AffineMatrix AffineMatrix::operator*(const float& factor) const noexcept {
    return AffineMatrix(matrix[0] * factor, matrix[3] * factor, matrix[6] * factor, matrix[1] * factor, matrix[4] * factor, matrix[7] * factor);
}

const std::array<float, 9>& AffineMatrix::getMatrix() const noexcept {
    return matrix;
}

std::array<float, 9>& AffineMatrix::getMatrix() noexcept {
    return matrix;
}

bool AffineMatrix::operator==(const AffineMatrix& rhs) const noexcept {

    auto l = getMatrix();
    auto r = rhs.getMatrix();

    float epsilon = 1e-6f;

    return
        (abs(l[0] - r[0]) < epsilon) && (abs(l[1] - r[1]) < epsilon) && (abs(l[2] - r[2]) < epsilon) &&
        (abs(l[3] - r[3]) < epsilon) && (abs(l[4] - r[4]) < epsilon) && (abs(l[5] - r[5]) < epsilon) &&
        (abs(l[6] - r[6]) < epsilon) && (abs(l[7] - r[7]) < epsilon) && (abs(l[8] - r[8]) < epsilon);
}

bool AffineMatrix::operator!=(const AffineMatrix& rhs) const noexcept {
    return !(*this == rhs);
}