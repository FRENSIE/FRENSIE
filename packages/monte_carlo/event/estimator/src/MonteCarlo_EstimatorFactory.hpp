//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorFactory.hpp
//! \author Alex Robinson
//! \brief  The estimator factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_FACTORY_DAGMC_HPP
#define MONTE_CARLO_ESTIMATOR_FACTORY_DAGMC_HPP

// Std Lib Includes
#include <iostream>
#include <stdexcept>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
//#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_ResponseFunction.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The estimator factory class
class EstimatorFactory
{

public:

  //! Constructor
  EstimatorFactory(
       const std::shared_ptr<EventHandler>& event_handler,
       const boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
       response_function_id_map,
       const std::shared_ptr<const SimulationGeneralProperties>& properties,
       std::ostream* os_warn = &std::cerr );

  //! Destructor
  virtual ~EstimatorFactory()
  { /* ... */ }

  //! Check if the parameter list describes an estimator
  bool isEstimatorRep( const Teuchos::ParameterList& object_rep ) const;

  //! Create and register an estimator
  void createAndRegisterEstimator(
                                 const Teuchos::ParameterList& estimator_rep );

  /*! Create and register cached estimators
   * \details All remaining cached estimator info (possibly pulled from the
   * geometry handler) will be deleted after the remaining estimators are
   * registered.
   */
  virtual void createAndRegisterCachedEstimators() = 0;

protected:

  //! Check if an estimator type is a cell estimator
  static bool isCellEstimator( const std::string& estimator_name );

  //! Check if an estimator type is a surface estimator
  static bool isSurfaceEstimator( const std::string& estimator_name );

  //! Check if an estimator type is a mesh estimator
  static bool isMeshEstimator( const std::string& estimator_name );

  //! Return the cell pulse height estimator name
  static const std::string& getCellPulseHeightEstimatorName();

  //! Return the cell track length flux estimator name
  static const std::string& getCellTrackLengthFluxEstimatorName();

  //! Return the cell collision flux estimator name
  static const std::string& getCellCollisionFluxEstimatorName();

  //! Return the surface flux estimator name
  static const std::string& getSurfaceFluxEstimatorName();

  //! Return the surface current estimator name
  static const std::string& getSurfaceCurrentEstimatorName();

  //! Verify that the estimator type is consistent with cached data
  virtual void verifyEstimatorTypeConsistency(
                                 const unsigned estimator_id,
                                 const std::string& estimator_type ) const = 0;

  //! Get the estimator particle types - required
  virtual void getEstimatorParticleType(
                           std::vector<ParticleType>& particle_types,
                           const unsigned estimator_id,
                           const Teuchos::ParameterList& estimator_rep ) const;

  //! Convert the particle type name to particle types
  void convertParticleTypeNameToParticleTypes(
                                 std::vector<ParticleType>& particle_types,
                                 const unsigned estimator_id,
                                 const std::string& particle_type_name ) const;

  //! Get the cells assigned to the estimator - required if cell estimator
  void getEstimatorCells(
                    std::vector<Geometry::Model::InternalCellHandle>&
                    assigned_cells,
                    const unsigned estimator_id,
                    const Teuchos::ParameterList& estimator_rep ) const;

  //! Verify the existence of cells
  virtual void verifyExistenceOfCells(
        const boost::unordered_set<Geometry::Model::InternalCellHandle>&
        cells,
        const unsigned estimator_id ) const = 0;

  //! Get the cached cells (add to set)
  virtual void getCachedCells(
       boost::unordered_set<Geometry::Model::InternalCellHandle>& cells,
       const unsigned estimator_id ) const = 0;

  //! Get the cell volumes
  virtual void getCellVolumes(
              std::vector<double>& cell_volumes,
              const std::vector<Geometry::Model::InternalCellHandle>&
              cells ) = 0;

  //! Get the surfaces assigned to the estimator - required if surface est.
  void getEstimatorSurfaces(
                 std::vector<Geometry::Model::InternalSurfaceHandle>&
                 assigned_surfaces,
                 const unsigned estimator_id,
                 const Teuchos::ParameterList& estimator_rep ) const;

  //! Verify the existence of surfaces
  virtual void verifyExistenceOfSurfaces(
     const boost::unordered_set<Geometry::Model::InternalSurfaceHandle>&
     surfaces,
     const unsigned estimator_id ) const = 0;

  //! Get the cached surfaces (add to set)
  virtual void getCachedSurfaces(
     boost::unordered_set<Geometry::Model::InternalSurfaceHandle>&
     surfaces,
     const unsigned estimator_id ) const = 0;

  //! Get the surface areas
  virtual void getSurfaceAreas(
           std::vector<double>& surface_areas,
           const std::vector<Geometry::Model::InternalSurfaceHandle>&
           surfaces ) = 0;

  //! Create and register a cell estimator
  void createAndRegisterCellEstimator(
      const std::string& cell_estimator_type,
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const std::vector<Geometry::Model::InternalCellHandle>& cells,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );

  // Create and register a surface estimator
  virtual void createAndRegisterSurfaceEstimator(
      const std::string& surface_estimator_type,
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const std::vector<Geometry::Model::InternalSurfaceHandle>&
      surfaces,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );

  //! Update the estimator cache info
  virtual void updateEstimatorCacheInfo( const unsigned estimator_id ) = 0;

