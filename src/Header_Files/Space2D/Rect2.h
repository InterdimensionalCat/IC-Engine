#pragma once
#include "Space2D.h"


namespace Space2D {
    template <typename T, typename SpaceType>
    class Rect2 final
    {

    public:

        using Point = Point2<T, SpaceType>;
        using Vec = Vec2<T, SpaceType>;
        using Normal_Vec = NormalizedVec2<T, SpaceType>;
        using Dimension = Dimension2<T, SpaceType>;
        using Matrix = AffineMatrix<T, SpaceType>;

        //constructs a rect with points (0,0) and (0,0)
        Rect2() noexcept {}

        explicit Rect2(const T& x0, const T& y0, const T& x1, const T& y1) noexcept : min(Point(x0, y0)), max(Point(x1, y1)) {}

        explicit Rect2(const Point& min, const Point& max) noexcept : min(min), max(max) {}

        //define a rect like an sfml rectangle(min_point + dimensions)
        explicit Rect2(const Point& min, const Dimension dim) noexcept : min(min), max(Point(min.x + dim.x, min.y + dim.y)) {}

        //define a rectangle as a sub area of a smaller rectangle such that
        //     _____________
        //    |             |
        //    |x0,y0__      |
        //    |  |   |      |
        //    |  |___x1, y1 |
        //    |_____________|
        //where (x0, x1) is base_rect.min + min_offset
        //and (x1, y1) is base_rect.max - max_offset
        explicit Rect2(const Rect2& base_rect, const Vec& min_offset, const Vec& max_offset) : min(base_rect.min + min_offset), max(base_rect.max - max_offset) {

        }

        //same constructor as above but as a ratio of the rectangle size
        explicit Rect2(const Rect2& base_rect, const Percent& min_offset_X, const Percent& min_offset_Y, const Percent& max_offset_X, const Percent& max_offset_Y) {


            min = base_rect.min + Point(base_rect.getWidth() * static_cast<T>(min_offset_X.get() / 100), base_rect.getHeight() * static_cast<T>(min_offset_Y.get() / 100));
            max = base_rect.max - Point(base_rect.getWidth() * static_cast<T>(max_offset_X.get() / 100), base_rect.getHeight() * static_cast<T>(max_offset_Y.get() / 100));
        }

        bool operator==(const Rect2& other) const noexcept {
            return min == other.min && max == other.max;
        }

        bool operator!=(const Rect2& other) const noexcept {
            return !(operator==(other));
        }

        Rect2& operator-=(const Vec& rhs) noexcept {
            min -= rhs;
            max -= rhs;
            return *this;
        }

        Rect2& operator-=(const Normal_Vec& rhs) noexcept {
            min -= rhs;
            max -= rhs;
            return *this;
        }

        Rect2 operator-(const Vec& rhs) const noexcept {
            return Rect2(min - rhs, max - rhs);
        }

        Rect2 operator-(const Normal_Vec& rhs) const noexcept {
            return Rect2(min - rhs, max - rhs);
        }

        Rect2& operator+=(const Vec& rhs) noexcept {
            min += rhs;
            max += rhs;
            return *this;
        }

        Rect2& operator+=(const Normal_Vec& rhs) noexcept {
            min += rhs;
            max += rhs;
            return *this;
        }

        Rect2 operator+(const Vec& rhs) const noexcept {
            return Rect2(min + rhs, max + rhs);
        }

        Rect2 operator+(const Normal_Vec& rhs) const noexcept {
            return Rect2(min + rhs, max + rhs);
        }

        T area() const noexcept {
            return (getWidth() * getHeight());
        }

        Point center() const noexcept {
            return Point((max + min) / 2);
        }

        bool contains(const Point& query) const noexcept {
            return (query.x > min.x) &&
                (query.x < max.x) &&
                (query.y > min.y) &&
                (query.y < max.y);

        }

        Dimension getSize() const noexcept {
            return Dimension(min, max);
        }

        T getWidth() const noexcept {
            return max.x - min.x;
        }

        T getHeight() const noexcept {
            return max.y - min.y;
        }

        void moveMinTo(const Point& new_min) noexcept {
            auto size = getSize();
            min = new_min;
            max = new_min + Vec(size.x, size.y);
        }

        void moveCenterTo(const Point& new_center) noexcept {
            auto size = getSize();
            min = new_center - (size / static_cast<T>(2));
            max = new_center + (size / static_cast<T>(2));
        }

        Normal_Vec getNormal_1_0() {
            return Normal_Vec(static_cast<T>(1), static_cast<T>(0));
        }

        Normal_Vec getNormal_neg1_0() {
            return Normal_Vec(static_cast<T>(-1), static_cast<T>(0));
        }

        Normal_Vec getNormal_0_1() {
            return Normal_Vec(static_cast<T>(0), static_cast<T>(1));
        }

        Normal_Vec getNormal_0_neg1() {
            return Normal_Vec(static_cast<T>(0), static_cast<T>(-1));
        }

        template <typename other_T, typename other_SpaceType>
        operator Rect2<other_T, other_SpaceType>() const noexcept {
            Matrix from = SpaceType::transform_ratio.getInverse();

            //step 1: apply inverse of the reletive space transform the object is in
            Rect2 first_transform = from.transformRect(*this);

            //step 2: copy contents into new type container
            Rect2<other_T, other_SpaceType> second_transform(
                static_cast<other_T>(first_transform.min.x), static_cast<other_T>(first_transform.min.y), 
                static_cast<other_T>(first_transform.max.x), static_cast<other_T>(first_transform.max.y)
            );

            AffineMatrix<other_T, other_SpaceType> to = other_SpaceType::transform_ratio;

            //apply the reletive space transform of the new space
            return to.transformRect(second_transform);
        }

#ifndef SFML_DISABLE
        template <typename SFMLType = T>
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

#endif

        friend std::ostream& operator << (std::ostream& os, const Rect2<T, SpaceType>& it) {
            const auto space = SpaceTypeNameMap<SpaceType>::name;
            os << space << "::Rect ( Min: " << it.min << ", Max: " << it.max << ")";
            return os;
        }


        Point min;
        Point max;
    };
}

