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

#ifndef PG_SAMPLER_BONES_H
#define PG_SAMPLER_BONES_H

template <typename T>
inline T rpg_gamma(const T& shape_, const T& scale_, int trunc = 1000);

// Ensure argument parity with other samplers by embedding trunc with a default of 1000.
template <typename T>
inline T rpg_gamma_trunc(const T& shape_, const T& scale_);

template <typename T>
inline T rpg_devroye(const T& shape_, const T& scale_);

//template <typename T>
//inline T rpg_alt(const T& shape_, const T& scale_);

template <typename T>
inline T rpg_sp(const T& shape_, const T& scale_);

template <typename T>
inline T rpg_normal(const T& shape_, const T& scale_);

inline arma::vec rpg_vector_hybrid(
    unsigned int n, double shape, double scale);

inline double rpg_scalar_hybrid(double shape, double scale);

template <typename T>
inline T rpg_hybrid(const T& shape_, const T& scale_);

#endif
