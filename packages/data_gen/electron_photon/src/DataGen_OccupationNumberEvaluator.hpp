//---------------------------------------------------------------------------//
//!
//! \file   DataGen_OccupationNumberEvaluator.hpp
//! \author Alex Robinson
//! \brief  The occupation number evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_HPP
#define DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"

namespace DataGen{

//! The occupation number evaluator
class OccupationNumberEvaluator
{

public:

  //! Constructor
  OccupationNumberEvaluator(
		   const Teuchos::Array<double>& electron_momentum_projections,
		   const Teuchos::Array<double>& compton_profile,
		   const double norm_constant_precision = 1e-6 );

  //! Destructor
  ~OccupationNumberEvaluator()
  { /* ... */ }

  //! Return the normalization constant used with the Compton profile
  double getComptonProfileNormConstant() const;

  //! Evaluate the compton profile
  double evaluateComptonProfile(
			     const double electron_momentum_projection ) const;

  //! Return the occupation number at a given electron momentum projection
  double evaluateOccupationNumber( const double electron_momentum_projection,
				   const double precision = 1e-6 ) const;

private:

  // The compton profile normalization constant (rounding error issue)
  double d_compton_profile_norm_constant;

  // The compton profile
  boost::scoped_ptr<const Utility::TabularDistribution<Utility::LogLin> >
  d_compton_profile;
};

} // end DataGen namespace

#endif // end DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_OccupationNumberEvaluator.hpp
//---------------------------------------------------------------------------//
