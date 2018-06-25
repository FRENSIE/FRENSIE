//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCellEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard cell estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_CELL_ESTIMATOR_HPP
#define MONTE_CARLO_STANDARD_CELL_ESTIMATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

//! The standard cell estimator base class
class StandardCellEstimator : public StandardEntityEstimator<Geometry::Model::InternalCellHandle>
{

private:

  // Typedef for the base estimator type
  typedef StandardEntityEstimator<Geometry::Model::InternalCellHandle>
  BaseEstimatorType;

public:

  //! Typedef for the cell id type
  typedef Geometry::Model::InternalCellHandle cellIdType;

  //! Constructor
  template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
  StandardCellEstimator( const Estimator::idType id,
			 const double multiplier,
			 const STLCompliantArrayA<cellIdType>& cell_ids,
			 const STLCompliantArrayB<double>& cell_volumes );

  //! Destructor
  virtual ~StandardCellEstimator()
  { /* ... */ }

protected:

  //! Assign discretization to an estimator dimension
  virtual void assignDiscretization(
              const Estimator::DimensionDiscretizationPointer& bins ) override;

  //! Assign the particle type to the estimator
  void assignParticleType( const ParticleType particle_type ) override;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardCellEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_CELL_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCellEstimator.hpp
//---------------------------------------------------------------------------//
