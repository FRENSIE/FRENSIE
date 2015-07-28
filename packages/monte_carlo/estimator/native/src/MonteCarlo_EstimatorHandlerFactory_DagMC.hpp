//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorHandlerFactory_DagMC.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  DagMC estimator handler factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_HANDLER_FACTORY_DAGMC_HPP
#define FACEMC_ESTIMATOR_HANDLER_FACTORY_DAGMC_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "FRENSIE_dagmc_config.hpp"
#include "MonteCarlo_EstimatorHandler.hpp"
#include "MonteCarlo_EstimatorHandlerFactoryDecl.hpp"

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_DagMCProperties.hpp"
#endif

namespace MonteCarlo{

/*! The specialization of the EstimatorHandlerFactory class for the DagMC 
 * geometry handler.
 * \ingroup estimator_module
 */ 
template<>
class EstimatorHandlerFactory<moab::DagMC>
{
public:


  //! Initialize the estimator handler using DagMC
  static void initializeHandler(
			        const Teuchos::ParameterList& response_reps,
				      const Teuchos::ParameterList& estimator_reps );

private:

  // Validate an estimator representation
  static void validateEstimatorRep( 
	  const Teuchos::ParameterList& estimator_rep,
	  const boost::unordered_map<unsigned,Teuchos::RCP<ResponseFunction> >&
	  response_id_map );

  // Test if two estimator types are equivalent
  static bool areEstimatorTypesEquivalent(
                                    const std::string& geometry_module_type,
					                const std::string& xml_type );

  // Test if an estimator type is a cell pulse height estimator
  static bool isCellPulseHeightEstimator( const std::string& estimator_name );

  // Test if an estimator type is a cell track length flux estimator
  static bool isCellTrackLengthFluxEstimator( 
					   const std::string& estimator_name );

  // Test if an estimator type is a cell collision flux estimator
  static bool isCellCollisionFluxEstimator(const std::string& estimator_name );

  // Test if an estimator type is a surface flux estimator
  static bool isSurfaceFluxEstimator( const std::string& estimator_name );

  // Test if an estimator type is a surface current estimator
  static bool isSurfaceCurrentEstimator( const std::string& estimator_name );
  
  // Create the estimator data maps using DagMC information
  static void createEstimatorDataMaps(
	boost::unordered_map<unsigned,std::string>& estimator_id_type_map,
	boost::unordered_map<unsigned,std::string>& estimator_id_ptype_map,
	boost::unordered_map<unsigned,
	          Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
	estimator_id_cells_map,
	boost::unordered_map<unsigned,
	       Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >&
	estimator_id_surfaces_map );	

  // Append data to estimator data maps
  static void appendDataToEstimatorDataMaps(
        const Teuchos::ParameterList& estimator_reps,
	boost::unordered_map<unsigned,std::string>& estimator_id_type_map,
	boost::unordered_map<unsigned,std::string>& estimator_id_ptype_map,
	boost::unordered_map<unsigned,
	          Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
	estimator_id_cells_map,
	boost::unordered_map<unsigned,
	       Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >&
	estimator_id_surfaces_map );

  // Append cells to assigned cells
  static void appendCellsToAssignedCells(
	      const unsigned estimator_id,
              Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      assigned_cells,
              const Teuchos::Array<unsigned>& extra_cells );

  // Append surfaces to assigned surfaces
  static void appendSurfacesToAssignedSurfaces(
	   const unsigned estimator_id,
	   Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   assigned_surfaces,
	   const Teuchos::Array<unsigned>& extra_surfaces );

  // Create cell volume map
  static void createCellVolumeMap(
       const boost::unordered_map<unsigned,
                  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
       estimator_id_cells_map,
       boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>&
       cell_volume_map );

  // Create the surface area map
  static void createSurfaceAreaMap(
    const boost::unordered_map<unsigned,
               Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >&
    estimator_id_surfaces_map,
    boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,double>&
    surface_area_map );

  // Create a cell pulse height estimator
  static void createPulseHeightEstimator(
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );

  // Create a cell track length flux estimator
  static void createCellTrackLengthFluxEstimator(
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells,
      const Teuchos::Array<double>& cell_volumes,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );
  
  // Create a cell collision flux estimator
  static void createCellCollisionFluxEstimator(
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells,
      const Teuchos::Array<double>& cell_volumes,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );  

  // Create a surface flux estimator
  static void createSurfaceFluxEstimator(
         const unsigned id,
	 const double multiplier,
	 const Teuchos::Array<ParticleType> particle_types,
	 const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	 surfaces,
	 const Teuchos::Array<double>& surface_areas,
	 const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
	 const bool energy_multiplication = false,
	 const Teuchos::ParameterList* bins = NULL );

  // Create a surface current estimator
  static void createSurfaceCurrentEstimator(
         const unsigned id,
	 const double multiplier,
	 const Teuchos::Array<ParticleType> particle_types,
	 const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	 surfaces,
	 const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
	 const bool energy_multiplication = false,
	 const Teuchos::ParameterList* bins = NULL );

