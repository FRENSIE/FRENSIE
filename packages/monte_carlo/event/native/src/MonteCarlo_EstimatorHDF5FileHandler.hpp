//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorHDF5FileHandler.hpp
//! \author Alex Robinson
//! \brief  Estimator hdf5 file handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_HDF5_FILE_HANDLER_HPP
#define MONTE_CARLO_ESTIMATOR_HDF5_FILE_HANDLER_HPP

// Std Lib Includes
#include <memory>
#include <vector>
#include <utility>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_HDF5FileHandler.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_HDF5FileHandler.hpp"
#include "Utility_HDF5TypeTraits.hpp"

namespace MonteCarlo{

//! The estimator hdf5 file handler
class EstimatorHDF5FileHandler : public MonteCarlo::HDF5FileHandler
{

public:

  //! Constructor (file ownership)
  EstimatorHDF5FileHandler(const std::string& hdf5_file_name,
                           const MonteCarlo::HDF5FileHandler::FileOps file_op =
                           OVERWRITE_FILE );

  //! Constructor (file sharing)
  EstimatorHDF5FileHandler(
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file );

  //! Destructor
  ~EstimatorHDF5FileHandler()
  { /* ... */ }

  //! Check if an estimator exists
  bool doesEstimatorExist( const InternalEventObserverHandle estimator_id ) const;

  //! Set the estimator as a surface estimator
  void setSurfaceEstimator( const InternalEventObserverHandle estimator_id );

  //! Check if the estimator is a surface estimator
  bool isSurfaceEstimator( const InternalEventObserverHandle estimator_id ) const;

  //! Set the estimator as a cell estimator
  void setCellEstimator( const InternalEventObserverHandle estimator_id );

  //! Check if the estimator is a cell estimator
  bool isCellEstimator( const InternalEventObserverHandle estimator_id ) const;

  //! Set the estimator as a mesh estimator
  void setMeshEstimator( const InternalEventObserverHandle estimator_id );

  //! Check if the estimator is a mesh estimator
  bool isMeshEstimator( const InternalEventObserverHandle estimator_id ) const;

  //! Set the estimator multiplier
  void setEstimatorMultiplier( const InternalEventObserverHandle estimator_id,
			       const double multiplier );

  //! Get the estimator multiplier
  void getEstimatorMultiplier( const InternalEventObserverHandle estimator_id,
			       double& multiplier ) const;

  //! Set the estimator response function ordering
  template<template<typename,typename...> class STLCompliantArray>
  void setEstimatorResponseFunctionOrdering(
		 const InternalEventObserverHandle estimator_id,
                 const STLCompliantArray<size_t>& response_function_ordering );

  //! Get the estimator response function ordering
  template<template<typename,typename...> class STLCompliantArray>
  void getEstimatorResponseFunctionOrdering(
		 const InternalEventObserverHandle estimator_id,
		 STLCompliantArray<size_t>& response_function_ordering ) const;

  //! Set the particle types assigned to the estimator
  template<template<typename,typename...> class STLCompliantArray>
  void setParticleTypes(
                       const InternalEventObserverHandle estimator_id,
                       const STLCompliantArray<ParticleType>& particle_types );

  //! Get the particle types assigned to the estimator
  template<template<typename,typename...> class STLCompliantArray>
  void getParticleTypes(
                       const InternalEventObserverHandle estimator_id,
                       STLCompliantArray<ParticleType>& particle_types ) const;

  //! Set the estimator dimension ordering
  template<template<typename,typename...> class STLCompliantArray>
  void setEstimatorDimensionOrdering(
	    const InternalEventObserverHandle estimator_id,
	    const STLCompliantArray<PhaseSpaceDimension>& dimension_ordering );

  //! Get the estimator dimension ordering
  template<template<typename,typename...> class STLCompliantArray>
  void getEstimatorDimensionOrdering(
	    const InternalEventObserverHandle estimator_id,
	    STLCompliantArray<PhaseSpaceDimension>& dimension_ordering ) const;

