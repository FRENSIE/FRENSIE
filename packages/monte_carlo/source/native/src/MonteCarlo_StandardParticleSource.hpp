//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSource.hpp
//! \author Alex Robinson
//! \brief  Standard source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>

// MONTE_CARLO Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_DirectionalDistribution.hpp"
#include "Utility_GlobalOpenMPSession.hpp"

namespace MonteCarlo{

//! The standard source class
class StandardParticleSource : public ParticleSource
{

private:
  
  // Typedef for scalar traits
  typedef Teuchos::ScalarTraits<double> ST;


public:
  
  //! Constructor
  StandardParticleSource( 
     const ModuleTraits::InternalSourceHandle id,
     const std::shared_ptr<Utility::SpatialDistribution>& spatial_distribution,
     const std::shared_ptr<Utility::DirectionalDistribution>& 
     directional_distribution,
     const std::shared_ptr<Utility::OneDDistribution>& 
     energy_distribution,
     const std::shared_ptr<Utility::OneDDistribution>& 
     time_distribution,
     const ParticleType particle_type );
  
  //! Destructor
  ~StandardParticleSource()
  { /* ... */ }

  //! Enable thread support
  void enableThreadSupport( const unsigned threads );

  //! Reset the source data
  void resetData();

  //! Reduce the source data
  void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process );

  //! Export the source data
  void exportData( 
            const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const;

  //! Print a summary of the source data
  void printSummary( std::ostream& os ) const;

  //! Set the spatial importance distribution
  void setSpatialImportanceDistribution( 
   const std::shared_ptr<Utility::SpatialDistribution>& spatial_distribution );

  //! Set the directional importance distribution
  void setDirectionalImportanceDistribution(
                       const std::shared_ptr<Utility::DirectionalDistribution>&
                       directional_distribution );

  //! Set the energy importance distribution
  void setEnergyImportanceDistribution(
       const std::shared_ptr<Utility::OneDDistribution>& energy_distribution );

  //! Set the time importance distribution
  void setTimeImportanceDistribution(
	 const std::shared_ptr<Utility::OneDDistribution>& time_distribution );

  //! Set the rejection cell
  template<typename PointLocationFunction>
  void setRejectionCell(const Geometry::ModuleTraits::InternalCellHandle& cell,
                        PointLocationFunction location_function );

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank,
			    const unsigned long long history );
  
  //! Return the number of sampling trials
  unsigned long long getNumberOfTrials() const;

  //! Return the number of samples
  unsigned long long getNumberOfSamples() const;

  //! Get the sampling efficiency from the source distribution
  double getSamplingEfficiency() const;

  //! Get the source id
  unsigned getId() const;

private:

  // Sample the particle position
  void sampleParticlePosition( ParticleState& particle );

  // Sample the particle direction
  void sampleParticleDirection( ParticleState& particle );

  // Sample the particle energy
  void sampleParticleEnergy( ParticleState& particle );
  
  // Sample the particle time
  void sampleParticleTime( ParticleState& particle );

  // Reduce the local samples counters
  unsigned long long reduceLocalSamplesCounters() const;

  // Reduce the local trials counters
  unsigned long long reduceLocalTrialsCounters() const;

  // The spatial distribution of the source 
  std::shared_ptr<Utility::SpatialDistribution> d_spatial_distribution;
  
  // The true spatial distribution of the source
  std::shared_ptr<Utility::SpatialDistribution> 
  d_spatial_importance_distribution;

  // The directional distribution
  std::shared_ptr<Utility::DirectionalDistribution> d_directional_distribution;

  // The true directional distribution of the source
  std::shared_ptr<Utility::DirectionalDistribution> 
  d_directional_importance_distribution;

  // The energy distribution
  std::shared_ptr<Utility::OneDDistribution> d_energy_distribution;

  // The true energy distribution of the source
  std::shared_ptr<Utility::OneDDistribution> d_energy_importance_distribution;

  // The time distribution
  std::shared_ptr<Utility::OneDDistribution> d_time_distribution;

  // The true time distribution of the source
  std::shared_ptr<Utility::OneDDistribution> d_time_importance_distribution;

  // The source id
  unsigned d_id;

  // The type of particle emitted
  ParticleType d_particle_type;

  // The cell rejection functions
  typedef boost::function<Geometry::PointLocation (const Geometry::Ray&)> CellRejectionFunction; 
  Teuchos::Array<CellRejectionFunction> d_cell_rejection_functions;

  // The number of trials
  Teuchos::Array<unsigned long long> d_number_of_trials;

  // The number of valid samples
  Teuchos::Array<unsigned long long> d_number_of_samples;
};

// Set a rejection cell
/*! \details A rejection cell is used to determine if a sampled particle
 * position should be kept or rejected. If the sampled point is inside of 
 * one of the rejection cells, it is kept. This function can be used to 
 * set multiple rejection cells. Only the master thread should call this
 * method.
 */
template<typename PointLocationFunction>
inline void StandardParticleSource::setRejectionCell( 
                        const Geometry::ModuleTraits::InternalCellHandle& cell,
                        PointLocationFunction location_function )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the cell is valid
  testPrecondition( cell != 
                    Geometry::ModuleTraits::invalid_internal_cell_handle );
  
  CellRejectionFunction new_cell_rejection_function = 
    boost::bind<Geometry::PointLocation>( location_function, _1, cell );

  d_cell_rejection_functions.push_back( new_cell_rejection_function );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.hpp
//---------------------------------------------------------------------------//
