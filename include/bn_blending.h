#ifndef BN_BLENDING_H
#define BN_BLENDING_H

#include "bn_fixed.h"

namespace bn::blending
{
    // Transparency (Alpha Blending)
    void set_transparency_alpha(fixed alpha);
    fixed transparency_alpha();

    // Fade Intensity (White/Black fade)
    // In standard Butano, this controls the intensity of the fade color.
    // For this port, we will store the value to allow logic to compile,
    // though rendering it requires a fullscreen overlay (not implemented here).
    void set_intensity_alpha(fixed alpha);
    fixed intensity_alpha();

    // Stub for setting fade color type (optional but common)
    void set_fade_alpha(fixed alpha);
}

#endif