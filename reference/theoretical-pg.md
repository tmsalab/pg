# Theoretical Polya Gamma Distribution's Mean and Variance

Compute the theoretical mean and variance for a Polya Gamma variable.

## Usage

``` r
pg_mean(h, z)

pg_var(h, z)
```

## Arguments

- h:

  A single `integer` value corresponding to the "shape" parameter.

- z:

  A single `numeric` value corresponding to the "scale" parameter.

## Value

Either the theoretical mean or theoretical variance for a Polya Gamma
distribution.

## Examples

``` r
# Fixed parameter distribution simulation ----

## Parameters  ----
h = 1; z = .5
## Attempt distribution recovery  ----
vector_of_pg_samples = rpg_vector(1e6, h, z)

head(vector_of_pg_samples)
#>            [,1]
#> [1,] 0.42752199
#> [2,] 0.17498515
#> [3,] 0.28089440
#> [4,] 0.40725434
#> [5,] 0.06024853
#> [6,] 0.15083483
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
#> [1,] 0.24481508 0.2449187
#> [2,] 0.03960535 0.0396598
```
