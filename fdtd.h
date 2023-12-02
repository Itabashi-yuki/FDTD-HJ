#include <cmath>

constexpr double C0{3.0e8};
constexpr double MU0{4.0 * M_PI *1.0e-7};
constexpr double EPS0{1.0 / MU0 / C0 / C0};

constexpr double Rx{2.0}; /*解析領域の長さ*/
constexpr double dx{0.01}; /*x方向セルサイズ*/

constexpr int Nx{int(Rx/dx)}; /*総セル数*/
constexpr double dt{ 0.99 * dx / C0 };