//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp
//! \author Philip Britt
//! \brief  Hex mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HEX_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_HEX_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <functional>

// Boost Includes
#include <boost/mpl/vector.hpp>
#include <boost/unordered_map.hpp>

// Moab Includes
#include <moab/Core.hpp>
#include <moab/ScdInterface.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The hex-mesh track length flux estimator class.
 * \Utilizes a structured hex mesh geometry to calculate
 * \flux.
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class HexMeshTrackLengthFluxEstimator : public StandardEntityEstimator<Utility::StructuredHexMesh::HexIndex>,
                                        public ParticleSubtrackEndingGlobalEventObserver
{
  // Typedef for base estimator type
  typedef StandardEntityEstimator<Utility::StructuredHexMesh::HexIndex> BaseEstimatorType

  // Typedef for entity norm constants map
  typedef typename BaseEstimatorType::EntityNormConstMap EntityNormConstMap;

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingGlobalEventObserver::EventTag>
  EventTags;

  //! Typedef for iterator over hex element IDs
  typedef Utility::StructuredHexMesh::HexIDIterator HexIDIterator;

  //! Constructor
  HexMeshTrackLengthFluxEstimator(
		     const Estimator::idType id,
		     const double multiplier,
		     const std::vector<double>& x_planes,
                     const std::vector<double>& y_planes,
                     const std::vector<double>& z_planes,
		     const std::string output_mesh_file_name = "hexmesh.vtk" );

  //! Destructor
  ~HexMeshTrackLengthFluxEstimator()
  { /* ... */ }

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const std::vector<ParticleType>& particle_types );

  //! Set the response functions
  void setResponseFunctions(
  const std::vector<std::shared_ptr<ResponseFunction> >& response_functions );

  //! Add current history estimator contribution
  void updateFromGlobalParticleSubtrackEndingEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  //! Print the estimator data
  void printSummary( std::ostream& os ) const;

  //! Get start iterator over list of hex element IDs
  HexIDIterator getStartHex() const;

  //! Get end iterator over list of hex element IDs
  HexIDIterator getEndHex() const;

  //! Print the estimator data
  void print( std::ostream& os ) const;

  //! Determine which hex the point is in
  moab::EntityHandle whichHexIsPointIn( const double point[3] );

protected:



private:

  // Default constructor
  HexMeshTrackLengthFluxEstimator();

  // Add current history estimator contribution
  void updateFromGlobalParticleSubtrackEndingEventNoTimeBinsImpl(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  // Add current history estimator contribution
  void updateFromGlobalParticleSubtrackEndingEventTimeBinsImpl(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  // Assign discretization to an estimator dimension
  void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                             const bool range_dimension ) final override;

  // Assign the particle type to the estimator
  void assignParticleType( const ParticleType particle_type ) final override;

  // Assign response function to the estimator
  void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function ) final override;

  // Export the estimator data and mesh as a vtk file
  void exportAsVtk();

  // The output mesh file name
  std::string d_output_mesh_file_name;

  // hex mesh object
  std::shared_ptr<Utility::StructuredHexMesh> d_hex_mesh;

  // The update function
  typedef std::function<void(const Particle&,const double[3],const double[3])> UpdateFunction;
  UpdateFunction d_update_method;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_HexMeshTrackLengthFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_HEX_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
