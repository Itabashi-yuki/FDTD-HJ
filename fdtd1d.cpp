#include "fdtd.h"

int main(){
    double *Ez = new double [Nx+1];
    double *Hy = new double [Nx];

    initialize(Ez, Hy); /*初期値設定*/

    for(int n = 1; n < 200; n++){
      update_e(Ez, Hy);
      update_e_pml(Ez, Hy);
      update_h(Hy, Ez);
      update_h_pml(Hy, Ez);

      output_ez(Ez, n);
    }

    delete [] Ez;
    delete [] Hy;

}
