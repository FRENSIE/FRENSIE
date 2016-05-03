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
const std::string EstimatorHDF5FileHandler::estimator_group_loc_name( 
							      "/Estimators/" );

// Constructor (file ownership)
/*! \details The EstimatorHDF5FileOps enum will determine how the HDF5 file
 * is opened. If the read only option is used, calling any of the set
 * methods will result in an exception.
 */
EstimatorHDF5FileHandler::EstimatorHDF5FileHandler( 
					   const std::string& hdf5_file_name,
					   const EstimatorHDF5FileOps file_op )
  : d_hdf5_file( new Utility::HDF5FileHandler ),
    d_hdf5_file_ownership( true )
{
  // Make sure the name is valid
  testPrecondition( hdf5_file_name.size() > 0 );
  
  Utility::HDF5FileHandler::throwExceptions();

  try{
    switch( file_op )
    {
    case OVERWRITE_ESTIMATOR_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndOverwrite( hdf5_file_name );
      break;
    case APPEND_ESTIMATOR_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndAppend( hdf5_file_name );
      break;
    case READ_ONLY_ESTIMATOR_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndReadOnly( hdf5_file_name );
      break;
    }
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to construct the estimator HDF5 file"
                           " handler!" );
}

// Constructor (file sharing)
EstimatorHDF5FileHandler::EstimatorHDF5FileHandler( 
                   const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  : d_hdf5_file( hdf5_file ),
    d_hdf5_file_ownership( false )
{
  // Make sure the file is valid
  testPrecondition( hdf5_file.get() );
  testPrecondition( hdf5_file->hasOpenFile() );

  Utility::HDF5FileHandler::throwExceptions();
}

// Destructor
EstimatorHDF5FileHandler::~EstimatorHDF5FileHandler()
{
  if( d_hdf5_file_ownership )
    d_hdf5_file->closeHDF5File();
}

// Check if an estimator exists
bool EstimatorHDF5FileHandler::doesEstimatorExist( 
					    const unsigned estimator_id ) const
{
  return d_hdf5_file->doesGroupExist( 
			     this->getEstimatorGroupLocation( estimator_id ) );
}

// Set the estimator as a surface estimator
void EstimatorHDF5FileHandler::setSurfaceEstimator( 
						  const unsigned estimator_id )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute( 
			       SURFACE_ENTITY, 
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set estimator " << estimator_id <<
                           " as a surface estimator!" );
}

// Check if the estimator is a surface estimator
bool EstimatorHDF5FileHandler::isSurfaceEstimator( 
					    const unsigned estimator_id ) const
{
  EntityType type;
  
  try{
    d_hdf5_file->readValueFromGroupAttribute( 
			       type,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to determine if estimator "
                           << estimator_id << " is a surface estimator!" );

  return (type == SURFACE_ENTITY);
					  
}

// Set the estimator as a cell estimator
void EstimatorHDF5FileHandler::setCellEstimator( const unsigned estimator_id )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute( 
			       CELL_ENTITY, 
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set estimator " << estimator_id <<
                           " as a cell estimator!" );
}

// Check if the estimator is a cell estimator
bool EstimatorHDF5FileHandler::isCellEstimator( 
					    const unsigned estimator_id ) const
{
  EntityType type;

  try{
    d_hdf5_file->readValueFromGroupAttribute( 
			       type,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to determine if estimator "
                           << estimator_id << " is a cell estimator!" );

  return (type == CELL_ENTITY);
}

// Set the estimator as a mesh estimator
void EstimatorHDF5FileHandler::setMeshEstimator( const unsigned estimator_id )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute( 
			       MESH_VOLUME_ENTITY, 
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set estimator " << estimator_id <<
                           " as a mesh estimator!" );
}

// Check if the estimator is a mesh estimator
bool EstimatorHDF5FileHandler::isMeshEstimator( 
					    const unsigned estimator_id ) const
{
  EntityType type;

  try{
    d_hdf5_file->readValueFromGroupAttribute( 
			       type,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to determine if estimator "
                           << estimator_id << " is a mesh estimator!" );

  return (type == MESH_VOLUME_ENTITY);
}

// Set the estimator multiplier
void EstimatorHDF5FileHandler::setEstimatorMultiplier( 
						   const unsigned estimator_id,
						   const double multiplier )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute(
			       multiplier,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "multiplier" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the multiplier for estimator "
                           << estimator_id << "!" );
}

// Get the estimator multiplier
void EstimatorHDF5FileHandler::getEstimatorMultiplier( 
						   const unsigned estimator_id,
						   double& multiplier ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute(
			       multiplier,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "multiplier" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the multiplier for estimator "
                           << estimator_id << "!" );
}

