//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistributionACEFactoryNeutronHelper.hpp
//! \author Alex Robinson
//! \brief  Nuclear scattering distribution ACE factory helper specialization
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_NEUTRON_HELPER_HPP
#define MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_NEUTRON_HELPER_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp"

namespace MonteCarlo{

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

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_NEUTRON_HELPER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistributionACEFactoryNeutronHelper.hpp
//---------------------------------------------------------------------------//
