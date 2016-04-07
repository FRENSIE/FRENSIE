//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSourceFactory.hpp
//! \author Alex Robinson
//! \brief  Standard particle source factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_SOURCE_FACTORY_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_SOURCE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceFactory.hpp"

namespace MonteCarlo{

//! The standard particle source factory
template<typename GeometryModuleInterface>
class StandardParticleSourceFactory : public ParticleSourceFactory
{
  
public:

  //! Get an instance of the factory
  static std::shared_ptr<ParticleSourceFactory> getInstance();

  //! Destructor
  ~StandardParticleSourceFactory()
  { /* ... */ }

  //! Create the particle source represented by the parameter list
  std::shared_ptr<ParticleSource>
  createSource( const Teuchos::ParameterList& source_rep,
		const ParticleModeType& particle_mode,
                std::ostream& os_warn = std::cerr );

private:

  // The factory instance
  static std::shared_ptr<ParticleSourceFactory> factory_instance;

  //! Constructor
  StandardParticleSourceFactory()
  { /* ... */ }
};

// Initialize static member data
template<typename GeometryModuleInterface>
std::shared_ptr<ParticleSourceFactory> 
StandardParticleSourceFactory<GeometryModuleInterface>::factory_instance(
		new StandardParticleSourceFactory<GeometryModuleInterface>() );

// Get an instance of the factory
template<typename GeometryModuleInterface>
inline std::shared_ptr<ParticleSourceFactory>
StandardParticleSourceFactory<GeometryModuleInterface>::getInstance()
{
  return factory_instance;
}

// Create the particle source represented by the parameter list
template<typename GeometryModuleInterface>
inline std::shared_ptr<ParticleSource>
StandardParticleSourceFactory<GeometryModuleInterface>::createSource( 
				     const Teuchos::ParameterList& source_rep,
				     const ParticleModeType& particle_mode,
                                     std::ostream& os_warn )
{
  return ParticleSourceFactory::createSourceImpl<GeometryModuleInterface>( 
                                          source_rep, particle_mode, os_warn );
} 

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSourceFactory.hpp
//---------------------------------------------------------------------------//
