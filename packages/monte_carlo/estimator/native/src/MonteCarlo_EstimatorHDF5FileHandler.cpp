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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::string EstimatorHDF5FileHandler::estimator_group_loc_name( 
							       "/Estimators" );

// Constructor
EstimatorHDF5FileHandler::EstimatorHDF5FileHandler( 
					    const std::string& hdf5_file_name )
  : d_hdf5_file()
{
  d_hdf5_file.openHDF5FileAndAppend( hdf5_file_name );
}

// Destructor
EstimatorHDF5FileHandler::~EstimatorHDF5FileHandler()
{
  d_hdf5_file.closeHDF5File();
}

// Set the simulation time
void EstimatorHDF5FileHandler::setSimulationTime( 
						const double simulation_time )
{
  // Make sure the simulation time is valid
  testPrecondition( simulation_time > 0.0 );
  
  d_hdf5_file.writeValueToGroupAttribute( simulation_time,
					  estimator_group_loc_name.c_str(),
					  "simulation_time" );
}

// Get the simulation time
void EstimatorHDF5FileHandler::getSimulationTime( 
						double& simulation_time ) const
{
  d_hdf5_file.readValueFromGroupAttribute( simulation_time,
					   estimator_group_loc_name.c_str(),
					   "simulation_time" );
}

// Set the last history simulated
void EstimatorHDF5FileHandler::setLastHistorySimulated( 
			     const unsigned long long last_history_simulated )
{
  // Make sure the last history simulated is valid
  testPrecondition( last_history_simulated > 0ull );
  
  d_hdf5_file.writeValueToGroupAttribute( last_history_simulated,
					  estimator_group_loc_name.c_str(),
					  "last_history_simulated" );
}

// Get the last history simulated
void EstimatorHDF5FileHandler::getLastHistorySimulated(
			     unsigned long long& last_history_simulated ) const
{
  d_hdf5_file.readValueFromGroupAttribute( last_history_simulated,
					   estimator_group_loc_name.c_str(),
					   "last_history_simulated" );
}

// Set the number of histories simulated
void EstimatorHDF5FileHandler::setNumberOfHistoriesSimulated(
			  const unsigned long long number_histories_simulated )
{
  // Make sure the number of histories simulated is valid
  testPrecondition( number_histories_simulated > 0ull );
  
  d_hdf5_file.writeValueToGroupAttribute( number_histories_simulated,
					  estimator_group_loc_name.c_str(),
					  "number_of_histories_simulated" );
}

// Get the number of histories simulated
void EstimatorHDF5FileHandler::getNumberOfHistoriesSimulated(
			 unsigned long long& number_histories_simulated ) const
{
  d_hdf5_file.readValueFromGroupAttribute( number_histories_simulated,
					   estimator_group_loc_name.c_str(),
					   "number_of_histories_simulated" );
}

// Check if an estimator exists
bool EstimatorHDF5FileHandler::doesEstimatorExist( 
					    const unsigned estimator_id ) const
{
  return d_hdf5_file.doesGroupExist( 
			     this->getEstimatorGroupLocation( estimator_id ) );
}

// Set the estimator as a surface estimator
void EstimatorHDF5FileHandler::setSurfaceEstimator( 
						  const unsigned estimator_id )
{
  d_hdf5_file.writeValueToGroupAttribute( 
			       0, 
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );
}

// Check if the estimator is a surface estimator
bool EstimatorHDF5FileHandler::isSurfaceEstimator( 
					    const unsigned estimator_id ) const
{
  int type;
  
  d_hdf5_file.readValueFromGroupAttribute( 
			       type,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );

  return (type == 0);
					  
}

// Set the estimator as a cell estimator
void EstimatorHDF5FileHandler::setCellEstimator( const unsigned estimator_id )
{
  d_hdf5_file.writeValueToGroupAttribute( 
			       1, 
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );
}

// Check if the estimator is a cell estimator
bool EstimatorHDF5FileHandler::isCellEstimator( 
					    const unsigned estimator_id ) const
{
  int type;

  d_hdf5_file.readValueFromGroupAttribute( 
			       type,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "entity_type" );

  return (type == 1);
}

