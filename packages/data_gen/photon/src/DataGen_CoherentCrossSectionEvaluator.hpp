//---------------------------------------------------------------------------//
//!
//! \file   DataGen_CoherentCrossSectionEvaluator.hpp
//! \author Alex Robinson
//! \brief  Coherent cross section evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_COHERENT_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_COHERENT_CROSS_SECTION_EVALUATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace DataGen{

/*! The coherent cross section evaluator class
 * \details This class generates the coherent cross section using
 * Waller-Hartree theory.
 */
class CoherentCrossSectionEvaluator
{

public:

  //! Default constructor (free electron)
  CoherentCrossSectionEvaluator();

  //! Constructor (bound electron)
  CoherentCrossSectionEvaluator(
			   const Teuchos::RCP<const Utility::OneDDistribution>&
			   atomic_form_factor );

  //! Destructor
  ~CoherentCrossSectionEvaluator()
  { /* ... */ }

  //! Evaluate the differential coherent cross section (dc/dmu)
  double evaluateDifferentialCrossSection(
				  const double scattering_angle_cosine ) const;

  //! Evaluate the coherent cross section
  double evaluateCrossSection( const double energy,
			       const double precision = 1e-6 ) const;

private:

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_atomic_form_factor;
};

} // end DataGen namespace

#endif // end DATA_GEN_COHERENT_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_CoherentCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
