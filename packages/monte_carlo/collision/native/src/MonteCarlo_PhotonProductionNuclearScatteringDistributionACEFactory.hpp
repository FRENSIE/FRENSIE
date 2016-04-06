//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp
//! \author Eli Moll
//! \brief  Photon production nuclear scattering distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_PRODUCTION_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_PHOTON_PRODUCTION_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

namespace MonteCarlo{

//! The scattering distribution factory class
class PhotonProductionNuclearScatteringDistributionACEFactory : public NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,MonteCarlo::PhotonState>
{
  
public:

  //! Constructor 
  PhotonProductionNuclearScatteringDistributionACEFactory( 
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSNeutronDataExtractor& raw_nuclide_data );
			
  //! Destructor
  ~PhotonProductionNuclearScatteringDistributionACEFactory()
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_PRODUCTION_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
