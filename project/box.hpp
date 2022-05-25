#ifndef BOX_HPP_INCLUDED
#define BOX_HPP_INCLUDED

#include <cmath>
#include <vector>
#include <functional>
#include <regex>
#include <exception>

#include "particle.hpp"
#include "vector3d.hpp"

class Box : public std::vector< Particle >
{
public:
    double dt;
	double themperature, default_themperature, delta_themperature;

public:
    static constexpr inline double fast_pow(double x, int n)
    {
        double result = 1;
        while (n) {
            if (n & 1) { n ^= 1; result *= x; }
            else { n >>= 1; x *= x; }
        }
        return result;
    }

    Box (double dt) : dt(dt) {}
    Box (double dt, double default_themperature, double delta_themperature) :
				dt(dt), default_themperature(default_themperature), delta_themperature(delta_themperature) {};

    virtual void clear_forces();
    virtual double calc_forces();
	virtual void move();
    virtual double calc_v();
	virtual void init_leapfrog();
	virtual void dump();
	void themperature_balance();
};

void Box::clear_forces()
{
	#if !(defined(PARALLEL))
    for (auto & particle: *this)
		particle.f.x = 0, particle.f.y = 0, particle.f.z = 0;
	#else
	#pragma omp parallel for schedule(static)
	for (size_t i = 0; i < size(); i++)
		(*this)[i].f.x = 0, (*this)[i].f.y = 0, (*this)[i].f.z = 0;
	#endif
}

double Box::calc_forces()
{
	clear_forces();
	double potential_energy = 0;
	for (size_t i = 1; i < size(); i++)
		for (size_t j = 0; j < i; j++) {
			vector3d rr = (*this)[i].r - (*this)[j].r;
			double dist2 = rr.length_sqr();
			rr *= (6.0 / fast_pow(dist2, 4) - 12.0 / fast_pow(dist2, 7));
			(*this)[i].f -= rr; (*this)[j].f += rr;
			potential_energy += (1.0 / fast_pow(dist2, 6)) - (1.0 / fast_pow(dist2, 3));
		}
	return potential_energy;
}
inline void Box::move()
{
	for (auto & particle: *this)
		particle.move(dt);
}
double Box::calc_v()
{
	double kinetic_energy = 0;

	#if !defined(PARALLEL)
	for (auto & particle: *this) {
		particle.calc_v(dt);
		kinetic_energy += particle.v.length_sqr() * particle.mass / 2;
	}
	#else
	#pragma omp parallel for schedule(static) reduction(+: kinetic_energy)
	for (size_t i = 0; i < size(); i++) {
		(*this)[i].calc_v(dt);
		kinetic_energy += (*this)[i].v.length_sqr() * (*this)[i].mass / 2;
	}
	#endif

	themperature = kinetic_energy / size(); //!TODO Boltsman constant
	return kinetic_energy;
}
void Box::init_leapfrog()
{
	clear_forces();
	calc_forces();
	for (size_t i = 0; i < size(); i++) {
		(*this)[i].v += dt / (*this)[i].mass / 2 * (*this)[i].f;
		double coeff = dt * dt / 2 / (*this)[i].mass;
		for (size_t j = 0; j < size(); j++)
			if (i != j) {
				vector3d ro = (*this)[i].r - (*this)[j].r;
				double dist2 = ro.length_sqr();
				(*this)[i].v += coeff * (6.0 / fast_pow(dist2, 4) - 12.0 / fast_pow(dist2, 6)) * ro;
			}
	}
}

void Box::dump()
{
    std::cout << "Box:" << std::endl;
    for (auto & particle: *this)
		std::cout << particle << std::endl;
	std::cout << std::endl;
}

void Box::themperature_balance()
{
    if (themperature == 0) {
		for (auto & particle: *this)
			themperature += particle.v.length_sqr() * particle.mass / 2;
		themperature /= size();
	}
    double lambda = sqrt(1 + delta_themperature * (default_themperature/themperature - 1));
	for (auto & particle: *this)
        particle.v *= lambda;
}
#endif // BOX_HPP_INCLUDED
