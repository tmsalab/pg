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

#ifndef PG_POLYAGAMMASP_MEAT_H
#define PG_POLYAGAMMASP_MEAT_H

inline double PolyaGammaApproxSP::rtigauss(double mu, double lambda, double trunc)
{
  // mu = fabs(mu);
  double X = trunc + 1.0;
  if (trunc < mu) { // mu > t
    double alpha = 0.0;
    while (r_unif() > alpha) {
      X = rtinvchi2(lambda, trunc);
      alpha = exp(-0.5 * lambda / (mu*mu) * X);
    }
    // printf("rtigauss, part i: %g\n", X);
  }
  else {
    while (X > trunc) {
      X = igauss(mu, lambda);
    }
    // printf("rtigauss, part ii: %g\n", X);
  }
  return X;
}

inline double PolyaGammaApproxSP::y_func(double v)
{
  double tol = 1e-6;
  double y   = 0.0;
  double r   = sqrt(fabs(v));
  if (v > tol)
    y = tan(r) / r;
  else if (v < -1*tol)
    y = tanh(r) / r;
  else
    y = 1 + (1/3) * v + (2/15) * v * v + (17/315) * v * v * v;
  return y;
}

inline double PolyaGammaApproxSP::cos_rt(double v)
{
  double y   = 0.0;
  double r   = sqrt(fabs(v));
  if (v >= 0)
    y = cos(r);
  else
    y = cosh(r);
  return y;
}

inline void PolyaGammaApproxSP::delta_func(double x, double mid, FD& delta)
{
  if (x >= mid) {
    delta.val = log(x) - log(mid);
    delta.der = 1.0 / x;
  }
  else {
    delta.val = 0.5 * (1 - 1.0 / x) - 0.5 * (1 - 1.0 / mid);
    delta.der = 0.5 / (x*x);
  }
}

inline double PolyaGammaApproxSP::phi_func(double x, double z, FD& phi)
{
  // double v = yv.v_func(x);
  double v = v_eval(x);
  double u = 0.5 * v;
  double t = u + 0.5 * z*z;

  phi.val = log(cosh(fabs(z))) - log(cos_rt(v)) - t * x;
  phi.der = -1.0 * t;

  return v;
}

inline double PolyaGammaApproxSP::tangent_to_eta(double x, double z, double mid, Line& tl)
{
  FD phi, delta, eta;
  double v;

  v = phi_func(x, z, phi);
  delta_func(x, mid, delta);

  eta.val = phi.val - delta.val;
  eta.der = phi.der - delta.der;

  // printf("v=%g\nphi=%g, phi.d=%g\ndelta=%g, delta.d=%g\neta=%g, eta.d=%g\n",
  // 	 v, phi.val, phi.der, delta.val, delta.der, eta.val, eta.der);

  tl.slope = eta.der;
  tl.icept = eta.val - eta.der * x;

  return v;
}

inline double PolyaGammaApproxSP::sp_approx(double x, double n, double z)
{
  // double v  = yv.v_func(x);
  double v = v_eval(x);
  double u  = 0.5 * v;
  double z2 = z * z;
  double t  = u + 0.5 * z2;
  // double m  = y_func(-1 * z2);

  double phi = log(cosh(z)) - log(cos_rt(v)) - t * x;

  double K2  = 0.0;
  if (fabs(v) >= 1e-6)
    K2 = x*x + (1-x) / v;
  else
    K2 = x*x - 1/3 - (2/15) * v;

  double log_spa = 0.5 * log(0.5 * n / __PI) - 0.5 * log(K2) + n * phi;
  return exp(log_spa);
}

