#include "fdtd.h"

void update_E(double *Ex, double *Ey, double *Ez, double *Hy, double *Hz, double **Jex, double **Jey, double **Jez, int n){
  int NEW = n % 2;
  int OLD = (n+1) % 2;

  for(int i = L + 1; i < Nx - L; i++){ /*プラズマ領域*/ 
    Ex[i] = Ex[i] - dt / EPS0 * Jex[OLD][i];
    Ey[i] = Ey[i] - dt / EPS0 / dx * (Hz[i] - Hz[i-1]) - dt / EPS0 * Jey[OLD][i];
    if(i != int(source_x / dx)){
      Ez[i] = Ez[i] + dt / EPS0 / dx * (Hy[i] - Hy[i-1]) - dt / EPS0 * Jez[OLD][i];
    } else {
      Ez[i] = Ez[i] + dt / EPS0 / dx * (Hy[i] - Hy[i-1]);
    }
  }  

}
