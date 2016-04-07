//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceFactory.hpp
//! \author Alex Robinson
//! \brief  Particle source factory base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_FACTORY_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <memory>
#include <iostream>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ParticleModeType.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The particle source factory base class
class ParticleSourceFactory
{

public:

  //! Constructor
  ParticleSourceFactory()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleSourceFactory()
  { /* ... */ }

  //! Create the particle source represented by the parameter list
  virtual std::shared_ptr<ParticleSource>
  createSource( const Teuchos::ParameterList& source_rep,
		const ParticleModeType& particle_mode,
                std::ostream& os_warn ) = 0;

protected:

  // Create the particle source represented by the parameter list
  template<typename GeometryModuleInterface>
  static std::shared_ptr<ParticleSource>
  createSourceImpl( const Teuchos::ParameterList& source_rep,
		    const ParticleModeType& particle_mode,
                    std::ostream& os_warn );

private:

  // Validate a source respresentation
  static void validateSourceRep( const Teuchos::ParameterList& source_rep,
				 const unsigned num_sources = 1u );

  // Get the particle type enum
  static ParticleType getParticleType( const Teuchos::ParameterList& source_rep,
				       const ParticleModeType& particle_mode );

  // Validate the particle type name
  static void validateParticleTypeName( const std::string& particle_type_name);

  // Create a standard source
  template<typename GeometryModuleInterface, typename SourceType>
  static double 
  createStandardSource( const Teuchos::ParameterList& source_rep,
                        const ParticleModeType& particle_mode,
                        std::shared_ptr<SourceType>& source,
                        std::ostream& os_warn,
                        const unsigned num_sources = 1u );

  // Create a cached state source
  static void
  createCachedStateSource( const Teuchos::ParameterList& source_rep,
                           const ParticleModeType& particle_mode,
                           std::shared_ptr<ParticleSource>& source,
                           std::ostream& os_warn );

  // Create a compound standard source
  template<typename GeometryModuleInterface>
  static void
  createCompoundStandardSource( const Teuchos::ParameterList& compound_source,
                                const ParticleModeType& particle_mode,
                                std::shared_ptr<ParticleSource>& source,
                                std::ostream& os_warn );

  // The default time distribution
  static const std::shared_ptr<Utility::OneDDistribution> s_default_time_dist;
};

//! The invalid particle source representation error
class InvalidParticleSourceRepresentation : public std::runtime_error
{
  
public:

  InvalidParticleSourceRepresentation( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleSourceFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_SOURCE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceFactory.hpp
//---------------------------------------------------------------------------//
