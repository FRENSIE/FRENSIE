//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEstimatorFactory_Root.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The standard estimator factory class specialization for Root
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_ROOT_HPP
#define MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_ROOT_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory.hpp"
#include "Geometry_Config.hpp"

#ifdef HAVE_FRENSIE_ROOT
#include "Geometry_Root.hpp"

namespace MonteCarlo{

//! The standard estimator factory class specialization for Root
template<>
class StandardEstimatorFactory<Geometry::Root> : public EstimatorFactory
{

public:

  //! Constructor
  StandardEstimatorFactory(
       const std::shared_ptr<EventHandler>& event_handler,
       const boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
       response_function_id_map,
       const std::shared_ptr<const SimulationGeneralProperties>& properties,
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

  //! Verify the existence of cells
  void verifyExistenceOfCells(
        const boost::unordered_set<Geometry::Model::EntityId>&
        cells,
        const unsigned estimator_id ) const;

  //! Get the cached cells (add to set)
  void getCachedCells(
       boost::unordered_set<Geometry::Model::EntityId>& cells,
       const unsigned estimator_id ) const;

  //! Get the cell volumes
  void getCellVolumes(
     std::vector<double>& cell_volumes,
     const std::vector<Geometry::Model::EntityId>& cells );

  //! Verify the existence of surfaces
  void verifyExistenceOfSurfaces(
     const boost::unordered_set<Geometry::Model::EntityId>&
     surfaces,
     const unsigned estimator_id ) const;

  //! Get the cached surfaces (add to set)
  void getCachedSurfaces(
           boost::unordered_set<Geometry::Model::EntityId>&
           surfaces,
           const unsigned estimator_id ) const;

  //! Get the surface areas
  void getSurfaceAreas(
           std::vector<double>& surface_areas,
           const std::vector<Geometry::Model::EntityId>&
           surfaces );

  //! Create and register a surface estimator
  void createAndRegisterSurfaceEstimator(
      const std::string& surface_estimator_type,
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const std::vector<Geometry::Model::EntityId>&
      surfaces,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );

  //! Update the estimator cache info
  void updateEstimatorCacheInfo( const unsigned id );

private:

  // The cell volume map
  boost::unordered_map<Geometry::Model::EntityId,double>
  d_cell_volume_map;

  // The surface area map
  boost::unordered_map<Geometry::Model::EntityId,double>
  d_surface_area_map;
};

} // end MonteCarlo namespace

#endif // end HAVE_FRENSIE_ROOT

#endif // end MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_ROOT_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEstimatorFactory_Root.hpp
//---------------------------------------------------------------------------//
