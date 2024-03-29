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

void output_E(double *Ex, double *Ey, double *Ez, double *Hy, double *Hz, double **Jex, double **Jey, double **Jez, const int n, double Ne_alt, double nu_alt){
  int NEW = n % 2;
  int OLD = (n + 1) % 2;

  std::ofstream ofs_E("./data/" + global_dirName + "/E_" + std::to_string(n) + ".dat");
  
  for(int i = 0; i <= Nx; i++){
    double x = i * dx * 1e-3;
    ofs_E << x << " " << Ex[i] << " " << Ey[i] << " " << Ez[i] <<  "\n";
  }

  ofs_E.close();
}
