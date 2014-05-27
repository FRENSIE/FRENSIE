//---------------------------------------------------------------------------//
//!
//! \file   GeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "EstimatorDimensionDiscretization.hpp"
#include "PhaseSpaceDimensionTraits.hpp"

namespace FACEMC{

//! The general estimator dimension discretization class
template<PhaseSpaceDimension dimension>
class GeneralEstimatorDimensionDiscretization : public EstimatorDimensionDiscretization
{

private:

  // Estimator phase space dimension traits typedef
  typedef Traits::PhaseSpaceDimensionTraits<dimension> DT;

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
  typedef Traits::PhaseSpaceDimensionTraits<COLLISION_NUMBER_DIMENSION> DT;

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

} // FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "GeneralEstimatorDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end GeneralEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
