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
				const InternalEventObserverHandle estimator_id,
                                const EntityIdType entity_id ) const
{
  return d_hdf5_file->doesGroupExist(
	    this->getEstimatorEntityGroupLocation( estimator_id, entity_id ) );
}

// Set the entity normalization constant
template<typename EntityIdType>
void EstimatorHDF5FileHandler::setEntityNormConstant(
				const InternalEventObserverHandle estimator_id,
                                const EntityIdType entity_id,
                                const double norm_constant )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute(
	      norm_constant,
	      this->getEstimatorEntityGroupLocation( estimator_id, entity_id ),
	      s_entity_norm_constant_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to set entity " << entity_id <<
                           " normalization constant for estimator "
                           << estimator_id << " in HDF5 file!" );
}

// Get the entity normalization constant
template<typename EntityIdType>
void EstimatorHDF5FileHandler::getEntityNormConstant(
				const InternalEventObserverHandle estimator_id,
                                const EntityIdType entity_id,
                                double& norm_constant ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute(
	      norm_constant,
	      this->getEstimatorEntityGroupLocation( estimator_id, entity_id ),
	      s_entity_norm_constant_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to get entity " << entity_id <<
                           " normalization constant form the HDF5 file for "
                           "estimator " << estimator_id << "!" );
}

