//---------------------------------------------------------------------------//
//!
//! \file   IntegralEstimator.hpp
//! \author Alex Robinson
//! \brief  Integral estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef INTEGRAL_ESTIMATOR_HPP
#define INTEGRAL_ESTIMATOR_HPP

// FACEMC Includes
#include "Estimator.hpp"

namespace FACEMC{

template<typename EntityHandle, 
	 typename ContributionMultiplierPolicy = Weight>
class IntegralEstimator : public Estimator
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  IntegralEstimator();

  //! Constructor
  IntegralEstimator( const unsigned long long id,
		     const double norm_constant,
		     const double multiplier = 1.0 );

  //! Destructor
  ~IntegralEstimator()
  { /* ... */ }

  //! Add estimator contribution from portion of current history
  void addPartialHistoryContribution( const BasicParticleState& particle,
				      const double raw_contribution );

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Print the estimator data
  void print( std::ostream& os ) const;

  //! Return the estimator id
  unsigned long long getId() const;

private:

  // The estimator id
  unsigned long long d_id;

  // The normalization constant
  double d_norm_constant;

  // The multiplier
  double d_multiplier;

  // 
}

} // end FACEMC namespace

#endif // end INTEGRAL_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end IntegralEstimator.hpp
//---------------------------------------------------------------------------//
