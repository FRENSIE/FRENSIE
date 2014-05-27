//---------------------------------------------------------------------------//
//!
//! \file   StandardCellEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard cell estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef STANDARD_CELL_ESTIMATOR_HPP
#define STANDARD_CELL_ESTIMATOR_HPP

// FACEMC Includes
#include "StandardEntityEstimator.hpp"
#include "ModuleTraits.hpp"

namespace FACEMC{

//! The standard cell estimator base class
class StandardCellEstimator : public StandardEntityEstimator<Traits::ModuleTraits::InternalCellHandle>
{
  
public:

  //! Typedef for the cell id type
  typedef Traits::ModuleTraits::InternalCellHandle cellIdType;

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

  //! Add estimator contribution from a portion of the current history
  virtual void addPartialHistoryContribution(
					   const ParticleState& particle,
					   const cellIdType cell_of_interest,
					   const double raw_contribution,
					   const double angle_cosine ) = 0;
};

} // end FACEMC namespace

#endif // end STANDARD_CELL_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end StandardCellEstimator.hpp
//---------------------------------------------------------------------------//
