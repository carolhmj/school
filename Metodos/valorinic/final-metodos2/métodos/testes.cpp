#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "hlibs/catch.hpp"
#include "métodos.h"
#include <cmath>


TEST_CASE("e^-x para x := 6 e step := 1e-4","[euler][backward]") {
	chp::equacaoDiferencial F = [](double y, double x){return -y;};

	const double step = 1e-4,
	             epsilon = 1e-1,
	             x = 6.0;

	const double y = 0.002478752176666,
	             y0 = 1;

	auto forward = chp::ForwardEuler(F,y0,step);
	auto backward = chp::BackwardEuler(F,y0,step,epsilon);
	auto rk4 = chp::RungeKutta4(F,y0,step);
	auto predCorr3 = chp::PreditorCorretor3(F,y0,step);
	auto predCorr4 = chp::PreditorCorretor4(F,y0,step);

	REQUIRE(forward(x) == Approx(y));
	REQUIRE(backward(x) == Approx(y));
	REQUIRE(rk4(x) == Approx(y));
	REQUIRE(predCorr3(x) == Approx(y));
	REQUIRE(predCorr4(x) == Approx(y));
}