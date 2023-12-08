#include "fdtd.h"

void update_e(double *Ez, double *Hy){
  for(int i = L + 1; i < Nx - L; i++){
    Ez[i] = Ez[i] + dt / EPS0 / dx * (Hy[i] - Hy[i-1]);   
  }

}
