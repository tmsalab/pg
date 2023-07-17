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

#ifndef PG_INVERSE_GAUSSIAN_MEAT
#define PG_INVERSE_GAUSSIAN_MEAT

inline double igauss(double mu, double lambda)
{
    // See R code for specifics.
    double mu2 = mu * mu;
    double Y = r_norm(0.0, 1.0);
    Y *= Y;
    double W = mu + 0.5 * mu2 * Y / lambda;
    double X = W - sqrt(W*W - mu2);
    if (r_unif() > mu / (mu + X))
        X = mu2 / X;
    return X;
}


inline double p_igauss(double x, double mu, double lambda)
{
    // z = 1 / mean
    double z = 1 / mu;
    double b = sqrt(lambda / x) * (x * z - 1);
    double a = sqrt(lambda / x) * (x * z + 1) * -1.0;
    // double y = p_norm(b, false) + exp(2 * lambda * z) * p_norm(a, false);
    double y = p_norm(b, false) + exp(2 * lambda * z + p_norm(a, true));
    return y;
}

#endif
