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
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ContractException.hpp"
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
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( last_pos > prop_value.size(),
                      std::runtime_error,
                      "the estimator property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( first_pos == last_pos,
                      std::runtime_error,
                      "the estimator property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
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

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCModel_def.hpp
//---------------------------------------------------------------------------//