//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardBasicEstimatorDimensionDiscretization.hpp"

namespace MonteCarlo{

/*! The general estimator dimension discretization class
 * \details If the dimension is not compatible with the continuous or 
 * discrete treatment provided by the 
 * StandardBasicEstimatorDimensionDiscretization class then a specialization of
 * this class should be made.
 */
template<PhaseSpaceDimension dimension>
class GeneralEstimatorDimensionDiscretization : public StandardBasicEstimatorDimensionDiscretization<typename PhaseSpaceDimensionTraits<dimension>::dimensionType>
{

private:

  // Estimator phase space dimension traits typedef
  typedef PhaseSpaceDimensionTraits<dimension> DT;

public:

  //! Constructor
  GeneralEstimatorDimensionDiscretization( 
                              const Teuchos::Array<typename DT::dimensionType>&
			      dimension_bin_boundaries );

  //! Destructor
  virtual ~GeneralEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the dimension name that has been discretized
  std::string getDimensionName() const;

  //! Check if the value is contained in the dimension discretization
  bool isValueInDiscretization( 
           const EstimatorParticleStateWrapper& particle_state_wrapper ) const;

  //! Check if the value is contained in the dimension discretization
  bool isValueInDiscretization( const Teuchos::any& any_value ) const;

  //! Calculate the index of the bin that the value falls in
  unsigned calculateBinIndex( 
           const EstimatorParticleStateWrapper& particle_state_wrapper ) const;

  //! Calculate the index of the bin that the value falls in
  unsigned calculateBinIndex( const Teuchos::any& any_value ) const;

  //! Export the bin boundaries
  void exportData( const unsigned estimator_id,
                   EstimatorHDF5FileHandler& hdf5_file ) const;

private:

  using StandardBasicEstimatorDimensionDiscretization<typename DT::dimensionType>::isValueInDiscretization;
  using StandardBasicEstimatorDimensionDiscretization<typename DT::dimensionType>::calculateBinIndex;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_GeneralEstimatorDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
