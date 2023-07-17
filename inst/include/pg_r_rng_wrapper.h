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


// MAKE SURE YOU CALL GetRNGSeed() and PutRNGSeed() WHEN USING THESE FUNCTIONS!!!

#ifndef SIMPLE_RNG_WRAPPER
#define SIMPLE_RNG_WRAPPER

#define RCHECK 1000

const double SQRT2PI = 2.50662827;

inline void check_R_interupt(int count)
{
    #ifdef USE_R
    if (count % RCHECK == 0) R_CheckUserInterrupt();
    #endif
}

// CDF
#define p_norm(X, USE_LOG) R::pnorm((X), 0.0, 1.0, true, (USE_LOG))
#define p_gamma_scale(X, SHAPE, SCALE, USE_LOG) R::pgamma((X), (SHAPE), (SCALE), 1, (USE_LOG))
#define p_gamma_rate(X, SHAPE, RATE, USE_LOG) R::pgamma((X), (SHAPE), (1./(RATE)), 1, (USE_LOG))

// Random variates
#define expon_mean(MEAN) R::rexp((MEAN))
#define expon_rate(RATE) R::rexp((1./(RATE)))
#define r_unif() R::runif(0.0, 1.0)
#define r_norm(MEAN, SD) R::rnorm((MEAN), (SD))
#define gamma_scale(SHAPE, SCALE) R::rgamma((SHAPE), (SCALE))
#define gamma_rate(SHAPE, RATE) R::rgamma((SHAPE), (1./(RATE)))

// Scientific functions
#define ln_gamma(X) R::lgammafn(X)

// Output


#endif
