#include "include.h"
#include "Space2D.h"

namespace Space2D {
    GameUnits::Matrix GameUnits::defaultTransform() {
        return GameUnits::Matrix();
    }

    PixelUnits::Matrix PixelUnits::defaultTransform() {
        return PixelUnits::Matrix().scale(60.0_percent, 60.0_percent);
    }

    ScreenUnits::Matrix ScreenUnits::defaultTransform() {
        return ScreenUnits::Matrix().scale(60.0_percent, 60.0_percent);
    }


    double GameUnits::scale() {
        return 1.0;
    }

    float PixelUnits::scale() {
        return 60.0;
    }

    float ScreenUnits::scale() {
        return 60.0;
    }

    GameUnits::Matrix GameUnits::transform_ratio = GameUnits::defaultTransform();
    PixelUnits::Matrix PixelUnits::transform_ratio = PixelUnits::defaultTransform();
    ScreenUnits::Matrix ScreenUnits::transform_ratio = ScreenUnits::defaultTransform();
}