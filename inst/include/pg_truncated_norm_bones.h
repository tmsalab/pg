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

// Method from Christian Robert, *Simulation of truncated normal variables*

// Code modified from <https://github.com/jwindle/BayesLogit>

#ifndef PG_TRUNCATED_NORM_BONES_H
#define PG_TRUNCATED_NORM_BONES_H

// Throw runtime exception or print message and return.
#ifndef TREOR
#ifndef NTHROW
#define TREOR(MESS, VAL) throw std::runtime_error(MESS);
#else
#ifndef USE_R
#define TREOR(MESS, VAL) {fprintf(stderr, MESS); return VAL;}
#else
#define TREOR(MESS, VAL) {Rprintf(MESS); return VAL;}
#endif
#endif
#endif

inline double flat(double left, double right);
inline double texpon_rate(double left, double rate);
inline double texpon_rate(double left, double right, double rate);
inline double alphastar(double left);
inline double lowerbound(double left);
inline double tnorm(double left);
inline double tnorm(double left, double mu, double sd);
inline double tnorm(double left, double right, double mu, double sd);
inline double rtinvchi2(double scale, double trunc);

#endif
