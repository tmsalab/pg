test_that("Ensure scalar draws match under given seed", {
  set.seed(1512)
  x1 = pg::rpg_scalar(1, 0.5)
  set.seed(1512)
  x2 = pg::rpg_scalar(1, 0.5)

  expect_equal(x1, x2, info = "Both samples should be equivalent")
})

test_that("Check scalar draws match reused C++ class draws", {
  set.seed(1512)

  h = c(1, 25, 35, 50, 100, 171)
  z = c(0.5, 4, 5, 6, 7, 8)

  x1 = rep(NA, length(h))
  for(i in seq_along(x1)) {
    x1[i] = pg::rpg_scalar(h[i], z[i])
  }
  # Cast to matrix
  x1 = matrix(x1)

  set.seed(1512)
  x2 = pg::rpg_hybrid(h, z)

  expect_equal(x1, x2, info = "Both samples should be equivalent")
})


test_that("Verify repeated sampling under same parameters matches", {
  set.seed(5123)
  x1 = pg::rpg_vector(10, 1, 0.5)
  set.seed(5123)
  x2 = pg::rpg_vector(10, 1, 0.5)

  expect_equal(x1, x2, info = "Both vectorized samples should be equivalent")
})

test_that("Ensure setting a seed results in different values being generated", {
  set.seed(9321)
  x1 = pg::rpg_vector(10, 1, 0.5)
  set.seed(5123)
  x2 = pg::rpg_vector(10, 1, 0.5)

  expect_false(isTRUE(all.equal(x1, x2)), info = "Samples should differ under seeds")
})
