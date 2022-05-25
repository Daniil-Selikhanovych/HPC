#ifndef PBH_INCLUDED
#define PBH_INCLUDED

#include <cstdlib>
#include <ctime>

#include "box.hpp"

class PeriodicBox : public Box
{
public:
	double walls_size;
public:
	PeriodicBox(double size_of_box, double dt, double default_themperature, double delta_themperature)
		: Box(dt, default_themperature, delta_themperature)
	{
		walls_size = size_of_box;
	};

    virtual double calc_forces();
    virtual void move();
	virtual void generate_crystal(double ro);
	virtual void generate_random_crystal(double ro, double correlation);
};

double PeriodicBox::calc_forces()
{
	clear_forces();
	double potential_energy = 0;
	#if defined(PARALLEL)
	#pragma omp parallel for reduction(+:potential_energy) schedule(dynamic, 20)
	for (size_t i = 0; i < size(); i++)
		for (size_t j = 0; j < size(); j++) {
			if (i == j)
				continue;
	#else
	for (size_t i = 1; i < size(); i++)
		for (size_t j = 0; j < i; j++) {
	#endif
			vector3d rr = (*this)[i].r - (*this)[j].r;
			rr.balance(walls_size);

			double dist2 = rr.length_sqr();

			rr *= 4 * (6.0 / fast_pow(dist2, 4) - 12.0 / fast_pow(dist2, 7));
			#if defined(PARALLEL)
			(*this)[i].f -= rr;
			if (i < j)
				potential_energy += 4 * ((1.0 / fast_pow(dist2, 6)) - (1.0 / fast_pow(dist2, 3)));
			#else
			(*this)[i].f -= rr; (*this)[j].f += rr;
			potential_energy += 4 * ((1.0 / fast_pow(dist2, 6)) - (1.0 / fast_pow(dist2, 3)));
			#endif
		}
	return potential_energy;
}

inline void PeriodicBox::move()
{
	#if !defined(PARALLEL)
	for (auto & particle: *this) {
        // std::cout << "Not use OpenMP \n" << std::endl;
		particle.move(dt);
		particle.r.balance(walls_size);
	}
    #else
	#pragma omp parallel for schedule(static)
	for (size_t i = 0; i < size(); i++) {
        // std::cout << "Use OpenMP \n" << std::endl;
        // int num_used_threads = omp_get_num_threads();
        // std::cout << "Use OpenMP with " << num_used_threads << " threads\n" << std::endl;
		(*this)[i].move(dt);
        (*this)[i].r.balance(walls_size);
	}
	#endif
}

void PeriodicBox::generate_crystal(double ro)
{
	int count = walls_size * walls_size * walls_size * ro;
    std::cout << "Number of particles = " << count << std::endl;

	int cube = 1;
	while (cube * cube * cube < count) cube++;
    double dist = walls_size / cube;
    (*this).clear();

	vector3d location;
	for (int i = 0; i < cube && count > 0; i++)
		for (int j = 0; j < cube && count > 0; j++)
			for (int k = 0; k < cube && count > 0; k++) {
				location = vector3d(-walls_size / 2 + dist * i,
									-walls_size / 2 + dist * j,
									-walls_size / 2 + dist * k);
				push_back(Particle(location));
				count--;
			}

}

void PeriodicBox::generate_random_crystal(double ro, double correlation)
{
	generate_crystal(ro);
	srand(time(0));
	std::function<double()> __rand = [correlation]() -> double
						{ return (double)(rand() % 2001 - 1000) * correlation / 1000; };

    for (auto particle: *this) {
		particle.r.x += __rand();
		particle.r.y += __rand();
		particle.r.z += __rand();
    }
}



#endif // PBH_INCLUDED
