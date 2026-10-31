# Sample from the Polya Gamma distribution PG(h, z)

Chooses the most efficient implemented method to sample from a Polya
Gamma distribution. Details on algorithm selection presented below.

## Usage

``` r
rpg_scalar(h, z)

rpg_vector(n, h, z)

rpg_hybrid(h, z)

rpg_gamma(h, z, trunc = 1000L)

rpg_devroye(h, z)

rpg_sp(h, z)

rpg_normal(h, z)
```

## Arguments

- h:

  `integer` values corresponding to the "shape" parameter.

- z:

  `numeric` values corresponding to the "scale" parameter.

- n:

  The number of samples to taken from a PG(h, z). Used only by the
  vector sampler.

- trunc:

  Truncation cut-off. Only used by the gamma sampler.

## Value

A single `numeric` value.

## Details

The following sampling cases are enabled:

- `h > 170`: Normal approximation method

- `h > 13`: Saddlepoint approximation method

- `h = 1` or `h = 2`: Devroye method

- `h > 0`: Sum of Gammas method.

- `h < 0`: Result is automatically set to zero.

## Examples

``` r
# Fixed parameter distribution simulation ----

## Parameters  ----
h = 1; z = .5

## Sample only one value  ----
single_value = rpg_scalar(h, z)
single_value
#> [1] 0.2921526

## Attempt distribution recovery  ----
vector_of_pg_samples = rpg_vector(1e6, h, z)

head(vector_of_pg_samples)
#>           [,1]
#> [1,] 1.1828284
#> [2,] 0.1552478
#> [3,] 0.5746456
#> [4,] 0.1060454
#> [5,] 0.1483075
#> [6,] 0.3371750
length(vector_of_pg_samples)
#> [1] 1000000

## Obtain the empirical results   ----
empirical_mean = mean(vector_of_pg_samples)
empirical_var = var(vector_of_pg_samples)

## Take the theoretical values ----
theoretical_mean = pg_mean(h, z)
theoretical_var = pg_var(h, z)

## Form a comparison table ----

# empirically sampled vs. theoretical values
rbind(c(empirical_mean, theoretical_mean),
      c(empirical_var, theoretical_var))
#>            [,1]      [,2]
#> [1,] 0.24460724 0.2449187
#> [2,] 0.03947098 0.0396598

# Varying distribution parameters ----

## Generate varying parameters ----
u_h = 20:100
u_z = 0.5*u_h

## Sample from varying parameters ----
x = rpg_hybrid(u_h, u_z)
```
