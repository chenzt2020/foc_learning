#include "foc.h"
#include <fstream>
int main()
{
    FOC foc;
    std::ofstream fout("test_foc.csv");
    for (double theta = 0; theta < 7; theta += 1e-3) {
        foc.u_d = 0.1;
        foc.u_q = 0;
        foc.theta = theta;
        foc.ipark();
        foc.svpwm();
        double u_a = foc.t_a - 0.5 * (foc.t_b + foc.t_c);
        double u_b = foc.t_b - 0.5 * (foc.t_a + foc.t_c);
        double u_c = -(u_a + u_b);
        fout << foc.t_a << ',' << foc.t_b << ',' << foc.t_c << '\n';
        // fout << u_a << ',' << u_b << ',' << u_c << '\n';
    }
}
