#include "fdtd.h"
#include <eigen3/Eigen/Dense>
#include <iostream>

void update_j(double **Jex, double **Jey, double **Jez, double *Ex, double *Ey, double *Ez, Eigen::Matrix3d *S, Eigen::Matrix3d *B, int n){
    for(int i = Nx_iono_lower; i < Nx; i++){ /*プラズマ領域の開始地点から終わりまで*/
        int NEW = n % 2;
        int OLD = (n + 1) % 2;

        Jex[NEW][i] = S[i](0,0) * Jex[OLD][i] + S[i](0,1) * Jey[OLD][i] + S[i](0,2) * Jez[OLD][i]
                     + B[i](0,0) * Ex[i] + B[i](0,1) * Ey[i] + B[i](0,2) * Ez[i];
        Jey[NEW][i] = S[i](1,0) * Jex[OLD][i] + S[i](1,1) * Jey[OLD][i] + S[i](1,2) * Jez[OLD][i]
                     + B[i](1,0) * Ex[i] + B[i](1,1) * Ey[i] + B[i](1,2) * Ez[i];
        Jez[NEW][i] = S[i](2,0) * Jex[OLD][i] + S[i](2,1) * Jey[OLD][i] + S[i](2,2) * Jez[OLD][i]
                     + B[i](2,0) * Ex[i] + B[i](2,1) * Ey[i] + B[i](2,2) * Ez[i];

    }
}