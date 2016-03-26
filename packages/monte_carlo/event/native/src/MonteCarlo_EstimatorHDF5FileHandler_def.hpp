//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorHDF5FileHandler_def.hpp
//! \author Alex Robinson
//! \brief  Estimator hdf5 file handler class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_HDF5_FILE_HANDLER_DEF_HPP
#define MONTE_CARLO_ESTIMATOR_HDF5_FILE_HANDLER_DEF_HPP

namespace MonteCarlo{

// Check if an entity is assigned to an estimator
template<typename EntityIdType>
bool EstimatorHDF5FileHandler::isEntityAssignedToEstimator( 
					   const unsigned estimator_id,
				           const EntityIdType entity_id ) const
{
  return d_hdf5_file->doesGroupExist(
	    this->getEstimatorEntityGroupLocation( estimator_id, entity_id ) );
}

// Set the entity normalization constant
template<typename EntityIdType>
void EstimatorHDF5FileHandler::setEntityNormConstant( 
						  const unsigned estimator_id,
						  const EntityIdType entity_id,
						  const double norm_constant )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute( 
	      norm_constant,
	      this->getEstimatorEntityGroupLocation( estimator_id, entity_id ),
	      "norm_constant" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
                           "Error: Unable to set entity " << entity_id <<  
                           " normalization constant for estimator " 
                           << estimator_id << "!" );
}

// Get the entity normalization constant
template<typename EntityIdType>
void EstimatorHDF5FileHandler::getEntityNormConstant( 
						  const unsigned estimator_id,
						  const EntityIdType entity_id,
						  double& norm_constant ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute(
	      norm_constant,
	      this->getEstimatorEntityGroupLocation( estimator_id, entity_id ),
	      "norm_constant" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
                           "Error: Unable to get entity " << entity_id <<  
                           " normalization constant for estimator " 
                           << estimator_id << "!" );
}

