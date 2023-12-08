#include "fdtd.h"

void update_h(double *Hy, double *Ez){
  for(int i = L; i < Nx - L; i++){
    Hy[i] = Hy[i] + dt / MU0 / dx * (Ez[i+1] - Ez[i]);
  }

}
