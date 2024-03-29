#include "fdtd.h"

void update_H_pml(double *Hy, double *Hz, double *Ey, double *Ez){
    double sigma_max = - (M + 1) * C0 / 2. / L / dx * log(R);

    for(int i=0; i<L; i++){
        double sigma_x = sigma_max * pow((L * dx - (i+0.5) * dx) / L / dx, M);

        Hy[i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1.0 / dt + sigma_x / 2.0 ) * Hy[i]
                 + 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / MU0 / dx * ( Ez[i+1] - Ez[i] );
        Hz[i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1.0 / dt + sigma_x / 2.0 ) * Hz[i]
                 - 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / MU0 / dx * ( Ey[i+1] - Ey[i] );
    }

    for(int i=Nx-L; i<Nx; i++){
        double sigma_x = sigma_max * pow(((i+0.5) * dx - (Nx - L) * dx) / L / dx, M);
 
        Hy[i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1.0 / dt + sigma_x / 2.0 ) * Hy[i]
                 + 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / MU0 / dx * ( Ez[i+1] - Ez[i] );
        Hz[i] = ( 1.0 / dt - sigma_x / 2.0 ) / ( 1.0 / dt + sigma_x / 2.0 ) * Hz[i]
                 - 1.0 / ( 1.0 / dt + sigma_x / 2.0 ) / MU0 / dx * ( Ey[i+1] - Ey[i] );    
}

}