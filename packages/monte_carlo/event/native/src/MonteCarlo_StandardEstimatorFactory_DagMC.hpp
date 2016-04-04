//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEstimatorFactory_DagMC.hpp
//! \author Alex Robinson
//! \brief  The standard estimator factory class specialization for DagMC
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_DAGMC_HPP
#define MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_DAGMC_HPP


// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory.hpp"
#include "Geometry_Config.hpp"

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_DagMC.hpp"

namespace MonteCarlo{

//! The standard estimator factory class specialization for DagMC
template<>
class StandardEstimatorFactory<Geometry::DagMC> : public EstimatorFactory
{

public:

  //! Constructor
  StandardEstimatorFactory(
       const std::shared_ptr<EventHandler>& event_handler,
       const boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
       response_function_id_map,
       std::ostream* os_warn = &std::cerr );

  //! Destructor
  ~StandardEstimatorFactory()
  { /* ... */ }

  //! Create and register cached estimators
  void createAndRegisterCachedEstimators();

protected:

  //! Verify that the estimator type is consistent with cached data
  void verifyEstimatorTypeConsistency( const unsigned estimator_id,
                                       const std::string& estimator_type ) const;

  //! Get the estimator particle types - required
  void getEstimatorParticleType( 
                           Teuchos::Array<ParticleType>& particle_types,
                           const unsigned estimator_id,
                           const Teuchos::ParameterList& estimator_rep ) const;

  //! Verify the existence of cells
  void verifyExistenceOfCells(
        const boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>&
        cells,
        const unsigned estimator_id ) const;

  //! Get the cached cells (add to set)
  void getCachedCells( 
       boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>& cells,
       const unsigned estimator_id ) const;

  //! Get the cell volumes
  void getCellVolumes( 
     Teuchos::Array<double>& cell_volumes,
     const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells );

  //! Verify the existence of surfaces
  void verifyExistenceOfSurfaces(
     const boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>&
     surfaces,
     const unsigned estimator_id ) const;

  //! Get the cached surfaces (add to set)
  void getCachedSurfaces(
     boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>&
     surfaces,
     const unsigned estimator_id ) const;

  //! Get the surface areas
  void getSurfaceAreas( 
           Teuchos::Array<double>& surface_areas,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
           surfaces );

  //! Update the estimator cache info
  void updateEstimatorCacheInfo( const unsigned id );
  
private:

  // Load estimator id maps with cell estimator properties
  void loadEstimatorIdMapsWithCellEstimatorProps();

  // Load estimator id mpas with surface estimator properties
  void loadEstimatorIdMapsWithSurfaceEstimatorProps();

  // Load the cell volume map
  void loadCellVolumeMap();

  // Load the surface area map
  void loadSurfaceAreaMap();

  // Convert a DagMC estimator type name to the standard estimator type name
  std::string convertDagMCEstimatorTypeNameToStandard(
                          const std::string& dagmc_estimator_type_name ) const;

  // The estimator id type map (from DagMC geom)
  boost::unordered_map<unsigned,std::string> d_geom_estimator_id_type_map;

  // The estimator id particle type map (from DagMC geom)
  boost::unordered_map<unsigned,std::string> d_geom_estimator_id_ptype_map;

  // The estimator id cells map (from DagMC geom)
  typedef boost::unordered_map<unsigned,Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> > EstimatorIdCellsMap;
  EstimatorIdCellsMap d_geom_estimator_id_cells_map;

  // The estimator id surfaces map (from DagMC geom)
  typedef boost::unordered_map<unsigned,Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> > EstimatorIdSurfacesMap;
  EstimatorIdSurfacesMap d_geom_estimator_id_surfaces_map;

  // The cell volume map
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>
  d_cell_volume_map;

  // The surface area map
  boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,double>
  d_surface_area_map;
};

} // end MonteCarlo namespace

#endif // end HAVE_FRENSIE_DAGMC

#endif // end MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_DAGMC_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEstimatorFactory_DagMC.hpp
//---------------------------------------------------------------------------//
