//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearScatteringDistributionACEFactory.cpp
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
#include "MonteCarlo_PhotonuclearScatteringDistributionACEFactory.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PhotonuclearScatteringDistributionACEFactory::PhotonuclearScatteringDistributionACEFactory( 
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSPhotonuclearDataExtractor& raw_nuclide_data )
  : NuclearScatteringDistributionACEFactory<MonteCarlo::PhotonState,MonteCarlo::PhotonState>( 
					   table_name,
					   atomic_weight_ratio,		       
					   true )
{
  // Make sure secondary particle has data
  testPrecondition( raw_nuclide_data.hasSecondaryParticleType(2) );

  initialize( raw_nuclide_data.extractMTRPBlock(2),
	      raw_nuclide_data.extractTYRPBlock(2),
	      raw_nuclide_data.extractLANDPBlock(2),
	      raw_nuclide_data.extractANDPBlock(2),
	      raw_nuclide_data.extractLDLWPBlock(2),
	      raw_nuclide_data.extractDLWPBlock(2));
 }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
