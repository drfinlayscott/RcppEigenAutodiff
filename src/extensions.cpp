// extensions.cpp
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


// Trying to figure out wrap implementation
// See RcppBDT for example
// See Vignette on extending
//
// Important (and I'm not sure it's in the extending vignette, maybe it's in the package one?)
// Need to have a header file named after the package, e.g. RcppEigenAutodiff.h
// This then gets automagically included in RcppExports.cpp

#include <RcppEigenAutodiff.h>

// Implement autodiff::real wrap
template <> SEXP Rcpp::wrap(const autodiff::real& obj){
	// Include for testing
	//Rprintf("In autodiff::real wrap implementation\n");
	double out = obj.val();
	return Rcpp::wrap(out);
}

// Implement autodiff::VectorXreal wrap - return Eigen vector class
template <> SEXP Rcpp::wrap(const autodiff::VectorXreal& obj){
	// Include for testing
	//Rprintf("In autodiff::VectorXreal wrap implementation\n");
	Eigen::VectorXd out = obj.cast<double>();
	return Rcpp::wrap(out);
}

// Implement autodiff::MatrixXreal wrap - could possibly write a generic one to cover VectorXreal and MatrixXreal
template <> SEXP Rcpp::wrap(const autodiff::MatrixXreal& obj){
	// Include for testing
	//Rprintf("In autodiff::MatrixXreal wrap implementation\n");
	Eigen::MatrixXd out = obj.cast<double>();
	return Rcpp::wrap(out);
}

// Test functions

// [[Rcpp::export]]
autodiff::real real_wrap_test(const double x)
{
	autodiff::real y = x;
	return y;
}

// [[Rcpp::export]]
autodiff::VectorXreal VectorXreal_wrap_test(const Eigen::VectorXd& x)
{
	autodiff::VectorXreal y = x;
	return y;
}

// [[Rcpp::export]]
autodiff::MatrixXreal MatrixXreal_wrap_test(const Eigen::MatrixXd& x)
{
	autodiff::MatrixXreal y = x;
	return y;
}


