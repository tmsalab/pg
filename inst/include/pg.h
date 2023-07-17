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

#ifndef PG_PG_H
#define PG_PG_H

#include <RcppArmadillo.h>

namespace pg {

#ifndef USE_R
#define USE_R
#endif

// Customized macros to work with RNGs
#include "pg_r_rng_wrapper.h"

// Main polya-gamma sampling class
#include "pg_polyagamma_bones.h"
#include "pg_polyagamma_meat.h"

// Utilities for saddlepoint estimation
#include "pg_inverse_gaussian_bones.h"
#include "pg_inverse_gaussian_meat.h"

#include "pg_truncated_norm_bones.h"
#include "pg_truncated_norm_meat.h"

#include "pg_truncated_gamma_bones.h"
#include "pg_truncated_gamma_meat.h"

#include "pg_invert_y_bones.h"
#include "pg_invert_y_meat.h"

// Saddlepoint-based polya-gamma sampling class
#include "pg_polyagamma_sp_bones.h"
#include "pg_polyagamma_sp_meat.h"


// Hybrid sampling definitions for C++
#include "pg_sampler_bones.h"
#include "pg_sampler_meat.h"

} // end namespace

#endif

