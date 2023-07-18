// This header file contains work done by
// (C) Nicholas Polson, James Scott, Jesse Windle, 2012-2019
// within the BayesLogit R package. This work is licensed under GPL v3 or greater.

// Modifications for header-only inclusion was done by
// (C) James Balamuta 2019

// pg is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.

// pg is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along with
// pg.  If not, see <https://www.gnu.org/licenses/>.

#ifndef PG_SAMPLER_MEAT_H
#define PG_SAMPLER_MEAT_H


////////////////////////////////////////////////////////////////////////////////
// Gamma //
////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline T rpg_gamma(const T& shape_, const T& scale_, int trunc) {
  PolyaGamma pg(trunc);

  // Assume
  unsigned int n = shape_.size();

  // Initialize a similar result object
  T result(n);

  for(unsigned int i = 0; i < n; ++i){

#ifdef USE_R
    if (i % 1000 == 0) R_CheckUserInterrupt();
#endif

    if (shape_[i] != 0.0)
      result[i] = pg.draw_sum_of_gammas(shape_[i], scale_[i]);
    else
      result[i] = 0.0;
  }

  return result;
}

template <typename T>
inline T rpg_gamma_trunc(const T& shape_, const T& scale_) {
  // Set with default value to align function calls
  return rpg_gamma(shape_, scale_, 1000);
}

////////////////////////////////////////////////////////////////////////////////
// Devroye //
////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline T rpg_devroye(const T& shape_, const T& scale_) {
  PolyaGamma pg(1);

  // Assume
  unsigned int n = shape_.size();

  // Initialize a similar result object
  T result(n);

  for(unsigned int i = 0; i < n; ++i){
    int shape = static_cast<int>(shape_[i]);
    if (shape != 0)
      result[i] = pg.draw(shape, scale_[i]);
    else
      result[i] = 0.0;
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////
// Alt //
////////////////////////////////////////////////////////////////////////////////


// template <typename T>
// inline T rpg_alt(const T& shape_, const T& scale_) {
//   PolyaGammaApproxAlt pg;
//
//   // Assume
//   unsigned int n = shape_.size();
//
//   // Initialize a similar result object
//   T result(n);
//
//   for(unsigned int i = 0; i < n; ++i){
//     if (shape_[i]!=0)
//       result[i] = pg.draw(shape_[i], scale_[i]);
//     else
//       result[i] = 0.0;
//   }
//
//   return result;
// }

////////////////////////////////////////////////////////////////////////////////
// Saddlepoint //
////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline T rpg_sp(const T& shape_, const T& scale_) {
  PolyaGammaApproxSP pg_sp;

  // Assume
  unsigned int n = shape_.size();

  // Initialize a similar result object
  T result(n);

  // Establish a double to handle return from pg_sp
  double d = 0.0;

  for(unsigned int i = 0; i < n; ++i){
    if (shape_[i] != 0) {
      // x[i] refers to an initialized vector with value 0.
      pg_sp.draw(d, shape_[i], scale_[i]);
      // Draw returns the number of iterations.
      // Silent reference return of the double.
      result[i] = d;
    } else {
      result[i] = 0.0;
    }
  }

  return result;
}


////////////////////////////////////////////////////////////////////////////////
// Normal approximation //
////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline T rpg_normal(const T& shape_, const T& scale_) {
  // Establish a Polya-Gamma class
  PolyaGamma pg;

  // Assume
  unsigned int n = shape_.size();

  // Initialize a similar result object
  T result(n);

  for(unsigned int i = 0; i < n; ++i) {
    // Think shape is equivalent ot sample size
    double m = pg.pg_m1(shape_[i], scale_[i]);
    double v = pg.pg_m2(shape_[i], scale_[i]) - m * m;
    result[i] = R::rnorm(m, sqrt(v));
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////
// Decider functions //
////////////////////////////////////////////////////////////////////////////////

inline double rpg_scalar_hybrid(double shape, double scale) {

  // Establish a Polya-Gamma class
  PolyaGamma pg;
  // Setup a Saddlepoint sampler
  PolyaGammaApproxSP pg_sp;

  double result = 0.0;

  if (shape > 170) {
    double m = pg.pg_m1(shape, scale);
    double v = pg.pg_m2(shape, scale) - m*m;
    result = R::rnorm(m, sqrt(v));
  }
  else if (shape > 13) {
    // x[i] refers to an initialized vector with value 0.
    pg_sp.draw(result, shape, scale);
    // Draw returns the number of iterations.
    // Silent reference return of the double.
  }
  else if (shape == 1 || shape == 2) {
    result = pg.draw(static_cast<int>(shape), scale);
  }
  // Disabled.
  // else if (shape > 1) {
  //     result = pg_alt.draw(shape, scale);
  // }
  else if (shape > 0) {
    result = pg.draw_sum_of_gammas(shape, scale);
  }
  else {
    result = 0.0;
  }

  return result;
}

inline arma::vec rpg_vector_hybrid(
    unsigned int n, double shape, double scale) {

  // Establish a Polya-Gamma class
  PolyaGamma pg;
  // Setup a Saddlepoint sampler
  PolyaGammaApproxSP pg_sp;

  arma::vec result(n);

  // Establish a double to handle return from pg_sp
  double d = 0.0;

  for(unsigned int i = 0; i < n; ++i) {
    if (shape > 170) {
      double m = pg.pg_m1(shape, scale);
      double v = pg.pg_m2(shape, scale) - m*m;
      result[i] = R::rnorm(m, sqrt(v));
    }
    else if (shape > 13) {
      // x[i] refers to an initialized vector with value 0.
      pg_sp.draw(d, shape, scale);
      // Draw returns the number of iterations.
      // Slient reference return of the double.
      result[i] = d;
    }
    else if (shape == 1 || shape == 2) {
      result[i] = pg.draw(static_cast<int>(shape), scale);
    }
    // Disabled.
    // else if (shape > 1) {
    //     result = pg_alt.draw(shape, scale);
    // }
    else if (shape > 0) {
      result[i] = pg.draw_sum_of_gammas(shape, scale);
    }
    else {
      result[i] = 0.0;
    }

  }

  return result;
}

// Assume shape_ and scale_ are equivalent
// Create a generic template update
template <typename T>
inline T rpg_hybrid(const T& shape_, const T& scale_) {

  // Establish a Polya-Gamma class
  PolyaGamma pg;

  // Setup a Saddlepoint sampler
  PolyaGammaApproxSP pg_sp;

  // Assume
  unsigned int n = shape_.size();

  // Initialize a similar result object
  T result(n);

  // Establish a double to handle return from pg_sp
  double d = 0.0;

  for(unsigned int i = 0; i < n; ++i) {
    double shape = shape_[i];
    double scale = scale_[i];

    // Think shape is equivalent ot sample size
    if (shape > 170) {
      double m = pg.pg_m1(shape, scale);
      double v = pg.pg_m2(shape, scale) - m * m;
      result[i] = R::rnorm(m, sqrt(v));
    }
    else if (shape > 13) {
      // x[i] refers to an initialized vector with value 0.
      pg_sp.draw(d, shape, scale);
      // Draw returns the number of iterations.
      // Silent reference return of the double.
      result[i] = d;
    }
    else if (shape == 1 || shape == 2) {
      result[i] = pg.draw(static_cast<int>(shape), scale);
    }
    // Disabled.
    // else if (shape > 1) {
    //     result = pg_alt.draw(shape, scale);
    // }
    else if (shape > 0) {
      result[i] = pg.draw_sum_of_gammas(shape, scale);
    }
    else {
      result[i] = 0.0;
    }

  }

  return result;
}

#endif