// Set the estimator response function ordering
void EstimatorHDF5FileHandler::setEstimatorResponseFunctionOrdering(
		  const unsigned estimator_id,
		  const Teuchos::Array<unsigned>& response_function_ordering )
{
  try{
    d_hdf5_file->writeArrayToGroupAttribute(
			       response_function_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "response_function_ordering" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the response function "
                           "ordering for estimator " << estimator_id << "!" );
}

// Get the estimator response function ordering
void EstimatorHDF5FileHandler::getEstimatorResponseFunctionOrdering(
		  const unsigned estimator_id,
		  Teuchos::Array<unsigned>& response_function_ordering ) const
{
  try{
    d_hdf5_file->readArrayFromGroupAttribute(
			       response_function_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "response_function_ordering" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the response function "
                           "ordering for estimator " << estimator_id << "!" );
}

// Set the estimator dimension ordering
void EstimatorHDF5FileHandler::setEstimatorDimensionOrdering(
	       const unsigned estimator_id,
	       const Teuchos::Array<PhaseSpaceDimension>& dimension_ordering )
{
  try{
    d_hdf5_file->writeArrayToGroupAttribute( 
			       dimension_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "dimension_ordering" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the dimension ordering for "
                           "estimator " << estimator_id << "!" );
}

// Get the estimator dimension ordering
void EstimatorHDF5FileHandler::getEstimatorDimensionOrdering(
	       const unsigned estimator_id,
	       Teuchos::Array<PhaseSpaceDimension>& dimension_ordering ) const
{
  dimension_ordering.clear();
  
  // If an exception is thrown, there are no estimator dimensions
  try{
    if( d_hdf5_file->doesGroupAttributeExist( 
			       this->getEstimatorGroupLocation( estimator_id ),
			       "dimension_ordering" ) )
    {
      d_hdf5_file->readArrayFromGroupAttribute( 
			       dimension_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "dimension_ordering" );
    }
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the dimension ordering for "
                           "estimator " << estimator_id << "!" );
}

// Set the total normalization constant
void EstimatorHDF5FileHandler::setEstimatorTotalNormConstant( 
			     const unsigned estimator_id,
			     const double total_norm_constant )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute(
			       total_norm_constant,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "total_norm_constant" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the normalization constant "
                           "for estimator " << estimator_id << "!" );
}

// Get the total normalization constant
void EstimatorHDF5FileHandler::getEstimatorTotalNormConstant( 
					    const unsigned estimator_id,
					    double& total_norm_constant ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute(
			       total_norm_constant,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "total_norm_constant" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the normalization constant "
                           "for estimator " << estimator_id << "!" );
}

// Set the raw estimator bin data over all entities (1st, 2nd moments)
void EstimatorHDF5FileHandler::setRawEstimatorTotalBinData(
	   const unsigned estimator_id,
	   const Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data )
{
  // Make sure the bin data is valid
  testPrecondition( raw_bin_data.size() > 0 );
  
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "raw_total_bin_data";
  
  try{
    d_hdf5_file->writeArrayToDataSet( raw_bin_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the raw total bin data for "
                           "estimator " << estimator_id << "!" );
}

// Get the raw estimator bin data over all entities (1st, 2nd moments)
void EstimatorHDF5FileHandler::getRawEstimatorTotalBinData(
	   const unsigned estimator_id,
	   Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data ) const
{
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "raw_total_bin_data";
  
  try{
    d_hdf5_file->readArrayFromDataSet( raw_bin_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the raw total bin data for "
                           "estimator " << estimator_id << "!" );
}

// Set the processed estimator bin data over all entities (mean, rel. err.)
void EstimatorHDF5FileHandler::setProcessedEstimatorTotalBinData(
     const unsigned estimator_id,
     const Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data )
{
  // Make sure the total bin data is valid
  testPrecondition( processed_bin_data.size() > 0 );
  
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "processed_total_bin_data";

  try{
    d_hdf5_file->writeArrayToDataSet( processed_bin_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the processed total bin data "
                           "for estimator " << estimator_id << "!" );
}

// Get the processed estimator bin data over all entities (mean, rel. err.)
void EstimatorHDF5FileHandler::getProcessedEstimatorTotalBinData(
     const unsigned estimator_id,
     Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data ) const
{
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "processed_total_bin_data";

  try{
    d_hdf5_file->readArrayFromDataSet( processed_bin_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the processed total bin data "
                           "for estimator " << estimator_id << "!" );
}

// Set the raw estimator total data over all entities 
void EstimatorHDF5FileHandler::setRawEstimatorTotalData(
	     const unsigned estimator_id,
	     const Teuchos::Array<Utility::Quad<double,double,double,double> >&
	     raw_total_data )
{
  // Make sure the total bin data is valid
  testPrecondition( raw_total_data.size() > 0 );
  
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "raw_total_data";

  try{
    d_hdf5_file->writeArrayToDataSet( raw_total_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the raw total data for "
                           "estimator " << estimator_id << "!" );
}

// Get the raw estimator total data over all entities
void EstimatorHDF5FileHandler::getRawEstimatorTotalData(
		   const unsigned estimator_id,
		   Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   raw_total_data ) const
{
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "raw_total_data";

  try{
    d_hdf5_file->readArrayFromDataSet( raw_total_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the raw total data for "
                           "estimator " << estimator_id << "!" );
}

// Set the processed estimator total data over all entities
void EstimatorHDF5FileHandler::setProcessedEstimatorTotalData(
	     const unsigned estimator_id,
	     const Teuchos::Array<Utility::Quad<double,double,double,double> >&
	     processed_total_data )
{
  // Make sure the total bin data is valid
  testPrecondition( processed_total_data.size() > 0 );
  
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "processed_total_data";

  try{
    d_hdf5_file->writeArrayToDataSet( processed_total_data, data_set_location);
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the processed total data for "
                           "estimator " << estimator_id << "!" );
}

// Get the processed estimator total data over all entities
void EstimatorHDF5FileHandler::getProcessedEstimatorTotalData(
		   const unsigned estimator_id,
	           Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   processed_total_data ) const
{
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "processed_total_data";

  try{
    d_hdf5_file->readArrayFromDataSet(processed_total_data, data_set_location);
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the processed total data for "
                           "estimator " << estimator_id << "!" );
}

// Get the estimator location
std::string EstimatorHDF5FileHandler::getEstimatorGroupLocation(
					    const unsigned estimator_id ) const
{
  std::ostringstream oss;
  oss << EstimatorHDF5FileHandler::estimator_group_loc_name;
  oss << estimator_id << "/";
  
  return oss.str();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
