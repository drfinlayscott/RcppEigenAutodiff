# Synopsis

**RcppEigenAutodiff** is a proof-of-concept package that combines the [RcppEigen](https://github.com/RcppCore/RcppEigen) package with the [AutoDiff](https://autodiff.github.io/) C++ library for automatic differentiation.

This is not the first time these two have been combined (e.g. see [Rcppautodiff](https://github.com/sn248/Rcppautodiff), but I wanted to try it myself as my already limited Rcpp / C++ skills were getting rusty and it seemed like a neat project to get back in the game.

# Example: simple Newton-Raphson solver

[Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) is a C++ template library for linear algebra that has various routines for solving linear systems.
**RcppEigenAutodiff** uses these to implement a simple Newton-Raphson solver, along with the Jacobian generated using **Autodiff**.

An example problem is included, taken from [Wikipedia](https://en.wikipedia.org/wiki/Newton's_method): 

$$5x_{1} + x_{1}x_{2}^2 + \sin^2(2x_{2}) = 2$$
$$e^{2x_{1} - x_{2}} + 4x_{2} = 3$$

```r
library(devtools)
devtools::load_all("RcppEigenAutodiff")
RcppEigenAutodiff::nr_test1()
```

# Author

Finlay Scott

# License

The package includes header files taken from **Autodiff** which are distributed under the MIT license.

This package is also distributed under the MIT license 2024 (see LICENSE file in package).

# Acknowledgements

Big thanks to the authors and maintainers of **Autodiff**, **Eigen**, **RcppEigen** and **Rcpp**.

