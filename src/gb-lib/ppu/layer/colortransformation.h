#ifndef COLORTRANSFORMATION_H
#define COLORTRANSFORMATION_H

#include <memory>
#include <unordered_map>

#include "../pixelbuffer.h"
#include "gbpalette.h"

const std::unordered_map<GbColors, Rgb> GbStdRgb
    = { { GbColors::White, { .r = 155, .g = 188, .b = 15 } }, { GbColors::LightGray, { .r = 139, .g = 172, .b = 15 } },
        { GbColors::DarkGray, { .r = 48, .g = 98, .b = 48 } }, { GbColors::Black, { .r = 15, .g = 56, .b = 15 } } };

template <typename InType, typename OutType> class ColorTransformation {
public:
  ColorTransformation(std::unordered_map<InType, OutType> mapping)
      : mapping_(std::move(mapping))
  {
  }

  auto convert(const InType in) { return mapping_[in]; }

  static std::unique_ptr<ColorTransformation<GbColors, Rgb>> makeGbStdRgb()
  {
    return std::make_unique<ColorTransformation<GbColors, Rgb>>(GbStdRgb);
  }

private:
  std::unordered_map<InType, OutType> mapping_;
};

using GbColorTransformation = ColorTransformation<GbColors, Rgb>;
using GbColorTransformationUP = std::unique_ptr<GbColorTransformation>;

#endif // COLORTRANSFORMATION_H