  //! Set the estimator dimension discretization
  template<PhaseSpaceDimension dimension,
           template<typename,typename...> class STLCompliantArray>
  void setEstimatorDimensionDiscretization(
                                const InternalEventObserverHandle estimator_id,
                                const STLCompliantArray<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>& discretization );

  //! Get the estimator dimension discretization
  template<PhaseSpaceDimension dimension,
           template<typename,typename...> class STLCompliantArray>
  void getEstimatorDimensionDiscretization(
                                const InternalEventObserverHandle estimator_id,
                                STLCompliantArray<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>& discretization ) const;

  //! Set the estimator entities and norm constants
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void setEstimatorEntities(
               const InternalEventObserverHandle estimator_id,
               const STLCompliantArray<STLCompliantPair<EntityIdType,double> >&
               entity_id_norms );

  //! Set the estimator entities and norm constants
  template<typename EntityIdType,
           template<typename,typename,typename...> class STLCompliantMap>
  void setEstimatorEntities(
                 const InternalEventObserverHandle estimator_id,
		 const STLCompliantMap<EntityIdType,double>& entity_id_norms );

  //! Get the estimator entities and norm constants
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void getEstimatorEntities(
                     const InternalEventObserverHandle estimator_id,
                     STLCompliantArray<STLCompliantPair<EntityIdType,double> >&
                     entity_id_norms ) const;

  //! Get the estimator entities and norm constants
  template<typename EntityIdType,
           template<typename,typename,typename...> class STLCompliantMap>
  void getEstimatorEntities(
                       const InternalEventObserverHandle estimator_id,
		       STLCompliantMap<EntityIdType,double>& entity_id_norms );

  //! Check if an entity is assigned to an estimator
  template<typename EntityIdType>
  bool isEntityAssignedToEstimator(
                                const InternalEventObserverHandle estimator_id,
                                const EntityIdType entity_id ) const;

  //! Set the entity normalization constant
  template<typename EntityIdType>
  void setEntityNormConstant( const InternalEventObserverHandle estimator_id,
			      const EntityIdType entity_id,
			      const double norm_constant );

  //! Get the entity normalization constant
  template<typename EntityIdType>
  void getEntityNormConstant( const InternalEventObserverHandle estimator_id,
			      const EntityIdType entity_id,
			      double& norm_constant ) const;

  //! Set the total normalization constant
  void setEstimatorTotalNormConstant(
                                const InternalEventObserverHandle estimator_id,
                                const double total_norm_constant );

  //! Get the total normalization constant
  void getEstimatorTotalNormConstant(
                                const InternalEventObserverHandle estimator_id,
                                double& total_norm_constant ) const;

  //! Set the raw estimator bin data for an entity (1st, 2nd moments)
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void setRawEstimatorEntityBinData(
                     const InternalEventObserverHandle estimator_id,
                     const EntityIdType entity_id,
	             const STLCompliantArray<STLCompliantPair<double,double> >&
                     raw_bin_data );

  //! Get the raw estimator bin data for an entity (1st, 2nd moments)
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void getRawEstimatorEntityBinData(
     const InternalEventObserverHandle estimator_id,
     const EntityIdType entity_id,
     STLCompliantArray<STLCompliantPair<double,double> >& raw_bin_data ) const;

  //! Set the processed estimator bin data for an entity (mean, relative error)
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void setProcessedEstimatorEntityBinData(
                     const InternalEventObserverHandle estimator_id,
                     const EntityIdType entity_id,
                     const STLCompliantArray<STLCompliantPair<double,double> >&
                     processed_bin_data );

  //! Get the processed estimator bin data for an entity (mean, relative error)
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void getProcessedEstimatorEntityBinData(
                           const InternalEventObserverHandle estimator_id,
                           const EntityIdType entity_id,
                           STLCompliantArray<STLCompliantPair<double,double> >&
                           processed_bin_data ) const;

