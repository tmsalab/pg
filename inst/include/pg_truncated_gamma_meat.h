// This header file contains work done by
// (C) Nicholas Polson, James Scott, Jesse Windle, 2012-2019
// within the BayesLogit R package. This work is licensed under GPL v3 or greater.

// Modifications for header-only inclusion was done by
// (C) James Balamuta 2019 - 2020

// pg is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.

// pg is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along with
// pg.  If not, see <https://www.gnu.org/licenses/>.

#ifndef PG_TRUNCATED_GAMMA_MEAT_H
#define PG_TRUNCATED_GAMMA_MEAT_H

// Truncatation at t = 1.
inline double right_tgamma_reject(double shape, double rate)
{
    double x = 2.0;
    while (x > 1.0)
        x = gamma_rate(shape, rate);
    return x;
}

double omega_k(int k, double a, double b)
{
    double log_coef = -b + (a+k-1) * log(b) - ln_gamma(a+k) - p_gamma_rate(1.0, a, b, true);
    return exp(log_coef);
}

// Truncation at t = 1.
double right_tgamma_beta(double shape, double rate)
{
    double a = shape;
    double b = rate;

    double u = r_unif();

    int k = 1;
    double cdf = omega_k(1, a, b);
    while (u > cdf) {
        cdf += omega_k(++k, a, b);
        if (k % 100000 == 0) {
	    #ifndef USE_R
            fprintf(stderr, "right_tgamma_beta (itr k=%i): a=%g, b=%g, u=%g, cdf=%g\n", k, a, b, u, cdf);
	    #else
	    Rprintf("right_tgamma_beta (itr k=%i): a=%g, b=%g, u=%g, cdf=%g\n", k, a, b, u, cdf);
            R_CheckUserInterrupt();
	    #endif
        }
    }

    return R::beta(a, k);
}

double rtgamma_rate(double shape, double rate, double right_t)
{
    // x \sim (a,b,t)
    // ty = x
    // y \sim (a, bt, 1);
    double a = shape;
    double b = rate * right_t;

    double p = p_gamma_rate(1.0, a, b, false);
    double y = 0.0;
    if (p > 0.95)
        y = right_tgamma_reject(a, b);
    else
        y = right_tgamma_beta(a,b);

    double x = right_t * y;
    return x;
}

double ltgamma(double shape, double rate, double trunc)
{
    double a = shape;
    double b = rate * trunc;

    if (trunc <=0) {
	#ifndef USE_R
        fprintf(stderr, "ltgamma: trunc = %g < 0\n", trunc);
	#else
        Rprintf("ltgamma: trunc = %g < 0\n", trunc);
	#endif
        return 0;
    }
    if (shape < 1) {
	#ifndef USE_R
        fprintf(stderr, "ltgamma: shape = %g < 1\n", shape);
	#else
        Rprintf("ltgamma: shape = %g < 1\n", shape);
	#endif
        return 0;
    }

    if (shape ==1) return expon_rate(1.) / rate + trunc;

    double d1 = b-a;
    double d3 = a-1;
    double c0 = 0.5 * (d1 + sqrt(d1*d1 + 4 * b)) / b;

    double x = 0.0;
    bool accept = false;

    while (!accept) {
        x = b + expon_rate(1.) / c0;
        double u = r_unif();

        double l_rho = d3 * log(x) - x * (1-c0);
        double l_M   = d3 * log(d3 / (1-c0)) - d3;

        accept = log(u) <= (l_rho - l_M);
    }

    return trunc * (x/b);
}

#endif
