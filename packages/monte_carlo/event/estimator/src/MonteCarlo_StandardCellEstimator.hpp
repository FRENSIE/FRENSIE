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
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The standard cell estimator base class
class StandardCellEstimator : public StandardEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>
{

private:

  // Typedef for the base estimator type
  typedef StandardEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>
  BaseEstimatorType;

public:

  //! Typedef for the cell id type
  typedef Geometry::ModuleTraits::InternalCellHandle cellIdType;

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

  //! Export the estimator data
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
		   const bool process_data ) const override;

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
