#pragma once
#include "SFML/Graphics.hpp"


namespace Space2D {

    class Dimension2;
    class Vec2;
    class Point2;
    class Poly2;
    class NormalizedVec2;
    class Rect2;

    class Rect2 final
    {

    public:

        //constructs a rect with points (0,0) and (0,0)
        Rect2() noexcept;

        explicit Rect2(const float& x0, const float& y0, const float& x1, const float& y1) noexcept;

        explicit Rect2(const Point2& min, const Point2& max) noexcept;

        //define a rect like an sfml rectangle(min_point + dimensions)
        explicit Rect2(const Point2& min, const Dimension2 dim) noexcept;

        //define a rectangle as a sub area of a smaller rectangle such that
        //     _____________
        //    |             |
        //    |x0,y0__      |
        //    |  |   |      |
        //    |  |___x1, y1 |
        //    |_____________|
        //where (x0, x1) is base_rect.min + min_offset
        //and (x1, y1) is base_rect.max - max_offset
        explicit Rect2(const Rect2& base_rect, const Vec2& min_offset, const Vec2& max_offset);

        //same constructor as above but as a ratio of the rectangle size
        explicit Rect2(const Rect2& base_rect, const Percent& min_offset_X, const Percent& min_offset_Y, const Percent& max_offset_X, const Percent& max_offset_Y);

        bool operator==(const Rect2& other) const noexcept;

        bool operator!=(const Rect2& other) const noexcept;

        Rect2& operator-=(const Vec& rhs) noexcept;

        Rect2& operator-=(const NormalizedVec2& rhs) noexcept;

        Rect2 operator-(const Vec2& rhs) const noexcept;

        Rect2 operator-(const NormalizedVec2& rhs) const noexcept;

        Rect2& operator+=(const Vec2& rhs) noexcept;

        Rect2& operator+=(const NormalizedVec2& rhs) noexcept;

        Rect2 operator+(const Vec2& rhs) const noexcept;

        Rect2 operator+(const NormalizedVec2& rhs) const noexcept;

        float area() const noexcept;

        Point center() const noexcept;

        bool contains(const Point2& query) const noexcept;

        Dimension getSize() const noexcept;

        float getWidth() const noexcept;

        float getHeight() const noexcept;

        void moveMinTo(const Point2& new_min) noexcept;

        void moveCenterTo(const Point2& new_center) noexcept;

        NormalVec getNormal_1_0();

        NormalVec getNormal_neg1_0();

        NormalVec getNormal_0_1();

        NormalVec getNormal_0_neg1();

        template <typename SFMLType = float>
        sf::Rect<SFMLType> toSFMLRect() const noexcept {
            sf::Vector2<SFMLType> v1 = sf::Vector2<SFMLType>(static_cast<SFMLType>(min.x), static_cast<SFMLType>(min.y));
            sf::Vector2<SFMLType> v2 = sf::Vector2<SFMLType>(static_cast<SFMLType>(getWidth()), static_cast<SFMLType>(getHeight()));
            return sf::Rect<SFMLType>(v1, v2);
        }
        
        //border size strictly adds to the size, so the RectangleShape will only retain the same dimensions as the s2d::Rect if border is 0.0f
        //however, section that is the "interior color" will never get clipped due to a large border size
        sf::RectangleShape makeDrawableSFMLRect(const float bordersize = 0.0f, const sf::Color interior_color = sf::Color(0,0,0,0), const sf::Color border_color = sf::Color(0, 0, 0, 0)) const {
            sf::RectangleShape newshape;
            newshape.setOutlineThickness(bordersize);
            newshape.setOutlineColor(border_color);
            newshape.setFillColor(interior_color);
            sf::Vector2f v1 = sf::Vector2f(static_cast<float>(min.x), static_cast<float>(min.y));
            sf::Vector2f v2 = sf::Vector2f(static_cast<float>(getWidth()), static_cast<float>(getHeight()));
            newshape.setPosition(v1);
            newshape.setSize(v2);
            return newshape;
        }

        friend std::ostream& operator << (std::ostream& os, const Rect2& it) {
            os  << "Rect ( Min: " << it.min << ", Max: " << it.max << ")";
            return os;
        }


        Point2 min;
        Point2 max;
    };
}

