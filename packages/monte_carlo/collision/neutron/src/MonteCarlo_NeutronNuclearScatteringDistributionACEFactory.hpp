//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  Neutron nuclear scattering distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_NEUTRON_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionACEFactoryNeutronHelper.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

namespace MonteCarlo{

//! The scattering distribution factory class
class NeutronNuclearScatteringDistributionACEFactory : public NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,MonteCarlo::NeutronState>
{

public:

  //! Constructor
  NeutronNuclearScatteringDistributionACEFactory(
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSNeutronDataExtractor& raw_nuclide_data );

  //! Destructor
  ~NeutronNuclearScatteringDistributionACEFactory()
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
