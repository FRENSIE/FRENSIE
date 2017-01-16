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
#include <functional>
#include <vector>
#include <map>
#include <set>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_ParticleSourceDimension.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"

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
   const ParticleType particle_type,
   const std::set<ParticleSourceDimensionType>& independent_dimensions,
   const std::map<ParticleSourceDimensionType,std::shared_ptr<const ParticleSourceDimension> >& dimensions,
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy );

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

  //! Set the critical line energies
  void setCriticalLineEnergies(
               const Teuchos::ArrayRCP<const double>& critical_line_energies );

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

  // Check if the sampled particle position is valid
  bool isSampledParticlePositionValid( const ParticleState& particle ) const;

  // Generate probe particles
  void generateProbeParticles(
                             ParticleSourcePhaseSpacePoint& phase_space_sample,
                             ParticleBank& bank,
                             const unsigned long long history ) const;

  // Reduce the local samples counters
  unsigned long long reduceLocalSamplesCounters() const;

  // Reduce the local trials counters
  unsigned long long reduceLocalTrialsCounters() const;

  // The source id
  unsigned d_id;

  // The type of particle emitted
  ParticleType d_particle_type;

  // The independent particle source dimensions
  std::set<ParticleSourceDimensionType> d_independent_dimensions;

  // The particle source dimensions
  std::map<ParticleSourceDimensionType,std::shared_ptr<const ParticleSourceDimension> > d_dimensions;

  // The spatial coordinate conversion policy
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
  d_spatial_coord_conversion_policy;

  // The directional coordinate conversion policy
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
  d_directional_coord_conversion_policy;

  // The critical line energies
  Teuchos::ArrayRCP<const double> d_critical_line_energies;

  // The cell rejection functions
  typedef std::function<Geometry::PointLocation (const Geometry::Ray&)> CellRejectionFunction;
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
    std::bind<Geometry::PointLocation>( location_function,
                                        std::placeholders::_1,
                                        cell );

  d_cell_rejection_functions.push_back( new_cell_rejection_function );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.hpp
//---------------------------------------------------------------------------//
