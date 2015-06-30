#include <functional>

namespace chp {
	typedef std::function<double(double,double)> equacaoDiferencial;
	typedef std::function<double(double)> funcaoReal;

	class ResolvedorEDO {
	protected:
		const equacaoDiferencial f;
		const double y0;
		const double step;
	public:
		ResolvedorEDO(equacaoDiferencial f,double y0,double step) : f(f), y0(y0),step(step) {};
		virtual double operator()(double) = 0;
	};

	class ForwardEuler : ResolvedorEDO {
	public:
		ForwardEuler(equacaoDiferencial f,double y0,double step) : ResolvedorEDO(f,y0,step) {};
		double operator()(double x);
	};

	class BackwardEuler : ResolvedorEDO {
	protected:
		const double epsilon;
	public:
		BackwardEuler(equacaoDiferencial f,double y0,double step,double epsilon) : ResolvedorEDO(f,y0,step),epsilon(epsilon) {};
		double operator()(double x);
	};

	class EulerModificado : ResolvedorEDO {
	protected:
		const double epsilon;
	public:
		EulerModificado(equacaoDiferencial f,double y0,double step,double epsilon) : ResolvedorEDO(f,y0,step),epsilon(epsilon) {};
		double operator()(double x);
	};

	class RungeKutta : ResolvedorEDO {
	public:
		RungeKutta(equacaoDiferencial f,double y0,double step) : ResolvedorEDO(f,y0,step) {};
		double operator()(double x);
	};
	
	class RungeKutta3 : ResolvedorEDO {
	public:
		RungeKutta3(equacaoDiferencial f,double y0,double step) : ResolvedorEDO(f,y0,step) {};
		double operator()(double x);
	};

	class RungeKutta4 : ResolvedorEDO {
	public:
		RungeKutta4(equacaoDiferencial f,double y0,double step) : ResolvedorEDO(f,y0,step) {};
		double operator()(double x);
	};

	class PreditorCorretor3 : ResolvedorEDO {
	public:
		PreditorCorretor3(equacaoDiferencial f,double y0,double step) : ResolvedorEDO(f,y0,step) {};
		double operator()(double x);
	};

	class PreditorCorretor4 : ResolvedorEDO {
	public:
		PreditorCorretor4(equacaoDiferencial f,double y0,double step) : ResolvedorEDO(f,y0,step) {};
		double operator()(double x);
	};

	double pontoFixo(funcaoReal,double,double);
}
