#include <cmath>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <fstream>

#include "plotter.hpp"
#include "box.hpp"
#include "periodic_box.hpp"

void test()
{
	std::fstream log;
	std::ios::sync_with_stdio(false);

	log.open("/home/alexander/oldhome/md2.log", std::ios::out);

    // double ro = 0.6;
    //PeriodicBox B(10, 0.005, 1.3, 0.0001);
    PeriodicBox B(6, 0.001, 1.3, 0.0001);
    //Box B(0.0005);
/*
    vector3d location;

    int c = 0, clim = B.walls_size * B.walls_size * B.walls_size * ro;
    for (double i = -B.walls_size / 2; i < B.walls_size / 2 && c < clim; i++)
		for (double j = -B.walls_size / 2; j < B.walls_size / 2 && c < clim; j++)
			for (double k = -B.walls_size / 2; k < B.walls_size / 2 && c < clim; k++)
			{
				location = vector3d(i, j, k);
				B.push_back(Particle(location));
				c++;
			}
*/
	B.generate_crystal(0.6);
    B.clear_forces();
    B.init_leapfrog();

    double e1, e2;

	bool enable_thermostat = true;
	#define STEPS 20000
    for (int i = 0; i < STEPS; i++)
    {
        B.move();
        e1 = B.calc_forces();
        e2 = B.calc_v();
        e1 /= B.size();
        e2 /= B.size();

        if (enable_thermostat)
			B.themperature_balance();

		if (i * 2 == STEPS)
			enable_thermostat = false;

		log << i << " " << e1 << " " << e2 << " " << e1 + e2 << std::endl;
		log.flush();
        if (i % 1000 == 0)
			std::cout << i << std::endl;

    }

    log.close();
}

