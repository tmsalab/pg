#' Theoretical Polya Gamma Distribution's Mean and Variance
#'
#' Compute the theoretical mean and variance for a Polya Gamma variable.
#'
#' @param h A single `integer` value corresponding to the "shape" parameter.
#' @param z A single `numeric` value corresponding to the "scale" parameter.
#'
#' @return
#' Either the theoretical mean or theoretical variance for a Polya Gamma
#' distribution.
#'
#' @export
#' @rdname theoretical-pg
#' @examples
#' # Fixed parameter distribution simulation ----
#'
#' ## Parameters  ----
#' h = 1; z = .5
#' ## Attempt distribution recovery  ----
#' vector_of_pg_samples = rpg_vector(1e6, h, z)
#'
#' head(vector_of_pg_samples)
#' length(vector_of_pg_samples)
#'
#' ## Obtain the empirical results   ----
#' empirical_mean = mean(vector_of_pg_samples)
#' empirical_var = var(vector_of_pg_samples)
#'
#' ## Take the theoretical values ----
#' theoretical_mean = pg_mean(h, z)
#' theoretical_var = pg_var(h, z)
#'
#' ## Form a comparison table ----
#'
#' # empirically sampled vs. theoretical values
#' rbind(c(empirical_mean, theoretical_mean),
#'       c(empirical_var, theoretical_var))
pg_mean = function(h, z) {
  (0.5*h / z) * tanh(0.5 *z)
}

#' @export
#' @rdname theoretical-pg
pg_var = function(h, z) {
  h / (4 * z ^ 3) * (sinh(z) - z) * (1 / cosh(0.5 * z) ^ 2)
}
