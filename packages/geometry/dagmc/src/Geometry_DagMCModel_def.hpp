//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCModel_def.hpp
//! \author Alex Robinson
//! \brief  DagMC model class template and inline definitions
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_MODEL_DEF_HPP
#define GEOMETRY_DAGMC_MODEL_DEF_HPP

// Std Lib Includes
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "Utility_JustInTimeInitializer.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Extract estimator property values
// An estimator property is assumed to have the form id.type.ptype
template<typename IntType>
void DagMCModel::extractEstimatorPropertyValues(
                                            const std::string& prop_value,
                                            IntType& estimator_id,
                                            EstimatorType& estimator_type,
                                            ParticleType& particle_type ) const
{
  size_t first_pos = prop_value.find_first_of( "." );
  size_t last_pos = prop_value.find_last_of( "." );

  // Make sure the estimator property format is valid
  TEST_FOR_EXCEPTION( first_pos > prop_value.size(),
                      std::runtime_error,
                      "the estimator property " << prop_value <<
                      " found in the .h5m file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( last_pos > prop_value.size(),
                      std::runtime_error,
                      "the estimator property " << prop_value <<
                      " found in the .h5m file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( first_pos == last_pos,
                      std::runtime_error,
                      "the estimator property " << prop_value <<
                      " found in the .h5m file is invalid (the form needs to "
                      "be id.type.ptype)!" );

  std::string id_string = prop_value.substr( 0, first_pos );

  std::istringstream iss( id_string );

  iss >> estimator_id;

  std::string estimator_name =
    prop_value.substr( first_pos+1, last_pos-first_pos-1 );

  // Make sure the estimator type is valid
  TEST_FOR_EXCEPTION(
                   !d_model_properties->isEstimatorNameValid( estimator_name ),
                   InvalidDagMCGeometry,
                   "estimator " << estimator_id <<
                   " has an invalid estimator type ("
                   << estimator_type << ") specified!" );

  estimator_type = d_model_properties->getEstimatorType( estimator_name );

  std::string particle_name =
    prop_value.substr( last_pos+1, prop_value.size()-last_pos-1);

  // Make sure the particle type is valid
  TEST_FOR_EXCEPTION(
                     !d_model_properties->isParticleNameValid( particle_name ),
                     InvalidDagMCGeometry,
                     "estimator " << estimator_id <<
                     " has an invalid particle type (" << particle_type <<
                     ") specified!" );

  particle_type = d_model_properties->getParticleType( particle_name );
}

// Save the model to an archive
template<typename Archive>
void DagMCModel::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( AdvancedModel );

  // Save the model properties - all other data will be reinitialized
  ar & BOOST_SERIALIZATION_NVP( d_model_properties );
}

// Load the model from an archive
template<typename Archive>
void DagMCModel::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( AdvancedModel );

  // Load the model properties only - all other data must be reinitialized
  ar & BOOST_SERIALIZATION_NVP( d_model_properties );

  Utility::JustInTimeInitializer::getInstance().addObject( *this );
}

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCModel_def.hpp
//---------------------------------------------------------------------------//
