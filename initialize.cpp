#include <cmath>
#include "fdtd.h"
#include <eigen3/Eigen/Dense>

void initialize(double *Ex, double *Ey, double *Ez, double *Hy, double *Hz, double *Jex_new, double *Jey_new, double *Jez_new, Eigen::Matrix3d *S, Eigen::Matrix3d *B){
    for(int i = 1; i < Nx; i++){
        double x = i * dx * 1e-3;
        Ex[i] = std::exp(-(x-Nx/10)*(x-Nx/10)/2/2/2);
        Ey[i] = std::exp(-(x-Nx/10)*(x-Nx/10)/2/2/2);
        Ez[i] = std::exp(-(x-Nx/10)*(x-Nx/10)/2/2/2);
        Hy[i] = 0.;
        Hz[i] = 0.;
        Jex_new[i] = 0.;
        Jey_new[i] = 0.;
        Jez_new[i] = 0.;
    }

    for(int i = 0; i < Nx_iono; i++){
        S[i] << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
        B[i] << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
    }

    Ex[0] = 0.;
    Ex[Nx] = 0.;
    Ey[0] = 0.;
    Ey[Nx] = 0.;
    Ez[0] = 0.;
    Ez[Nx] = 0.;
    Hy[0] = 0.;
    Hz[0] = 0.;
}
