#include "fdtd.h"

void update_e_pml(double *Ez, double *Hy){
    double sigma_max = - (M + 1) * C0 / 2. / L / dx * log(R);

    for(int i=1; i<=L; i++){
        double sigma_x = sigma_max * pow((L * dx - i * dx) / L / dx, M);
        Ez[i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1.0 / dt + sigma_x / 2.0 ) * Ez[i] + 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / EPS0 / dx * ( Hy[i] - Hy[i-1] );
    }

    for(int i=Nx-L; i<Nx; i++){
        double sigma_x = sigma_max * pow((i * dx - (Nx - L) * dx) / L / dx, M);
        Ez[i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1.0 / dt + sigma_x / 2.0 ) * Ez[i] + 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / EPS0 / dx * ( Hy[i] - Hy[i-1] );
    }

}
