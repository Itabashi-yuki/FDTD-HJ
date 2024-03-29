#include <cmath>
#include "fdtd.h"
#include <eigen3/Eigen/Dense>

void initialize(double *Ex, double *Ey, double *Ez, double **ey, double **ez, double *Hy, double *Hz, double **Jex, double **Jey, double **Jez, Eigen::Matrix3d *S, Eigen::Matrix3d *B){

    for(int i = 1; i < Nx; i++){
        double x = i * dx;
        Ex[i] = 0;
        Ey[i] = 0;
        // Ez[i] = std::exp(-(x-Sx)*(x-Sx)/sigma/sigma/2.0);
        Ez[i] = 0.;
        Hy[i] = 0.;
        Hz[i] = 0.;
    }

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < Nx; j++){
            ey[i][j] = 0.;
            ez[i][j] = 0.;
            Jex[i][j] = 0.;
            Jey[i][j] = 0.;
            Jez[i][j] = 0.;
        }
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
    ey[0][Nx] = 0.;
    ey[1][Nx] = 0.;
    Hy[0] = 0.;
    Hz[0] = 0.;
}

double cal_Jz(double t){
    double Jz = 0.0;
    if(0 <= t && t < t0){
        Jz = sin( 2 * M_PI * f0 * t) * std::exp( -( t - t0 ) * ( t - t0 ) / 2.0 / sigma / sigma ) / dx;
    } else if (t0 <= t){
        Jz = sin(2 * M_PI * f0 * t) / dx;
    }
    return Jz;
}