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
#include "MonteCarlo_NuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

namespace MonteCarlo{

//! The nuclear scattering distribution factory helper for neutron scattering
template<>
class NuclearScatteringDistributionACEFactoryHelper<NeutronState,NeutronState>;

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

//! The nuclear scattering distribution factory helper for neutron scattering
template<>
class NuclearScatteringDistributionACEFactoryHelper<NeutronState,NeutronState>
{
public:

  //! Create the elastic scattering distribution
  static void createElasticScatteringDistribution(
             std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >& distribution,
             const std::string ace_table_name,
             const bool defined_in_cm_system,
             const double atomic_weight_ratio,
             const double free_gas_threshold,
             const std::shared_ptr<const NuclearScatteringAngularDistribution>&
             angular_distribution );

  //! Check if elastic scattering is handled implicitly in ACE table
  static bool isElasticScatteringImplicit();
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
