#include "fdtd.h"
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iostream>

constexpr double M2KM{1e-3}; /* z[m] -> [km] */

double nu(const double z){ /* 衝突周波数の計算 */
    return 4.303e11 * exp (-0.1622 * z * M2KM); 
}

double omg_p(const double Ne){ /* Ne [m^-3] からプラズマ周波数を計算 */
  return sqrt( Ne * CHARGE_e * CHARGE_e / ( MASS_e * EPS0 ) );
}

void initialize_plasma(Eigen::Matrix3d *S, Eigen::Matrix3d *B, double Ne_alt, double nu_alt){
    /*電子密度の設定*/
    double *Alt = new double [Nx]; /*[km]*/
    double *Ne = new double [Nx];  /*[m^-3]*/
    std::ifstream ifs("Ne.dat");
    
    for(int i = Nx_iono_lower; i <= Nx; i++){
        ifs >> Alt[i] >> Ne[i];
    }

    /* 入力ファイルの高度と解析領域における位置のズレの修正
       現実的な解析領域にすれば、必要ない */
    int Ne_alt_int = int(90 +  2 * (Ne_alt - 60));

    /* 入力した高度Ne_alt[m]での一様な電子密度分布の設定 */
    double Ne_const = Ne[Ne_alt_int];
    std::cout << "Ne = " << Ne_const << std::endl;

    // double Ne_const = 3.91935e+07; //高度60kmでの電子密度
    // double Ne_const = 6.16177e+07; //高度62.5kmでの電子密度
    // double Ne_const = 9.47739e+07; //高度65kmでの電子密度
    // double Ne_const = 1.72003e+08; //高度67.5kmでの電子密度
    // double Ne_const = 2.37686e+08; //高度70kmでの電子密度
    // double Ne_const = 3.74176e+08; //高度75kmでの電子密度
    
    /* 入力した高度nu_alt[m]での一様な衝突周波数の設定 */
    double nu_const = nu(nu_alt * 1.0e3); 

    for(int i = Nx_iono_lower; i <= Nx_iono_upper; i++){
        /* 高度z[m] 入力した電子密度分布ファイルの高度と解析領域におけるプラズマ領域のズレから20000[m]を足している。修正必須 */
        // double z = i * dx + 20000; 

        /* 高度によった分布を用いているものをコメントアウト */
        // double Omg_0 = 1 / dt + nu(z) / 2.;
        double Omg_0 = 1 / dt + nu_const / 2.;
        
        // double Omg_0_prime = 1 / dt - nu(z) / 2.;
        double Omg_0_prime = 1 / dt - nu_const / 2.;
        
        const double Omg_c{CHARGE_e * 50000e-9 / MASS_e}; /* F0 = 50000[nT]にしている */ 
        
        // double Omg_p = omg_p(Ne[i]);
        double Omg_p = omg_p(Ne_const);
        
        // std::cout << "Omg_p" << " " << i * dx * 1e-3 << " " << Omg_p << std::endl;

        Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
        Eigen::Matrix3d A, R1, R2;
        Eigen::Vector3d b;
        
        const double THETA = M_PI / 4;
        const double PHI = M_PI / 4;

        b << std::sin(THETA) * std::cos(PHI) , std::sin(THETA) * std::sin(PHI), std::cos(THETA);
    
        R2 << 0, b(2), -b(1),
            -b(2), 0, b(0),
            b(1), -b(0), 0;
    
        R1 = Omg_c / 2. * R2;

        A = Omg_0 * I + R1;

        S[i] = A.inverse() * (Omg_0_prime * I - R1);
        B[i] = EPS0 * Omg_p * Omg_p * A.inverse();
    }

    // std::ofstream ofs_S("./check/S.dat");
    // std::ofstream ofs_B("./check/B.dat");
    // for(int i = Nx_iono_lower; i <= Nx_iono_upper; i++){
    //     ofs_S << i * dx * 1e-3 << " " << S[i] << std::endl;
    //     ofs_B << i * dx * 1e-3 << " " << B[i] << std::endl;
    // }
    
    // ofs_S.close();
    // ofs_B.close();

    delete [] Alt;
    delete [] Ne;

}