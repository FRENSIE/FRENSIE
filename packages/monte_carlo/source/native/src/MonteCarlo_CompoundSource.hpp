//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_CompoundSource.hpp
//! \author Alex Robinson
//! \brief  Compound source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPOUND_SOURCE_HPP
#define MONTE_CARLO_COMPOUND_SOURCE_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The compound source class
 * \details This class stores an array of the other source classes and can
 * be used to represent more complicated sources (i.e. sources that reside in
 * multiple locations). Each source will have an associated value that is used 
 * to sample the source that will be used for sampling a particle state.
 */
class CompoundSource : public ParticleSource
{

public:
  
  //! Constructor
  CompoundSource( 
               const Teuchos::Array<std::shared_ptr<ParticleSource> >& sources,
               const Teuchos::Array<double>& source_sampling_weights );

  //! Destructor
  ~CompoundSource()
  { /* ... */ }

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
			    const unsigned long long history );
  
  //! Return the sampling efficiency from the source
  double getSamplingEfficiency() const;

private:

  // The sources (first = source, second = source weight CDF, 
  // third = number of samples from source)
  Teuchos::Array<Utility::Trip<std::shared_ptr<ParticleSource>,double,unsigned> > 
  d_sources;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPOUND_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompoundSource.hpp
//---------------------------------------------------------------------------//

