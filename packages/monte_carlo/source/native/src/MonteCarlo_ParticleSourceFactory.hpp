//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceFactory.hpp
//! \author Alex Robinson
//! \brief  Particle source factory base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SOURCE_FACTORY_HPP
#define FACEMC_PARTICLE_SOURCE_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_DistributedSource.hpp"

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
  virtual Teuchos::RCP<ParticleSource>
  createSource( const Teuchos::ParameterList& source_rep ) = 0;

protected:

  // Create the particle source represented by the parameter list
  template<typename GeometryHandler>
  static Teuchos::RCP<ParticleSource>
  createSourceImpl( const Teuchos::ParameterList& source_rep );

private:

  // Validate a source respresentation
  static void validateSourceRep( const Teuchos::ParameterList& source_rep,
				 const unsigned num_sources = 1u );

  // Validate the particle type name
  static void validateParticleTypeName( const std::string& particle_type_name);

  // Create a distributed source
  template<typename GeometryHandler>
  static double 
  createDistributedSource(const Teuchos::ParameterList& source_rep,
			  Teuchos::RCP<ParticleSource>& source,
			  const unsigned num_sources = 1u );

  // Create a state source
  static double
  createStateSource( const Teuchos::ParameterList& source_rep,
		     Teuchos::RCP<ParticleSource>& source,
		     const unsigned num_sources = 1u );

  // Create a compound source
  template<typename GeometryHandler>
  static void
  createCompoundSource( const Teuchos::ParameterList& compound_source,
			Teuchos::RCP<ParticleSource>& source );

  // The default time distribution
  static const Teuchos::RCP<Utility::OneDDistribution> s_default_time_dist;
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

#endif // end FACEMC_PARTICLE_SOURCE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceFactory.hpp
//---------------------------------------------------------------------------//
