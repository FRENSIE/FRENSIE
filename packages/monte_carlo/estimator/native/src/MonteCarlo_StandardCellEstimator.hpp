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
  
public:

  //! Typedef for the cell id type
  typedef Geometry::ModuleTraits::InternalCellHandle cellIdType;

  //! Constructor
  StandardCellEstimator( const Estimator::idType id,
			 const double multiplier,
			 const Teuchos::Array<cellIdType>& cell_ids,
			 const Teuchos::Array<double>& cell_volumes );

  //! Destructor
  virtual ~StandardCellEstimator()
  { /* ... */ }

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Export the estimator data
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
		   const bool process_data ) const;

protected:

  //! Assign bin boundaries to an estimator dimension
  virtual void assignBinBoundaries(
     const std::shared_ptr<EstimatorDimensionDiscretization>& bin_boundaries );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_CELL_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCellEstimator.hpp
//---------------------------------------------------------------------------//
