//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCellEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Standard cell estimator class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_CELL_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_STANDARD_CELL_ESTIMATOR_DEF_HPP

namespace MonteCarlo{

// Constructor
template<template<typename,typename...> class STLCompliantArrayA,
         template<typename,typename...> class STLCompliantArrayB>
StandardCellEstimator::StandardCellEstimator(
         const Estimator::idType id,
         const double multiplier,
	 const STLCompliantArrayA<StandardCellEstimator::cellIdType>& cell_ids,
         const STLCompliantArrayB<double>& cell_volumes )
  : StandardEntityEstimator<cellIdType>(id, multiplier, cell_ids, cell_volumes)
{ /* ... */ }
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_CELL_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCellEstimator_def.hpp
//---------------------------------------------------------------------------//