  //! Return the warning output stream
  std::ostream& getWarningOutputStream() const;

private:

  //! Check if an estimator type is a cell pulse height estimator
  static bool isCellPulseHeightEstimator( const std::string& estimator_name );

  //! Check if an estimator type is a cell track length flux estimator
  static bool isCellTrackLengthFluxEstimator(
					   const std::string& estimator_name );

  //! Check if an estimator type is a cell collision flux estimator
  static bool isCellCollisionFluxEstimator(const std::string& estimator_name );

  //! Check if an estimator type is a surface flux estimator
  static bool isSurfaceFluxEstimator( const std::string& estimator_name );

  //! Check if an estimator type is a surface current estimator
  static bool isSurfaceCurrentEstimator( const std::string& estimator_name );

  //! Check if an estimator type is a tet mesh track length flux estimator
  static bool isTetMeshTrackLengthFluxEstimator(
                                           const std::string& estimator_name );

  //! Check if an estimator type is a hex mesh track length flux estimator
  static bool isHexMeshTrackLengthFluxEstimator(
                                           const std::string& estimator_name );

  //! Check if an object type is an estimator
  static bool isEstimator( const std::string& object_name );

  //! Get the estimator id - required
  unsigned getEstimatorId( const Teuchos::ParameterList& estimator_rep ) const;

  //! Get the estimator type - required
  void getEstimatorType( std::string& estimator_type,
                         const unsigned estimator_id,
                         const Teuchos::ParameterList& estimator_rep ) const;

  //! Get the estimator multiplier - optional
  double getEstimatorMultiplier(
                           const unsigned estimator_id,
                           const Teuchos::ParameterList& estimator_rep ) const;

  //! Check if energy multiplication was requested - optional
  bool isEnergyMultiplicationRequested(
                           const unsigned estimator_id,
                           const Teuchos::ParameterList& estimator_rep ) const;

  //! Get the estimator bins - optional
  const Teuchos::ParameterList* getEstimatorBins(
                           const unsigned estimator_id,
                           const Teuchos::ParameterList& estimator_rep ) const;

  //! Get the response functions assigned to the estimator - optional
  void getResponseFunctions(
        std::vector<std::shared_ptr<ResponseFunction> >& response_functions,
        const unsigned estimator_id,
        const Teuchos::ParameterList& estimator_rep ) const;

  //! Create and register a cell pulse height estimator
  void createAndRegisterCellPulseHeightEstimator(
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const std::vector<Geometry::Model::InternalCellHandle>& cells,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL ) const;

  //! Create and register a cell track length flux estimator
  void createAndRegisterCellTrackLengthFluxEstimator(
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const std::vector<Geometry::Model::InternalCellHandle>& cells,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );

  //! Create and register a cell collision flux estimator
  void createAndRegisterCellCollisionFluxEstimator(
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const std::vector<Geometry::Model::InternalCellHandle>& cells,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );

  // Create and register a surface flux estimator
  void createAndRegisterSurfaceFluxEstimator(
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const std::vector<Geometry::Model::InternalSurfaceHandle>&
      surfaces,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL );

  // Create and register a surface current estimator
  void createAndRegisterSurfaceCurrentEstimator(
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const std::vector<Geometry::Model::InternalSurfaceHandle>&
      surfaces,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL ) const;

  //! Create and register a tet mesh track length flux estimator
  void createAndRegisterTetMeshTrackLengthFluxEstimator(
      const Teuchos::ParameterList& estimator_rep,
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL ) const;

  //! Create and register a hex mesh track length flux estimator
  void createAndRegisterHexMeshTrackLengthFluxEstimator(
      const Teuchos::ParameterList& estimator_rep,
      const unsigned id,
      const double multiplier,
      const std::vector<ParticleType> particle_types,
      const std::vector<std::shared_ptr<ResponseFunction> >& response_funcs,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL ) const;

  //! Assign bins to an estimator
  void assignBinsToEstimator( const Teuchos::ParameterList& bins,
                              std::shared_ptr<Estimator>& estimator ) const;

  // The surface current estimator name
  static const std::string s_surface_current_name;

  // The surface flux estimator name
  static const std::string s_surface_flux_name;

  // The cell pulse height estimator name
  static const std::string s_cell_pulse_height_name;

  // The cell track-length flux estimator name
  static const std::string s_cell_track_length_flux_name;

  // The cell collision flux estimator name
  static const std::string s_cell_collision_flux_name;

  // The tet mesh track-length flux estimator name
  static const std::string s_tet_mesh_track_length_flux_name;

  // The hex mesh track-length flux estimator name
  static const std::string s_hex_mesh_track_length_flux_name;

  // The event handler
  std::shared_ptr<EventHandler> d_event_handler;

  // The response function id map
  boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >
  d_response_function_id_map;

  // The simulation properties
  std::shared_ptr<const SimulationGeneralProperties> d_properties;

  // The warning output stream
  std::ostream* d_os_warn;
};

//! The invalid estimator representation error
class InvalidEstimatorRepresentation : public std::runtime_error
{

public:

  InvalidEstimatorRepresentation( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

} // end MonteCarlo

#endif // end MONTE_CARLO_ESTIMATOR_FACTORY_DAGMC_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorFactory.hpp
//---------------------------------------------------------------------------//
