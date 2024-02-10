#include "fdtd.h"

void update_e(double *Ex, double *Ey, double *Ez, double *Hy, double *Hz, double *Jex_new, double *Jey_new, double *Jez_new){
  for(int i = L + 1; i < Nx_iono_lower; i++){ /*PML端からプラズマ領域端まで*/
    Ex[i] = Ex[i] - dt / EPS0;
    Ey[i] = Ey[i] - dt / EPS0 / dx * (Hz[i] - Hz[i-1]);
    Ez[i] = Ez[i] + dt / EPS0 / dx * (Hy[i] - Hy[i-1]);  
  }

  for(int i = Nx_iono_lower; i <= Nx_iono_upper; i++){ /*プラズマ領域*/ 
    Ex[i] = Ex[i] - dt / EPS0 * Jex_new[i];
    Ey[i] = Ey[i] - dt / EPS0 / dx * (Hz[i] - Hz[i-1]) - dt / EPS0 * Jey_new[i];
    Ez[i] = Ez[i] + dt / EPS0 / dx * (Hy[i] - Hy[i-1]) - dt / EPS0 * Jez_new[i];
  }
  
  for(int i = Nx_iono_upper + 1; i < Nx - L; i++){ /*プラズマ領域端からPML端まで*/
    Ex[i] = Ex[i] - dt / EPS0;
    Ey[i] = Ey[i] - dt / EPS0 / dx * (Hz[i] - Hz[i-1]);
    Ez[i] = Ez[i] + dt / EPS0 / dx * (Hy[i] - Hy[i-1]);  
  }
}
