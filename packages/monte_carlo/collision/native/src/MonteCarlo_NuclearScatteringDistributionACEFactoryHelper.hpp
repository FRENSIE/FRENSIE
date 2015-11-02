//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp
//! \author Alex Robinson
//! \brief  Nuclear scattering distribution factory helper class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HELPER_HPP
#define MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HELPER_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

//! The nuclear scattering distribution factory helper
template<typename IncomingParticleType, typename OutgoingParticleType>
class NuclearScatteringDistributionACEFactoryHelper
{
public:
  
  //! Create the elastic scattering distribution
  static void createElasticScatteringDistribution( 
		      Teuchos::RCP<NuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType> >& distribution,
		      const std::string ace_table_name,
		      const bool defined_in_cm_system,
		      const double atomic_weight_ratio,
          const Teuchos::RCP<NuclearScatteringAngularDistribution>&
		      angular_distribution )
  {
    THROW_EXCEPTION( std::logic_error,
		     "Error: elastic scattering for different particle types ("
		       << IncomingParticleType::type << " !="
		       << OutgoingParticleType::type << ") is not possible!");
  }

  /*! Check if elastic scattering is handled implicitly in ACE table
   * \details In some ACE tables, an elastic scattering distribution is always
   * given and will therefore not appear in the mtr block 
   * (e.g. continuous-energy neutron tables).
   */
  static bool isElasticScatteringImplicit()
  {
    return false;
  }
};

//! The nuclear scattering distribution factory helper
template<typename ParticleType>
class NuclearScatteringDistributionACEFactoryHelper<ParticleType,ParticleType>
{
public:
  
  //! Create the elastic scattering distribution
  static void createElasticScatteringDistribution( 
          Teuchos::RCP<NuclearScatteringDistribution<ParticleType,ParticleType> >& distribution,
          const std::string ace_table_name,
		      const bool defined_in_cm_system,
		      const double atomic_weight_ratio,
          const Teuchos::RCP<NuclearScatteringAngularDistribution>&
		      angular_distribution )
  {
    THROW_EXCEPTION( std::logic_error,
		     "Error: elastic scattering is not defined for "
		     << ParticleType::type << "!");
  }

  //! Check if elastic scattering is handled implicitly in ACE table
  static bool isElasticScatteringImplicit()
  {
    return false;
  }
};

//! The nuclear scattering distribution factory helper for neutron scattering
template<>
class NuclearScatteringDistributionACEFactoryHelper<NeutronState,NeutronState>
{
public:
  
  //! Create the elastic scattering distribution
  static void createElasticScatteringDistribution( 
		      Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> >& distribution,
		      const std::string ace_table_name,
		      const bool defined_in_cm_system,
		      const double atomic_weight_ratio,
                      const Teuchos::RCP<NuclearScatteringAngularDistribution>&
		      angular_distribution );

  //! Check if elastic scattering is handled implicitly in ACE table
  static bool isElasticScatteringImplicit();
};

}

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HELPER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp
//---------------------------------------------------------------------------//
