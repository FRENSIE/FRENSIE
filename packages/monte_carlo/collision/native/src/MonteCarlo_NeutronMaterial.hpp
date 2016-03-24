//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronMaterial.hpp
//! \author Alex Robinson
//! \brief  Neutron material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_MATERIAL_HPP
#define MONTE_CARLO_NEUTRON_MATERIAL_HPP

// Std Lib Includes
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_Nuclide.hpp"
#include "MonteCarlo_SAlphaBeta.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The neutron material class
class NeutronMaterial
{

public:

  //! Constructor
  NeutronMaterial( 
		const ModuleTraits::InternalMaterialHandle id,
		const double density,
		const std::unordered_map<std::string,Teuchos::RCP<Nuclide> >&
		nuclide_name_map,
		const Teuchos::Array<double>& nuclide_fractions,
		const Teuchos::Array<std::string>& nuclide_names );

  //! Destructor
  ~NeutronMaterial()
  { /* ... */ }

  //! Return the material id
  ModuleTraits::InternalMaterialHandle getId() const;
  
  //! Return the material number density (atom/b-cm)
  double getNumberDensity() const;

  //! Return the macroscopic total cross section (1/cm)
  double getMacroscopicTotalCrossSection( const double energy ) const;

  //! Return the macroscopic absorption cross section (1/cm)
  double getMacroscopicAbsorptionCrossSection( const double energy ) const;

  //! Return the survival probability
  double getSurvivalProbability( const double energy ) const;

  //! Return the macroscopic cross section (1/cm) for a specific reaction
  double getMacroscopicReactionCrossSection( 
				     const double energy,
				     const NuclearReactionType reaction) const;

  //! Collide with a neutron
  void collideAnalogue( NeutronState& neutron, ParticleBank& bank ) const;

  //! Collide with a neutron and survival bias
  void collideSurvivalBias( NeutronState& neutron, ParticleBank& bank ) const;

private:

  // Get the atomic weight ratio from a nuclide pointer
  static double getNuclideAWR( 
		    const Utility::Pair<double,Teuchos::RCP<Nuclide> >& pair );

  // Sample the nuclide that is collided with
  unsigned sampleCollisionNuclide( const double energy ) const;

  // The material id
  ModuleTraits::InternalMaterialHandle d_id;

  // The number density of the material
  double d_number_density;

  // The nuclides that make up the material 
  // (FIRST = nuclide_number_density, SECOND = nuclide pointer)
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Nuclide> > > d_nuclides;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronMaterial.hpp
//---------------------------------------------------------------------------//
