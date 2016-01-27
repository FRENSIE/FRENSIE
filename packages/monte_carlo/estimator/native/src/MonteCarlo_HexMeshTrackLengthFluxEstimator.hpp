//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Hex mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HEX_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_HEX_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/mpl/vector.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

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

/*! The hex-mesh track length flux estimator class
 * \details This class is based off of the TrackLengthMeshTally written by
 * Kerry Dunn (UW-Madison CNERG group). The DAGMC repo that contains her
 * class can be found at https://github.com/svalinn/DAGMC.
 */
template<typename ContributionMutliplierPolicy = WeightMultiplier>
class HexMeshTrackLengthFluxEstimator : public StandardEntityEstimator<moab::EntityHandle>,
  public ParticleSubtrackEndingGlobalEventObserver
{

public:

  //! Typedef for the cell id type
  typedef Geometry::ModuleTraits::InternalCellHandle cellIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingGlobalEventObserver::EventTag>
  EventTags;

  //! Constructor
  HexMeshTrackLengthFluxEstimator(
		     const Estimator::idType id,
		     const double multiplier,
		     const std::string input_mesh_file_name,
		     const std::string output_mesh_file_name = "hexmesh.h5m" );

  //! Destructor
  ~HexMeshTrackLengthFluxEstimator()
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
  void exportData( EstimatorHDF5FileHandler& hdf5_file,
		   const bool process_data ) const;

  //! Print the estimator data
  void print( std::ostream& os ) const;

  //! Get all hex elements
  const moab::Range getAllHexElements() const;

  //! Test if a point is in the mesh
  bool isPointInMesh( const double point[3] );

  //! Determine which hex the point is in
  moab::EntityHandle whichHexIsPointIn( const double point[3] );

private:

  // Assign bin boundaries to an estimator dimension
  void assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries );

  // The tolerance used for geometric tests
  static const double s_tol;

  // The moab instance that stores all mesh data
  Teuchos::RCP<moab::Interface> d_moab_interface;

  // The hex meshset
  moab::EntityHandle d_hex_meshset;

  // The kd-tree for finding point in hex
  Teuchos::RCP<moab::AdaptiveKDTree> d_kd_tree;
  
  // The root of the kd-tree
  moab::EntityHandle d_kd_tree_root;

  // The map of hex ids and barycentric coordinate transform matrices
  boost::unordered_map<moab::EntityHandle,moab::Matrix3> 
  d_hex_barycentric_transform_matrices;
  
  // The map of hex ids and reference vertices
  boost::unordered_map<moab::EntityHandle, moab::CartVect>
  d_hex_reference_vertices;
  
  // The output mesh file name
  std::string d_output_mesh_name;
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
