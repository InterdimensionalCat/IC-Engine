#pragma once
#include "Space2D.h"

#include "AngularType.h"
#include <vector>

#ifndef SFML_DISABLE
#include "SFML/Graphics.hpp"
#endif

namespace Space2D {
    template <typename T, typename SpaceType>
    class AffineMatrix final
    {

        //matrix form:
        //[a b tx]
        //[c d ty]
        //[0 0 1]

        //[0 3 6]
        //[1 4 7]
        //[2 5 8]


    private:
        T matrix[9];

        //T& a = this->matrix[0][0];
        //T& b = this->matrix[0][1];
        //T& tx = this->matrix[0][2];

        //T& c = this->matrix[1][0];
        //T& d = this->matrix[1][1];
        //T& ty = this->matrix[1][2];


    public:

        using Dimension = Dimension2<T, SpaceType>;
        using Vec = Vec2<T, SpaceType>;
        using Point = Point2<T, SpaceType>;
        using Poly = Poly2<T, SpaceType>;
        using Normal_Vec = NormalizedVec2<T, SpaceType>;
        using Rect = Rect2<T, SpaceType>;

        AffineMatrix() noexcept : matrix{1, 0, 0, 0, 1, 0, 0, 0, 1} {}

        explicit AffineMatrix(const T& fill_value) noexcept : matrix{ 
            {fill_value, fill_value, fill_value}, 
            {fill_value, fill_value, fill_value}, 
            {fill_value, fill_value, fill_value} } {}

        explicit AffineMatrix(
            const T& a00, const T& a01, const T& a02, 
            const T& a10, const T& a11, const T& a12, 
            const T& a20 = 0, const T& a21 = 0, const T& a22 = 1
        ) noexcept : matrix{a00, a10, a20, a01, a11, a21, a02, a12, a22} {}


        //all transformations are applied on points
        Point transformPoint(const Point& p) const noexcept {
            return Point(
                matrix[0] * p.x + matrix[3] * p.y + matrix[6],
                matrix[1] * p.x + matrix[4] * p.y + matrix[7]
            );
        }

        //all transformations excluding translations are applied on vectors
        Vec transformVec(const Vec& v) const noexcept {
            return Vec(
                matrix[0] * v.x + matrix[3] * v.y,
                matrix[1] * v.x + matrix[4] * v.y
            );
        }

        //all transformations excluding translations are applied on vectors,
        //but their magnitude will remain 1 no matter what
        Normal_Vec transformNormalVec(const Normal_Vec& v) const noexcept {
            return Normal_Vec(
                matrix[0] * v.x + matrix[3] * v.y,
                matrix[1] * v.x + matrix[4] * v.y
            );
        }

        //all transformations excluding translations are applied on Dimensions
        Dimension transformDim(const Dimension& d) const noexcept {
            return Dimension(
                matrix[0] * d.x + matrix[3] * d.y,
                matrix[1] * d.x + matrix[4] * d.y
            );
        }

        //all transformations are applied on Rectangles
        //however they maintain their axis-aligned properties
        Rect transformRect(const Rect& r) {
            return Rect(
                transformPoint(r.min),
                transformPoint(r.max)
            );
        }

        //all transformations are applied to Polygons
        Poly transformPoly(const Poly& to_transform) const noexcept {
            std::vector<Point> polypoints(0);
            auto polylen = to_transform.size();
            polypoints.reserve(polylen);

            for (size_t i = 0; i < polylen; i++) {
                polypoints.push_back(transformPoint(to_transform[i]));
            }

            return Poly(polypoints, transformPoint(to_transform.cent));

        }


