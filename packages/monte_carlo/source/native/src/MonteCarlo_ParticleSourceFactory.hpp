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

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_DistributedSource.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "MonteCarlo_ParticleModeType.hpp"

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
		const ParticleModeType& particle_mode ) = 0;

protected:

  // Create the particle source represented by the parameter list
  template<typename GeometryHandler>
  static std::shared_ptr<ParticleSource>
  createSourceImpl( const Teuchos::ParameterList& source_rep,
		    const ParticleModeType& particle_mode );

private:

  // Validate a source respresentation
  static void validateSourceRep( const Teuchos::ParameterList& source_rep,
				 const unsigned num_sources = 1u );

  // Get the particle type enum
  static ParticleType getParticleType( const Teuchos::ParameterList& source_rep,
				       const ParticleModeType& particle_mode );

  // Validate the particle type name
  static void validateParticleTypeName( const std::string& particle_type_name);

  // Create a distributed source
  template<typename GeometryHandler>
  static double 
  createDistributedSource(const Teuchos::ParameterList& source_rep,
			  const ParticleModeType& particle_mode,
			  std::shared_ptr<ParticleSource>& source,
			  const unsigned num_sources = 1u );

  // Create a state source
  static double
  createStateSource( const Teuchos::ParameterList& source_rep,
		     const ParticleModeType& particle_mode,
		     std::shared_ptr<ParticleSource>& source,
		     const unsigned num_sources = 1u );

  // Create a compound source
  template<typename GeometryHandler>
  static void
  createCompoundSource( const Teuchos::ParameterList& compound_source,
			const ParticleModeType& particle_mode,
			std::shared_ptr<ParticleSource>& source );

  // The default time distribution
  static const std::shared_ptr<Utility::OneDDistribution> s_default_time_dist;
};

//! The invalid particle source representation error
class InvalidParticleSourceRepresentation : public std::logic_error
{
  
public:

  InvalidParticleSourceRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg )
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
