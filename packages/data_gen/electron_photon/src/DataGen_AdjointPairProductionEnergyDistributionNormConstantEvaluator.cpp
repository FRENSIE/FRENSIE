//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator.cpp
//! \author Alex Robinson
//! \brief  The adjoint pair production energy dist. norm const. evaluator def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
AdjointPairProductionEnergyDistributionNormConstantEvaluator::AdjointPairProductionEnergyDistributionNormConstantEvaluator(
                        std::unique_ptr<const MonteCarlo::PhotoatomicReaction>&
                        pair_production_cs )
{
  // Make sure the cross section is valid
  testPrecondition( pair_production_cs.get() );

  // Take ownership of the cross section
  d_pair_production_cs.swap( pair_production_cs );
}    

// Return the norm constant at a given energy
double AdjointPairProductionEnergyDistributionNormConstantEvaluator::evaluateEnergyDistributionNormConstant(
                                                 const double energy,
                                                 const double precision ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  
  long double norm_constant;

  if( energy <= d_pair_production_cs->getThresholdEnergy() )
    norm_constant = 0.0;
  else
  {
    std::function<double(double)> cs_evaluation_wrapper =
      std::bind<double>( (double(MonteCarlo::PhotoatomicReaction::*)(double) const)&MonteCarlo::PhotoatomicReaction::getCrossSection,
                         std::cref( *d_pair_production_cs ),
                         std::placeholders::_1 );

    long double abs_error;

    Utility::GaussKronrodIntegrator<long double> quadrature_gkq( precision );

    quadrature_gkq.integrateAdaptively<15>(
                                    cs_evaluation_wrapper,
                                    d_pair_production_cs->getThresholdEnergy(),
                                    energy,
                                    norm_constant,
                                    abs_error );
  }

  // Make sure the norm constant is valid
  testPostcondition( norm_constant >= 0.0 );

  return norm_constant;
}

// Return a function that wraps the norm constant evaluation method
std::function<double(double)>
AdjointPairProductionEnergyDistributionNormConstantEvaluator::getEnergyDistributionNormConstantEvaluationWrapper(
                                                 const double precision ) const
{
  return std::bind<double>( &AdjointPairProductionEnergyDistributionNormConstantEvaluator::evaluateEnergyDistributionNormConstant,
                            std::cref( *this ),
                            std::placeholders::_1,
                            precision );
}
  
} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator.cpp
//---------------------------------------------------------------------------//