// Set the estimator multiplier
void EstimatorHDF5FileHandler::setEstimatorMultiplier( 
						   const unsigned estimator_id,
						   const double multiplier )
{
  d_hdf5_file.writeValueToGroupAttribute(
			       multiplier,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "multiplier" );
}

// Get the estimator multiplier
void EstimatorHDF5FileHandler::getEstimatorMultiplier( 
						   const unsigned estimator_id,
						   double& multiplier ) const
{
  d_hdf5_file.readValueFromGroupAttribute(
			       multiplier,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "multiplier" );
}

// Set the estimator response function ordering
void EstimatorHDF5FileHandler::setEstimatorResponseFunctionOrdering(
		  const unsigned estimator_id,
		  const Teuchos::Array<unsigned>& response_function_ordering )
{
  d_hdf5_file.writeArrayToGroupAttribute(
			       response_function_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "response_function_ordering" );
}

// Get the estimator response function ordering
void EstimatorHDF5FileHandler::getEstimatorResponseFunctionOrdering(
		  const unsigned estimator_id,
		  Teuchos::Array<unsigned>& response_function_ordering ) const
{
  d_hdf5_file.readArrayFromGroupAttribute(
			       response_function_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "response_function_ordering" );
}

// Set the estimator dimension ordering
void EstimatorHDF5FileHandler::setEstimatorDimensionOrdering(
	       const unsigned estimator_id,
	       const Teuchos::Array<PhaseSpaceDimension>& dimension_ordering )
{
  d_hdf5_file.writeArrayToGroupAttribute( 
			       dimension_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "dimension_ordering" );
}

// Get the estimator dimension ordering
void EstimatorHDF5FileHandler::getEstimatorDimensionOrdering(
	       const unsigned estimator_id,
	       Teuchos::Array<PhaseSpaceDimension>& dimension_ordering ) const
{
  d_hdf5_file.readArrayFromGroupAttribute( 
			       dimension_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       "dimension_ordering" );
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
  
  data_set_location += "/raw_total_bin_data";
  
  d_hdf5_file.writeArrayToDataSet( raw_bin_data, data_set_location );
}

// Get the raw estimator bin data over all entities (1st, 2nd moments)
void EstimatorHDF5FileHandler::getRawEstimatorTotalBinData(
	   const unsigned estimator_id,
	   Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data ) const
{
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "/raw_total_bin_data";

  d_hdf5_file.readArrayFromDataSet( raw_bin_data, data_set_location );
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
  
  data_set_location += "/processed_total_bin_data";

  d_hdf5_file.writeArrayToDataSet( processed_bin_data, data_set_location );
}

// Get the processed estimator bin data over all entities (mean, rel. err.)
void EstimatorHDF5FileHandler::getProcessedEstimatorTotalBinData(
     const unsigned estimator_id,
     Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data ) const
{
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "/processed_total_bin_data";

  d_hdf5_file.readArrayFromDataSet( processed_bin_data, data_set_location );
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
  
  data_set_location += "/raw_total_data";

  d_hdf5_file.writeArrayToDataSet( raw_total_data, data_set_location );
}

// Get the raw estimator total data over all entities
void EstimatorHDF5FileHandler::getRawEstimatorTotalData(
		   const unsigned estimator_id,
		   Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   raw_total_data ) const
{
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "/raw_total_data";

  d_hdf5_file.readArrayFromDataSet( raw_total_data, data_set_location );
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
  
  data_set_location += "/processed_total_data";

  d_hdf5_file.writeArrayToDataSet( processed_total_data, data_set_location );
}

// Get the processed estimator total data over all entities
void EstimatorHDF5FileHandler::getProcessedEstimatorTotalData(
		   const unsigned estimator_id,
	           Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   processed_total_data ) const
{
  std::string data_set_location = 
    this->getEstimatorGroupLocation( estimator_id );
  
  data_set_location += "/processed_total_data";

  d_hdf5_file.readArrayFromDataSet( processed_total_data, data_set_location );
}

// Get the estimator location
std::string EstimatorHDF5FileHandler::getEstimatorGroupLocation(
					    const unsigned estimator_id ) const
{
  std::ostringstream oss( estimator_group_loc_name );
  oss << "/" << estimator_id;

  return oss.str();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
