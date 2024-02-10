#include <cmath>
#include <eigen3/Eigen/Dense>

constexpr double C0{3.0e8};
constexpr double MU0{4.0 * M_PI *1.0e-7};
constexpr double EPS0{1.0 / MU0 / C0 / C0};
constexpr double CHARGE_e{1.602e-19}; //[C]
constexpr double MASS_e{9.1e-31};     //[kg]

constexpr double Rx{100.0e3}; /*解析領域の長さ*/
constexpr double dx{0.5e3}; /*x方向セルサイズ*/

constexpr int Nx{int(Rx/dx)}; /*総セル数*/
constexpr double dt{ 0.1 * 0.9999 * dx / C0 };
constexpr double Tmax { 0.00085 };
// constexpr double Tmax { 0.085 };
constexpr int Nt { int(Tmax/dt) };

constexpr int Nx_iono_upper{Nx / 2 + 10};
constexpr int Nx_iono_lower{Nx / 2 - 10};
constexpr int Nx_iono{Nx_iono_upper - Nx_iono_lower + 1};

// /*えびの 緯度経度*/
// constexpr double Tx_Latitude{32.067650};
// constexpr double Tx_Longitude{130.828978};

// /* おおたかどや山 緯度経度 */
// // constexpr double Tx_Latitude { 37.372097972301226 };
// // constexpr double Tx_Longitude { 140.84913351739013 };

// /*調布 緯度経度*/
// constexpr double Rx_Latitude{35.65966};
// constexpr double Rx_Longitude{139.54328};

// constexpr int Year{2023};
// constexpr int Month{10};
// constexpr int Day{12};
// constexpr int Hour{9};
// constexpr int Min{0};

/* PMLパラメタ*/
constexpr double M{3.5};
constexpr double R{1.0e-6};
constexpr int L{10};

/* Prototype */
void initialize(double *Ex, double *Ey, double *Ez, double *Hy, double *Hz, double *Jex_new, double *Jey_new, double *Jez_new, Eigen::Matrix3d *S, Eigen::Matrix3d *B);

void update_e(double *Ex, double *Ey, double *Ez, double *Hy, double *Hz, double *Jex_new, double *Jey_new, double *Jez_new);

void update_e_pml(double *Ez, double *Hy);

void update_h(double *Hy, double *Hz, double *Ey, double *Ez);

void update_h_pml(double *Hy, double *Ez);

void update_j(double *Jex_new, double *Jey_new, double *Jez_new, double *Jex_old, double *Jey_old, double *Jez_old, double *Ex, double *Ey, double *Ez, Eigen::Matrix3d *S, Eigen::Matrix3d *B);

void initialize_plasma(Eigen::Matrix3d *S, Eigen::Matrix3d *, double Ne_alt, double nu_alt);

void output_ez(double *Ez, const int n, double Ne_alt, double nu_alt);

void output_time(double n, double Ne_alt, double nu_alt);