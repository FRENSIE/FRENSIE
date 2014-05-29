//---------------------------------------------------------------------------//
//!
//! \file   Facemc_GeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define FACEMC_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_EstimatorDimensionDiscretization.hpp"
#include "Facemc_PhaseSpaceDimensionTraits.hpp"

namespace Facemc{

//! The general estimator dimension discretization class
template<PhaseSpaceDimension dimension>
class GeneralEstimatorDimensionDiscretization : public EstimatorDimensionDiscretization
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
  ~GeneralEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the dimension name that has been discretized
  std::string getDimensionName() const;

  //! Return the number of bins in the discretization
  unsigned getNumberOfBins() const;

  //! Check if the value is contained in the dimension discretization
  bool isValueInDiscretization( const Teuchos::any& any_container ) const;

  //! Calculate the index of the bin that the value falls in
  unsigned calculateBinIndex( const Teuchos::any& any_container ) const;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os, const unsigned bin_index) const;

  //! Print the dimension discretization
  void print( std::ostream& os ) const;

private:

  // The dimension bin boundaries
  Teuchos::Array<typename DT::dimensionType> d_dimension_bin_boundaries;
};

/*! The general estimator dimension discretization class specialized for
 * the collision number bin dimension
 */
template<>
class GeneralEstimatorDimensionDiscretization<COLLISION_NUMBER_DIMENSION> : public EstimatorDimensionDiscretization
{

private:

  // Estimator phase space dimension traits typedef
  typedef PhaseSpaceDimensionTraits<COLLISION_NUMBER_DIMENSION> DT;

public:

  //! Constructor
  GeneralEstimatorDimensionDiscretization( 
                              const Teuchos::Array<typename DT::dimensionType>&
			      dimension_bin_boundaries );

  //! Destructor
  ~GeneralEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the dimension name that has been discretized
  std::string getDimensionName() const;

  //! Return the number of bins in the discretization
  unsigned getNumberOfBins() const;

  //! Check if the value is contained in the dimension discretization
  bool isValueInDiscretization( const Teuchos::any& any_container ) const;

  //! Calculate the index of the bin that the value falls in
  unsigned calculateBinIndex( const Teuchos::any& any_container ) const;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os, const unsigned bin_index) const;

  //! Print the dimension discretization
  void print( std::ostream& os ) const;

private:

  // The dimension bin boundaries
  Teuchos::Array<typename DT::dimensionType> d_dimension_bin_boundaries;
};

} // end Facemc namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Facemc_GeneralEstimatorDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end Facemc_GeneralEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
