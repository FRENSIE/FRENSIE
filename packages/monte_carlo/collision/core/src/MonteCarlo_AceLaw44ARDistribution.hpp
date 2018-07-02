//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw44ARDistribution.hpp
//! \author Alex Robinson
//! \brief  The law 44 AR distribution base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_44_AR_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_44_AR_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

/*! The law 44 AR distribution base class
 * \ingroup ace_laws
 */
class AceLaw44ARDistribution
{

public:

  //! Constructor
  AceLaw44ARDistribution(
		  const Utility::ArrayView<const double>& outgoing_energy_grid,
		  const Utility::ArrayView<const double>& A_array,
		  const Utility::ArrayView<const double>& R_array );

  //! Destructor
  virtual ~AceLaw44ARDistribution()
  { /* ... */ }

  //! Sample A and R from the distribution
  virtual void sampleAR( const unsigned outgoing_index,
			 const double energy_prime,
			 double& sampled_A,
			 double& sampled_R ) const = 0;

protected:

  //! Return the outgoing energy grid
  double getOutgoingEnergyGridPoint( const unsigned outgoing_index ) const;

  //! Return the A value
  double getAValue( const unsigned outgoing_index ) const;

  //! Return the R value
  double getRValue( const unsigned outgoing_index ) const;

private:

  // The outgoing energy grid
  std::vector<double> d_outgoing_energy_grid;

  // The A array
  std::vector<double> d_A;

  // The R array
  std::vector<double> d_R;
};

// Return the outgoing energy grid
inline double AceLaw44ARDistribution::getOutgoingEnergyGridPoint(
				         const unsigned outgoing_index ) const
{
  // Make sure the outgoing index is valid
  testPrecondition( outgoing_index < d_outgoing_energy_grid.size() );

  return d_outgoing_energy_grid[outgoing_index];
}

// Return the A value
inline double AceLaw44ARDistribution::getAValue(
					  const unsigned outgoing_index ) const
{
  // Make sure the outgoing index is valid
  testPrecondition( outgoing_index < d_A.size() );

  return d_A[outgoing_index];
}

// Return the R value
inline double AceLaw44ARDistribution::getRValue(
					  const unsigned outgoing_index ) const
{
  // Make sure the outgoing index is valid
  testPrecondition( outgoing_index < d_R.size() );

  return d_R[outgoing_index];
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_44_AR_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw44ARDistribution.hpp
//---------------------------------------------------------------------------//
