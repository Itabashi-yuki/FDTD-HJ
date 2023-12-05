#include <cmath>
#include "fdtd.h"

void initialize(double *Ez, double *Hy){
    for(int i = 1; i < Nx; i++){
        double x = i * dx;
        Ez[i] = std::exp(-(x-Rx/2.)*(x-Rx/2.)/2/0.1/0.1);
        Hy[i] = 0.;
    }
    Ez[0] = 0.;
    Ez[Nx] = 0.;
    Hy[0] = 0.;
}
