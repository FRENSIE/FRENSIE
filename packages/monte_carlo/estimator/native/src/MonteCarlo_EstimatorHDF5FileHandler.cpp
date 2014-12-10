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
			   "Ownership Constructor Error" );
}

// Constructor (file sharing)
EstimatorHDF5FileHandler::EstimatorHDF5FileHandler( 
		      const Teuchos::RCP<Utility::HDF5FileHandler>& hdf5_file )
  : d_hdf5_file( hdf5_file ),
    d_hdf5_file_ownership( false )
{
  // Make sure the file is valid
  testPrecondition( !hdf5_file.is_null() );
  testPrecondition( hdf5_file->hasOpenFile() );
}

// Destructor
EstimatorHDF5FileHandler::~EstimatorHDF5FileHandler()
{
  if( d_hdf5_file_ownership )
    d_hdf5_file->closeHDF5File();
}

// Set the simulation time
void EstimatorHDF5FileHandler::setSimulationTime( 
						const double simulation_time )
{
  // Make sure the simulation time is valid
  testPrecondition( simulation_time > 0.0 );
  
  try{
    d_hdf5_file->writeValueToGroupAttribute( simulation_time,
					     estimator_group_loc_name,
					     "simulation_time" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, "Set Simulation Time Error" );
}

// Get the simulation time
void EstimatorHDF5FileHandler::getSimulationTime( 
						double& simulation_time ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute( simulation_time,
					      estimator_group_loc_name,
					      "simulation_time" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, "Get Simulation Time Error" );
}

// Set the last history simulated
void EstimatorHDF5FileHandler::setLastHistorySimulated( 
			     const unsigned long long last_history_simulated )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute( last_history_simulated,
					     estimator_group_loc_name,
					     "last_history_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Set Last History Simulated Error" );
}

// Get the last history simulated
void EstimatorHDF5FileHandler::getLastHistorySimulated(
			     unsigned long long& last_history_simulated ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute( last_history_simulated,
					      estimator_group_loc_name,
					      "last_history_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get Last History Simulated Error" );
}

// Set the number of histories simulated
void EstimatorHDF5FileHandler::setNumberOfHistoriesSimulated(
			  const unsigned long long number_histories_simulated )
{
  // Make sure the number of histories simulated is valid
  testPrecondition( number_histories_simulated > 0ull );
  
  try{
    d_hdf5_file->writeValueToGroupAttribute( number_histories_simulated,
					     estimator_group_loc_name,
					     "number_of_histories_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Set Number of Histories Simulated Error" );
}

// Get the number of histories simulated
void EstimatorHDF5FileHandler::getNumberOfHistoriesSimulated(
			 unsigned long long& number_histories_simulated ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute( number_histories_simulated,
					      estimator_group_loc_name,
					      "number_of_histories_simulated");
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get Number of Histories Simulated Error" );
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
			   "Set Surface Estimator Error" );
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
			   "Is Surface Estimator Error" );

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
			   "Set Cell Estimator Error" );
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
			   "Is Cell Estimator Error" );

  return (type == CELL_ENTITY);
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
			   "Set Estimator Multiplier Error" );
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
			   "Get Estimator Multiplier Error" );
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
			   "Set Estimator Response Function Ordering Error" );
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
			   "Get Estimator Response Function Ordering Error" );
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
			   "Set Estimator Dimension Ordering Error" );
}

// Get the estimator dimension ordering
void EstimatorHDF5FileHandler::getEstimatorDimensionOrdering(
	       const unsigned estimator_id,
	       Teuchos::Array<PhaseSpaceDimension>& dimension_ordering ) const
{
  try{
    d_hdf5_file->readArrayFromGroupAttribute( 
			       dimension_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "dimension_ordering" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get Estimator Dimension Ordering Error" );
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
			   "Set Total Norm Constant Error" );
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
			   "Get Total Norm Constant Error" );
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
			   "Set Raw Estimator Total Bin Data Error" );
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
			   "Get Raw Estimator Total Bin Data Error" );
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
			   "Set Processed Estimator Total Bin Data Error" );
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
			   "Get Processed Estimator Total Bin Data Error" );
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
			   "Set Raw Estimator Total Data Error" );
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
			   "Get Raw Estimator Total Data Error" );
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
			   "Set Processed Estimator Total Data Error" );
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
			   "Get Processed Estimator Total Data Error" );
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
