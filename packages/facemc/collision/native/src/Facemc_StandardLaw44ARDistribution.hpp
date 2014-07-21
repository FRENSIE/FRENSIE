//---------------------------------------------------------------------------//
//!
//! \file   Facemc_StandardLaw44ARDistribution.hpp
//! \author Alex Robinson
//! \brief  The standard law 44 AR distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_LAW_44_AR_DISTRIBUTION_HPP
#define FACEMC_STANDARD_LAW_44_AR_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Facemc_Law44ARDistribution.hpp"

namespace Facemc{

//! The standard law 44 AR distribution base class
template<typename Law44InterpolationPolicy>
class StandardLaw44ARDistribution : Law44ARDistribution
{

public:

  //! Constructor
  StandardLaw44ARDistribution( 
		   const Teuchos::ArrayRCP<const double>& outgoing_energy_grid,
		   const Teuchos::ArrayView<const double>& A_array,
		   const Teuchos::ArrayView<const double>& R_array );

  //! Destructor
  ~StandardLaw44ARDistribution()
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

#include "Facemc_StandardLaw44ARDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_STANDARD_LAW_44_AR_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_StandardLaw44ARDistribution.hpp
//---------------------------------------------------------------------------//
