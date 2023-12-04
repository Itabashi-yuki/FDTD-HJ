#include "fdtd.h"

void update_e(double *Ez, double *Hy){

  for(int i = 1; i < Nx; i++){
    Ez[i] = Ez[i] + dt / EPS0 / dx * (Hy[i] - Hy[i-1]);   
  }

}
