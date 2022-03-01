#ifndef COLOR_HPP
#define COLOR_HPP

struct Color
{
  float r;
  float g;
  float b;
  float a{255.0f};
};

namespace Colors
{
  const Color Black{Color{0.0f, 0.0f, 0.0f}};
  const Color White{Color{255.0f, 255.0f, 255.0f}};
  const Color Gray{Color{127.5f, 127.5f, 127.5f}};
  const Color Red{Color{255.0f, 0.0f, 0.0f}};
  const Color Green{Color{0.0f, 255.0f, 0.0f}};
  const Color Blue{Color{0.0f, 0.0f, 255.0f}};
  const Color Yellow{Color{255.0f, 255.0f, 0.0f}};
}

#endif