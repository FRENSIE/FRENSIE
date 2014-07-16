//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_NeutronScatteringEnergyDistributionFactory.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  Neutron scattering energy distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistributionFactory.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ThirtyTwoEquiprobableBinDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

#include "Facemc_NeutronScatteringDistributionFactory.hpp"

namespace Facemc{

// Create the energy distribution
void NeutronScatteringEnergyDistributionFactory::createDistribution(
	     const Teuchos::ArrayView<const double>& dlw_block_array,
	     const unsigned dlw_block_array_start_index,
	     const std::string& table_name,
	     const NuclearReactionType reaction)
//	     Teuchos::RCP<ElasticNeutronScatteringDistribution>& distribution )
	   //  Teuchos::RCP<NeutronScatteringEnergyDistribution>& distribution )
{
  // Make sure the dlw block array is valid
  testPrecondition( dlw_block_array.size() > 0 );
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistributionFactory.cpp
//---------------------------------------------------------------------------//
