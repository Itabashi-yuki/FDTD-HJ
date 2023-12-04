#include <iostream>
#include <fstream>
#include <string>
#include "fdtd.h"

void output_ez(double *Ez, const int n){

  std::ofstream ofs_Ez("./data/Ez_" + std::to_string(n) + ".dat");

  for(int i = 0; i <= Nx; i++){
    double x = i * dx;
    ofs_Ez << x << " " << Ez[i] << " " << "\n";
  }
  ofs_Ez.close();
}
