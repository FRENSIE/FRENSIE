//---------------------------------------------------------------------------//
//!
//! \file   Utility_BoostSolver.cpp
//! \author Alex Bennett
//! \brief  Boost Solver
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>

// Boost Includes
#include <boost/numeric/odeint.hpp>

// FRENSIE Includes
#include "Utility_BoostSolver.hpp"

namespace Utility {

BoostSolver::BoostSolver(const Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& matrix,
                         const Teuchos::Array<double>& y) :
  m_system(BatemanSystem(matrix)),
  m_jacobian(BatemanJacobian(matrix))
{
  m_y.resize( y.size() );
  for(int i = 0; i != m_y.size(); i++)
  {
    m_y(i) = y[i];
  }
}

void BoostSolver::getNumberDensities(Teuchos::Array<double>& y)
{
  y.resize(m_y.size(),0);
  for(int i = 0; i != m_y.size(); i++)
  {
    y[i] = m_y(i);
  }
}

void BoostSolver::Solve(const double& time)
{
  size_t nstep = boost::numeric::odeint::integrate_adaptive( 
           boost::numeric::odeint::rosenbrock4_controller<boost::numeric::odeint::rosenbrock4<double> >(1e-6,1e-6),
           std::make_pair( m_system, m_jacobian ),
           m_y,
           0.0,
           time,
           0.1);
}

void BoostSolver::BatemanSystem::operator()(const boost::numeric::ublas::vector<double>& y,
                                                  boost::numeric::ublas::vector<double>& dxdt,
                                            double time)
{
  for(int i = 0; i != dxdt.size(); i++)
  {
    dxdt(i) = 0.0;

    for(int j = 0; j != dxdt.size(); j++)
    {
      dxdt(i) += (*m_matrix)(i,j) * y(j);
    }
  }
}

void BoostSolver::BatemanJacobian::operator()(const boost::numeric::ublas::vector<double>& m_y,
                                                    boost::numeric::ublas::matrix<double>& jacobian,
                                              const double& time,
                                                    boost::numeric::ublas::vector<double>& dfdt )
{
  for(int i = 0; i != jacobian.size1(); i++)
  {
    for(int j = 0; j != jacobian.size2(); j++)
    {
      jacobian(i,j) = (*m_matrix)(i,j);
    }

    dfdt(i) = 0.0;
  }
}
 

} // end namespace utility

//---------------------------------------------------------------------------//
// end Utility_BoostSolver.cpp
//---------------------------------------------------------------------------//

