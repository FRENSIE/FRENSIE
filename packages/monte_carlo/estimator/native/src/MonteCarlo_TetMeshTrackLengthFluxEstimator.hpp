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

// Boost Includes
#include <boost/mpl/vector.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Moab Includes
#include <moab/Interface.hpp>
#include <moab/AdaptiveKDTree.hpp>
#include <moab/OrientedBoxTreeTool.hpp>
#include <moab/Matrix3.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The tet-mesh track length flux estimator class
template<typename ContributionMutliplierPolicy = WeightMultiplier>
class TetMeshTrackLengthFluxEstimator : public Estimator
{

public:

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
  void updateFromParticleSubtrackEndingEvent(
			      const ParticleState& particle,
			      const Geometry::ModuleTraits::InternalCellHandle,
			      const double track_length );

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Print the estimator data
  void print( std::ostream& os ) const;

private:

  // Assign bin boundaries to an estimator dimension
  void assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries );

  // The moab instance that stores all mesh data
  Teuchos::RCP<moab::Interface> d_moab_interface;

  // The kd-tree for finding point in tet
  Teuchos::RCP<moab::AdaptiveKDTree> d_kd_tree;
  
  // The root of the kd-tree
  moab::EntityHandle d_kd_tree_root;
  
  // The oriented box tree for finding intersections with the mesh
  Teuchos::RCP<moab::OrientedBoxTreeTool> d_obb_tree;

  // The root of the obb-tree
  moab::EntityHandle d_obb_tree_root;

  // The last tet that was visited
  moab::EntityHandle d_last_visited_tet;

  // The last cell that was visited
  Geometry::ModuleTraits::InternalCellHandle d_last_visited_cell;

  // The map of tet ids and tet volumes
  boost::unordered_map<moab::EntityHandle,double> 
  d_tet_volumes;

  // The map of tet ids and barycentric coordinate transform matrices
  boost::unordered_map<moab::EntityHandle,moab::Matrix3> 
  d_tet_barycentric_transform_matrices;

  // The map of tet estimator moments
  boost::unordered_map<moab::EntityHandle,Teuchos::Array<Utility::Pair<double,double> > >
  d_tet_estimator_moments;

  // The map of tet current history contributions
  boost::unordered_map<moab::EntityHandle,Teuchos::Array<double> >
  d_tet_estimator_current_history_contributions;

  // The set of tet that have been updated
  boost::unordered_set<moab::EntityHandle>
  d_tets_updated_this_history;
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
