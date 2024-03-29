#include "fdtd.h"

void update_E_pml(double *Ex, double *Ey, double *Ez, double **ey, double **ez, double *Hy, double *Hz, double **Jex, double **Jey, double **Jez, int n){
    int OLD = (n + 1) % 2;

    for(int i=1; i<=L; i++){

        Ex[i] = Ex[i] - dt / EPS0 * Jex[OLD][i];
        Ey[i] = Ey[i] + ey[NEW][i] - ey[OLD][i] - dt / EPS0 * Jey[OLD][i];
        Ez[i] = Ez[i] + ez[NEW][i] - ez[OLD][i] - dt / EPS0 * Jez[OLD][i];
    }

    for(int i=Nx-L; i<Nx; i++){

        Ex[i] = Ex[i] - dt / EPS0 * Jex[OLD][i];
        Ey[i] = Ey[i] + ey[NEW][i] - ey[OLD][i] - dt / EPS0 * Jey[OLD][i];
        Ez[i] = Ez[i] + ez[NEW][i] - ez[OLD][i] - dt / EPS0 * Jez[OLD][i];

    }

}
