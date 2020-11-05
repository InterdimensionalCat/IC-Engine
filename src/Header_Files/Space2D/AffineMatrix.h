#pragma once
#include <array>
#include "SFML/Graphics.hpp"

namespace Space2D {

    class Dimension2;
    class Vec2;
    class Point2;
    class Poly2;
    class NormalizedVec2;
    class Rect2;

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
        std::array<float, 9> matrix;
        //float matrix[9];

        //T& a = this->matrix[0][0];
        //T& b = this->matrix[0][1];
        //T& tx = this->matrix[0][2];

        //T& c = this->matrix[1][0];
        //T& d = this->matrix[1][1];
        //T& ty = this->matrix[1][2];


    public:

        AffineMatrix() noexcept;

        explicit AffineMatrix(const float& fill_value) noexcept;

        explicit AffineMatrix(
            const float& a00, const float& a01, const float& a02,
            const float& a10, const float& a11, const float& a12,
            const float& a20 = 0, const float& a21 = 0, const float& a22 = 1
        ) noexcept;

        //all transformations are applied on points
        Point2 transformPoint(const Point2& p) const noexcept;

        //all transformations excluding translations are applied on vectors
        Vec2 transformVec(const Vec2& v) const noexcept;

        //all transformations excluding translations are applied on vectors,
        //but their magnitude will remain 1 no matter what
        NormalizedVec2 transformNormalVec(const NormalizedVec2& v) const noexcept;

        //all transformations excluding translations are applied on Dimensions
        Dimension2 transformDim(const Dimension2& d) const noexcept;

        //all transformations are applied on Rectangles
        //however they maintain their axis-aligned properties
        Rect2 transformRect(const Rect2& r);

        //all transformations are applied to Polygons
        Poly2 transformPoly(const Poly2& to_transform) const noexcept;

        AffineMatrix getInverse() const noexcept;

        AffineMatrix operator*(const AffineMatrix& rhs) const noexcept;

        AffineMatrix& operator*=(const AffineMatrix& rhs) noexcept;

        AffineMatrix& translate(const Vec& translation_vec) noexcept;

        AffineMatrix& rotate(const Radians& rad) noexcept;

        AffineMatrix& rotate(const Radians& rad, Point center) noexcept;

        AffineMatrix& scale(const Percent& scale_x, const Percent& scale_y) noexcept;

        AffineMatrix& scale(const float& x_factor, const float& y_factor) noexcept;

        AffineMatrix& scale(const Percent& scale_x, const Percent& scale_y, const Point& center) noexcept;

        AffineMatrix& scale(const float& scale_x, const float& scale_y, const Point& center) noexcept;

        AffineMatrix& shear(const float& shear_factor_X, const float& shear_factor_Y) noexcept;

        AffineMatrix& shear(const float& shear_factor_X, const float& shear_factor_Y, Point center) noexcept;

        AffineMatrix& reflectX() noexcept;

        AffineMatrix& reflectY() noexcept;

        AffineMatrix& linearReflection(const Vec& line_slope) noexcept;

        AffineMatrix& linearReflection(const Vec& line_slope, const Point& intercept) noexcept;

        AffineMatrix& orthagonalProjection(const Vec& line_slope) noexcept;

        AffineMatrix& orthagonalProjection(const Vec& line_slope, const Point& intercept) noexcept;

        AffineMatrix& operator*=(const float& factor) noexcept;

        AffineMatrix operator*(const float& factor) const noexcept;

        const std::array<float, 9>& getMatrix() const noexcept;

        std::array<float, 9>& getMatrix() noexcept;

        bool operator==(const AffineMatrix& rhs) const noexcept;

        bool operator!=(const AffineMatrix& rhs) const noexcept;

        sf::Transform toSFMLMatrix() const noexcept {
            return sf::Transform(
                static_cast<float>(matrix[0]), static_cast<float>(matrix[3]), static_cast<float>(matrix[6]),
                static_cast<float>(matrix[1]), static_cast<float>(matrix[4]), static_cast<float>(matrix[7]),
                static_cast<float>(matrix[2]), static_cast<float>(matrix[5]), static_cast<float>(matrix[8])
                );
        }
        friend std::ostream& operator << (std::ostream& os, const AffineMatrix& it) {
            auto mat = it.getMatrix();
            os << "Matrix\n";
            os << "[ " << mat[0] << ", " << mat[3] << ", " << mat[6] << "]\n";
            os << "[ " << mat[1] << ", " << mat[4] << ", " << mat[7] << "]\n";
            os << "[ " << mat[2] << ", " << mat[5] << ", " << mat[8] << "]\n";
            return os;
        }
    };
}