//---------------------------------------------------------------------------//
//!
//! \file   NeutronPhotonScatteringDistributionACEFactory.cpp
//! \author Eli Moll
//! \brief  Photon production nuclear scattering distribution factory class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <stdexcept>

// Trilinos Includes
#include "Teuchos_ArrayView.hpp"
#include "Teuchos_Array.hpp"

// FRENSIE Includes
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"

namespace MonteCarlo{

// Constructor
PhotonProductionNuclearScatteringDistributionACEFactory::PhotonProductionNuclearScatteringDistributionACEFactory( 
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSNeutronDataExtractor& raw_nuclide_data )
  : NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,MonteCarlo::PhotonState>( 
					   table_name,
					   atomic_weight_ratio,
					   raw_nuclide_data.extractMTRPBlock(),
					   raw_nuclide_data.extractLANDPBlock(),
					   raw_nuclide_data.extractANDPBlock(),
					   raw_nuclide_data.extractLDLWPBlock(),
					   raw_nuclide_data.extractDLWPBlock() )
{ /* ... */ }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
