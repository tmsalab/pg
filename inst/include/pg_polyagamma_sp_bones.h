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

#ifndef PG_POLYAGAMMASP_BONES_H
#define PG_POLYAGAMMASP_BONES_H

// Function and derivative.
struct FD {
  double val;
  double der;
};

struct Line {
  double slope;
  double icept;
};


// PolyaGamma approximation by SP.
class PolyaGammaApproxSP
{

public:

  int draw(double& d, double h, double z, int max_iter=200);

protected:

  // Helper.
  
  double w_left (double trunc, double h, double z);
  double w_right(double trunc, double h, double z);

  void   delta_func(double x, double z  , FD& delta);
  double phi_func  (double x, double mid, FD& phi);
  
  double tangent_to_eta(double x, double z, double mid, Line& tl);

  double sp_approx(double x, double n, double z);

  double cos_rt(double v);

  // YV yv;

  double rtigauss(double mu, double lambda, double trunc);
  double y_func(double v); // y = tan(sqrt(v)) / sqrt(v);

};

#endif
