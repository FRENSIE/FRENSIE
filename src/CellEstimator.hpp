//---------------------------------------------------------------------------//
//!
//! \file   CellEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell estimator base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_ESTIMATOR_HPP
#define CELL_ESTIMATOR_HPP

// FACEMC Includes
#include "StandardEstimator.hpp"

namespace FACEMC{

//! The cell estimator base class
template<typename CellId>
class CellEstimator : public StandardEstimator<CellId>
{

public:

  //! Constructor
  CellEstimator( const unsigned long long id,
		 const CellId& cell_id,
		 const double norm_constant,
		 const double multiplier = 1.0 );

  //! Destructor
  virtual ~CellEstimator()
  { /* ... */ }

  //! Calculate and add estimator contribution from a portion of the cur. hist.
  virtual void calculateAndAddPartialHistoryContribution( 
					   const BasicParticleState& particle,
					   const double raw_contribution ) = 0;

  //! Print the estimator data
  virtual print( std::ostream& os ) const;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "CellEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end CELL_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end CellEstimator.hpp
//---------------------------------------------------------------------------//
