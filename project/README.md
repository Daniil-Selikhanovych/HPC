# Particles modeling in periodic bounding box

1. Main script - ```bash run_all.sh```.
2. Requirements:
   1. C++ and OpenMP  
   2. Python: ```pip install numpy``` for mean and std calculation of time in ```calculate_mean_std.py```.
   3. GNUplot for plotting kinetic and potential energies dynamics (file ```gnuplot.gnu```)

3. Structure of the project:
   1. ```vector3d.hpp``` - file contains class ```vector3d``` which implements operations ```+, -, *``` for
   vectors in 3D space. 
   Method ```balance``` creates duplicate of the particle in case the coordinates exceeded 
   in modulis ```walls_size``` value.
   2. ```particle.hpp``` - file contains class ```Particle``` which consists of mass ```mass``` 
   and vectors ```r, v, f``` for position, velocity and force acting on the particle respectively. 
   It implements operations:
      1. ```move``` 
      2. ```calc_v```
      3. ```calc_forces```