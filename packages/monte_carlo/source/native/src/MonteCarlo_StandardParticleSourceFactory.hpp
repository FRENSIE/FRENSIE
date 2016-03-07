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
template<typename GeometryHandler>
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
		const ParticleModeType& particle_mode );

private:

  // The factory instance
  static std::shared_ptr<ParticleSourceFactory> factory_instance;

  //! Constructor
  StandardParticleSourceFactory()
  { /* ... */ }
};

// Initialize static member data
template<typename GeometryHandler>
std::shared_ptr<ParticleSourceFactory> 
StandardParticleSourceFactory<GeometryHandler>::factory_instance(
			new StandardParticleSourceFactory<GeometryHandler>() );

// Get an instance of the factory
template<typename GeometryHandler>
inline std::shared_ptr<ParticleSourceFactory>
StandardParticleSourceFactory<GeometryHandler>::getInstance()
{
  return factory_instance;
}

// Create the particle source represented by the parameter list
template<typename GeometryHandler>
inline std::shared_ptr<ParticleSource>
StandardParticleSourceFactory<GeometryHandler>::createSource( 
				     const Teuchos::ParameterList& source_rep,
				     const ParticleModeType& particle_mode )
{
  return ParticleSourceFactory::createSourceImpl<GeometryHandler>(source_rep, particle_mode );
} 

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSourceFactory.hpp
//---------------------------------------------------------------------------//
