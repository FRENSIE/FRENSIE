//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EstimatorHandlerFactory.hpp
//! \author Alex Robinson
//! \brief  Estimator handler factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_HANDLER_FACTORY_HPP
#define FACEMC_ESTIMATOR_HANDLER_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Facemc_EstimatorHandler.hpp"

namespace Facemc{

//! The estimator handler factory
class EstimatorHandlerFactory
{

public:

  //! Initialize the estimator handler using DagMC
  static void initializeHandlerUsingDagMC(
			        const Teuchos::ParameterList& response_reps,
				const Teuchos::ParameterList& estimator_reps );


private:

  // Constructor
  EstimatorHandlerFactory();

  // Validate an estimator representation
  static void validateEstimatorRep( 
	  const Teuchos::ParameterList& estimator_rep,
	  const boost::unordered_map<unsigned,Teuchos::RCP<ResponseFunction> >&
	  response_id_map );

  // Create the estimator data maps using DagMC information
  static void createEstimatorDataMapsUsingDagMC(
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
};

//! The invalid estimator representation error
class InvalidEstimatorRepresentation : public std::logic_error
{
  
public:

  InvalidEstimatorRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

} // end Facemc namespace

#endif // end FACEMC_ESTIMATOR_HANDLER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Facemc_EstimatorHandlerFactory.hpp
//---------------------------------------------------------------------------//
