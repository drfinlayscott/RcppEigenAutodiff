// RcppEigenAutodiff.h
//
// Copyright (C) 2024 Finlay Scott
//
// This file is part of RcppEigenAutodiff and is licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// You should have received a copy of the MIT License along with RcppEigenAutodiff.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.




// Package header file, used by RcppExports.cpp
// Has implicit wraps for autodiff classes using non-intrusive extension (see Rcpp vignette).
// Need to be declared here so RccpExports has access to them.
// Order of includes is important

#include <RcppCommon.h>

// Include AD headers here as local?
// Doesn't seem to matter - why would it?
#include <autodiff/forward/real.hpp>
#include <autodiff/forward/real/eigen.hpp>

// Declare wrap specialisation for autodiff::real
template <> SEXP Rcpp::wrap(const autodiff::real& obj);

// Declare wrap specialisation for autodiff::VectorXreal
// I think this is actually an instance of a templated Eigen class Vector (itself a subspecies of Matrix)
// Could make a generic wrap? But would probably still need the individual implementations so leave for now
template <> SEXP Rcpp::wrap(const autodiff::VectorXreal& obj);
template <> SEXP Rcpp::wrap(const autodiff::MatrixXreal& obj);
// Add array classes too

#include <Rcpp.h>

#include <RcppEigen.h>
// [[Rcpp::depends(RcppEigen)]]

// [[Rcpp::plugins(cpp17)]]


