//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronMaterial.cpp
//! \author Luke Kersting
//! \brief  Positron material class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_PositronMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PositronMaterial::PositronMaterial(
               const ModuleTraits::InternalMaterialHandle id,
               const double density,
               const PositronatomNameMap& positronatom_name_map,
               const std::vector<double>& positronatom_fractions,
               const std::vector<std::string>& positronatom_names )
  : d_id( id ),
    d_number_density( density ),
    d_atoms( positronatom_fractions.size() )
{
  // Make sure the id is valid
  testPrecondition( id != ModuleTraits::invalid_internal_material_handle );
  // Make sure the density is valid
  testPrecondition( density != 0.0 );
  // Make sure the fraction values are valid (all positive or all negative)
  testPrecondition( areFractionValuesValid( positronatom_fractions.begin(),
                                            positronatom_fractions.end() ) );
  testPrecondition( positronatom_fractions.size() == positronatom_names.size() );

  // Copy the positron-atoms that make up this material
  for( unsigned i = 0u; i < positronatom_fractions.size(); ++i )
  {
    d_atoms[i].first = positronatom_fractions[i];

    PositronatomNameMap::const_iterator atom =
      positronatom_name_map.find( positronatom_names[i] );

    TEST_FOR_EXCEPTION( atom == positronatom_name_map.end(),
                        std::logic_error,
                        "atom " << positronatom_names[i] <<
                        " has not been loaded!" );

    d_atoms[i].second = atom->second;
  }

  // Convert weight fractions to atom fractions
  if( d_atoms.front().first < 0.0 )
  {
    convertWeightFractionsToAtomFractions<Utility::FIRST,Utility::SECOND>(
                        d_atoms.begin(),
                        d_atoms.end(),
                        d_atoms.begin(),
                        d_atoms.end(),
                        &PositronMaterial::getAtomicWeight );
  }
  else // Normalize the atom fractions
  {
    normalizeFractionValues<Utility::FIRST>( d_atoms.begin(), d_atoms.end() );
  }

  // Convert the mass density to a number density
  if( density < 0.0 )
  {
    d_number_density =
      convertMassDensityToNumberDensity<Utility::FIRST,Utility::SECOND>(
                      -1.0*density,
                      d_atoms.begin(),
                      d_atoms.end(),
                      d_atoms.begin(),
                      d_atoms.end(),
                      &PositronMaterial::getAtomicWeight );
  }

  // Convert the atom fractions to isotopic number densities
  scaleAtomFractionsByNumberDensity<Utility::FIRST>( d_number_density,
                                                     d_atoms.begin(),
                                                     d_atoms.end() );
}

// Return the material id
ModuleTraits::InternalMaterialHandle PositronMaterial::getId() const
{
  return d_id;
}

// Return the number density (atom/b-cm)
double PositronMaterial::getNumberDensity() const
{
  return d_number_density;
}

// Return the macroscopic total cross section (1/cm)
double PositronMaterial::getMacroscopicTotalCrossSection(
                            const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getTotalCrossSection( energy );
  }

  return cross_section;
}

// Return the macroscopic absorption cross section (1/cm)
double PositronMaterial::getMacroscopicAbsorptionCrossSection(
                            const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getAbsorptionCrossSection( energy );
  }

  return cross_section;
}

// Return the survival probability
double PositronMaterial::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;
  double total_cross_sec = this->getMacroscopicTotalCrossSection( energy );

  if( total_cross_sec > 0.0 )
  {
    survival_prob = 1.0 -
      this->getMacroscopicAbsorptionCrossSection( energy )/total_cross_sec;
  }
  else
    survival_prob = 1.0;

  // Make sure the survival probability is valid
  testPostcondition( !QT::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the macroscopic cross section (1/cm) for a specific reaction
double PositronMaterial::getMacroscopicReactionCrossSection(
                     const double energy,
                     const PositronatomicReactionType reaction ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section += d_atoms[i].first*
      d_atoms[i].second->getReactionCrossSection( energy, reaction );
  }

  return cross_section;
}


// Collide with a positron
void PositronMaterial::collideAnalogue( PositronState& positron,
                                        ParticleBank& bank ) const
{
  unsigned atom_index = sampleCollisionAtom( positron.getEnergy() );

  d_atoms[atom_index].second->collideAnalogue( positron, bank );
}

// Collide with a positron and survival bias
/*! \details The method of survival biasing that has been implemented is to
 * first select the nuclide that is collided with. The particle weight is
 * then multiplied by the survival probability associated with the
 * microscopic cross sections for the collision nuclide. An alternative method
 * would be to multiply the weight of the particle by the macroscopic
 * survival probability associated with the material and then sample a
 * collision nuclide. The latter method appears to be more involved than the
 * former, which is why the former was chosen.
 */
void PositronMaterial::collideSurvivalBias( PositronState& positron,
                                            ParticleBank& bank ) const
{
  unsigned atom_index = sampleCollisionAtom( positron.getEnergy() );

  d_atoms[atom_index].second->collideSurvivalBias( positron, bank );
}

// Get the atomic weight from an atom pointer
double PositronMaterial::getAtomicWeight(
       const Utility::Pair<double,std::shared_ptr<const Positronatom> >& pair )
{
  return pair.second->getAtomicWeight();
}

// Sample the atom that is collided with
unsigned PositronMaterial::sampleCollisionAtom( const double energy ) const
{
  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    this->getMacroscopicTotalCrossSection( energy );

  double partial_total_cs = 0.0;

  unsigned collision_atom_index = std::numeric_limits<unsigned>::max();

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    partial_total_cs +=
      d_atoms[i].first*d_atoms[i].second->getTotalCrossSection( energy );

    if( scaled_random_number < partial_total_cs )
    {
      collision_atom_index = i;

      break;
    }
  }

  // Make sure a collision index was found
  testPostcondition( collision_atom_index !=
             std::numeric_limits<unsigned>::max() );

  return collision_atom_index;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronMaterial.cpp
//---------------------------------------------------------------------------//