// Set the estimator bin boundaries
template<PhaseSpaceDimension dimension>
void EstimatorHDF5FileHandler::setEstimatorBinBoundaries(
                                                   const unsigned estimator_id,
						   const Teuchos::Array<typename PhaseSpaceDimensionTraits<dimension>::dimensionType>& bin_boundaries )
{
  std::string bin_boundary_set = 
    this->getEstimatorGroupLocation( estimator_id );

  bin_boundary_set += PhaseSpaceDimensionTraits<dimension>::name();
  
  try{
    d_hdf5_file->writeArrayToDataSet( bin_boundaries, bin_boundary_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the " << dimension <<
                           " bin boundaries for estimator " 
                           << estimator_id << "!" );
}

// Get the estimator bin boundaries
template<PhaseSpaceDimension dimension>
void EstimatorHDF5FileHandler::getEstimatorBinBoundaries(
						   const unsigned estimator_id,
						   Teuchos::Array<typename PhaseSpaceDimensionTraits<dimension>::dimensionType>& bin_boundaries ) const
{
  std::string bin_boundary_set = 
    this->getEstimatorGroupLocation( estimator_id );

  bin_boundary_set += PhaseSpaceDimensionTraits<dimension>::name();

  try{
    d_hdf5_file->readArrayFromDataSet( bin_boundaries, bin_boundary_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the " << dimension <<
                           " bin boundaries for estimator " 
                           << estimator_id << "!" );
}

// Set the estimator entities and norm constants
template<typename EntityIdType>
void EstimatorHDF5FileHandler::setEstimatorEntities(
		     const unsigned estimator_id,
                     const Teuchos::Array<Utility::Pair<EntityIdType,double> >&
		     entity_id_norms )
{
  std::string estimator_entities_data_set = 
    this->getEstimatorGroupLocation( estimator_id );
  
  estimator_entities_data_set += "entity_norm_constants";
  
  try{
    d_hdf5_file->writeArrayToDataSet( entity_id_norms,
				      estimator_entities_data_set );

    // d_hdf5_file->writeArrayToGroupAttribute(
    // 			       entity_id_norms,
    // 			       this->getEstimatorGroupLocation( estimator_id ),
    // 			       "estimator_entity_ids" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the entity normalization "
                           "constants for estimator " << estimator_id << "!" );
}

// Set the estimator entities and norm constants
template<typename EntityIdNormConstMap>
void EstimatorHDF5FileHandler::setEstimatorEntities(
				  const unsigned estimator_id,
				  const EntityIdNormConstMap& entity_id_norms )
{
  // Make sure the key type is valid
  testStaticPrecondition( (boost::is_integral<typename EntityIdNormConstMap::key_type>::value) );
  // Make sure the value type is valid
  testStaticPrecondition( (boost::is_floating_point<typename EntityIdNormConstMap::mapped_type>::value ) );

  // Construct an array from the map
  Teuchos::Array<Utility::Pair<typename EntityIdNormConstMap::key_type,
			       double> > 
    entity_id_norms_copy( entity_id_norms.size() );

  typename EntityIdNormConstMap::const_iterator entity_data;
  unsigned i;

  for( entity_data = entity_id_norms.begin(), i = 0; 
       entity_data != entity_id_norms.end();
       ++entity_data, ++i )
  {
    entity_id_norms_copy[i].first = entity_data->first;
    entity_id_norms_copy[i].second = entity_data->second;
  }

  setEstimatorEntities( estimator_id, entity_id_norms_copy );
}

// Get the estimator entities and norm constants
template<typename EntityIdType>
void EstimatorHDF5FileHandler::getEstimatorEntities(
		           const unsigned estimator_id,
                           Teuchos::Array<Utility::Pair<EntityIdType,double> >&
			   entity_id_norms ) const
{
  std::string estimator_entities_data_set = 
    this->getEstimatorGroupLocation( estimator_id );
  
  estimator_entities_data_set += "entity_norm_constants";
  
  try{
    d_hdf5_file->readArrayFromDataSet( entity_id_norms,
				       estimator_entities_data_set );
    
    // d_hdf5_file->readArrayFromGroupAttribute(
    // 			       entity_id_norms,
    // 			       this->getEstimatorGroupLocation( estimator_id ),
    // 			       "estimator_entity_ids" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the entity normalization "
                           "constants for estimator " << estimator_id << "!" );
}

// Get the estimator entities and norm constants
template<typename EntityIdNormConstMap>
void EstimatorHDF5FileHandler::getEstimatorEntities(
				  const unsigned estimator_id,
				  EntityIdNormConstMap& entity_id_norms ) const
{
  // Make sure the key type is valid
  testStaticPrecondition( (boost::is_integral<typename EntityIdNormConstMap::key_type>::value) );
  // Make sure the value type is valid
  testStaticPrecondition( (boost::is_floating_point<typename EntityIdNormConstMap::mapped_type>::value ) );

  Teuchos::Array<Utility::Pair<typename EntityIdNormConstMap::key_type,
			       double> > 
    entity_id_norms_copy;

  getEstimatorEntities( estimator_id, entity_id_norms_copy );

  // Convert the array to a map
  for( unsigned i = 0; i < entity_id_norms_copy.size(); ++i )
  {
    entity_id_norms[entity_id_norms_copy[i].first] = 
      entity_id_norms_copy[i].second;
  }
}
  
// Set the raw estimator bin data for an entity (1st, 2nd moments)
template<typename EntityIdType>
void EstimatorHDF5FileHandler::setRawEstimatorEntityBinData(
	   const unsigned estimator_id,
	   const EntityIdType entity_id,
	   const Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data )
{
  std::string bin_boundaries_data_set = 
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  bin_boundaries_data_set += "raw_bin_data";
  
  try{
    d_hdf5_file->writeArrayToDataSet( raw_bin_data, bin_boundaries_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the raw entity "
                           << entity_id << " bin data for estimator "
                           << estimator_id << "!" );
}

// Get the raw estimator bin data for an entity (1st, 2nd moments)
template<typename EntityIdType>
void EstimatorHDF5FileHandler::getRawEstimatorEntityBinData(
	   const unsigned estimator_id,
	   const EntityIdType entity_id,
	   Teuchos::Array<Utility::Pair<double,double> >& raw_bin_data ) const
{
  std::string bin_boundaries_data_set = 
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  bin_boundaries_data_set += "raw_bin_data";

  try{
    d_hdf5_file->readArrayFromDataSet( raw_bin_data, bin_boundaries_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the raw entity "
                           << entity_id << " bin data for estimator "
                           << estimator_id << "!" );
}

// Set the processed estimator bin data for an entity (mean, relative error)
template<typename EntityIdType>
void EstimatorHDF5FileHandler::setProcessedEstimatorEntityBinData(
     const unsigned estimator_id,
     const EntityIdType entity_id,
     const Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data )
{
  std::string bin_boundaries_data_set = 
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  bin_boundaries_data_set += "processed_bin_data";

  try{
    d_hdf5_file->writeArrayToDataSet( processed_bin_data, 
				      bin_boundaries_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the processed entity " 
                           << entity_id << " bin data for estimator "
                           << estimator_id << "!" );
}

// Get the processed estimator bin data for an entity (mean, relative error)
template<typename EntityIdType>
void EstimatorHDF5FileHandler::getProcessedEstimatorEntityBinData(
     const unsigned estimator_id,
     const EntityIdType entity_id,
     Teuchos::Array<Utility::Pair<double,double> >& processed_bin_data ) const
{
  std::string bin_boundaries_data_set = 
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  bin_boundaries_data_set += "processed_bin_data";

  try{
    d_hdf5_file->readArrayFromDataSet( processed_bin_data, 
				       bin_boundaries_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the processed entity " 
                           << entity_id << " bin data for estimator "
                           << estimator_id << "!" );
}

// Set the raw estimator total data for an entity 
template<typename EntityIdType>
void EstimatorHDF5FileHandler::setRawEstimatorEntityTotalData(
	     const unsigned estimator_id,
	     const EntityIdType entity_id,
             const Teuchos::Array<Utility::Quad<double,double,double,double> >&
	     raw_total_data )
{
  std::string total_data_set = 
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  total_data_set += "raw_total_data";

  try{
    d_hdf5_file->writeArrayToDataSet( raw_total_data, total_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the raw entity "
                           << entity_id << " total data for estimator "
                           << estimator_id << "!" );
}

// Get the raw estimator total data for an entity 
template<typename EntityIdType>
void EstimatorHDF5FileHandler::getRawEstimatorEntityTotalData(
		   const unsigned estimator_id,
		   const EntityIdType entity_id,
                   Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   raw_total_data ) const
{
  std::string total_data_set = 
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  total_data_set += "raw_total_data";

  try{
    d_hdf5_file->readArrayFromDataSet( raw_total_data, total_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the raw entity "
                           << entity_id << " total data for estimator "
                           << estimator_id << "!" );
}

// Set the processed estimator total data for an entity 
template<typename EntityIdType>
void EstimatorHDF5FileHandler::setProcessedEstimatorEntityTotalData(
	     const unsigned estimator_id,
	     const EntityIdType entity_id,
             const Teuchos::Array<Utility::Quad<double,double,double,double> >&
	     processed_total_data )
{
  std::string total_data_set = 
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  total_data_set += "processed_total_data";
  
  try{
    d_hdf5_file->writeArrayToDataSet( processed_total_data, total_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the processed entity "
                           << entity_id << " total data for estimator "
                           << estimator_id << "!" );
}

// Get the processed estimator total data for an entity
template<typename EntityIdType>
void EstimatorHDF5FileHandler::getProcessedEstimatorEntityTotalData(
	           const unsigned estimator_id,
		   const EntityIdType entity_id,
                   Teuchos::Array<Utility::Quad<double,double,double,double> >&
		   processed_total_data ) const
{
  std::string total_data_set = 
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  total_data_set += "processed_total_data";

  try{
    d_hdf5_file->readArrayFromDataSet( processed_total_data, total_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the processed entity "
                           << entity_id << " total data for estimator "
                           << estimator_id << "!" );
}

// Get the estimator entity location
template<typename EntityIdType>
std::string EstimatorHDF5FileHandler::getEstimatorEntityGroupLocation( 
					  const unsigned estimator_id,
					  const EntityIdType entity_id ) const
{
  std::ostringstream oss;
  oss << this->getEstimatorGroupLocation( estimator_id );
  oss << entity_id << "/";

  return oss.str();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ESTIMATOR_HDF5_FILE_HANDLER_DEF_HPP 

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHDF5FileHandler_def.hpp
//---------------------------------------------------------------------------//
