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

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_HDF5FileHandler.hpp"
#include "Utility_HDF5TypeTraits.hpp"

namespace MonteCarlo{

//! The estimator hdf5 file handler
class EstimatorHDF5FileHandler
{

public:

  //! Enum for file operations
  enum EstimatorHDF5FileOps{
    OVERWRITE_ESTIMATOR_HDF5_FILE = 0,
    APPEND_ESTIMATOR_HDF5_FILE,
    READ_ONLY_ESTIMATOR_HDF5_FILE
  };

  //! Constructor (file ownership)
  EstimatorHDF5FileHandler( 
	  const std::string& hdf5_file_name,
	  const EstimatorHDF5FileOps file_op = OVERWRITE_ESTIMATOR_HDF5_FILE );

  //! Constructor (file sharing)
  EstimatorHDF5FileHandler( 
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file );

  //! Destructor
  ~EstimatorHDF5FileHandler();

  //! Check if an estimator exists
  bool doesEstimatorExist( const unsigned estimator_id ) const;

  //! Set the estimator as a surface estimator
  void setSurfaceEstimator( const unsigned estimator_id );

  //! Check if the estimator is a surface estimator
  bool isSurfaceEstimator( const unsigned estimator_id ) const;

  //! Set the estimator as a cell estimator
  void setCellEstimator( const unsigned estimator_id );

  //! Check if the estimator is a cell estimator
  bool isCellEstimator( const unsigned estimator_id ) const;

  //! Set the estimator as a mesh estimator
  void setMeshEstimator( const unsigned estimator_id );

  //! Check if the estimator is a mesh estimator
  bool isMeshEstimator( const unsigned estimator_id ) const;
  
  //! Set the estimator multiplier
  void setEstimatorMultiplier( const unsigned estimator_id,
			       const double multiplier );

  //! Get the estimator multiplier
  void getEstimatorMultiplier( const unsigned estimator_id,
			       double& multiplier ) const;
  
  //! Set the estimator response function ordering
  void setEstimatorResponseFunctionOrdering(
		  const unsigned estimator_id,
		  const Teuchos::Array<unsigned>& response_function_ordering );

  //! Get the estimator response function ordering
  void getEstimatorResponseFunctionOrdering(
		  const unsigned estimator_id,
		  Teuchos::Array<unsigned>& response_function_ordering ) const;

  //! Set the estimator dimension ordering
  void setEstimatorDimensionOrdering(
	       const unsigned estimator_id,
	       const Teuchos::Array<PhaseSpaceDimension>& dimension_ordering );

  //! Get the estimator dimension ordering
  void getEstimatorDimensionOrdering(
	       const unsigned estimator_id,
	       Teuchos::Array<PhaseSpaceDimension>& dimension_ordering ) const;

  //! Set the estimator bin boundaries
  template<PhaseSpaceDimension dimension>
  void setEstimatorBinBoundaries( const unsigned estimator_id,
				  const Teuchos::Array<typename PhaseSpaceDimensionTraits<dimension>::dimensionType>& bin_boundaries );

  //! Get the estimator bin boundaries
  template<PhaseSpaceDimension dimension>
  void getEstimatorBinBoundaries( const unsigned estimator_id,
				  Teuchos::Array<typename PhaseSpaceDimensionTraits<dimension>::dimensionType>& bin_boundaries ) const;

  //! Set the estimator entities and norm constants
  template<typename EntityIdType>
  void setEstimatorEntities(
		     const unsigned estimator_id,
                     const Teuchos::Array<Utility::Pair<EntityIdType,double> >&
		     entity_id_norms );

  //! Set the estimator entities and norm constants
  template<typename EntityIdNormConstMap>
  void setEstimatorEntities( const unsigned estimator_id,
			     const EntityIdNormConstMap& entity_id_norms );

  //! Get the estimator entities and norm constants
  template<typename EntityIdType>
  void getEstimatorEntities(
		           const unsigned estimator_id,
                           Teuchos::Array<Utility::Pair<EntityIdType,double> >&
			   entity_id_norms ) const;

  //! Get the estimator entities and norm constants
  template<typename EntityIdNormConstMap>
  void getEstimatorEntities( const unsigned estimator_id,
			     EntityIdNormConstMap& entity_id_norms ) const;

  //! Check if an entity is assigned to an estimator
  template<typename EntityIdType>
  bool isEntityAssignedToEstimator( const unsigned estimator_id,
				    const EntityIdType entity_id ) const;

  //! Set the entity normalization constant
  template<typename EntityIdType>
  void setEntityNormConstant( const unsigned estimator_id,
			      const EntityIdType entity_id,
			      const double norm_constant );

  //! Get the entity normalization constant
  template<typename EntityIdType>
  void getEntityNormConstant( const unsigned estimator_id,
			      const EntityIdType entity_id,
			      double& norm_constant ) const;

  //! Set the total normalization constant
  void setEstimatorTotalNormConstant( const unsigned estimator_id,
				      const double total_norm_constant );

