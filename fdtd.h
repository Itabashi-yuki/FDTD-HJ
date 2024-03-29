#include <cmath>
#include <eigen3/Eigen/Dense>

extern std::string global_dirName;

constexpr double C0{3.0e8};
constexpr double MU0{4.0 * M_PI *1.0e-7};
constexpr double EPS0{1.0 / MU0 / C0 / C0};
constexpr double CHARGE_e{-1.602e-19}; //[C]
constexpr double MASS_e{9.109e-31};     //[kg]
constexpr double B0{50000e-9}; 
// constexpr double B0{0.0}; 

// constexpr double Rx{100.0e3}; /*解析領域の長さ*/
constexpr double Rx{2.0e5}; /*解析領域の長さ*/
// constexpr double dx{0.25e3}; /*x方向セルサイズ*/
constexpr double dx{0.125e3}; /*x方向セルサイズ*/

constexpr int Nx{int(Rx/dx)}; /*総セル数*/
// constexpr double dt{ 0.001 * 0.9999 * dx / C0 };
constexpr double dt{  0.999 * dx / C0 };
constexpr double dt_p{  dt / 2.0 }; /*プラズマ中のdt*/
// constexpr double Tmax { 0.003 };
// constexpr double Tmax { 0.00085 };
// constexpr int Nt { int(Tmax/dt) };
constexpr int Nt { 5000 };

constexpr double Rx_iono_lower {65.0e3};
constexpr int Nx_iono_upper{Nx};
// constexpr int Nx_iono_lower{Nx / 2 - 10};
constexpr int Nx_iono_lower{int(Rx_iono_lower / dx)};
constexpr int Nx_iono{Nx_iono_upper - Nx_iono_lower + 1};

/* PMLパラメタ*/
constexpr double M{3.5};
constexpr double R{1.0e-6};
constexpr int L{8};

// constexpr double Sx { 20.0e3 };
// constexpr double sigma { 3.0e3 };

constexpr double obs_x1 { 60.0e3 }; /* [km] */
constexpr double obs_x2 { 65.0e3 }; /* [km] */
constexpr double obs_x3 { 150.0e3 }; /* [km] */

/*電流源パラメタ*/
constexpr double f0 { 40.0e3 };
constexpr double dx_0 { 500 };
constexpr double Dt0 { dx_0 / C0 };
constexpr double sigma { 70 * Dt0 };
constexpr double t0 { 4.0 * sigma };
constexpr double source_x { 50.0e3 };

/* Prototype */
void initialize(double *Ex, double *Ey, double *Ez, double **ey, double **ez, double *Hy, double *Hz, double **Jex, double **Jey, double **Jez, Eigen::Matrix3d *S, Eigen::Matrix3d *B);

void update_E(double *Ex, double *Ey, double *Ez, double *Hy, double *Hz, double **Jex, double **Jey, double **Jez, int n);

void update_E_pml(double *Ex, double *Ey, double *Ez, double **ey, double **ez, double *Hy, double *Hz, double **Jex, double **Jey, double **Jez, int n);

void update_H(double *Hy, double *Hz, double *Ey, double *Ez);

void update_H_pml(double *Hy, double *Hz, double *Ey, double *Ez);

void update_e_pml(double **ey, double **ez, double *Hy, double *Hz, int n);

void update_j(double **Jex, double **Jey, double **Jez, double *Ex, double *Ey, double *Ez, Eigen::Matrix3d *S, Eigen::Matrix3d *B, int n);

void initialize_plasma(Eigen::Matrix3d *S, Eigen::Matrix3d *, double Ne_alt, double nu_alt);

void output_E(double *Ex, double *Ey, double *Ez, double *Hy, double *Hz, double **Jex, double **Jey, double **Jez, const int n, double Ne_alt, double nu_alt);

double cal_Jz(double t);

void make_dir();

void output_pal();