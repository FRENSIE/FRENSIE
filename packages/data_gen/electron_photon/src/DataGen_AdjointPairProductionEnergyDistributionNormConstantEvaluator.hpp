//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator.hpp
//! \author Alex Robinson
//! \brief  The adjoint pair production energy dist. norm const. evaluator decl
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_PAIR_PRODUCTION_ENERGY_DISTRIBUTION_NORM_CONSTANT_EVALUATOR_HPP
#define DATA_GEN_ADJOINT_PAIR_PRODUCTION_ENERGY_DISTRIBUTION_NORM_CONSTANT_EVALUATOR_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"

namespace DataGen{

/*! The adjoint pair production energy distribution norm constant evaluator
 * \details This class is designed to be used for both pair production and
 * triplet production.
 */
class AdjointPairProductionEnergyDistributionNormConstantEvaluator
{

public:

  //! Construction helper
  template<typename InterpPolicy,
           bool processed_cross_section,
           typename FloatType,
           template<typename,typename...> class Array>
  static std::shared_ptr<AdjointPairProductionEnergyDistributionNormConstantEvaluator>
  createEvaluator( const Array<FloatType>& energy_grid,
                   const Array<FloatType>& pair_production_cross_section,
                   const unsigned threshold_energy_index );

  //! Destructor
  ~AdjointPairProductionEnergyDistributionNormConstantEvaluator()
  { /* ... */ }

  //! Return the norm constant at a given energy
  double evaluateEnergyDistributionNormConstant(
                                         const double energy,
                                         const double precision = 1e-6 ) const;

  //! Return a function that wraps the norm constant evaluation method
  std::function<double(double)>
  getEnergyDistributionNormConstantEvaluationWrapper(
                                         const double precision = 1e-6 ) const;

private:

  //! Constructor
  AdjointPairProductionEnergyDistributionNormConstantEvaluator(
                        std::unique_ptr<const MonteCarlo::PhotoatomicReaction>&
                        pair_production_cs );

  // The pair production cross section
  std::unique_ptr<const MonteCarlo::PhotoatomicReaction> d_pair_production_cs;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_ADJOINT_PAIR_PRODUCTION_ENERGY_DISTRIBUTION_NORM_CONSTANT_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointPairProductionEnergyDistributionNormContstantEvaluator.hpp
//---------------------------------------------------------------------------//