inline int PolyaGammaApproxSP::draw(double& d, double n, double z, int maxiter)
{
  if (n < 1) {
    #ifndef USE_R
    fprintf(stderr, "PolyaGammaApproxSP::draw: n must be >= 1.\n");
    #else
    Rprintf("PolyaGammaApproxSP::draw: n must be >= 1.\n");
    #endif
    return -1.;
  }

  z = 0.5 * fabs(z);

  double xl = y_func(-1*z*z);    // Mode of phi - Left point.
  double md = xl * 1.1;          // Mid point.
  double xr = xl * 1.2;          // Right point.

  // printf("xl, md, xr: %g, %g, %g\n", xl, md, xr);

  // Inflation constants
  // double vmd  = yv.v_func(md);
  double vmd  = v_eval(md);
  double K2md = 0.0;

  if (fabs(vmd) >= 1e-6)
    K2md = md*md + (1-md) / vmd;
  else
    K2md = md*md - 1/3 - (2/15) * vmd;

  double m2 = md * md;
  double al = m2*md / K2md;
  double ar = m2    / K2md;

  // printf("vmd, K2md, al, ar: %g, %g %g %g\n", vmd, K2md, al, ar);

  // Tangent lines info.
  Line ll, lr;
  tangent_to_eta(xl, z, md, ll);
  tangent_to_eta(xr, z, md, lr);

  double rl = -1. * ll.slope;
  double rr = -1. * lr.slope;
  double il = ll.icept;
  double ir = lr.icept;

  // printf("rl, rr, il, ir: %g, %g, %g, %g\n", rl, rr, il, ir);

  // Constants
  double lcn = 0.5 * log(0.5 * n / __PI);
  double rt2rl = sqrt(2 * rl);

  // printf("sqrt(rl): %g\n", rt2rl);

  // Weights
  double wl, wr, wt, pl;


  // // to cross-reference R script
  // double term1, term2, term3, term4, term5;
  // term1 = exp(0.5 * log(al));
  // term2 = exp(- n * rt2rl + n * il + 0.5 * n * 1./md);
  // term3 = p_igauss(md, 1./rt2rl, n);
  // printf("l terms 1-3: %g, %g, %g\n", term1, term2, term3);

  wl = exp(0.5 * log(al) - n * rt2rl + n * il + 0.5 * n * 1./md) *
    p_igauss(md, 1./rt2rl, n);

  // // to cross-reference R script
  // term1 = exp(0.5 * log(ar));
  // term2 = exp(lcn);
  // term3 = exp(- n * log(n * rr) + n * ir - n * log(md));
  // term4 = exp(ln_gamma(n));
  // term5 = (1.0 - p_gamma_rate(md, n, n*rr, false));
  // printf("r terms 1-5: %g, %g, %g, %g, %g\n", term1, term2, term3, term4, term5);

  wr = exp(0.5 * log(ar) + lcn + (- n * log(n * rr) + n * ir - n * log(md) + ln_gamma(n)) ) *
    (1.0 - p_gamma_rate(md, n, n*rr, false));
  // yv.upperIncompleteGamma(md, n, n*rr);

  // printf("wl, wr, lcn: %g, %g, %g\n", wl, wr, lcn);

  wt = wl + wr;
  pl = wl / wt;

  // Sample
  bool go  = true;
  int iter = 0;
  double X = 2.0;
  double F = 0.0;

  while(go && iter < maxiter) {
    // Put first so check on first pass.
    #ifdef USE_R
    if (iter % 1000 == 0) R_CheckUserInterrupt();
    #endif

    iter++;

    double phi_ev;
    if (r_unif() < pl) {
      X = rtigauss(1./rt2rl, n, md);
      phi_ev = n * (il - rl * X) + 0.5 * n * ((1.-1./X) - (1.-1./md));
      F = exp(0.5 * log(al) + lcn - 1.5 * log(X) + phi_ev);
    }
    else {
      X = ltgamma(n, n*rr, md);
      phi_ev = n * (ir - rr * X) + n * (log(X) - log(md));
      F = exp(0.5 * log(ar) + lcn + phi_ev) / X;
    }

    double spa = sp_approx(X, n, z);

    if (F * r_unif() < spa) go = false;

  }

  // return n * 0.25 * X;
  d = n * 0.25 * X;
  return iter;
}

#endif
