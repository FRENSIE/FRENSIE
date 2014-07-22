//---------------------------------------------------------------------------//
//!
//! \file   Facemc_StandardAceLaw44ARDistribution.hpp
//! \author Alex Robinson
//! \brief  The standard law 44 AR distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_HPP
#define FACEMC_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Facemc_AceLaw44ARDistribution.hpp"

namespace Facemc{

//! The standard law 44 AR distribution base class
template<typename AceLaw44InterpolationPolicy>
class StandardAceLaw44ARDistribution : public AceLaw44ARDistribution
{

public:

  //! Constructor
  StandardAceLaw44ARDistribution( 
		   const Teuchos::ArrayView<const double>& outgoing_energy_grid,
		   const Teuchos::ArrayView<const double>& A_array,
		   const Teuchos::ArrayView<const double>& R_array );

  //! Destructor
  ~StandardAceLaw44ARDistribution()
  { /* ... */ }

  //! Sample A and R from the distribution
  void sampleAR( const unsigned outgoing_index,
		 const double energy_prime,
		 double& sampled_A,
		 double& sampled_R ) const;
};

} // end Facemc namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Facemc_StandardAceLaw44ARDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_StandardAceLaw44ARDistribution.hpp
//---------------------------------------------------------------------------//
