test_that("Verify repeated sampling under same parameters matches", {

  h = rep_len(c(1, 2, 3), 100)
  z = rep_len(c(4, 5, 6), 100)

  set.seed(5123)
  x1 = pg::rpg_sp(h, z)
  set.seed(5123)
  x2 = pg::rpg_sp(h, z)

  expect_equal(x1, x2, info = "Samples should be equivalent")
})

test_that("Ensure setting a seed results in different values being generated", {
  h = rep_len(c(1, 2, 3), 100)
  z = rep_len(c(4, 5, 6), 100)

  set.seed(9143)
  x1 = pg::rpg_sp(h, z)
  set.seed(5123)
  x2 = pg::rpg_sp(h, z)

  expect_false(isTRUE(all.equal(x1, x2)), info = "Samples should differ under seeds")
})

test_that("Ensure estimation is reasonably matching with theoretical mean", {
  h = 100
  z = 4

  h_vec = rep_len(h, 1e6)
  z_vec = rep_len(z, 1e6)

  set.seed(5503)
  x = pg::rpg_sp(h_vec, z_vec)

  mean_empirical_recovery = mean(x)
  mean_theoretical_recovery = pg::pg_mean(h, z)

  var_empirical_recovery = c(var(x))
  var_theoretical_recovery = pg::pg_var(h, z)

  expect_equal(mean_empirical_recovery, mean_theoretical_recovery,
               tolerance = 0.01,
               info = "Sample mean matches")

  expect_equal(var_empirical_recovery, var_theoretical_recovery,
               tolerance = 0.01,
               info = "Sample variance matches")
})
