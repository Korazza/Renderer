#include "Noise.hpp"

bool Noise::pInitialized = Noise::initializeP();

bool Noise::initializeP()
{
  for (int i{0}; i < 256; i++)
    Noise::p[256 + i] = Noise::p[i] = Noise::permutation[i];
  return true;
}

double Noise::fade(double t) { return t * t * t * (t * (t * 6.0 - 15.0) + 10.0); }

double Noise::lerp(double t, double a, double b) { return a + t * (b - a); }

double Noise::grad(int hash, double x)
{
  return (hash & 1) == 0 ? x : -x;
}

double Noise::grad(int hash, double x, double y)
{
  return ((hash & 1) == 0 ? x : -x) + ((hash & 2) == 0 ? y : -y);
}

double Noise::grad(int hash, double x, double y, double z)
{
  int h{hash & 15};
  double u{h < 8.0 ? x : y},
      v{h < 4.0 ? y : h == 12.0 || h == 14.0 ? x
                                             : z};
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double Noise::Perlin(double x)
{
  int X{(int)floor(x) & 255};

  x -= floor(x);

  double u{Noise::fade(x)};

  return Noise::lerp(u, Noise::grad(Noise::p[X], x), Noise::grad(Noise::p[X + 1], x - 1)) * 2;
}

double Noise::Perlin(double x, double y)
{
  int X{(int)floor(x) & 255},
      Y{(int)floor(y) & 255};

  x -= floor(x);
  y -= floor(y);

  double u{Noise::fade(x)},
      v{Noise::fade(y)};

  int A{(Noise::p[X] + Y) & 255},
      B{(Noise::p[X + 1] + Y) & 255};

  return Noise::lerp(
      v,
      Noise::lerp(
          u,
          Noise::grad(Noise::p[A], x, y),
          Noise::grad(Noise::p[B], x - 1, y)),
      Noise::lerp(
          u,
          Noise::grad(Noise::p[A + 1], x, y - 1),
          Noise::grad(Noise::p[B + 1], x - 1, y - 1)));
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

  return Noise::lerp(
      w,
      Noise::lerp(
          v,
          Noise::lerp(
              u,
              Noise::grad(Noise::p[AA], x, y, z),
              Noise::grad(Noise::p[BA], x - 1, y, z)),
          Noise::lerp(
              u,
              Noise::grad(Noise::p[AB], x, y - 1, z),
              Noise::grad(Noise::p[BB], x - 1, y - 1, z))),
      Noise::lerp(
          v,
          Noise::lerp(
              u,
              Noise::grad(Noise::p[AA + 1], x, y, z - 1),
              Noise::grad(Noise::p[BA + 1], x - 1, y, z - 1)),
          Noise::lerp(
              u,
              Noise::grad(Noise::p[AB + 1], x, y - 1, z - 1),
              Noise::grad(Noise::p[BB + 1], x - 1, y - 1, z - 1))));
}