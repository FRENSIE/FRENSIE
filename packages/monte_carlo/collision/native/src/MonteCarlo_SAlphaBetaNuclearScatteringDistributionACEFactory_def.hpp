//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory_def.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  S(alpha,beta) nuclear scattering distribution factor base class template defs.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP
#define MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP

// Std Lib Includes
#include <sstream>
#include <stdexcept>

// Trilinos Includes
#include "Teuchos_ArrayView.hpp"

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionFactoryHelpers.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.hpp"
#include "MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename IncomingParticleType, typename OutgoingParticleType>
SAlphaBetaNuclearScatteringDistributionACEFactory<IncomingParticleType,
			OutgoingParticleType>::SAlphaBetaNuclearScatteringDistributionACEFactory( 
            const std::string& table_name,
					  const double atomic_weight_ratio )
  : NuclearScatteringDistributionACEFactory( table_name, atomic_weight_ratio ),
    d_table_name( table_name ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{ /* ... */ }

// Constructor
/*! \details The ArrayView objects are based by value so that data extractor
 * class extract member functions can be used directly in the constructor. 
 * Passing by reference would not allow this to be done.
 */
template<typename IncomingParticleType, typename OutgoingParticleType>
SAlphaBetaNuclearScatteringDistributionACEFactory<IncomingParticleType,
		  OutgoingParticleType>::SAlphaBetaNuclearScatteringDistributionACEFactory(
			    const std::string& table_name,
			    const double atomic_weight_ratio,
			    const Teuchos::ArrayView<const double> mtr_block,
			    const Teuchos::ArrayView<const double> tyr_block,
			    const Teuchos::ArrayView<const double> land_block,
			    const Teuchos::ArrayView<const double> and_block,
			    const Teuchos::ArrayView<const double> ldlw_block,
			    const Teuchos::ArrayView<const double> dlw_block,
			    const Teuchos::ArrayView<const double> itxe_block,
 	        const Teuchos::ArrayView<const double> itce_block,
	 	      const Teuchos::ArrayView<const double> itca_block )
  : NuclearScatteringDistributionACEFactory( table_name,
                                             atomic_weight_ratio,
                                             mtr_block,
                                             tyr_block,
                                             and_block,
                                             ldlw_block,
                                             dlw_block ),
    d_table_name( table_name ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{
  this->initialize( mtr_block,
		    tyr_block,
		    land_block,
		    and_block,
		    ldlw_block,
		    dlw_block,
		    itxe_block,
		    itce_block,
		    itca_block );
}

// Constructor (no TYR block)
/*! \details The ArrayView objects are based by value so that data extractor
 * class extract member functions can be used directly in the constructor. 
 * Passing by reference would not allow this to be done. If the tyr block is
 * not given, all reactions are assumed to take place in the lab system and
 * the multiplicities are assumed to be one.
 */
template<typename IncomingParticleType, typename OutgoingParticleType>
SAlphaBetaNuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::SAlphaBetaNuclearScatteringDistributionACEFactory(
			    const std::string& table_name,
			    const double atomic_weight_ratio,
			    const Teuchos::ArrayView<const double> mtr_block,
			    const Teuchos::ArrayView<const double> land_block,
			    const Teuchos::ArrayView<const double> and_block,
			    const Teuchos::ArrayView<const double> ldlw_block,
			    const Teuchos::ArrayView<const double> dlw_block,
			    const Teuchos::ArrayView<const double> itxe_block,
 	        const Teuchos::ArrayView<const double> itce_block,
	 	      const Teuchos::ArrayView<const double> itca_block )
  : NuclearScatteringDistributionACEFactory( table_name,
                                             atomic_weight_ratio,
                                             mtr_block,
                                             tyr_block,
                                             and_block,
                                             ldlw_block,
                                             dlw_block ),
    d_table_name( table_name ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{
  this->initialize( mtr_block,
		    land_block,
		    and_block,
		    ldlw_block,
		    dlw_block,
		    itxe_block,
		    itce_block,
		    itca_block );
}

// Initialize the factory
template<typename IncomingParticleType, typename OutgoingParticleType>
void SAlphaBetaNuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initialize(
		   const Teuchos::ArrayView<const double> mtr_block,
		   const Teuchos::ArrayView<const double> tyr_block,
		   const Teuchos::ArrayView<const double> land_block,
		   const Teuchos::ArrayView<const double> and_block,
		   const Teuchos::ArrayView<const double> ldlw_block,
		   const Teuchos::ArrayView<const double> dlw_block,
		   const Teuchos::ArrayView<const double> itxe_block,
 	     const Teuchos::ArrayView<const double> itce_block,
	 	   const Teuchos::ArrayView<const double> itca_block  )
{
  initializeReactionOrderingMap( mtr_block, tyr_block );
  initializeReactionRefFrameMap( mtr_block, tyr_block );
  initializeReactionAngularDistStartIndexMap( land_block );
  initializeReactionAngularDistMap( land_block, and_block );
  initializeReactionEnergyDistStartIndexMap( ldlw_block );
  initializeReactionEnergyDistMap( ldlw_block, dlw_block );
}

// Initialize the factory (no TYR block)
template<typename IncomingParticleType, typename OutgoingParticleType>
void SAlphaBetaNuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initialize(
		   const Teuchos::ArrayView<const double> mtr_block,
		   const Teuchos::ArrayView<const double> land_block,
		   const Teuchos::ArrayView<const double> and_block,
		   const Teuchos::ArrayView<const double> ldlw_block,
		   const Teuchos::ArrayView<const double> dlw_block,
		   const Teuchos::ArrayView<const double> itxe_block,
 	     const Teuchos::ArrayView<const double> itce_block,
	 	   const Teuchos::ArrayView<const double> itca_block )
{
  // Create a ficticious TYR block (all multiplicity 1 in lab system)
  Teuchos::Array<double> dummy_tyr_block( mtr_block.size(), 1.0 );
  
  initializeReactionOrderingMap( mtr_block, dummy_tyr_block );
  initializeReactionRefFrameMap( mtr_block, dummy_tyr_block );
  initializeReactionAngularDistStartIndexMap( land_block );
  initializeReactionAngularDistMap( land_block, and_block );
  initializeReactionEnergyDistStartIndexMap( ldlw_block );
  initializeReactionEnergyDistMap( ldlw_block, dlw_block );
}

// Check if there is an elastic S(alpha,beta) reaction
bool SAlphaBetaNuclearScatteringDistributionACEFactory::isElasticSAlphaBeta( 
  const Teuchos::ArrayView<const double> itce_block );

// Check if the elastic S(alpha,beta) reaction is implicit
bool isImplicitElasticSAlphaBeta(
  const Teuchos::ArrayView<const double> itca_block );
  
// Create S(alpha,beta) distributions
void createSAlphaBetaScatteringDistributions(
  const unsigned reaction_type,
  Teuchos::RCP<DistributionType>& distribution );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory_def.hpp
//---------------------------------------------------------------------------//