  // Create a tet mesh track length flux estimator
  static void createTetMeshTrackLengthFluxEstimator(
	 const unsigned id,
	 const double multiplier,
	 const Teuchos::Array<ParticleType> particle_types,
	 const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
	 const std::string& mesh_file_name,
	 const std::string& output_mesh_file_name,
	 const bool energy_multiplication = false,
	 const Teuchos::ParameterList* bins = NULL );

  // Assign bins to an estimator
  static void assignBinsToEstimator( const Teuchos::ParameterList& bins,
				     Teuchos::RCP<Estimator>& estimator ); 

  // Fill cell volumes array
  static void fillCellVolumesArray( 
       const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells,
	const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
	                           double>& cell_volume_map,
	Teuchos::Array<double>& cell_volumes );

  // Fill the surface areas array
  static void fillSurfaceAreasArray(
      const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
      surfaces,
      const boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,
                                 double>& surface_area_map,
      Teuchos::Array<double>& surface_areas );	

  // Check if the estimator type is valid
  static bool isEstimatorTypeValid( const std::string& estimator_type );

  // Check if a cell estimator type is valid
  static bool isCellEstimatorTypeValid( const std::string& estimator_type );

  // Check if a surface estimator type is valid
  static bool isSurfaceEstimatorTypeValid( const std::string& estimator_type );
  
  // Check if a mesh estimator type is valid
  static bool isMeshEstimatorTypeValid( const std::string& estimator_type );

  // The surface current estimator name
  static const std::string surface_current_name;

  // The surface flux estimator name
  static const std::string surface_flux_name;

  // The cell pulse height estimator name
  static const std::string cell_pulse_height_name;

  // The cell track-length flux estimator name
  static const std::string cell_track_length_flux_name;

  // The cell collision flux estimator name
  static const std::string cell_collision_flux_name;

  // The tet mesh track-length flux estimator name
  static const std::string tet_mesh_track_length_flux_name;
};

// Test if an estimator type is a cell pulse height estimator
inline bool EstimatorHandlerFactory<moab::DagMC>::isCellPulseHeightEstimator( 
					    const std::string& estimator_name )
{
#ifdef HAVE_FRENSIE_DAGMC
  return (estimator_name == 
	  Geometry::DagMCProperties::getCellPulseHeightName() ||
	  estimator_name ==
	  EstimatorHandlerFactory<moab::DagMC>::cell_pulse_height_name);
#else
  return estimator_name == EstimatorHandlerFactory<moab::DagMC>::cell_pulse_height_name;
#endif
}

// Test if an estimator type is a cell track length flux estimator
inline bool EstimatorHandlerFactory<moab::DagMC>::isCellTrackLengthFluxEstimator( 
					    const std::string& estimator_name )
{
#ifdef HAVE_FRENSIE_DAGMC
  return (estimator_name == 
	  Geometry::DagMCProperties::getCellTrackLengthFluxName() ||
	  estimator_name ==
	  EstimatorHandlerFactory<moab::DagMC>::cell_track_length_flux_name);
#else
  return estimator_name ==
    EstimatorHandlerFactory<moab::DagMC>::cell_track_length_flux_name;
#endif
}

// Test if an estimator type is a cell collision flux estimator
inline bool EstimatorHandlerFactory<moab::DagMC>::isCellCollisionFluxEstimator(
					    const std::string& estimator_name )
{
#ifdef HAVE_FRENSIE_DAGMC
  return (estimator_name == 
          Geometry::DagMCProperties::getCellCollisionFluxName() ||
          estimator_name ==
          EstimatorHandlerFactory<moab::DagMC>::cell_collision_flux_name);
#else
  return estimator_name == EstimatorHandlerFactory<moab::DagMC>::cell_collision_flux_name;
#endif
}

// Test if an estimator type is a surface flux estimator
inline bool EstimatorHandlerFactory<moab::DagMC>::isSurfaceFluxEstimator(
					    const std::string& estimator_name )
{
#ifdef HAVE_FRENSIE_DAGMC
  return (estimator_name == 
	  Geometry::DagMCProperties::getSurfaceFluxName() ||
	  estimator_name == 
	  EstimatorHandlerFactory<moab::DagMC>::surface_flux_name);
#else
  return estimator_name == EstimatorHandlerFactory<moab::DagMC>::surface_flux_name;
#endif
}

// Test if an estimator type is a surface current estimator
inline bool EstimatorHandlerFactory<moab::DagMC>::isSurfaceCurrentEstimator( 
					    const std::string& estimator_name )
{
#ifdef HAVE_FRENSIE_DAGMC
  return (estimator_name == 
	  Geometry::DagMCProperties::getSurfaceCurrentName() ||
	  estimator_name == 
	  EstimatorHandlerFactory<moab::DagMC>::surface_current_name);
#else
  return estimator_name == EstimatorHandlerFactory<moab::DagMC>::surface_current_name;
#endif
}

} // end MonteCarlo namespace

#endif // end FACEMC_ESTIMATOR_HANDLER_FACTORY_DAGMC_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandlerFactory_DagMC.hpp
//---------------------------------------------------------------------------//
