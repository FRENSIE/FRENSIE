//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace MonteCarlo{

// Constructor
template<PhaseSpaceDimension dimension>
GeneralEstimatorDimensionDiscretization<dimension>::GeneralEstimatorDimensionDiscretization( const Teuchos::Array<typename DT::dimensionType>& dimension_bin_boundaries )
  : StandardBasicEstimatorDimensionDiscretization<typename DT::dimensionType>( dimension, dimension_bin_boundaries )
{
  // Make sure the bins are valid
  testPrecondition( dimension_bin_boundaries.front() >= DT::lowerBound() );
  testPrecondition( dimension_bin_boundaries.back() <= DT::upperBound() );
}

// Return the dimension name that has been discretized
template<PhaseSpaceDimension dimension>
inline std::string GeneralEstimatorDimensionDiscretization<dimension>::getDimensionName() const
{
  return DT::name();
}

// Check if the value is contained in the dimension discretization
template<PhaseSpaceDimension dimension>
inline bool GeneralEstimatorDimensionDiscretization<dimension>::isValueInDiscretization( 
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{
  return isValueInDiscretization( 
                      getDimensionValue<dimension>( particle_state_wrapper ) );
}

// Check if the value is contained in the dimension discretization
template<PhaseSpaceDimension dimension>
inline bool GeneralEstimatorDimensionDiscretization<dimension>::isValueInDiscretization( 
                                          const Teuchos::any& any_value ) const
{
  return this->isValueInDiscretization( 
                                   getDimensionValue<dimension>( any_value ) );
}

// Calculate the index of the bin that the value falls in
template<PhaseSpaceDimension dimension>
unsigned GeneralEstimatorDimensionDiscretization<dimension>::calculateBinIndex(
            const EstimatorParticleStateWrapper& particle_state_wrapper ) const
{
  // Make sure the value is in the dimension discretization
  testPrecondition( this->isValueInDiscretization( particle_state_wrapper ) );
  
  return this->calculateBinIndex( 
                      getDimensionValue<dimension>( particle_state_wrapper ) );
}

// Calculate the index of the bin that the value falls in
template<PhaseSpaceDimension dimension>
unsigned GeneralEstimatorDimensionDiscretization<dimension>::calculateBinIndex(
                                          const Teuchos::any& any_value ) const
{
  // Make sure the value is in the dimension discretization
  testPrecondition( this->isValueInDiscretization( any_value ) );
  
  return this->calculateBinIndex( getDimensionValue<dimension>( any_value ) );
}

// Export the bin boundaries
template<PhaseSpaceDimension dimension>
void GeneralEstimatorDimensionDiscretization<dimension>::exportData( 
                                    const unsigned estimator_id,
                                    EstimatorHDF5FileHandler& hdf5_file ) const
{
  hdf5_file.setEstimatorBinBoundaries<dimension>( estimator_id, 
						  this->getBinBoundaries() );
}

} // end MonteCarlo namespace						     

#endif // end MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_GeneralEstimatorDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
