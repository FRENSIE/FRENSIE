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

// Boost Includes
#include <boost/mpl/vector.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trillinos includes
#include <Teuchos_Array.hpp>

// Moab Includes
#include <moab/Core.hpp>
#include <moab/ScdInterface.hpp>
#include <moab/Matrix3.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_StructuredHexMesh.hpp"

namespace MonteCarlo{

template<typename ContributionMutliplierPolicy = WeightMultiplier>
class HexMeshTrackLengthFluxEstimator : public StandardEntityEstimator<Utility::StructuredHexMesh::HexIndex>,
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
		     const Teuchos::Array<double>& x_planes,
                     const Teuchos::Array<double>& y_planes,
                     const Teuchos::Array<double>& z_planes,
		     const std::string output_mesh_file_name = "hexmesh.vtk" );

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
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                   const bool process_data ) const;

  //! Print the estimator data
  void printSummary( std::ostream& os ) const;

  Utility::StructuredHexMesh::HexIDIterator getStartHex() const;
  
  Utility::StructuredHexMesh::HexIDIterator getEndHex() const;

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
  
  // The output mesh file name
  std::string d_output_mesh_file_name;
  
  // hex mesh object
  std::shared_ptr<Utility::StructuredHexMesh> d_hex_mesh;

  // starting iterator over the hex mesh elements
  Utility::StructuredHexMesh::HexIDIterator d_hex_begin;
  
  // ending iterator for the hex mesh elements
  Utility::StructuredHexMesh::HexIDIterator d_hex_end;

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
