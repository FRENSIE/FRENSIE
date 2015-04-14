//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.cpp
//! \author Alex Robinson, Ryan Pease
//! \brief  Photon photon Photonuclear scattering distribution factory class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <stdexcept>

// Trilinos Includes
#include "Teuchos_ArrayView.hpp"

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PhotonuclearNeutronScatteringDistributionACEFactory::PhotonuclearNeutronScatteringDistributionACEFactory( 
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSPhotonuclearDataExtractor& raw_nuclide_data )
  : NuclearScatteringDistributionACEFactory<MonteCarlo::PhotonState,MonteCarlo::NeutronState>( 
					   table_name,
					   atomic_weight_ratio,		       
					   true )
{
  // Make sure secondary particle has data
  testPrecondition( raw_nuclide_data.hasSecondaryParticleType(1) );

  initialize( raw_nuclide_data.extractMTRPBlock(1),
	      raw_nuclide_data.extractTYRPBlock(1),
	      raw_nuclide_data.extractLANDPBlock(1),
	      raw_nuclide_data.extractANDPBlock(1),
	      raw_nuclide_data.extractLDLWPBlock(1),
	      raw_nuclide_data.extractDLWPBlock(1));
 }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
