#include "fdtd.h"
#include <eigen3/Eigen/Dense>
#include <iostream>

void update_j(double *Jex_new, double *Jey_new, double *Jez_new, double *Jex_old, double *Jey_old, double *Jez_old, double *Ex, double *Ey, double *Ez, Eigen::Matrix3d *S, Eigen::Matrix3d *B){
    for(int i = Nx_iono_lower; i <= Nx_iono_upper; i++){ /*プラズマ領域の開始地点から終わりまで*/
        Jex_old[i] = Jex_new[i];
        Jey_old[i] = Jey_new[i];
        Jez_old[i] = Jez_new[i];

        Jex_new[i] = S[i](0,0) * Jex_old[i] + S[i](0,1) * Jey_old[i] + S[i](0,2) * Jez_old[i] + B[i](0,0) * Ex[i] + B[i](0,1) * Ey[i] + B[i](0,2) * Ez[i];
        Jey_new[i] = S[i](1,0) * Jex_old[i] + S[i](1,1) * Jey_old[i] + S[i](1,2) * Jez_old[i] + B[i](1,0) * Ex[i] + B[i](1,1) * Ey[i] + B[i](1,2) * Ez[i];
        Jez_new[i] = S[i](2,0) * Jex_old[i] + S[i](2,1) * Jey_old[i] + S[i](2,2) * Jez_old[i] + B[i](2,0) * Ex[i] + B[i](2,1) * Ey[i] + B[i](2,2) * Ez[i];

    }
}