  /*! \brief Set the raw estimator total data for an entity
   * (1st, 2nd, 3rd, 4th moments)
   */
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename,typename,typename> class STLCompliantQuad>
  void setRawEstimatorEntityTotalData(
       const InternalEventObserverHandle estimator_id,
       const EntityIdType entity_id,
       const STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
       raw_total_data );

  /*! \brief Get the raw estimator total data for an entity
   * (1st, 2nd, 3rd, 4th moments)
   */
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename,typename,typename> class STLCompliantQuad>
  void getRawEstimatorEntityTotalData(
             const InternalEventObserverHandle estimator_id,
             const EntityIdType entity_id,
             STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
             raw_total_data ) const;

  /*! \brief Set the processed estimator total data for an entity
   * (mean, relative error, variance of variance, figure of merit )
   */
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename,typename,typename> class STLCompliantQuad>
  void setProcessedEstimatorEntityTotalData(
       const InternalEventObserverHandle estimator_id,
       const EntityIdType entity_id,
       const STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
       processed_total_data );

  /*! \brief Get the processed estimator total data for an entity
   * (mean, relative error, variance of variance, figure of merit)
   */
  template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename,typename,typename> class STLCompliantQuad>
  void getProcessedEstimatorEntityTotalData(
	     const InternalEventObserverHandle estimator_id,
             const EntityIdType entity_id,
             STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
             processed_total_data ) const;

  //! Set the raw estimator bin data over all entities (1st, 2nd moments)
  template<template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void setRawEstimatorTotalBinData(
                     const InternalEventObserverHandle estimator_id,
	             const STLCompliantArray<STLCompliantPair<double,double> >&
                     raw_bin_data );

  //! Get the raw estimator bin data over all entities (1st, 2nd moments)
  template<template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void getRawEstimatorTotalBinData(
                           const InternalEventObserverHandle estimator_id,
	                   STLCompliantArray<STLCompliantPair<double,double> >&
                           raw_bin_data ) const;

  //! Set the processed estimator bin data over all entities (mean, rel. err.)
  template<template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void setProcessedEstimatorTotalBinData(
                     const InternalEventObserverHandle estimator_id,
                     const STLCompliantArray<STLCompliantPair<double,double> >&
                     processed_bin_data );

  //! Get the processed estimator bin data over all entities (mean, rel. err.)
  template<template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
  void getProcessedEstimatorTotalBinData(
                           const InternalEventObserverHandle estimator_id,
                           STLCompliantArray<STLCompliantPair<double,double> >&
                           processed_bin_data ) const;

  /*! \brief Set the raw estimator total data over all entities
   * (1st, 2nd, 3rd, 4th moments)
   */
  template<template<typename,typename...> class STLCompliantArray,
           template<typename,typename,typename,typename> class STLCompliantQuad>
  void setRawEstimatorTotalData(
       const InternalEventObserverHandle estimator_id,
       const STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
       raw_total_data );

  /*! \brief Get the raw estimator total data over all entities
   * (1st, 2nd, 3rd, 4th moments)
   */
  template<template<typename,typename...> class STLCompliantArray,
           template<typename,typename,typename,typename> class STLCompliantQuad>
  void getRawEstimatorTotalData(
             const InternalEventObserverHandle estimator_id,
	     STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
             raw_total_data ) const;

  /*! \brief Set the processed estimator total data over all entities
   * (mean, relative error, variance of variance, figure of merit)
   */
  template<template<typename,typename...> class STLCompliantArray,
           template<typename,typename,typename,typename> class STLCompliantQuad>
  void setProcessedEstimatorTotalData(
       const InternalEventObserverHandle estimator_id,
       const STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
       processed_total_data );

  /*! \brief Get the processed estimator total data over all entities
   * (mean, relative error, variance of variance, figure of merit)
   */
  template<template<typename,typename...> class STLCompliantArray,
           template<typename,typename,typename,typename> class STLCompliantQuad>
  void getProcessedEstimatorTotalData(
             const InternalEventObserverHandle estimator_id,
	     STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
             processed_total_data ) const;

private:

