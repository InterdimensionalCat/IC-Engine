#pragma once

//declaration of Space2D types and SFML_DISABLE preprossor directive
namespace Space2D {

    //uncomment the lines below if using Space2D without SFML
#ifndef SFML_DISABLE
    //#define SFML_DISABLE
#endif

    template<typename T, typename SpaceType>
    class Vec2;

    template<typename T, typename SpaceType>
    class Point2;

    template<typename T, typename SpaceType>
    class NormalizedVec2;

    template<typename T, typename SpaceType>
    class Dimension2;

    template<typename T, typename SpaceType>
    class Rect2;

    template<typename T, typename SpaceType>
    class AffineMatrix;

    template<typename T, typename SpaceType>
    class Poly2;
}

//definition of Space2D base class
namespace Space2D {


	template <typename SpaceName, typename units>
	class Space
	{
    public:

        //Space 2D primatives:
		using Point = Point2<units, SpaceName>;
        using Vec = Vec2<units, SpaceName>;
        using Normal_Vec = NormalizedVec2<units, SpaceName>;
        using Rectangle = Rect2<units, SpaceName>;
        using Poly = Poly2<units, SpaceName>;
        using Matrix = AffineMatrix<units, SpaceName>;
        using Dimension = Dimension2<units, SpaceName>;


        //this must be defined in Space2D.cpp for each space
        static Matrix transform_ratio;

        //lerp functions for primatives that make sense for it
        using T = units;

        static T lerp(const T a, const T b, const double t) {
            return a + (static_cast<T>(t) * (b - a));
        }

        //TODO: more space-related helpers here
	};

}

//alias for Space2D
namespace s2d {
    using namespace Space2D;
}

#include <string>

//definition of SpaceTypeNameMap
namespace Space2D {

    template <typename T>
    struct SpaceTypeNameMap final { static const std::string name; };

    template <typename T>
    const std::string SpaceTypeNameMap <T>::name = "NoSpaceNameDefined";
}


//Create definitions of spaces here:
namespace Space2D {

    //every space must be added to the SpaceIDS
    enum class SpaceIDs
    {
        //units of the map not adjusted for view
        GameUnits = 0,

        //game units but in pixels
        PixelUnits,

        //pixel units but adjusted for the window/whatever view the transform manager is transforming for
        ScreenUnits,

        //shared space used for translating in spaces
        GUITranslate
    };


    //actual class definitions are here
    //each space given here has a defaultTransform() member
    //this is not necessasary but its helpful for reverting 
    //transformations that have acted on this space
    struct GameUnits final : Space<GameUnits, double> {
        static inline SpaceIDs id = SpaceIDs::GameUnits;

        static GameUnits::Matrix defaultTransform();
        static double scale();
    };
    template <> const std::string SpaceTypeNameMap<GameUnits>::name = "GameUnits";

    struct PixelUnits final : Space<PixelUnits, float> {
        static inline SpaceIDs id = SpaceIDs::PixelUnits;

        static PixelUnits::Matrix defaultTransform();
        static float scale();
    };
    template <> const std::string SpaceTypeNameMap<PixelUnits>::name = "PixelUnits";

    struct ScreenUnits final : Space<ScreenUnits, float> {
        static inline SpaceIDs id = SpaceIDs::ScreenUnits;

        static ScreenUnits::Matrix defaultTransform();
        static float scale();
    };
    template <> const std::string SpaceTypeNameMap<ScreenUnits>::name = "ScreenUnits";
}
#include "AffineMatrix.h"
#include "AngularType.h"
#include "Dimension2.h"
#include "NormalizedVec2.h"
#include "Point2.h"
#include "Point2.h"
#include "Poly2.h"
#include "Rect2.h"
#include "Vec2.h"

