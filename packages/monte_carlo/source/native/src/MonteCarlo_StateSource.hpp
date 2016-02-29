//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StateSource.hpp
//! \author Alex Robinson
//! \brief  State source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STATE_SOURCE_HPP
#define MONTE_CARLO_STATE_SOURCE_HPP

// Std Lib Includes
#include <string>

// Boost includes
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "Utility_ArchivableObject.hpp"

namespace MonteCarlo{

//! The state source class
class StateSource : public ParticleSource
{
  
public:

  //! Constructor
  StateSource( const std::string& state_source_bank_archive_name,
	       const std::string& bank_name_in_archive,
	       const Utility::ArchivableObject::ArchiveType archive_type );

  //! Destructor
  ~StateSource()
  { /* ... */ }

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
			    const unsigned long long history );

  //! Return the sampling efficiency from the source 
  double getSamplingEfficiency() const;

private:

  // Compare two particle state cores
  static bool compareHistoryNumbers( const ParticleState& state_a,
				     const ParticleState& state_b );

  // The possible states
  boost::unordered_map<unsigned long long,Teuchos::Array<boost::shared_ptr<ParticleState> > >
  d_particle_states;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STATE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StateSource.hpp
//---------------------------------------------------------------------------//