  // Enum for estimator entity type
  enum EntityType{
    SURFACE_ENTITY = 0,
    CELL_ENTITY,
    MESH_VOLUME_ENTITY,
  };

  // Allow HDF5 type traits specialization friend access
  friend class Utility::HDF5TypeTraits<EstimatorHDF5FileHandler::EntityType>;

  // Get the estimator location
  std::string getEstimatorGroupLocation(
                        const InternalEventObserverHandle estimator_id ) const;

  // Get the estimator entity location
  template<typename EntityIdType>
  std::string getEstimatorEntityGroupLocation(
                                const InternalEventObserverHandle estimator_id,
                                const EntityIdType entity_id ) const;

  // The estimator group location and name
  static const char* s_estimator_group_loc_name;

  // The entity type attribute name
  static const char* s_entity_type_attr_name;

  // The multiplier attribute name
  static const char* s_multiplier_attr_name;

  // The total normalization constant attribute name
  static const char* s_total_norm_constant_attr_name;

  // The entity normalization constant attribute name
  static const char* s_entity_norm_constant_attr_name;

  // The response function ordering attribute name
  static const char* s_response_function_ordering_attr_name;

  // The particle types attribute name
  static const char* s_particle_types_attr_name;

  // The dimension ordering attribute name
  static const char* s_dimension_ordering_attr_name;

  // The entity normalization constants data set relative location
  static const char* s_entity_norm_constant_relative_loc;

  // The entity raw bin data data set relative location
  static const char* s_entity_raw_bin_data_relative_loc;

  // The entity processed bin data data set relative location
  static const char* s_entity_processed_bin_data_relative_loc;

  // The entity raw total data data set relative location
  static const char* s_entity_raw_total_data_relative_loc;

  // The entity processed total data data set relative location
  static const char* s_entity_processed_total_data_relative_loc;

  // The raw total bin data data set relative location
  static const char* s_raw_total_bin_data_relative_loc;

  // The processed total bin data data set relative location
  static const char* s_processed_total_bin_data_relative_loc;

  // The raw total data data set relative location
  static const char* s_raw_total_data_relative_loc;

  // The processed total data data set relative location
  static const char* s_processed_total_data_relative_loc;
};

} // end MonteCarlo namespace

namespace Utility{

/*! Specialization of the Utility::HDf5TypeTraits for estimator entity type
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<MonteCarlo::EstimatorHDF5FileHandler::EntityType>
{
  //! Return the HDF5 data type
  static inline H5::EnumType dataType()
  {
    H5::EnumType hdf5_estimator_entity_type(
		  sizeof( MonteCarlo::EstimatorHDF5FileHandler::EntityType ) );

    MonteCarlo::EstimatorHDF5FileHandler::EntityType value =
      MonteCarlo::EstimatorHDF5FileHandler::SURFACE_ENTITY;

    hdf5_estimator_entity_type.insert( "SURFACE_ENTITY", &value );

    value = MonteCarlo::EstimatorHDF5FileHandler::CELL_ENTITY;

    hdf5_estimator_entity_type.insert( "CELL_ENTITY", &value );

    value = MonteCarlo::EstimatorHDF5FileHandler::MESH_VOLUME_ENTITY;

    hdf5_estimator_entity_type.insert( "MESH_VOLUME_ENTITY", &value );

    return hdf5_estimator_entity_type;
  }

  //! Return the name of the type
  static inline std::string name()
  {
    return "EntityType";
  }

  //! Returns the zero value for this type
  static inline MonteCarlo::EstimatorHDF5FileHandler::EntityType
  zero()
  {
    return MonteCarlo::EstimatorHDF5FileHandler::SURFACE_ENTITY;
  }

  //! Returns the unit value for this type
  static inline MonteCarlo::EstimatorHDF5FileHandler::EntityType
  one()
  {
    return MonteCarlo::EstimatorHDF5FileHandler::CELL_ENTITY;
  }
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_EstimatorHDF5FileHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ESTIMATOR_HDF5_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHDF5FileHandler.hpp
//---------------------------------------------------------------------------//
