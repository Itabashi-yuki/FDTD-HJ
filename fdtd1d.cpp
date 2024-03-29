#include <iostream>
#include <fstream>
#include "fdtd.h"
#include <eigen3/Eigen/Dense>

int main(){
    double *Ex = new double [Nx+1];
    double *Ey = new double [Nx+1];
    double *Ez = new double [Nx+1];
    double *Hy = new double [Nx];
    double *Hz = new double [Nx];
    double **ey = new double *[2];
    double **ez = new double *[2];
    double **Jex = new double*[2];
    double **Jey = new double*[2];
    double **Jez = new double*[2];
    for(int i = 0; i < 2; i++){
      ey[i] = new double[Nx+1];
      ez[i] = new double[Nx+1];
      Jex[i] = new double[Nx];
      Jey[i] = new double[Nx];
      Jez[i] = new double[Nx];
    }

    Eigen::Matrix3d *S = new Eigen::Matrix3d[Nx + 1];
    Eigen::Matrix3d *B = new Eigen::Matrix3d[Nx + 1];

    make_dir();

    initialize(Ex, Ey, Ez, ey, ez, Hy, Hz, Jex, Jey, Jez, S, B); /*初期値設定*/

    double Ne_alt, nu_alt;
    Ne_alt = nu_alt = 0.0;
    // std::cin >> Ne_alt;
    // std::cin >> nu_alt;
    // std::cout << "Ne_alt = " << Ne_alt << std::endl;
    // std::cout << "nu_alt = " << nu_alt << std::endl;
 
    initialize_plasma(S, B, Ne_alt, nu_alt);

    bool flag = false;

    std::ofstream ofs_obs("./data/" + global_dirName +  "/obs_miyajima.dat");

    for(int n = 1; n < Nt; n++){
      if(n % 1000 == 0)
        std::cout << "n = " << n << " / " << Nt << std::endl;

      double t = ( n - 0.5 ) * dt;

      update_E(Ex, Ey, Ez, Hy, Hz, Jex, Jey, Jez, n);
      update_e_pml(ey, ez, Hy, Hz, n);
      update_E_pml(Ex, Ey, Ez, ey, ez, Hy, Hz, Jex, Jey, Jez, n);
      Ez[int(source_x / dx)] -= dt / EPS0 * cal_Jz(t);

      update_H(Hy, Hz, Ey, Ez);
      update_H_pml(Hy, Hz, Ey, Ez);
      update_j(Jex, Jey, Jez, Ex, Ey, Ez, S, B, n);
      
      ofs_obs << n * dt << " " << Ez[int(obs_x1 / dx)] << " " << Ez[int(obs_x2 / dx)] << " " << Ez[int(obs_x3 / dx)] << std::endl;
      if(n % 1 == 0)
        output_E(Ex, Ey, Ez, Hy, Hz, Jex, Jey, Jez , n, Ne_alt, nu_alt);
    }

    output_pal();

    if(!flag)
        std::cout << "発散しませんでした" << std::endl;
      
    ofs_obs.close();

    delete [] Ex;
    delete [] Ey;
    delete [] Ez;

    delete [] Hy;
    delete [] Hz;
    for(int i=0; i<2; i++){
      delete [] ey[i];
      delete [] ez[i];
      delete [] Jex[i];
      delete [] Jey[i];
      delete [] Jez[i];
    }
    delete [] S;
    delete [] B;

}
