#include <iostream>
#include "fdtd.h"
#include <eigen3/Eigen/Dense>

int main(){
    double *Ex = new double [Nx+1];
    double *Ey = new double [Nx+1];
    double *Ez = new double [Nx+1];
    double *Hy = new double [Nx];
    double *Hz = new double [Nx];
    double *Jex_new = new double [Nx];
    double *Jey_new = new double [Nx];
    double *Jez_new = new double [Nx];
    double *Jex_old = new double [Nx];
    double *Jey_old = new double [Nx];
    double *Jez_old = new double [Nx];

    Eigen::Matrix3d *S = new Eigen::Matrix3d[Nx + 1];
    Eigen::Matrix3d *B = new Eigen::Matrix3d[Nx + 1];

    initialize(Ex, Ey, Ez, Hy, Hz, Jex_new, Jey_new, Jez_new, S, B); /*初期値設定*/

    double Ne_alt, nu_alt;
    std::cin >> Ne_alt;
    std::cin >> nu_alt;
    std::cout << "Ne_alt = " << Ne_alt << std::endl;
    std::cout << "nu_alt = " << nu_alt << std::endl;
 
    initialize_plasma(S, B, Ne_alt, nu_alt);

    bool flag = false;

    for(int n = 1; n < Nt; n++){
      update_e(Ex, Ey, Ez, Hy, Hz, Jex_new, Jey_new, Jez_new);
      update_e_pml(Ez, Hy);
      update_h(Hy, Hz, Ey, Ez);
      update_h_pml(Hy, Ez);
      update_j(Jex_new, Jey_new, Jez_new, Jex_old, Jey_old, Jez_old, Ex, Ey, Ez, S, B);

      /* 発散時間の計測 */
      if((Ez[Nx + 20] > 10 || Ez[Nx + 20] < -10) && !flag){
        std::cout << "Ez = " <<  Ez[Nx + 20] << std::endl;
        std::cout << "n =" << n << std::endl;
        std::cout << n * dt << " / " << Tmax << std::endl;
        output_time(n, Ne_alt, nu_alt);
        flag = true;
        break;
      }

      output_ez(Ez, n, Ne_alt, nu_alt);
    }

    if(!flag)
        std::cout << "発散しませんでした" << std::endl;
      

    delete [] Ex;
    delete [] Ey;
    delete [] Ez;
    delete [] Hy;
    delete [] Hz;
    delete [] Jex_new;
    delete [] Jey_new;
    delete [] Jez_new;
    delete [] Jex_old;
    delete [] Jey_old;
    delete [] Jez_old;
    delete [] S;
    delete [] B;

}
