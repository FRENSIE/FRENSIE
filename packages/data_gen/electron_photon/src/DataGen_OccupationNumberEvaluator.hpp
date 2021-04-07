//---------------------------------------------------------------------------//
//!
//! \file   DataGen_OccupationNumberEvaluator.hpp
//! \author Alex Robinson
//! \brief  The occupation number evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_HPP
#define DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfile.hpp"

namespace DataGen{

//! The occupation number evaluator
class OccupationNumberEvaluator
{

public:

  //! Construction helper
  template<typename InterpPolicy,
           typename GridMomentumUnit,
           typename GridInverseMomentumUnit = typename Utility::UnitTraits<GridMomentumUnit>::InverseUnit,
           template<typename,typename...> class Array>
  static std::shared_ptr<OccupationNumberEvaluator> createEvaluator(
                            const Array<double>& electron_momentum_projections,
                            const Array<double>& compton_profile,
                            const double norm_constant_precision = 1e-6 );

  //! Destructor
  ~OccupationNumberEvaluator()
  { /* ... */ }

  //! Return the normalization constant used with the Compton profile
  double getComptonProfileNormConstant() const;

  //! Evaluate the Compton profile
  double evaluateComptonProfile(
			     const double electron_momentum_projection ) const;

  //! Return a function that wraps the Compton profile evaluation method
  std::function<double(double)> getComptonProfileEvaluationWrapper() const;

  //! Return the occupation number at a given electron momentum projection
  double evaluateOccupationNumber( const double electron_momentum_projection,
				   const double precision = 1e-6 ) const;

  //! Return a function that wraps the occupation number evaluation method
  std::function<double(double)> getOccupationNumberEvaluationWrapper(
                                         const double precision = 1e-6 ) const;

private:

  //! Constructor
  OccupationNumberEvaluator(
            std::unique_ptr<const MonteCarlo::ComptonProfile>& compton_profile,
            const double norm_constant_precision );

  // The compton profile normalization constant (rounding error issue)
  double d_compton_profile_norm_constant;

  // The compton profile
  std::unique_ptr<const MonteCarlo::ComptonProfile> d_compton_profile;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_OccupationNumberEvaluator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_OccupationNumberEvaluator.hpp
//---------------------------------------------------------------------------//
