//---------------------------------------------------------------------------//
//!
//! \file   Facemc_StandardCellEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard cell estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_CELL_ESTIMATOR_HPP
#define FACEMC_STANDARD_CELL_ESTIMATOR_HPP

// FRENSIE Includes
#include "Facemc_StandardEntityEstimator.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

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

private:

  // Assign bin boundaries to an estimator dimension
  void assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries );
};

} // end Facemc namespace

#endif // end FACEMC_STANDARD_CELL_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end Facemc_StandardCellEstimator.hpp
//---------------------------------------------------------------------------//
