//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HashedGeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Hashed general estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HASHED_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_HASHED_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

//! The hashed general estimator dimension discretization class
template<PhaseSpaceDimension dimension>
class HashedGeneralEstimatorDimensionDiscretization : public GeneralEstimatorDimensionDiscretization<dimension>
{

public:
  
  //! Constructor
  HashedGeneralEstimatorDimensionDiscretization( 
			      const Teuchos::Array<typename DT::dimensionType>&
			      dimension_bin_boundaries,
			      const unsigned hash_grid_bins );

  //! Destructor
  ~HashedGeneralEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Calculate the index of the bin that the value falls in
  unsigned calculateBinIndex( const Teuchos::any& any_container ) const;

private:

  // The hash-based grid searcher
  boost::scoped_ptr<Utility::HashBasedGridSearcher> d_grid_searcher;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HASHED_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HashedGeneralEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
