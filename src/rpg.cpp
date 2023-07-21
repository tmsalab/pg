#include "pg.h"

//' Sample from the Polya Gamma distribution PG(h, z)
//'
//' Chooses the most efficient implemented method to sample from a Polya Gamma
//' distribution. Details on algorithm selection presented below.
//'
//' @param n     The number of samples to taken from a PG(h, z). Used only by
//'              the vector sampler.
//' @param h     `integer` values corresponding to the "shape" parameter.
//' @param z     `numeric` values corresponding to the "scale" parameter.
//' @param trunc Truncation cut-off. Only used by the gamma sampler.
//'
//' @return
//' A single `numeric` value.
//'
//' @details
//' The following sampling cases are enabled:
//'
//' - `h > 170`: Normal approximation method
//' - `h > 13`: Saddlepoint approximation method
//' - `h = 1` or `h = 2`: Devroye method
//' - `h > 0`: Sum of Gammas method.
//' - `h < 0`: Result is automatically set to zero.
//'
//' @export
//' @rdname rpg-sampler
//'
//' @examples
//' # Fixed parameter distribution simulation ----
//'
//' ## Parameters  ----
//' h = 1; z = .5
//'
//' ## Sample only one value  ----
//' single_value = rpg_scalar(h, z)
//' single_value
//'
//' ## Attempt distribution recovery  ----
//' vector_of_pg_samples = rpg_vector(1e6, h, z)
//'
//' head(vector_of_pg_samples)
//' length(vector_of_pg_samples)
//'
//' ## Obtain the empirical results   ----
//' empirical_mean = mean(vector_of_pg_samples)
//' empirical_var = var(vector_of_pg_samples)
//'
//' ## Take the theoretical values ----
//' theoretical_mean = pg_mean(h, z)
//' theoretical_var = pg_var(h, z)
//'
//' ## Form a comparison table ----
//'
//' # empirically sampled vs. theoretical values
//' rbind(c(empirical_mean, theoretical_mean),
//'       c(empirical_var, theoretical_var))
//'
//' # Varying distribution parameters ----
//'
//' ## Generate varying parameters ----
//' u_h = 20:100
//' u_z = 0.5*u_h
//'
//' ## Sample from varying parameters ----
//' x = rpg_hybrid(u_h, u_z)
// [[Rcpp::export]]
double rpg_scalar(const double h, const double z) {
  return pg::rpg_scalar_hybrid(h, z);
}

//' @export
//' @rdname rpg-sampler
// [[Rcpp::export]]
arma::vec rpg_vector(unsigned int n, const double h, const double z) {
  return pg::rpg_vector_hybrid(n, h, z);
}

//' @export
//' @rdname rpg-sampler
// [[Rcpp::export]]
arma::vec rpg_hybrid(const arma::vec& h, const arma::vec& z) {
  return pg::rpg_hybrid(h, z);
}


// Local function only available inside of the package namespace.
// [[Rcpp::export]]
arma::vec rpg_scalar_loop(const arma::vec& h, const arma::vec& z) {
  unsigned int n = h.size();
  arma::vec result(n);
  for(unsigned int i = 0; i < h.size(); ++i) {
    result[i] = pg::rpg_scalar_hybrid(h[i], z[i]);
  }

  return result;
}

//' @export
//' @rdname rpg-sampler
// [[Rcpp::export]]
arma::vec rpg_gamma(const arma::vec& h, const arma::vec& z, int trunc = 1000) {
  return pg::rpg_gamma(h, z, trunc);
}

//' @export
//' @rdname rpg-sampler
// [[Rcpp::export]]
arma::vec rpg_devroye(const arma::vec& h, const arma::vec& z) {
  return pg::rpg_devroye(h, z);
}

//' @export
//' @rdname rpg-sampler
// [[Rcpp::export]]
arma::vec rpg_sp(const arma::vec& h, const arma::vec& z) {
  return pg::rpg_sp(h, z);
}

//' @export
//' @rdname rpg-sampler
// [[Rcpp::export]]
arma::vec rpg_normal(const arma::vec& h, const arma::vec& z) {
  return pg::rpg_normal(h, z);
}
