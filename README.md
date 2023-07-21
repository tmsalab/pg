
<!-- README.md is generated from README.Rmd. Please edit that file -->

# pg

<!-- badges: start -->

[![R-CMD-check](https://github.com/tmsalab/pg/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/tmsalab/pg/actions/workflows/R-CMD-check.yaml)
[![Package-License](http://img.shields.io/badge/license-GPL%20(%3E=3)-brightgreen.svg?style=flat)](http://www.gnu.org/licenses/gpl-3.0.html)
<!-- badges: end -->

The goal of pg is to provide both *R* and *C++* header access to the
Polya Gamma distribution sampling routine.

## Installation

You can install the development version of `pg` from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("tmsalab/pg")
```

## Usage

Let `X` be a Polya Gamma Distribution denoted by `PG(h, z)`, where `h`
is the “shape” parameter and `z` is the “scale” parameter. Presently,
the following sampling cases are enabled:

- `h > 170`: Normal approximation method
- `h <= 170` and `h > 13`: Saddlepoint method
- `h = 1` or `h = 2`: Devroye method
- `h > 0`: Sum of gammas method.
- `h < 0`: Result is automatically set to zero.

Not implemented:

- `h <= 13` and `h > 1`: Alternative method (waiting for verification)

The package structure allows for the sampling routines to be accessed
either via *C++* or through *R*. The return type can be either a single
value or a vector. When repeat sampling is needed with the same `b` and
`c`, please use the vectorized sampler.

### Sampling with C++

Using the sampling routine in *C++* through a standalone `.cpp` file
requires either the `rpg_scalar_hybrid()`, `rpg_vector_hybrid()`, or
`rpg_hybrid()` function to be accessed in the `pg` *C++* namespace. Each
of these functions will automatically select the appropriate algorithm
based on criteria discussed previously.

``` cpp
#include <pg.h>
// [[Rcpp::depends(RcppArmadillo, pg)]]

// [[Rcpp::export]]
double rpg_scalar(const double h, const double z) {
  return pg::rpg_scalar_hybrid(h, z);
}

// [[Rcpp::export]]
arma::vec rpg_hybrid(const arma::vec& h, const arma::vec& z) {
  return pg::rpg_hybrid(h, z);
}

// [[Rcpp::export]]
arma::vec rpg_vector(unsigned int n, const double h, const double z) {
  return pg::rpg_vector_hybrid(n, h, z);
}
```

For use within an *R* package, include a the `pg` package name in the
`DESCRIPTION` file. From there, include the `pg.h` header in a similar
manner to the stand-alone *C++* example.

    LinkingTo: 
        Rcpp,
        RcppArmadillo
        pg

### Sampling with R

For use within an *R* file, you can do:

``` r
# Number of observations to sample
n = 4
# Select the PG(h, z) values
h = 1; z = 0.5

# Set a seed for reproducibility
set.seed(141)

# Sample a single observation
pg::rpg_scalar(h, z)
#> [1] 0.05752942

# Set a seed for reproducibility
set.seed(141)

# Sample a vector of observations
pg::rpg_vector(n, h, z)
#>            [,1]
#> [1,] 0.05752942
#> [2,] 0.38752679
#> [3,] 0.38710433
#> [4,] 0.18847913
```

## See also

The following are useful resources regarding the Polya Gamma
distribution.

- Papers
  - “Bayesian Inference for Logistic Models Using Pólya–Gamma Latent
    Variables” by Nicholas G. Polson, James G. Scott, and Jesse
    Windle (2013)
    [doi:10.1080/01621459.2013.829001](https://doi.org/10.1080/01621459.2013.829001).
    Paper that invented the Polya Gamma
  - “Sampling Polya Gamma random variates: alternate and approximate
    techniques” by Jesse Windle, Nicholas G. Polson, and James G.
    Scott (2014) <https://arxiv.org/abs/1405.0506>. Provides an
    efficiency overview of the different sampling approaches to sampling
    from a Polya Gamma distribution.
- R Implementations:
  - [`BayesLogit`](https://cran.r-project.org/package=BayesLogit) *R*
    package by Nicholas G. Polson, James G. Scott, and Jesse Windle.
    Provides the main *C++* class samplers contained used by the `pg`
    package.
  - [`pgdraw`](https://cran.r-project.org/package=pgdraw) by Daniel F.
    Schmidt and Enes Makalic. This package construction relies heavily
    on free-floating functions and `Rcpp` data structures.
  - [`bayesCL`](https://cran.r-project.org/package=bayesCL) by Rok
    Cesnovar and Erik Strumbelj. This package boast a sampler that is
    100x faster through offloading of the computation onto a GPU.
    Though, the package is not actively maintained.
- Support in other languages:
  - `Python` has the
    [`pypolyagamma`](https://github.com/slinderman/pypolyagamma) package
    by Scott Linderman.
  - `Stan` [lacks an
    implementation](https://discourse.mc-stan.org/t/sampling-from-a-polya-gamma-distribution/8067)
    for the Polya Gamma distribution since it relies on joint proposals
    rather than full conditionals.

## Author

James Balamuta leaning heavily on work done in
[`BayesLogit`](https://cran.r-project.org/package=BayesLogit) *R*
package by Nicholas G. Polson, James G. Scott, and Jesse Windle.

## Citing the `pg` package

To ensure future development of the package, please cite `pg` package if
used during an analysis or simulation study. Citation information for
the package may be acquired by using in *R*:

``` r
citation("pg")
```

## License

GPL (\>= 3)
