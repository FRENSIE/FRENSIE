//---------------------------------------------------------------------------//
//!
//! \file   DataGen_OccupationNumberEvaluator_def.hpp
//! \author Alex Robinson
//! \brief  The occupation number evaluator template definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_DEF_HPP
#define DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
/*! \details The full electron momentum grid and Compton profile should
 * be given.
 */
template<typename InterpPolicy,
         typename GridMomentumUnit,
         typename GridInverseMomentumUnit,
         template<typename,typename...> class Array>
std::shared_ptr<OccupationNumberEvaluator>
OccupationNumberEvaluator::createEvaluator(
                            const Array<double>& electron_momentum_projections,
                            const Array<double>& compton_profile,
                            const double norm_constant_precision )
{
  // Make sure the electron momentum projections are valid
  testPrecondition( electron_momentum_projections.size() > 1 );
  testPrecondition( electron_momentum_projections.front() != 0.0 );
  testPrecondition( electron_momentum_projections.front() ==
		    -electron_momentum_projections.back() );
  testPrecondition( Utility::Sort::isSortedAscending(
				       electron_momentum_projections.begin(),
				       electron_momentum_projections.end() ) );
  // Make sure the compton profile is valid
  testPrecondition( compton_profile.back() > 0.0 );
  testPrecondition( compton_profile.front() == compton_profile.back() );
  testPrecondition( compton_profile.size() ==
		    electron_momentum_projections.size() );
  // Make sure the precision is valid
  testPrecondition( norm_constant_precision > 0.0 );
  testPrecondition( norm_constant_precision < 1.0 );

  // Create the raw compton profile
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<GridMomentumUnit,GridInverseMomentumUnit> > raw_compton_profile(
     new Utility::UnitAwareTabularDistribution<InterpPolicy,GridMomentumUnit,GridInverseMomentumUnit>(
                                                electron_momentum_projections,
                                                compton_profile ) );

  // Store the profile in a tabular distribution for quick interpolation
  std::unique_ptr<const MonteCarlo::ComptonProfile> unit_aware_compton_profile(
      new MonteCarlo::StandardComptonProfile<GridMomentumUnit,GridInverseMomentumUnit>( raw_compton_profile ) );

  return std::shared_ptr<OccupationNumberEvaluator>(
                    new OccupationNumberEvaluator( unit_aware_compton_profile,
                                                   norm_constant_precision ) );
}

} // end DataGen namespace

#endif // DATA_GEN_OCCUPATION_NUMBER_EVALUATOR_DEF_HPP

//---------------------------------------------------------------------------//
// DataGen_OccupationNumberEvaluator_def.hpp
//---------------------------------------------------------------------------//
