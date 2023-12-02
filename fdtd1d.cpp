#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "fdtd.h"

int main(){
    double *Ez = new double [Nx+1];
    double *Hy = new double [Nx];

    /*初期値設定*/
    for(int i = 1; i < Nx; i++){
        double x = i * dx;
        Ez[i] = std::exp(-(x-Rx/2.)*(x-Rx/2.)/2/0.1/0.1);
        Hy[i] = 0.;
    }
    Ez[0] = 0.;
    Ez[Nx] = 0.;
    Hy[0] = 0.;

    for(int n = 1; n < 200; n++){
        for(int i = 1; i < Nx; i++){
            Ez[i] = Ez[i] + dt / EPS0 / dx * (Hy[i] - Hy[i-1]);   
        }
        for(int i = 0; i < Nx; i++){
            Hy[i] = Hy[i] + dt / MU0 / dx * (Ez[i+1] - Ez[i]);
        }

        std::ofstream ofs_Ez("./data/Ez_" + std::to_string(n) + ".dat");
        for(int i = 0; i < Nx+1; i++){
            double x = i * dx;
            ofs_Ez << x << " " << Ez[i] << " " << "\n";
        }
        ofs_Ez.close();
    }

    delete [] Ez;
    delete [] Hy;

}