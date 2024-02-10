#include "fdtd.h"
#include <iostream>
#include <fstream>
#include <string>

void output_time(double n, double Ne_alt, double nu_alt){
    std::ofstream ofs_time("./data/threshold_crossing_time_x.dat", std::ios::app);

    ofs_time << Ne_alt << " " << nu_alt << " " << n * dt << std::endl;
}