// Set the estimator response function ordering
template<template<typename,typename...> class STLCompliantArray>
void EstimatorHDF5FileHandler::setEstimatorResponseFunctionOrdering(
		  const InternalEventObserverHandle estimator_id,
		  const STLCompliantArray<size_t>& response_function_ordering )
{
  try{
    this->getHDF5File().writeArrayToGroupAttribute(
			       response_function_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_response_function_ordering_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the response function ordering for "
                           "estimator " << estimator_id << " in the HDF5 "
                           "file!" );
}

// Get the estimator response function ordering
template<template<typename,typename...> class STLCompliantArray>
void EstimatorHDF5FileHandler::getEstimatorResponseFunctionOrdering(
		  const InternalEventObserverHandle estimator_id,
		  STLCompliantArray<size_t>& response_function_ordering ) const
{
  try{
    this->getHDF5File().readArrayFromGroupAttribute(
			       response_function_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_response_function_ordering_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the response function ordering from "
                           "the HDF5 file for estimator " << estimator_id <<
                           "!" );
}

// Set the particle types assigned to the estimator
template<template<typename,typename...> class STLCompliantArray>
void EstimatorHDF5FileHandler::setParticleTypes(
                        const InternalEventObserverHandle estimator_id,
                        const STLCompliantArray<ParticleType>& particle_types )
{
  try{
    this->getHDF5File().writeArrayToGroupAttribute(
			       particle_types,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_particle_types_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the particle types for "
                           "estimator " << estimator_id << " in the HDF5 "
                           "file!" );
  }
}

// Get the particle types assigned to the estimator
template<template<typename,typename...> class STLCompliantArray>
void EstimatorHDF5FileHandler::getParticleTypes(
                        const InternalEventObserverHandle estimator_id,
                        STLCompliantArray<ParticleType>& particle_types ) const
{
  try{
    this->getHDF5File().readArrayFromGroupAttribute(
			       particle_types,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_particle_types_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the particle tpyes from the HDF5 "
                           "file for estimator " << estimator_id << "!" );
}

// Set the estimator dimension ordering
template<template<typename,typename...> class STLCompliantArray>
void EstimatorHDF5FileHandler::setEstimatorDimensionOrdering(
	     const InternalEventObserverHandle estimator_id,
	     const STLCompliantArray<PhaseSpaceDimension>& dimension_ordering )
{
  try{
    this->getHDF5File().writeArrayToGroupAttribute(
			       dimension_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_dimension_ordering_attr_name );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the dimension discretization "
                           "ordering for estimator " << estimator_id << " in"
                           "the HDF5 file!" );
}

// Get the estimator dimension ordering
template<template<typename,typename...> class STLCompliantArray>
void EstimatorHDF5FileHandler::getEstimatorDimensionOrdering(
	     const InternalEventObserverHandle estimator_id,
	     STLCompliantArray<PhaseSpaceDimension>& dimension_ordering ) const
{
  dimension_ordering.clear();

  // If an exception is thrown, there are no estimator dimensions
  try{
    if( this->getHDF5File().doesGroupAttributeExist(
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_dimension_ordering_attr_name ) )
    {
      this->getHDF5File().readArrayFromGroupAttribute(
			       dimension_ordering,
			       this->getEstimatorGroupLocation( estimator_id ),
			       s_dimension_ordering_attr_name );
    }
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the dimension ordering from the "
                           "HDF5 file for estimator " << estimator_id << "!" );
}

// Set the estimator dimension discretization
template<PhaseSpaceDimension dimension,
         template<typename,typename...> class STLCompliantArray>
void EstimatorHDF5FileHandler::setEstimatorDimensionDiscretization(
                                const InternalEventObserverHandle estimator_id,
                                const STLCompliantArray<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>& discretization )
{
  std::string discretization_set =
    this->getEstimatorGroupLocation( estimator_id );

  discretization_set +=
    ObserverPhaseSpaceDimensionTraits<dimension>::basicName();

  try{
    d_hdf5_file->writeArrayToDataSet( discretization, discretization_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the " << dimension <<
                           " discretization for estimator "
                           << estimator_id << " in the HDF5 file!" );
}

// Get the estimator dimension discretization
template<PhaseSpaceDimension dimension,
         template<typename,typename...> class STLCompliantArray>
void EstimatorHDF5FileHandler::getEstimatorDimensionDiscretization(
				const InternalEventObserverHandle estimator_id,
                                STLCompliantArray<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>& discretization ) const
{
  std::string discretization_set =
    this->getEstimatorGroupLocation( estimator_id );

  discretization_set +=
    ObserverPhaseSpaceDimensionTraits<dimension>::basicName();

  try{
    d_hdf5_file->readArrayFromDataSet( discretization, discretization_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the " << dimension <<
                           " discretization from the HDF5 file for estimator "
                           << estimator_id << "!" );
}

// Set the estimator entities and norm constants
template<typename EntityIdType,
           template<typename,typename...> class STLCompliantArray,
           template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::setEstimatorEntities(
	       const InternalEventObserverHandle estimator_id,
               const STLCompliantArray<STLCompliantPair<EntityIdType,double> >&
               entity_id_norms )
{
  std::string estimator_entities_data_set =
    this->getEstimatorGroupLocation( estimator_id );

  estimator_entities_data_set += s_entity_norm_constant_relative_loc;

  try{
    d_hdf5_file->writeArrayToDataSet( entity_id_norms,
				      estimator_entities_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the entity normalization "
                           "constants for estimator " << estimator_id <<
                           " in the HDF5 file!" );
}

// Set the estimator entities and norm constants
template<typename EntityIdType,
         template<typename,typename,typename...> class STLCompliantMap>
void EstimatorHDF5FileHandler::setEstimatorEntities(
                  const InternalEventObserverHandle estimator_id,
                  const STLCompliantMap<EntityIdType,double>& entity_id_norms )
{
  // Construct an array from the map
  std::vector<std::pair<EntityIdType,double> >
    entity_id_norms_copy( entity_id_norms.size() );

  typename EntityIdNormConstMap::const_iterator entity_data;
  size_t i;

  for( entity_data = entity_id_norms.begin(), i = 0;
       entity_data != entity_id_norms.end();
       ++entity_data, ++i )
  {
    entity_id_norms_copy[i].first = entity_data->first;
    entity_id_norms_copy[i].second = entity_data->second;
  }

  this->setEstimatorEntities( estimator_id, entity_id_norms_copy );
}

// Get the estimator entities and norm constants
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::getEstimatorEntities(
		     const InternalEventObserverHandle estimator_id,
                     STLCompliantArray<STLCompliantPair<EntityIdType,double> >&
                     entity_id_norms ) const
{
  std::string estimator_entities_data_set =
    this->getEstimatorGroupLocation( estimator_id );

  estimator_entities_data_set += s_entity_norm_constant_relative_loc;

  try{
    d_hdf5_file->readArrayFromDataSet( entity_id_norms,
				       estimator_entities_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the entity normalization "
                           "constants from the HDF5 file for estimator "
                           << estimator_id << "!" );
}

// Get the estimator entities and norm constants
template<typename EntityIdType,
         template<typename,typename,typename...> class STLCompliantMap>
void EstimatorHDF5FileHandler::getEstimatorEntities(
                  const InternalEventObserverHandle estimator_id,
		  STLCompliantMap<EntityIdType,double>& entity_id_norms ) const
{
  std::vector<std::pair<EntityIdType,double> > entity_id_norms_copy;

  this->getEstimatorEntities( estimator_id, entity_id_norms_copy );

  entity_id_norms.insert( entity_id_norms_copy.begin(),
                          entity_id_norms_copy.end() );
}

// Set the raw estimator bin data for an entity (1st, 2nd moments)
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::setRawEstimatorEntityBinData(
                     const InternalEventObserverHandle estimator_id,
                     const EntityIdType entity_id,
	             const STLCompliantArray<STLCompliantPair<double,double> >&
                     raw_bin_data )
{
  std::string bin_boundaries_data_set =
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  bin_boundaries_data_set += s_entity_raw_bin_data_relative_loc;

  try{
    d_hdf5_file->writeArrayToDataSet( raw_bin_data, bin_boundaries_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the raw entity "
                           << entity_id << " bin data for estimator "
                           << estimator_id << " in the HDF5 file!" );
}

// Get the raw estimator bin data for an entity (1st, 2nd moments)
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::getRawEstimatorEntityBinData(
	                   const InternalEventObserverHandle estimator_id,
                           const EntityIdType entity_id,
	                   STLCompliantArray<STLCompliantPair<double,double> >&
                           raw_bin_data ) const
{
  std::string bin_boundaries_data_set =
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  bin_boundaries_data_set += s_entity_raw_bin_data_relative_loc;

  try{
    d_hdf5_file->readArrayFromDataSet( raw_bin_data, bin_boundaries_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the raw entity "
                           << entity_id << " bin data from the HDF5 file for "
                           "estimator " << estimator_id << "!" );
}

// Set the processed estimator bin data for an entity (mean, relative error)
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::setProcessedEstimatorEntityBinData(
                     const InternalEventObserverHandle estimator_id,
                     const EntityIdType entity_id,
                     const STLCompliantArray<STLCompliantPair<double,double> >&
                     processed_bin_data )
{
  std::string bin_boundaries_data_set =
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  bin_boundaries_data_set += s_entity_processed_bin_data_relative_loc;

  try{
    d_hdf5_file->writeArrayToDataSet( processed_bin_data,
				      bin_boundaries_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the processed entity "
                           << entity_id << " bin data for estimator "
                           << estimator_id << " in the HDF5 file!" );
}

// Get the processed estimator bin data for an entity (mean, relative error)
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::getProcessedEstimatorEntityBinData(
                           const InternalEventObserverHandle estimator_id,
                           const EntityIdType entity_id,
                           STLCompliantArray<STLCompliantPair<double,double> >&
                           processed_bin_data ) const
{
  std::string bin_boundaries_data_set =
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  bin_boundaries_data_set += s_entity_processed_bin_data_relative_loc;

  try{
    d_hdf5_file->readArrayFromDataSet( processed_bin_data,
				       bin_boundaries_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the processed entity "
                           << entity_id << " bin data from the HDF5 file for "
                           "estimator " << estimator_id << "!" );
}

// Set the raw estimator total data for an entity
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename,typename,typename> class STLCompliantQuad>
void EstimatorHDF5FileHandler::setRawEstimatorEntityTotalData(
       const InternalEventObserverHandle estimator_id,
       const EntityIdType entity_id,
       const STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
       raw_total_data )
{
  std::string total_data_set =
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  total_data_set += s_entity_raw_total_data_relative_loc;

  try{
    d_hdf5_file->writeArrayToDataSet( raw_total_data, total_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the raw entity "
                           << entity_id << " total data for estimator "
                           << estimator_id << " in the HDF5 file!" );
}

// Get the raw estimator total data for an entity
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename,typename,typename> class STLCompliantQuad>
void EstimatorHDF5FileHandler::getRawEstimatorEntityTotalData(
	     const InternalEventObserverHandle estimator_id,
             const EntityIdType entity_id,
             STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
             raw_total_data ) const
{
  std::string total_data_set =
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  total_data_set += s_entity_raw_total_data_relative_loc;

  try{
    d_hdf5_file->readArrayFromDataSet( raw_total_data, total_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the raw entity "
                           << entity_id << " total data from the HDF5 file "
                           "for estimator " << estimator_id << "!" );
}

// Set the processed estimator total data for an entity
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename,typename,typename> class STLCompliantQuad>
void EstimatorHDF5FileHandler::setProcessedEstimatorEntityTotalData(
       const InternalEventObserverHandle estimator_id,
       const EntityIdType entity_id,
       const STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
       processed_total_data )
{
  std::string total_data_set =
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  total_data_set += s_entity_processed_total_data_relative_loc;

  try{
    d_hdf5_file->writeArrayToDataSet( processed_total_data, total_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the processed entity "
                           << entity_id << " total data for estimator "
                           << estimator_id << " in the HDF5 file!" );
}

// Get the processed estimator total data for an entity
template<typename EntityIdType,
         template<typename,typename...> class STLCompliantArray,
         template<typename,typename,typename,typename> class STLCompliantQuad>
void EstimatorHDF5FileHandler::getProcessedEstimatorEntityTotalData(
             const InternalEventObserverHandle estimator_id,
             const EntityIdType entity_id,
             STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
             processed_total_data ) const
{
  std::string total_data_set =
    this->getEstimatorEntityGroupLocation( estimator_id, entity_id );

  total_data_set += s_entity_processed_total_data_relative_loc;

  try{
    d_hdf5_file->readArrayFromDataSet( processed_total_data, total_data_set );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the processed entity "
                           << entity_id << " total data from the HDF5 file "
                           "for estimator " << estimator_id << "!" );
}

// Set the raw estimator bin data over all entities (1st, 2nd moments)
template<template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::setRawEstimatorTotalBinData(
      const InternalEventObserverHandle estimator_id,
      const STLCompliantArray<STLCompliantPair<double,double> >& raw_bin_data )
{
  // Make sure the bin data is valid
  testPrecondition( raw_bin_data.size() > 0 );

  std::string data_set_location =
    this->getEstimatorGroupLocation( estimator_id );

  data_set_location += s_raw_total_bin_data_relative_loc;

  try{
    this->getHDF5File().writeArrayToDataSet( raw_bin_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the raw total bin data for "
                           "estimator " << estimator_id << " in the HDF5 "
                           "file!" );
}

// Get the raw estimator bin data over all entities (1st, 2nd moments)
template<template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::getRawEstimatorTotalBinData(
                           const InternalEventObserverHandle estimator_id,
	                   STLCompliantArray<STLCompliantPair<double,double> >&
                           raw_bin_data ) const
{
  std::string data_set_location =
    this->getEstimatorGroupLocation( estimator_id );

  data_set_location += s_raw_total_bin_data_relative_loc;

  try{
    this->getHDF5File().readArrayFromDataSet(
                                             raw_bin_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the raw total bin data from the "
                           "HDF5 file for estimator " << estimator_id << "!" );
}

// Set the processed estimator bin data over all entities (mean, rel. err.)
template<template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::setProcessedEstimatorTotalBinData(
                     const InternalEventObserverHandle estimator_id,
                     const STLCompliantArray<STLCompliantPair<double,double> >&
                     processed_bin_data )
{
  // Make sure the total bin data is valid
  testPrecondition( processed_bin_data.size() > 0 );

  std::string data_set_location =
    this->getEstimatorGroupLocation( estimator_id );

  data_set_location += s_processed_total_bin_data_relative_loc;

  try{
    this->getHDF5File().writeArrayToDataSet(
                                       processed_bin_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the processed total bin data "
                           "for estimator " << estimator_id << " in the "
                           "HDF5 file!" );
}

// Get the processed estimator bin data over all entities (mean, rel. err.)
template<template<typename,typename...> class STLCompliantArray,
         template<typename,typename> class STLCompliantPair>
void EstimatorHDF5FileHandler::getProcessedEstimatorTotalBinData(
                           const InternalEventObserverHandle estimator_id,
                           STLCompliantArray<STLCompliantPair<double,double> >&
                           processed_bin_data ) const
{
  std::string data_set_location =
    this->getEstimatorGroupLocation( estimator_id );

  data_set_location += s_processed_total_bin_data_relative_loc;

  try{
    this->getHDF5File().readArrayFromDataSet(
                                       processed_bin_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the processed total bin data from "
                           "the HDF5 file for estimator " << estimator_id <<
                           "!" );
}

// Set the raw estimator total data over all entities
template<template<typename,typename...> class STLCompliantArray,
         template<typename,typename,typename,typename> class STLCompliantQuad>
void EstimatorHDF5FileHandler::setRawEstimatorTotalData(
       const InternalEventObserverHandle estimator_id,
       const STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
       raw_total_data )
{
  // Make sure the total bin data is valid
  testPrecondition( raw_total_data.size() > 0 );

  std::string data_set_location =
    this->getEstimatorGroupLocation( estimator_id );

  data_set_location += s_raw_total_data_relative_loc;

  try{
    this->getHDF5File().writeArrayToDataSet(
                                           raw_total_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the raw total data for "
                           "estimator " << estimator_id << " in the HDF5 "
                           "file!" );
}

// Get the raw estimator total data over all entities
template<template<typename,typename...> class STLCompliantArray,
         template<typename,typename,typename,typename> class STLCompliantQuad>
void EstimatorHDF5FileHandler::getRawEstimatorTotalData(
             const InternalEventObserverHandle estimator_id,
	     STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
             raw_total_data ) const
{
  std::string data_set_location =
    this->getEstimatorGroupLocation( estimator_id );

  data_set_location += s_raw_total_data_relative_loc;

  try{
    this->getHDF5File().readArrayFromDataSet(
                                           raw_total_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the raw total data from the HDF5 "
                           "file for estimator " << estimator_id << "!" );
}

// Set the processed estimator total data over all entities
template<template<typename,typename...> class STLCompliantArray,
         template<typename,typename,typename,typename> class STLCompliantQuad>
void EstimatorHDF5FileHandler::setProcessedEstimatorTotalData(
       const InternalEventObserverHandle estimator_id,
       const STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
       processed_total_data )
{
  // Make sure the total bin data is valid
  testPrecondition( processed_total_data.size() > 0 );

  std::string data_set_location =
    this->getEstimatorGroupLocation( estimator_id );

  data_set_location += s_processed_total_data_relative_loc;

  try{
    this->getHDF5File().writeArrayToDataSet(
                                      processed_total_data, data_set_location);
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to set the processed total data for "
                           "estimator " << estimator_id << " in the HDF5 "
                           "file!" );
}

// Get the processed estimator total data over all entities
template<template<typename,typename...> class STLCompliantArray,
         template<typename,typename,typename,typename> class STLCompliantQuad>
void EstimatorHDF5FileHandler::getProcessedEstimatorTotalData(
             const InternalEventObserverHandle estimator_id,
	     STLCompliantArray<STLCompliantQuad<double,double,double,double> >&
             processed_total_data ) const
{
  std::string data_set_location =
    this->getEstimatorGroupLocation( estimator_id );

  data_set_location += s_processed_total_data_relative_loc;

  try{
    this->getHDF5File().readArrayFromDataSet(
                                     processed_total_data, data_set_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Unable to get the processed total data from the "
                           "HDF5 file for estimator " << estimator_id << "!" );
}

// Get the estimator entity location
template<typename EntityIdType>
std::string EstimatorHDF5FileHandler::getEstimatorEntityGroupLocation(
				const InternalEventObserverHandle estimator_id,
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
