//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tet mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TET_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_TET_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// Std Lib Includes
#include <string>
#include <memory>

// Boost Includes
#include <boost/mpl/vector.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/scoped_ptr.hpp>

// Moab Includes
#include <moab/Interface.hpp>
#include <moab/AdaptiveKDTree.hpp>
#include <moab/Matrix3.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

/*! The tet-mesh track length flux estimator class
 * \ingroup particle_subtrack_ending_global_event
 * \details This class is based off of the TrackLengthMeshTally written by
 * Kerry Dunn (UW-Madison CNERG group). The DAGMC repo that contains her
 * class can be found at https://github.com/svalinn/DAGMC.
 */
template<typename ContributionMutliplierPolicy = WeightMultiplier>
class TetMeshTrackLengthFluxEstimator : public StandardEntityEstimator<moab::EntityHandle>,
  public ParticleSubtrackEndingGlobalEventObserver
{

public:

  //! Typedef for the cell id type
  typedef Geometry::ModuleTraits::InternalCellHandle cellIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingGlobalEventObserver::EventTag>
  EventTags;

  //! Constructor
  TetMeshTrackLengthFluxEstimator(
		     const Estimator::idType id,
		     const double multiplier,
		     const std::string input_mesh_file_name,
		     const std::string output_mesh_file_name = "tetmesh.h5m" );

  //! Destructor
  ~TetMeshTrackLengthFluxEstimator()
  { /* ... */ }

  //! Set the response functions
  void setResponseFunctions(
  const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Add current history estimator contribution
  void updateFromGlobalParticleSubtrackEndingEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  //! Export the estimator data
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
		   const bool process_data ) const;

  //! Print a summary of the estimator data
  void printSummary( std::ostream& os ) const;

  //! Get all tet elements
  const moab::Range getAllTetElements() const;

  //! Test if a point is in the mesh
  bool isPointInMesh( const double point[3] );

  //! Determine which tet the point is in
  moab::EntityHandle whichTetIsPointIn( const double point[3] );

private:

  // Assign bin boundaries to an estimator dimension
  void assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries );

  // The tolerance used for geometric tests
  static const double s_tol;

  // The moab instance that stores all mesh data
  boost::scoped_ptr<moab::Interface> d_moab_interface;

  // The tet meshset
  moab::EntityHandle d_tet_meshset;

  // The kd-tree for finding point in tet
  boost::scoped_ptr<moab::AdaptiveKDTree> d_kd_tree;
  
  // The root of the kd-tree
  moab::EntityHandle d_kd_tree_root;

  // The map of tet ids and barycentric coordinate transform matrices
  boost::unordered_map<moab::EntityHandle,moab::Matrix3> 
  d_tet_barycentric_transform_matrices;
  
  // The map of tet ids and reference vertices
  boost::unordered_map<moab::EntityHandle, moab::CartVect>
  d_tet_reference_vertices;
  
  // The output mesh file name
  std::string d_output_mesh_name;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_TetMeshTrackLengthFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_TET_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
