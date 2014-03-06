//---------------------------------------------------------------------------//
//!
//! \file   CellEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell estimator base class definition.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_ESTIMATOR_DEF_HPP
#define CELL_ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

template<typename CellId>
CellEstimator<CellId>::CellEstimator( const unsigned long long id,
				      const CellId& cell_id,
				      const double norm_constant,
				      const double multiplier )
  : StandardEstimator<CellId>( id, cell_id, norm_constant, multiplier )
{ /* ... */ }

// Print the estimator data
template<typename CellId>
void CellEstimator<CellId>::print( std::ostream& os ) const
{
  os << "Estimator " << getId() << ": Cell " << getEntityId() << std::endl;
  
  os << Estimator::printImplementation( os );
}

} // end FACEMC namespace

#endif // end CELL_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end CellEstimator_def.hpp
//---------------------------------------------------------------------------//
