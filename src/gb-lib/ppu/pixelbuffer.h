#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <array>
#include <cstdint>

#include "ppu_constants.h"

template <class T, size_t Width, size_t Height> class PixelBuffer {
public:
  PixelBuffer() = default;

  const T* data() const;

  T& at(size_t x, size_t y);
  const T& at(size_t x, size_t y) const;

  size_t width() const;
  size_t height() const;
  size_t size() const;

private:
  static size_t transformCoords(size_t x, size_t y);

  std::array<T, Width * Height> data_;
};

template <class T, size_t Width, size_t Height> inline auto PixelBuffer<T, Width, Height>::data() const -> const T*
{
  return data_.data();
}

template <class T, size_t Width, size_t Height> inline auto PixelBuffer<T, Width, Height>::at(size_t x, size_t y) -> T&
{
  return data_[transformCoords(x, y)];
}

template <class T, size_t Width, size_t Height>
inline auto PixelBuffer<T, Width, Height>::at(size_t x, size_t y) const -> const T&
{
  return data_[transformCoords(x, y)];
}

template <class T, size_t Width, size_t Height> inline size_t PixelBuffer<T, Width, Height>::width() const
{
  return Width;
}

template <class T, size_t Width, size_t Height> inline size_t PixelBuffer<T, Width, Height>::height() const
{
  return Height;
}

template <class T, size_t Width, size_t Height> inline size_t PixelBuffer<T, Width, Height>::size() const
{
  return Width * Height;
}

template <class T, size_t Width, size_t Height>
inline auto PixelBuffer<T, Width, Height>::transformCoords(size_t x, size_t y) -> size_t
{
  return (x > Width || y > Height) ? 0U : (y * Width) + x;
}

struct Rgb {
  uint8_t a = 0xFFU;
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

using GbPixelBuffer = PixelBuffer<Rgb, LcdWidth, LcdHeight>;

#endif // PIXELBUFFER_H
