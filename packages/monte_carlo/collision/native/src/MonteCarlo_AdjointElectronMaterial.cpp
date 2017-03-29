//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronMaterial.cpp
//! \author Luke Kersting
//! \brief  AdjointElectron material class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectronMaterial::AdjointElectronMaterial(
               const ModuleTraits::InternalMaterialHandle id,
               const double density,
               const AdjointElectroatomNameMap& adjoint_electroatom_name_map,
               const Teuchos::Array<double>& adjoint_electroatom_fractions,
               const Teuchos::Array<std::string>& adjoint_electroatom_names )
  : d_id( id ),
    d_number_density( density ),
    d_atoms( adjoint_electroatom_fractions.size() )
{
  // Make sure the id is valid
  testPrecondition( id != ModuleTraits::invalid_internal_material_handle );
  // Make sure the density is valid
  testPrecondition( density != 0.0 );
  // Make sure the fraction values are valid (all positive or all negative)
  testPrecondition( areFractionValuesValid( adjoint_electroatom_fractions.begin(),
                                            adjoint_electroatom_fractions.end() ) );
  testPrecondition( adjoint_electroatom_fractions.size() ==
                    adjoint_electroatom_names.size() );

  // Copy the electroatoms that make up this material
  for( unsigned i = 0u; i < adjoint_electroatom_fractions.size(); ++i )
  {
    d_atoms[i].first = adjoint_electroatom_fractions[i];

    AdjointElectroatomNameMap::const_iterator atom =
      adjoint_electroatom_name_map.find( adjoint_electroatom_names[i] );

    TEST_FOR_EXCEPTION( atom == adjoint_electroatom_name_map.end(),
                        std::logic_error,
                        "Error: atom " << adjoint_electroatom_names[i] <<
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
                        &AdjointElectronMaterial::getAtomicWeight );
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
                      &AdjointElectronMaterial::getAtomicWeight );
  }

  // Convert the atom fractions to isotopic number densities
  scaleAtomFractionsByNumberDensity<Utility::FIRST>( d_number_density,
                                                     d_atoms.begin(),
                                                     d_atoms.end() );
}

// Return the material id
ModuleTraits::InternalMaterialHandle AdjointElectronMaterial::getId() const
{
  return d_id;
}

// Return the number density (atom/b-cm)
double AdjointElectronMaterial::getNumberDensity() const
{
  return d_number_density;
}

// Return the macroscopic total cross section (1/cm)
double AdjointElectronMaterial::getMacroscopicTotalCrossSection(
                            const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getTotalCrossSection( energy );
  }

  return cross_section;
}

// Return the macroscopic total forward cross section (1/cm)
double AdjointElectronMaterial::getMacroscopicTotalForwardCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( size_t i = 0; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getTotalForwardCrossSection( energy );
  }

  return cross_section;
}

// Return the macroscopic absorption cross section (1/cm)
double AdjointElectronMaterial::getMacroscopicAbsorptionCrossSection(
                            const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getAbsorptionCrossSection( energy );
  }

  return cross_section;
}

// Return the adjoint weight factor
double AdjointElectronMaterial::getAdjointWeightFactor(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;

  double macroscopic_total_forward_cross_section =
    this->getMacroscopicTotalForwardCrossSection( energy );

  if( macroscopic_total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getMacroscopicTotalCrossSection( energy )/
      this->getMacroscopicTotalForwardCrossSection( energy );
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPrecondition( weight_factor > 0.0 );

  return weight_factor;
}

// Return the survival probability
double AdjointElectronMaterial::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
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
  testPostcondition( !ST::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the macroscopic cross section (1/cm) for a specific reaction
double AdjointElectronMaterial::getMacroscopicReactionCrossSection(
                     const double energy,
                     const AdjointElectroatomicReactionType reaction ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section += d_atoms[i].first*
      d_atoms[i].second->getReactionCrossSection( energy, reaction );
  }

  return cross_section;
}


// Collide with a adjoint electron
void AdjointElectronMaterial::collideAnalogue(
    AdjointElectronState& adjoint_electron,
    ParticleBank& bank ) const
{
  unsigned atom_index = this->sampleCollisionAtom( adjoint_electron.getEnergy() );

  d_atoms[atom_index].second->collideAnalogue( adjoint_electron, bank );
}

// Collide with a adjoint electron and survival bias
void AdjointElectronMaterial::collideSurvivalBias(
    AdjointElectronState& adjoint_electron,
    ParticleBank& bank ) const
{
  unsigned atom_index = this->sampleCollisionAtom( adjoint_electron.getEnergy() );

  d_atoms[atom_index].second->collideSurvivalBias( adjoint_electron, bank );
}

// Get the atomic weight from an atom pointer
double AdjointElectronMaterial::getAtomicWeight(
         const Utility::Pair<double,Teuchos::RCP<const AdjointElectroatom> >& pair )
{
  return pair.second->getAtomicWeight();
}

// Sample the atom that is collided with
unsigned AdjointElectronMaterial::sampleCollisionAtom( const double energy ) const
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
// end MonteCarlo_AdjointElectronMaterial.cpp
//---------------------------------------------------------------------------//
