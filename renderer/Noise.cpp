#include "Noise.hpp"

bool Noise::initializeP()
{
  for (int i = 0; i < 256; i++)
    Noise::p[256 + i] = Noise::p[i] = Noise::permutation[i];
  return true;
}

double Noise::fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }

double Noise::grad(int hash, double x, double y, double z)
{
  int h = hash & 15;
  double u = h < 8 ? x : y,
         v = h < 4 ? y : h == 12 || h == 14 ? x
                                            : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double Noise::Perlin(double x, double y, double z)
{
  int X{(int)floor(x) & 255},
      Y{(int)floor(y) & 255},
      Z{(int)floor(z) & 255};
  x -= floor(x);
  y -= floor(y);
  z -= floor(z);
  double u{Noise::fade(x)},
      v{Noise::fade(y)},
      w{Noise::fade(z)};
  int A{Noise::p[X] + Y}, AA{Noise::p[A] + Z}, AB{Noise::p[A + 1] + Z},
      B{Noise::p[X + 1] + Y}, BA{Noise::p[B] + Z}, BB{Noise::p[B + 1] + Z};

  return std::lerp(
      std::lerp(
          std::lerp(
              Noise::grad(Noise::p[AA], x, y, z),
              Noise::grad(Noise::p[BA], x - 1, y, z),
              u),
          std::lerp(
              Noise::grad(Noise::p[AB], x, y - 1, z),
              Noise::grad(Noise::p[BB], x - 1, y - 1, z),
              u),
          v),
      std::lerp(
          std::lerp(
              Noise::grad(Noise::p[AA + 1], x, y, z - 1),
              Noise::grad(Noise::p[BA + 1], x - 1, y, z - 1),
              u),
          std::lerp(
              Noise::grad(Noise::p[AB + 1], x, y - 1, z - 1),
              Noise::grad(Noise::p[BB + 1], x - 1, y - 1, z - 1),
              u),
          v),
      w);
}