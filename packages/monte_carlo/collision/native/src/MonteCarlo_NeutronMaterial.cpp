//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronMaterial.cpp
//! \author Alex Robinson
//! \brief  Neutron material class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
NeutronMaterial::NeutronMaterial(
	        const ModuleTraits::InternalMaterialHandle id,
	        const double density,
	        const std::unordered_map<std::string,Teuchos::RCP<Nuclide> >&
	        nuclide_name_map,
	        const Teuchos::Array<double>& nuclide_fractions,
	        const Teuchos::Array<std::string>& nuclide_names )
  : d_id( id ),
    d_number_density( density ),
    d_nuclides( nuclide_fractions.size() )
{
  // Make sure the fraction values are valid (all positive or all negative)
  testPrecondition( areFractionValuesValid( nuclide_fractions.begin(),
					    nuclide_fractions.end() ) );
  testPrecondition( nuclide_fractions.size() == nuclide_names.size() );
		    
  // Copy the nuclides that make up this material
  for( unsigned i = 0u; i < nuclide_fractions.size(); ++i )
  {
    d_nuclides[i].first = nuclide_fractions[i];
    
    d_nuclides[i].second = nuclide_name_map.find( nuclide_names[i] )->second;
  }

  // Convert weight fractions to atom fractions
  if( d_nuclides.front().first < 0.0 )
  {
    convertWeightFractionsToAtomFractions<Utility::FIRST,Utility::SECOND>( 
					     d_nuclides.begin(),
					     d_nuclides.end(),
					     d_nuclides.begin(),
					     d_nuclides.end(),
					     &NeutronMaterial::getNuclideAWR );
  }
  else // Normalize the atom fractions
  {
    normalizeFractionValues<Utility::FIRST>( d_nuclides.begin(), d_nuclides.end() );
  }
    
  // Convert the mass density to a number density
  if( density < 0.0 )
  {
    d_number_density = 
      convertMassDensityToNumberDensity<Utility::FIRST,Utility::SECOND>(
					     -1.0*density,
					     d_nuclides.begin(),
					     d_nuclides.end(),
					     d_nuclides.begin(),
					     d_nuclides.end(),
					     &NeutronMaterial::getNuclideAWR );
    
    // Atomic weight ratios were used to do the conversion - divide by the
    // neutron amu to get the correct number density
    d_number_density /= Utility::PhysicalConstants::neutron_rest_mass_amu;
  }

  // Convert the atom fractions to isotopic number densities
  scaleAtomFractionsByNumberDensity<Utility::FIRST>( d_number_density,
						     d_nuclides.begin(),
						     d_nuclides.end() );
}

// Return the material id
ModuleTraits::InternalMaterialHandle NeutronMaterial::getId() const
{
  return d_id;
}

// Return the material number density (atom/b-cm)
double NeutronMaterial::getNumberDensity() const
{
  return d_number_density;
}

// Return the macroscopic total crosss section (1/cm)
double NeutronMaterial::getMacroscopicTotalCrossSection( 
						    const double energy ) const
{
  double cross_section = 0.0;
  
  for( unsigned i = 0u; i < d_nuclides.size(); ++i )
  {
    cross_section += 
      d_nuclides[i].first*d_nuclides[i].second->getTotalCrossSection( energy );
  }

  return cross_section;
}

// Return the macroscopic absorption cross section (1/cm)
double NeutronMaterial::getMacroscopicAbsorptionCrossSection( 
						    const double energy ) const
{
  double cross_section = 0.0;
  
  for( unsigned i = 0u; i < d_nuclides.size(); ++i )
  {
    cross_section += d_nuclides[i].first*
      d_nuclides[i].second->getAbsorptionCrossSection( energy );
  }

  return cross_section;
}

// Return the survival probability
double NeutronMaterial::getSurvivalProbability( const double energy ) const
{
  double total_cross_sec = this->getMacroscopicTotalCrossSection( energy );

  double absorption_cross_sec = 
    this->getMacroscopicAbsorptionCrossSection( energy );

  return 1.0 - absorption_cross_sec/total_cross_sec;
}

// Return the macroscopic cross section (1/cm)
double NeutronMaterial::getMacroscopicReactionCrossSection( 
				     const double energy,
				     const NuclearReactionType reaction ) const
{
  double cross_section = 0.0;
  
  for( unsigned i = 0u; i < d_nuclides.size(); ++i )
  {
    cross_section += d_nuclides[i].first*
      d_nuclides[i].second->getReactionCrossSection( energy, reaction );
  }

  return cross_section;
}

// Collide with a neutron
void NeutronMaterial::collideAnalogue( NeutronState& neutron, 
				       ParticleBank& bank ) const
{
  unsigned nuclide_index = sampleCollisionNuclide( neutron.getEnergy() );

  d_nuclides[nuclide_index].second->collideAnalogue( neutron, bank );
}

// Collide with a neutron and survival bias
/*! \details The method of survival biasing that has been implemented is to
 * first select the nuclide that is collided with. The particle weight is
 * then multiplied by the survival probability associated with the 
 * microscopic cross sections for the collision nuclide. An alternative method
 * would be to multiply the weight of the particle by the macroscopic
 * survival probability associated with the material and then sample a 
 * collision nuclide. The latter method appears to be more involved than the
 * former, which is why the former was chosen.
 */
void NeutronMaterial::collideSurvivalBias( NeutronState& neutron, 
					   ParticleBank& bank ) const
{
  unsigned nuclide_index = sampleCollisionNuclide( neutron.getEnergy() );

  d_nuclides[nuclide_index].second->collideSurvivalBias( neutron, bank );
}

// Sample the nuclide that is collided with
unsigned NeutronMaterial::sampleCollisionNuclide( const double energy ) const
{
  double scaled_random_number = 
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    this->getMacroscopicTotalCrossSection( energy );

  double partial_total_cs = 0.0;

  unsigned collision_nuclide_index = std::numeric_limits<unsigned>::max();
  
  for( unsigned i = 0u; i < d_nuclides.size(); ++i )
  {
    partial_total_cs += 
      d_nuclides[i].first*d_nuclides[i].second->getTotalCrossSection( energy );
    
    if( scaled_random_number < partial_total_cs )
    {
      collision_nuclide_index = i;

      break;
    }
  }

  // Make sure a collision index was found
  testPostcondition( collision_nuclide_index != 
		     std::numeric_limits<unsigned>::max() );
  
  return collision_nuclide_index;
}

// Get the atomic weight ratio from a nuclide pointer
double NeutronMaterial::getNuclideAWR( 
		     const Utility::Pair<double,Teuchos::RCP<Nuclide> >& pair )
{
  return pair.second->getAtomicWeightRatio();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronMaterial.cpp
//---------------------------------------------------------------------------//
