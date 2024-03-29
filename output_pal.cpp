#include <iostream>
#include <fstream>
#include "fdtd.h"

void output_pal(){
    std::ofstream ofs_pal("data/"+ global_dirName +"/pal.dat");

    ofs_pal << "omg_0とomg_primeの式変形をした" << std::endl;
    ofs_pal << std::endl;
    ofs_pal << "Rx = " << Rx << std::endl;
    ofs_pal << "dx = " << dx << std::endl;
    ofs_pal << "dt = " << dt << std::endl;
    ofs_pal << "dt_p = " << dt_p << std::endl;
    ofs_pal << "Tmax = " << dt * Nt << std::endl;
    ofs_pal << "Rx_iono_lower = " << Rx_iono_lower << std::endl;
    ofs_pal << std::endl;
    ofs_pal << "--- PMLパラメタ ---" << std::endl;
    ofs_pal << "M = " << M << std::endl;
    ofs_pal << "R = " << R << std::endl;
    ofs_pal << "L = " << L << std::endl;
    ofs_pal << std::endl;
    ofs_pal << "--- 電流源パラメタ ---" << std::endl;
    ofs_pal << "f0 = " << f0 << std::endl;
    ofs_pal << "dx_0 = " << dx_0 << std::endl;
    ofs_pal << "Dt0 = " << Dt0 << std::endl;
    ofs_pal << "sigma = " << sigma << std::endl;
    ofs_pal << "t0 = " << t0 << std::endl;
    ofs_pal << "source_x = " << source_x << std::endl;

    ofs_pal.close();
}