        AffineMatrix getInverse() const noexcept {

            T determinant = matrix[0] * (matrix[4] * matrix[8] - matrix[7] * matrix[5])
                - matrix[3] * (matrix[1] * matrix[8] - matrix[7] * matrix[2])
                + matrix[6] * (matrix[1] * matrix[5] - matrix[4] * matrix[2]);


            if (determinant != static_cast<T>(0))
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

        AffineMatrix operator*(const AffineMatrix& rhs) const noexcept {

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

        AffineMatrix& operator*=(const AffineMatrix& rhs) noexcept {

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

        AffineMatrix& translate(const Vec& translation_vec) noexcept {

            auto trans_vec_inv = this->getInverse().transformVec(translation_vec);

            return ((*this) *= AffineMatrix(
                1, 0, trans_vec_inv.x,
                0, 1, trans_vec_inv.y,
                0, 0, 1
            ));
        }

        AffineMatrix& rotate(const Radians& rad) noexcept {
            auto val = rad.get();

            auto cosval = cos(val);
            auto sinval = sin(val);

            return ((*this) *= AffineMatrix(
                cosval, sinval, 0, 
                -sinval, cosval, 0
            ));
        }

        AffineMatrix& rotate(const Radians& rad, Point center) noexcept {

            auto val = rad.get();

            auto cosval = cos(val);
            auto sinval = sin(val);



            return ((*this) *= AffineMatrix(
                cosval, sinval, center.x * (1 - cosval) - center.y * sinval,
                -sinval, cosval, center.y * (1 - cosval) + center.x * sinval
            ));
        }

        AffineMatrix& scale(const Percent& scale_x, const Percent& scale_y) noexcept {

            auto sx = scale_x.get() / 100;
            auto sy = scale_x.get() / 100;

            T x = static_cast<T>(sx);
            T y = static_cast<T>(sy);

            return ((*this) *= AffineMatrix(
                x, 0, 0, 
                0, y, 0
            ));
        }

        AffineMatrix& scale(const Percent& scale_x, const Percent& scale_y, const Point& center) noexcept {

            T x = static_cast<T>(scale_x.get() / 100);
            T y = static_cast<T>(scale_y.get() / 100);

            return((*this) *= AffineMatrix(
                x, 0, center.x * (1 - x),
                0, y, center.y * (1 - y)
            ));
        }

        AffineMatrix& shear(const T& shear_factor_X, const T& shear_factor_Y) noexcept {
            return((*this) *= AffineMatrix(
                1, shear_factor_X.value, 0,
                shear_factor_Y.value, 1, 0
            ));
        }

        AffineMatrix& shear(const T& shear_factor_X, const T& shear_factor_Y, Point center) noexcept {

            center *= -1;

            auto sx = shear_factor_X.value;
            auto sy = shear_factor_Y.value;

            return((*this) *= AffineMatrix(
                1, sx,  -(center.y * sx),
                sy, 1, center.x * sy
            ));
        }

        AffineMatrix& reflectX() noexcept {
           return linearReflection(Vec(1, 0));
        }

        AffineMatrix& reflectY() noexcept {
           return linearReflection(Vec(0, 1));
        }

        AffineMatrix& linearReflection(const Vec& line_slope) noexcept {
            auto a = -line_slope.y;
            auto b = line_slope.x;

            (*this) *= (AffineMatrix(
                b * b - a * a, -2 * a * b, 0,
                -2 * a * b, a * a - b * b, 0
            ) * (1 / line_slope.MagSquared()));


            return *this;
        }

        AffineMatrix& linearReflection(const Vec& line_slope, const Point& intercept) noexcept {
            auto a = -line_slope.y;
            auto b = line_slope.x;
            T c; //the y intercept
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

        AffineMatrix& orthagonalProjection(const Vec& line_slope) noexcept {

            Normal_Vec a = line_slope.Normalize();

            (*this) *= (AffineMatrix(
                a.x * a.x, a.x * a.y, 0,
                a.x * a.y, a.y * a.y, 0
            ));
            return *this;
        }

        AffineMatrix& orthagonalProjection(const Vec& line_slope, const Point& intercept) noexcept {
            Normal_Vec v = line_slope.Normalize();

            auto a = -line_slope.y;
            auto b = line_slope.x;
            T c; //the y intercept
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

        AffineMatrix& operator*=(const T& factor) noexcept {

            matrix[0] *= factor;
            matrix[1] *= factor;

            matrix[3] *= factor;
            matrix[4] *= factor;

            matrix[6] *= factor;
            matrix[7] *= factor;

            return *this;
        }

        AffineMatrix operator*(const T& factor) const noexcept {
            return AffineMatrix(matrix[0] * factor, matrix[3] * factor, matrix[6] * factor, matrix[1] * factor, matrix[4] * factor, matrix[7] * factor);
        }

        const auto getMatrix() const noexcept {
            return matrix;
        }

        auto getMatrix() noexcept {
            return matrix;
        }

        bool operator==(const AffineMatrix& rhs) const noexcept {

            auto l = getMatrix();
            auto r = rhs.getMatrix();

            double epsilon = 1e-6;

            return
                (abs(l[0] - r[0]) < epsilon) && (abs(l[1] - r[1]) < epsilon) && (abs(l[2] - r[2]) < epsilon) &&
                (abs(l[3] - r[3]) < epsilon) && (abs(l[4] - r[4]) < epsilon) && (abs(l[5] - r[5]) < epsilon) &&
                (abs(l[6] - r[6]) < epsilon) && (abs(l[7] - r[7]) < epsilon) && (abs(l[8] - r[8]) < epsilon);
        }

        bool operator!=(const AffineMatrix& rhs) const noexcept {
            return !(*this == rhs);
        }

        template <typename other_T, typename other_SpaceType>
        operator AffineMatrix<other_T, other_SpaceType>() const noexcept {



            AffineMatrix from = SpaceType::transform_ratio.getInverse();

            //step 1: apply inverse of the reletive space transform the object is in
            AffineMatrix first_transform = *this * from;

            //step 2: copy contents into new type container
            AffineMatrix<other_T, other_SpaceType> second_transform(
                static_cast<other_T>(first_transform.matrix[0]), static_cast<other_T>(first_transform.matrix[3]), static_cast<other_T>(first_transform.matrix[6]),
                static_cast<other_T>(first_transform.matrix[1]), static_cast<other_T>(first_transform.matrix[4]), static_cast<other_T>(first_transform.matrix[7]),
                static_cast<other_T>(first_transform.matrix[2]), static_cast<other_T>(first_transform.matrix[5]), static_cast<other_T>(first_transform.matrix[8])
            );

            AffineMatrix<other_T, other_SpaceType> to = other_SpaceType::transform_ratio;

            //apply the reletive space transform of the new space
            return (second_transform * to);
        }

#ifndef SFML_DISABLE
        sf::Transform toSFMLMatrix() const noexcept {
            return Transform(
                static_cast<float>(matrix[0]), static_cast<float>(matrix[3]), static_cast<float>(matrix[6]),
                static_cast<float>(matrix[1]), static_cast<float>(matrix[4]), static_cast<float>(matrix[7]),
                static_cast<float>(matrix[2]), static_cast<float>(matrix[5]), static_cast<float>(matrix[8])
                );
        }
#endif

        friend std::ostream& operator << (std::ostream& os, const AffineMatrix& it) {
            auto mat = it.getMatrix();
            const auto space = SpaceTypeNameMap<SpaceType>::name;
            os << space << "::Matrix\n";
            os << "[ " << mat[0] << ", " << mat[3] << ", " << mat[6] << "]\n";
            os << "[ " << mat[1] << ", " << mat[4] << ", " << mat[7] << "]\n";
            os << "[ " << mat[2] << ", " << mat[5] << ", " << mat[8] << "]\n";
            return os;
        }
    };
}