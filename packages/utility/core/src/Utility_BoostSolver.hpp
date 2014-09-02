//---------------------------------------------------------------------------//
//!
//! \file   Utility_BoostSolver.hpp
//! \author Alex Bennett
//! \brief  Boost Solver
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BOOST_SOLVER_HPP
#define UTILITY_BOOST_SOLVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>
#include <Teuchos_RCP.hpp>

// Boost Includes
#include <boost/numeric/ublas/vector.hpp>

namespace Utility {

class BoostSolver
{
friend class BatemanSystem;
friend class BatemanJacobian;

public:
  //Constructor
  BoostSolver(const Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& matrix,
              const Teuchos::Array<double>& y);

  void getNumberDensities(Teuchos::Array<double>& y);

  void Solve(const double& time);

private:
  class BatemanSystem
  {
  public:
    BatemanSystem(const Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& matrix) : m_matrix(matrix) {};
    void operator()(const boost::numeric::ublas::vector<double>& y,
                          boost::numeric::ublas::vector<double>& dxdt,
                          double time);

  private:
    Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > m_matrix;
  };

  class BatemanJacobian
  {
  public:
    BatemanJacobian(const Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& matrix): m_matrix(matrix) {};
    void operator()(const boost::numeric::ublas::vector<double>& y,
                          boost::numeric::ublas::matrix<double>& jacobian,
                    const double& time,
                          boost::numeric::ublas::vector<double>& dfdt);

  private:
    Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > m_matrix;
  };

  const BatemanSystem& m_system;
  const BatemanJacobian& m_jacobian;

  boost::numeric::ublas::vector<double> m_y;
};

} // end namespace utility

#endif // end UTILITY_BOOST_SOLVER_HPP

//---------------------------------------------------------------------------//
// end Utility_BoostSolver.hpp
//---------------------------------------------------------------------------//

