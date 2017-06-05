//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceHandler.hpp
//! \author Alex Robinson
//! \brief  The source handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SOURCE_HANDLER_HPP
#define MONTE_CARLO_SOURCE_HANDLER_HPP

// Std Lib Includes
#include <memory>
#include <map>
#include <utility>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ModuleTraits.hpp"

namespace MonteCarlo{

//! The soure handler class
class SourceHandler
{

public:

  //! Constructor
  SourceHandler();

  //! Destructor
  ~SourceHandler()
  { /* ... */ }

  //! Add a source to the source handler
  void addSource( const std::shared_ptr<ParticleSource>& source,
                  const double weight = 1.0 );

  //! Get the number of sources
  size_t getNumberOfSources() const;

  //! Check if a source exists
  bool doesSourceExist( const ModuleTraits::InternalROIHandle source_id ) const;

  //! Enable thread support
  void enableThreadSupport( const size_t threads );

  //! Reset the source data
  void resetSourceData();

  //! Reduce the source data
  void reduceSourceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  //! Export the source data
  void exportSourceData( const std::shared_ptr<Utility::HDF5FileHandler>&
                         hdf5_file ) const;

  //! Print the source summaries
  void printSourceSummaries( std::ostream& os ) const;

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
			    const unsigned long long history );

private:

  // The sources (first = source, second = source weight)
  typedef std::map<ModuleTraits::InternalROIHandle,std::shared_ptr<ParticleSource> >
  SourceIdMap;

  SourceIdMap d_sources;

  // The source cdf
  typedef Teuchos::Array<std::pair<ModuleTraits::InternalROIHandle, double> > SourceIdCDFPairArray;

  SourceIdCDFPairArray d_source_cdf;

  // The total source weight
  double d_total_source_weight;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SOURCE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceHandler.hpp
//---------------------------------------------------------------------------//