  //! Get the total normalization constant
  void getEstimatorTotalNormConstant( const unsigned estimator_id,
				      double& total_norm_constant ) const;
  
  //! Set the raw estimator bin data for an entity (1st, 2nd moments)
  template<typename EntityIdType>
  void setRawEstimatorEntityBinData(
	   const unsigned estimator_id,
	   const EntityIdType entity_id,
	   const Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data );

  //! Get the raw estimator bin data for an entity (1st, 2nd moments)
  template<typename EntityIdType>
  void getRawEstimatorEntityBinData(
	   const unsigned estimator_id,
	   const EntityIdType entity_id,
	   Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data ) const;

  //! Set the processed estimator bin data for an entity (mean, relative error)
  template<typename EntityIdType>
  void setProcessedEstimatorEntityBinData(
     const unsigned estimator_id,
     const EntityIdType entity_id,
     const Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data );

  //! Get the processed estimator bin data for an entity (mean, relative error)
  template<typename EntityIdType>
  void getProcessedEstimatorEntityBinData(
     const unsigned estimator_id,
     const EntityIdType entity_id,
     Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data ) const;

  /*! \brief Set the raw estimator total data for an entity 
   * (1st, 2nd, 3rd, 4th moments)
   */
  template<typename EntityIdType>
  void setRawEstimatorEntityTotalData(
	     const unsigned estimator_id,
	     const EntityIdType entity_id,
             const Teuchos::Array<Utility::Quad<double,double,double,double> >&
	     raw_total_data );

  /*! \brief Get the raw estimator total data for an entity 
   * (1st, 2nd, 3rd, 4th moments)
   */
  template<typename EntityIdType>
  void getRawEstimatorEntityTotalData(
		   const unsigned estimator_id,
		   const EntityIdType entity_id,
                   Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   raw_total_data ) const;

  /*! \brief Set the processed estimator total data for an entity 
   * (mean, relative error, variance of variance, figure of merit )
   */
  template<typename EntityIdType>
  void setProcessedEstimatorEntityTotalData(
	     const unsigned estimator_id,
	     const EntityIdType entity_id,
             const Teuchos::Array<Utility::Quad<double,double,double,double> >&
	     processed_total_data ); 

  /*! \brief Get the processed estimator total data for an entity
   * (mean, relative error, variance of variance, figure of merit)
   */
  template<typename EntityIdType>
  void getProcessedEstimatorEntityTotalData(
	           const unsigned estimator_id,
		   const EntityIdType entity_id,
                   Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   processed_total_data ) const;

  //! Set the raw estimator bin data over all entities (1st, 2nd moments)
  void setRawEstimatorTotalBinData(
	   const unsigned estimator_id,
	   const Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data );

  //! Get the raw estimator bin data over all entities (1st, 2nd moments)
  void getRawEstimatorTotalBinData(
	   const unsigned estimator_id,
	   Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data ) const;

  //! Set the processed estimator bin data over all entities (mean, rel. err.)
  void setProcessedEstimatorTotalBinData(
     const unsigned estimator_id,
     const Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data );

  //! Get the processed estimator bin data over all entities (mean, rel. err.)
  void getProcessedEstimatorTotalBinData(
     const unsigned estimator_id,
     Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data ) const;

  /*! \brief Set the raw estimator total data over all entities 
   * (1st, 2nd, 3rd, 4th moments)
   */
  void setRawEstimatorTotalData(
	     const unsigned estimator_id,
	     const Teuchos::Array<Utility::Quad<double,double,double,double> >&
	     raw_total_data );

  /*! \brief Get the raw estimator total data over all entities
   * (1st, 2nd, 3rd, 4th moments)
   */
  void getRawEstimatorTotalData(
		   const unsigned estimator_id,
		   Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   raw_total_data ) const;

  /*! \brief Set the processed estimator total data over all entities
   * (mean, relative error, variance of variance, figure of merit)
   */
  void setProcessedEstimatorTotalData(
	     const unsigned estimator_id,
	     const Teuchos::Array<Utility::Quad<double,double,double,double> >&
	     processed_total_data );

  /*! \brief Get the processed estimator total data over all entities
   * (mean, relative error, variance of variance, figure of merit)
   */
  void getProcessedEstimatorTotalData(
		   const unsigned estimator_id,
	           Teuchos::Array<Utility::Quad<double,double,double,double> >&
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
  std::string getEstimatorGroupLocation( const unsigned estimator_id ) const;

  // Get the estimator entity location
  template<typename EntityIdType>
  std::string getEstimatorEntityGroupLocation( 
					  const unsigned estimator_id,
					  const EntityIdType entity_id ) const;

  // The estimator group location and name
  static const std::string estimator_group_loc_name;

  // The HDF5 file handler
  std::shared_ptr<Utility::HDF5FileHandler> d_hdf5_file;

  // The ownership flag
  bool d_hdf5_file_ownership;
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
