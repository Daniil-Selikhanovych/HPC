#ifndef PAHPPINCLUDED
#define PAHPPINCLUDED

#include "vector3d.hpp"
#include <cmath>

class Particle
{
public:
    vector3d r, v, f;
    double mass;

    Particle() : mass(1) {};
    Particle(vector3d r) :
        r(r), mass(1) {};
    Particle(vector3d r, double mass) :
        r(r), mass(mass) {};
    Particle(vector3d r, vector3d v) :
        r(r), v(v), mass(1) {};
    Particle(vector3d r, vector3d v, double mass) :
        r(r), v(v), mass(mass) {};

    static constexpr inline double fast_pow(double x, int n)
    {
        double result = 1;
        while(n) {
            if (n & 1) { n ^= 1; result *= x; }
            else { n >>= 1; x *= x; }
        }
        return result;
    }

    inline void clear_forces()
    {
        f.x = 0, f.y = 0, f.z = 0;
    }

    inline double calc_force(Particle & other)
    {
        vector3d rr = other.r - r;
        double dist2 = rr.length_sqr();

        rr *= 4 * (6.0 / fast_pow(dist2, 4) - 12.0 / fast_pow(dist2, 7));
        f += rr;
        other.f -= rr;
        return 4 * (1.0 / fast_pow(dist2, 6)) - (1.0 / fast_pow(dist2, 3));
    }

    inline void move(double dt)
    {
        r += dt * v;
    }

    inline void calc_v(double dt)
    {
        v += dt / mass * f;
    }

    friend std::ostream & operator << (std::ostream & os, Particle & P)
    {
        os << "Particle: \n" << "     r = " << P.r <<
                        "\n     v = " << P.v << "\n     f = " << P.f << std::endl;
        return os;
    }
};

#endif
