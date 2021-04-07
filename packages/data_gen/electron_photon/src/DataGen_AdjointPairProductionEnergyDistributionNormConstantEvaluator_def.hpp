//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator_def.hpp
//! \author Alex Robinson
//! \brief  The adjoint pair production energy dist. norm const. evaluator decl
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_PAIR_PRODUCTION_ENERGY_DISTRIBUTION_NORM_CONSTANT_EVALUATOR_DEF_HPP
#define DATA_GEN_ADJOINT_PAIR_PRODUCTION_ENERGY_DISTRIBUTION_NORM_CONSTANT_EVALUATOR_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

template<typename InterpPolicy,
         bool processed_cross_section,
         typename FloatType,
         template<typename,typename...> class Array>
std::shared_ptr<AdjointPairProductionEnergyDistributionNormConstantEvaluator>
AdjointPairProductionEnergyDistributionNormConstantEvaluator::createEvaluator(
                         const Array<FloatType>& energy_grid,
                         const Array<FloatType>& pair_production_cross_section,
                         const unsigned threshold_energy_index )
{
  // Make sure the energy distribution is valid
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );
  // Make sure the pair production cross section is valid
  testPrecondition( pair_production_cross_section.size() +
                    threshold_energy_index == energy_grid.size() );

  std::shared_ptr<std::vector<double> > energy_grid_copy(
       new std::vector<double>( energy_grid ) );

  std::shared_ptr<std::vector<double> > pair_production_cross_section_copy(
       new std::vector<double>( pair_production_cross_section ) );

  std::unique_ptr<const MonteCarlo::PhotoatomicReaction> pair_production_cs(
        new MonteCarlo::PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>(
                                            energy_grid_copy,
                                            pair_production_cross_section_copy,
                                            threshold_energy_index ) );

  return std::shared_ptr<AdjointPairProductionEnergyDistributionNormConstantEvaluator>(
         new AdjointPairProductionEnergyDistributionNormConstantEvaluator(
                                                        pair_production_cs ) );
}

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_PAIR_PRODUCTION_ENERGY_DISTRIBUTION_NORM_CONSTANT_EVALUATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator_def.hpp
//---------------------------------------------------------------------------//
