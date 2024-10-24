// newton_raphson.cpp
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

#include <RcppEigenAutodiff.h>

// Simple Newton-Raphson
// find x: f(x) = 0
// x1 = x0 - f(x0) / f'(x0)
// w = f(x0) / f'(x0)
// We want w.
// Rearrange w:
// f'(x0) w = f(x0)
// Solve this system, give it f'(x0) and f(x0) to get w
// x1 = x0 - w
//
// f'(x0) is Jacobian

// These look interesting for future projects
// https://github.com/PatWie/CppNumericalSolvers

// The vector function for which the Jacobian is needed
autodiff::VectorXreal f1(const autodiff::VectorXreal& x)
{
    return x * x.sum();
}

// Just get the Jacobian to get familiar with workings of RcppEigen and autodiff.
// [[Rcpp::export]]
Rcpp::List nr_jac_solve_test()
{
	// Input vector x with 5 variables
    autodiff::VectorXreal x(5);                          
    x << 1, 2, 3, 4, 5;                         
	// The output vector F = f(x) evaluated together with Jacobian matrix below
	autodiff::VectorXreal F; // VectorXreal is an autodiff class
	Eigen::MatrixXd J = jacobian(f1, wrt(x), at(x), F); // evaluate the output vector F and the Jacobian matrix dF/dx

	// Converstion of autodiff vector to RcppEigen type so we can get values back to R
	Eigen::VectorXd Fout = F.cast<double>();

	// Solve J w = f(x0)
	Eigen::VectorXd qr = J.colPivHouseholderQr().solve(Fout);
	Eigen::VectorXd lu_partial = J.partialPivLu().solve(Fout);

	Rcpp::List out = Rcpp::List::create(
			Rcpp::Named("jacobian", J),
			Rcpp::Named("fout", Fout ),
			Rcpp::Named("qr", qr),
			Rcpp::Named("lu_partial", lu_partial));
    return out ;
}

// 2D Newton-Raphson example taken from Wikipedia: https://en.wikipedia.org/wiki/Newton's_method 
//  5 * x1^2 + x1*x2^2 + sin^2(2 * x2) = 2
//  exp(2 x1 - x2) + 4 * x2 = 3
//  Find x1 and x2 (0.567... -0.309)
autodiff::VectorXreal f2(const autodiff::VectorXreal& x)
{
    autodiff::VectorXreal out(2);                          
	// Indexing starts at 0
	out(0) = 5 * pow(x(0),2) + x(0) * pow(x(1),2) + pow(sin(2 * x(1)),2) - 2;
	out(1) = exp(2 * x(0) - x(1)) + 4 * x(1) - 3;
	return out;
}

// Norm function for AD reals - could template it for other types but too much for now?
autodiff::real norm(const autodiff::VectorXreal& x){
	// Thought Vector uses the matrix class not array class - didn't complain though
	//const VectorXreal xprod = x.array() * x.array(); // Coefficient multiplication - not linear algebra - can we do this with AD? Apparently
	const autodiff::ArrayXreal xprod = x.array() * x.array(); 
	autodiff::real xsum = xprod.sum();
	return sqrt(xsum);
}

// [[Rcpp::export]]
Rcpp::List nr_test1()
{
	// Input vector x with 5 variables
    autodiff::VectorXreal x(2);                          
    x << 1, 1; // Initial values
	// The output vector F = f(x) evaluated together with Jacobian matrix below
	// Get inital value of F - are we already at solution?
	autodiff::VectorXreal F = f2(x); // VectorXreal is an autodiff class
	autodiff::real Fnorm = norm(F);
	double tolerance = 1e-9;
	int counter = 0;
	const int max_iterations = 100;

	// Version using all AD classes - could use Eigen class for J and cast F to Eigen classes?
	// e.g. 
	// Fout = F.cast<double>();
	// J.colPivHouseholderQr().solve(Fout);
	// Where is J Eigen class - does it matter? More overhead with AD class?
	// Choose QR or LU
	autodiff::VectorXreal qr;
	//autodiff::VectorXreal lu_partial; 
	autodiff::MatrixXreal J;
	
	// Loop
	Rprintf("Entering solver loop\n");
	while((Fnorm > tolerance) && (counter < max_iterations)){
		// Get Jacobian and F(x)
		J = jacobian(f2, wrt(x), at(x), F); // evaluate the output vector F and the Jacobian matrix dF/dx
		// Solve J w = f(x0)
		// Two methods available - lu_partial might be slightly faster, qr might be slightly more robust - see Eigen documentation for details
		qr = J.colPivHouseholderQr().solve(F);
		//lu_partial = J.partialPivLu().solve(F);
		// Update x
		x = x - qr;
		// Update terminating conditions
		counter++;
		Fnorm = norm(F);
		Rprintf("counter: %i\n", counter);
		Rprintf("Fnorm: %f\n", Fnorm); // No need to cast for printing - seems to be implicit - nice
	}
	Rprintf("Finished solver loop\n");
	// Use implicit wraps to return autodiff:: objects back to R - nice!
	Rcpp::List out = Rcpp::List::create(
			Rcpp::Named("jacobian", J),
			Rcpp::Named("f", F ),
			Rcpp::Named("x", x),
			Rcpp::Named("qr", qr),
			//Rcpp::Named("lu_partial", lu_partial),
			Rcpp::Named("fnorm", Fnorm),
			Rcpp::Named("counter", counter));
    return out ;
}

