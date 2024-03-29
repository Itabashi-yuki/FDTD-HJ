#include "fdtd.h"

void update_e_pml(double **ey, double **ez, double *Hy, double *Hz, int n){
    int NEW = n % 2;
    int OLD = (n + 1) % 2;
    double sigma_max = - (M + 1) * C0 / 2. / L / dx * log(R);

    for(int i=1; i<=L; i++){
        double sigma_x = sigma_max * pow((L * dx - i * dx) / L / dx, M);

        ey[NEW][i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1 /dt + sigma_x / 2.0 ) * ey[OLD][i]
                     - 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / EPS0 / dx * ( Hz[i] - Hz[i-1]);
        ez[NEW][i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1 /dt + sigma_x / 2.0 ) * ez[OLD][i]
                     + 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / EPS0 / dx * ( Hy[i] - Hy[i-1]);
    }

    for(int i=Nx-L; i<Nx; i++){
        double sigma_x = sigma_max * pow((i * dx - (Nx - L) * dx) / L / dx, M);

        ey[NEW][i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1.0 /dt + sigma_x / 2.0 ) * ey[OLD][i]
                     - 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / EPS0 / dx * ( Hz[i] - Hz[i-1]);
        ez[NEW][i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1.0 /dt + sigma_x / 2.0 ) * ez[OLD][i]
                     + 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / EPS0 / dx * ( Hy[i] - Hy[i-1]);
    }
}