#include <iostream>
#include <fstream>
#include <string>
#include "fdtd.h"
#include <sstream>
#include <iomanip>

/* double型をstring型に変換したときの小数点以下の扱い (以下は小数点以下一桁まで表示) */
std::string to_string_custom(double value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << value;
    std::string str = ss.str();

    return str;
}

void output_ez(double *Ez, const int n, double Ne_alt, double nu_alt){

  std::ofstream ofs_Ez("./data/after_modifying_update_j/x/const_" + to_string_custom(Ne_alt) + "km_" + to_string_custom(nu_alt) + "km/Ez_" + std::to_string(n) + ".dat");
  // std::ofstream ofs_Ez("./test/Ez_" + std::to_string(n) + ".dat"); /*デバック用*/
  
  /* 各点における時間変化の計測 */
  std::ofstream time_change("./data/time_change/before_modifying_update_j/x/Ez_time_change_" + to_string_custom(Ne_alt) + "km_" + to_string_custom(nu_alt) + "km_Tmax_0.085.dat", std::ios::app);
  // std::ofstream time_change("./test/time_change/Ez_time_change_" + to_string_custom(Ne_alt) + "km_" + to_string_custom(nu_alt) + "km_xy.dat", std::ios::app); /*デバック用*/

  time_change << n * dt << " " << Ez[Nx_iono_lower - 20] << " " << Ez[Nx/2] << " " << Ez[Nx_iono_upper + 20] << std::endl;

  for(int i = 0; i <= Nx; i++){
    double x = i * dx * 1e-3;
    ofs_Ez << x << " " << Ez[i] << " " << "\n";
  }

  ofs_Ez.close();
}
