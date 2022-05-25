#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <thread>
#include <iomanip>
#include <omp.h>

#include "box.hpp"
#include "periodic_box.hpp"
#include "plotter.hpp"

int main(void)
{
    double T = 1.38;
    double ro = 1.0;
    int steps = 100000;
    bool enable_thermostat = true;

    double walls_size = 6; // Box size
    double delta_time = 0.001;
    double delta_themperature = 0.0001;
    double correlation = 0.1;

    #if defined(PARALLEL)
        int num_threads = 8;
        omp_set_num_threads(num_threads);
        std::cout << "Use OpenMP with num threads = " << num_threads << std::endl;;
    #else
        std::cout << "Not use OpenMP" << std::endl;
    #endif

    srand(time(0));
    std::ios::sync_with_stdio(false);
    std::fstream log;
    log.open("core_logs_not_parallel.log", std::ios::out);

    PeriodicBox B(walls_size, delta_time, T, 4 * delta_themperature);
    B.generate_random_crystal(ro, correlation);
    B.clear_forces();
    B.init_leapfrog();

    double potential_energy, kinetic_energy;
    bool __cur_thermostat = enable_thermostat;
    int ps = 0, ps_old = 0;
    clock_t start, end;
    start = clock();
    for (int step = 0; step < steps; step++)
    {
        B.move();
        potential_energy = B.calc_forces() / B.size();
        kinetic_energy = B.calc_v() / B.size();

        if (__cur_thermostat)
        {
            B.themperature_balance();
            if (step * 8 == steps)
                B.delta_themperature = 2 * delta_themperature;
            if (step * 4 == steps)
                B.delta_themperature = delta_themperature;
            if (step * 2 == steps)
                __cur_thermostat = false;
        }
        log << step << " " << potential_energy << " " << kinetic_energy
            << " " << potential_energy + kinetic_energy << std::endl;
        log.flush();

        ps = step * 100 / steps;
        if (ps != ps_old || step == 0)
        {
            std::cout << "\rProgress: " << ps << "%" <<  ", potential energy = "
                      << std::setprecision(3) << std::setw(6) << potential_energy << ", kinetic energy = " << std::setprecision(3) << std::setw(6) << kinetic_energy;
            std::cout.flush();
            ps_old = ps;
        }
    }
    std::cout << "\nCompleted!" << std::endl;
    end = clock();
    printf("Computation time: %.1f seconds.\n", (double)(end - start)/CLOCKS_PER_SEC);

    log.close();

    log.open("core_not_parallel_logs_runtime.log",  std::ios_base::app | std::ios::out);
    log << "Computation time: " << (double)(end - start)/CLOCKS_PER_SEC << " seconds.\n";
    log.close();

    return 0;
}