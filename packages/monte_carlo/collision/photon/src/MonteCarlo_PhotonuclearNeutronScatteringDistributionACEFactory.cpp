//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.cpp
//! \author Alex Robinson, Ryan Pease
//! \brief  Photon photon Photonuclear scattering distribution factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
PhotonuclearNeutronScatteringDistributionACEFactory::PhotonuclearNeutronScatteringDistributionACEFactory(
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSPhotonuclearDataExtractor& raw_nuclide_data )
  : NuclearScatteringDistributionACEFactory<MonteCarlo::PhotonState,MonteCarlo::NeutronState>(
					   table_name,
					   atomic_weight_ratio )
{
  // Make sure secondary particle has data
  testPrecondition( raw_nuclide_data.hasSecondaryParticleType( Data::XSSPhotonuclearDataExtractor::NEUTRON ) );

  Data::XSSPhotonuclearDataExtractor::OutgoingParticleType
    outgoing_particle_type = Data::XSSPhotonuclearDataExtractor::NEUTRON;

  initialize( raw_nuclide_data.extractMTRPBlock( outgoing_particle_type ),
	      raw_nuclide_data.extractTYRPBlock( outgoing_particle_type ),
	      raw_nuclide_data.extractLANDPBlock( outgoing_particle_type ),
	      raw_nuclide_data.extractANDPBlock( outgoing_particle_type ),
	      raw_nuclide_data.extractLDLWPBlock( outgoing_particle_type ),
	      raw_nuclide_data.extractDLWPBlock( outgoing_particle_type ) );
 }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
