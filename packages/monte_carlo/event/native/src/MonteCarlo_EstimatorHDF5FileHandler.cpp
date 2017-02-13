//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorHDF5FileHandler.hpp
//! \author Alex Robinson
//! \brief  Estimator hdf5 file handler class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const char* EstimatorHDF5FileHandler::s_estimator_group_loc_name = 
  "/Estimators/";
const char* EstimatorHDf5FileHandler::s_entity_type_attr_name =
  "entity_type";
const char* EstimatorHDf5FileHandler::s_multiplier_attr_name =
  "multiplier";
const char* EstimatorHDf5FileHandler::s_total_norm_constant_attr_name =
  "total_norm_constant";
const char* EstimatorHDf5FileHandler::s_entity_norm_constant_attr_name =
  "norm_constant";
const char* EstimatorHDf5FileHandler::s_response_function_ordering_attr_name =
  "response_function_ordering";
const char* EstimatorHDf5FileHandler::s_particle_types_attr_name =
  "particle_types";
const char* EstimatorHDf5FileHandler::s_dimension_ordering_attr_name =
  "dimension_ordering";
const char* EstimatorHDf5FileHandler::s_entity_norm_constant_relative_loc =
  "entity_norm_constants";
const char* EstimatorHDf5FileHandler::s_entity_raw_bin_data_relative_loc =
  "raw_bin_data";
const char* EstimatorHDf5FileHandler::s_entity_processed_bin_data_relative_loc=
  "processed_bin_data";
const char* EstimatorHDf5FileHandler::s_entity_raw_total_data_relative_loc =
  "raw_total_data";
const char* EstimatorHDf5FileHandler::s_entity_processed_total_data_relative_loc =
  "processed_total_data";
const char* EstimatorHDf5FileHandler::s_raw_total_bin_data_relative_loc =
  "raw_total_bin_data";
const char* EstimatorHDf5FileHandler::s_processed_total_bin_data_relative_loc =
  "processed_total_bin_data";
const char* EstimatorHDf5FileHandler::s_raw_total_data_relative_loc =
  "raw_total_data";
const char* EstimatorHDf5FileHandler::s_processed_total_data_relative_loc =
  "processed_total_data";

// Constructor (file ownership)
/*! \details The MonteCarlo::HDF5FileHandler::FileOps enum will determine how 
 * the HDF5 file is opened. If the read only option is used, calling any of the
 * set methods will result in an exception.
 */
EstimatorHDF5FileHandler::EstimatorHDF5FileHandler(
                           const std::string& hdf5_file_name,
			   const MonteCarlo::HDF5FileHandler::FileOps file_op )
  : MonteCarlo::HDF5FileHandler( hdf5_file_name, file_op )
{ /* ... */ }

// Constructor (file sharing)
EstimatorHDF5FileHandler::EstimatorHDF5FileHandler(
                   const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  : MonteCarlo::HDF5FileHandler( hdf5_file )
{ /* ... */ }

// Check if an estimator exists
bool EstimatorHDF5FileHandler::doesEstimatorExist(
			 const InternalEventObserverHandle estimator_id ) const
{
  return this->getHDF5File().doesGroupExist(
			     this->getEstimatorGroupLocation( estimator_id ) );
}

// Set the estimator as a surface estimator
void EstimatorHDF5FileHandler::setSurfaceEstimator(
			       const InternalEventObserverHandle estimator_id )
{
  try{
    this->getHDF5File().writeValueToGroupAttribute(
			       SURFACE_ENTITY,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_entity_type_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set estimator " << estimator_id <<
                           " as a surface estimator in the HDF5 file!" );
}

// Check if the estimator is a surface estimator
bool EstimatorHDF5FileHandler::isSurfaceEstimator(
			 const InternalEventObserverHandle estimator_id ) const
{
  EntityType type;

  try{
    this->getHDF5File().readValueFromGroupAttribute(
			       type,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_entity_type_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to determine if estimator "
                           << estimator_id << " is a surface estimator!" );

  return (type == SURFACE_ENTITY);

}

// Set the estimator as a cell estimator
void EstimatorHDF5FileHandler::setCellEstimator(
                               const InternalEventObserverHandle estimator_id )
{
  try{
    this->getHDF5File().writeValueToGroupAttribute(
			       CELL_ENTITY,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_entity_type_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set estimator " << estimator_id <<
                           " as a cell estimator in the HDF5 file!" );
}

// Check if the estimator is a cell estimator
bool EstimatorHDF5FileHandler::isCellEstimator(
			 const InternalEventObserverHandle estimator_id ) const
{
  EntityType type;

  try{
    this->getHDF5File().readValueFromGroupAttribute(
			       type,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_entity_type_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to determine if estimator "
                           << estimator_id << " is a cell estimator!" );

  return (type == CELL_ENTITY);
}

// Set the estimator as a mesh estimator
void EstimatorHDF5FileHandler::setMeshEstimator(
                               const InternalEventObserverHandle estimator_id )
{
  try{
    this->getHDF5File().writeValueToGroupAttribute(
			       MESH_VOLUME_ENTITY,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_entity_type_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set estimator " << estimator_id <<
                           " as a mesh estimator in the HDF5 file!" );
}

// Check if the estimator is a mesh estimator
bool EstimatorHDF5FileHandler::isMeshEstimator(
			 const InternalEventObserverHandle estimator_id ) const
{
  EntityType type;

  try{
    this->getHDF5File().readValueFromGroupAttribute(
			       type,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_entity_type_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to determine if estimator "
                           << estimator_id << " is a mesh estimator!" );

  return (type == MESH_VOLUME_ENTITY);
}

// Set the estimator multiplier
void EstimatorHDF5FileHandler::setEstimatorMultiplier(
				const InternalEventObserverHandle estimator_id,
                                const double multiplier )
{
  try{
    this->getHDF5File().writeValueToGroupAttribute(
			       multiplier,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_multiplier_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the multiplier for estimator "
                           << estimator_id << " in the HDF5 file!" );
}

// Get the estimator multiplier
void EstimatorHDF5FileHandler::getEstimatorMultiplier(
				const InternalEventObserverHandle estimator_id,
                                double& multiplier ) const
{
  try{
    this->getHDF5File().readValueFromGroupAttribute(
			       multiplier,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_multiplier_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the multiplier from the HDF5 file "
                           "for estimator " << estimator_id << "!" );
}

// Set the total normalization constant
void EstimatorHDF5FileHandler::setEstimatorTotalNormConstant(
			        const InternalEventObserverHandle estimator_id,
                                const double total_norm_constant )
{
  try{
    this->getHDF5File().writeValueToGroupAttribute(
			       total_norm_constant,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_total_norm_constant_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the normalization constant "
                           "for estimator " << estimator_id << "in the"
                           "HDF5 file!" );
}

// Get the total normalization constant
void EstimatorHDF5FileHandler::getEstimatorTotalNormConstant(
				const InternalEventObserverHandle estimator_id,
                                double& total_norm_constant ) const
{
  try{
    this->getHDF5File().readValueFromGroupAttribute(
			       total_norm_constant,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_total_norm_constant_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the normalization constant from the "
                           "HDF5 file for estimator " << estimator_id << "!" );
}

// Get the estimator location
std::string EstimatorHDF5FileHandler::getEstimatorGroupLocation(
			 const InternalEventObserverHandle estimator_id ) const
{
  std::ostringstream oss;
  oss << EstimatorHDF5FileHandler::s_estimator_group_loc_name;
  oss << estimator_id << "/";

  return oss.str();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
