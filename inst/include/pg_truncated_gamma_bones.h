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

// See Philippe, *Simulation of right and left truncated gamma
// distributions by mixtures* and Dagpunar *Sampling of variates from
// a truncated gamma distribution*

#ifndef PG_TRUNCATED_GAMMA_BONES_H
#define PG_TRUNCATED_GAMMA_BONES_H

inline double right_tgamma_reject(double shape, double rate);
inline double omega_k(int k, double a, double b);
inline double right_tgamma_beta(double shape, double rate);
inline double rtgamma_rate(double shape, double rate, double right_t);
inline double ltgamma(double shape, double rate, double trunc);

#endif
