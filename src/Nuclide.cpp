//---------------------------------------------------------------------------//
//!
//! \file   Nuclide.cpp
//! \author Alex Robinson
//! \brief  The nuclide class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FACEMC Includes
#include "Nuclide.hpp"
#include "NuclearReactionFactory.hpp"
#include "RandomNumberGenerator.hpp"
#include "SearchAlgorithms.hpp"
#include "InterpolationPolicy.hpp"
#include "ExceptionTestMacros.hpp"

namespace FACEMC{

// Constructor
Nuclide::Nuclide( const std::string& name,
		  const unsigned atomic_number,
		  const unsigned atomic_mass_number,
		  const unsigned isomer_number,
		  const double atomic_weight_ratio,
		  const double temperature,
		  const XSSNeutronDataExtractor& raw_nuclide_data )
  : d_name( name ),
    d_atomic_number( atomic_number ),
    d_atomic_mass_number( atomic_mass_number ),
    d_isomer_number( isomer_number ),
    d_atomic_weight_ratio( atomic_weight_ratio ),
    d_temperature( temperature ),
    d_energy_grid(),
    d_total_cross_section( raw_nuclide_data.extractTotalCrossSection() ),
    d_absorption_cross_section( 
		       raw_nuclide_data.extractTotalAbsorptionCrossSection() )
{
  // Create a deep copy of the energy grid
  d_energy_grid.deepCopy( raw_nuclide_data.extractEnergyGrid() );

  // Create the nuclear reaction factory
  NuclearReactionFactory reaction_factory( 
				 d_name,
				 d_atomic_weight_ratio,
				 d_temperature,
				 d_energy_grid.getConst(),
				 raw_nuclide_data.extractElasticCrossSection(),
				 raw_nuclide_data.extractMTRBlock(),
				 raw_nuclide_data.extractLQRBlock(),
				 raw_nuclide_data.extractTYRBlock(),
				 raw_nuclide_data.extractLSIGBlock(),
				 raw_nuclide_data.extractSIGBlock(),
				 raw_nuclide_data.extractLANDBlock(),
				 raw_nuclide_data.extractANDBlock(),
				 raw_nuclide_data.extractLDLWBlock(),
				 raw_nuclide_data.extractDLWBlock() );

  // Create the elastic reaction
  Teuchos::RCP<NuclearReaction> elastic_reaction;
  reaction_factory.createElasticReaction( elastic_reaction );

  d_nuclear_reactions[N__N_ELASTIC_REACTION] = elastic_reaction;

  // Create all of the non-elastic reactions
  Teuchos::Array<Teuchos::RCP<NuclearReaction> > other_reactions;
  reaction_factory.createNonElasticReactions( other_reactions );

  for( unsigned i = 0; i < other_reactions.size(); ++i )
  {
    d_nuclear_reactions[other_reactions[i]->getReactionType()] = 
      other_reactions[i];
  }

  // Calculate the total absorption cross section
  
  // Calculate the total cross section
}

// Return the nuclide name
const std::string& Nuclide::getName() const
{
  return d_name;
}

// Return the atomic number of the nuclide
unsigned Nuclide::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic mass number of the nuclide
unsigned Nuclide::getAtomicMassNumber() const
{
  return d_atomic_mass_number;
}

// Return the nuclear isomer number of the nuclide
unsigned Nuclide::getIsomerNumber() const
{
  return d_isomer_number;
}
  
// Return the atomic weight ratio
double Nuclide::getAtomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Return the temperature of the nuclide (in MeV)
double Nuclide::getTemperature() const
{
  return d_temperature;
}
  
// Return the total cross section at the desired energy
double Nuclide::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  if( energy < d_energy_grid[d_energy_grid.size()-1] )
  {
    Teuchos::ArrayRCP<const double>::const_iterator lower_energy_grid_pt,
      upper_energy_grid_pt;

    lower_energy_grid_pt = d_energy_grid.begin();
    upper_energy_grid_pt = d_energy_grid.end();

    lower_energy_grid_pt = 
      Search::binarySearchContinuousData( lower_energy_grid_pt, 
					  upper_energy_grid_pt,
					  energy );
    
    upper_energy_grid_pt = lower_energy_grid_pt;
    ++upper_energy_grid_pt;

    unsigned cs_index = 
      std::distance( d_energy_grid.getConst().begin(), lower_energy_grid_pt );

    return LinLin::interpolate( *lower_energy_grid_pt,
				*upper_energy_grid_pt,
				energy,
				d_total_cross_section[cs_index],
				d_total_cross_section[cs_index+1] );
  }
  else if( energy == d_energy_grid[d_energy_grid.size()-1] )
    return d_total_cross_section.back();
  else // energy > d_energy_grid[d_energy_grid.size()-1]
    return 0.0;
}

// Return the total absorption cross section at the desired energy
double Nuclide::getAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  if( energy < d_energy_grid[d_energy_grid.size()-1] )
  {
    Teuchos::ArrayRCP<const double>::const_iterator lower_energy_grid_pt,
      upper_energy_grid_pt;

    lower_energy_grid_pt = d_energy_grid.begin();
    upper_energy_grid_pt = d_energy_grid.end();

    lower_energy_grid_pt = 
      Search::binarySearchContinuousData( lower_energy_grid_pt, 
					  upper_energy_grid_pt,
					  energy );
    
    upper_energy_grid_pt = lower_energy_grid_pt;
    ++upper_energy_grid_pt;

    unsigned cs_index = 
      std::distance( d_energy_grid.getConst().begin(), lower_energy_grid_pt );

    return LinLin::interpolate( *lower_energy_grid_pt,
				*upper_energy_grid_pt,
				energy,
				d_absorption_cross_section[cs_index],
				d_absorption_cross_section[cs_index+1] );
  }
  else if( energy == d_energy_grid[d_energy_grid.size()-1] )
    return d_absorption_cross_section.back();
  else // energy > d_energy_grid[d_energy_grid.size()-1]
    return 0.0;
}
 
// Return the survival probability at the desired energy
double Nuclide::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  
  double survival_prob = 1.0 - this->getAbsorptionCrossSection( energy )/
    this->getTotalCrossSection( energy );

  // Make sure the survival probability is valid
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );
  
  return survival_prob;
}

// Return the cross section for a specific nuclear reaction
double Nuclide::getReactionCrossSection( 
				     const double energy,
				     const NuclearReactionType reaction ) const
{
  switch( reaction )
  {
  case N__TOTAL_REACTION:
    return getTotalCrossSection( energy );
  default:
    boost::unordered_map<NuclearReactionType,
			 Teuchos::RCP<NuclearReaction> >::const_iterator
      nuclear_reaction;
    
    nuclear_reaction = d_nuclear_reactions.find( reaction );
    
    if( nuclear_reaction != d_nuclear_reactions.end() )
      return nuclear_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for the nuclide, return 0
      return 0.0;
  }
}
  
// Collide with a neutron
void Nuclide::collideAnalogue( NeutronState& neutron, 
			       ParticleBank& bank ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  double total_cross_section = 
    this->getTotalCrossSection( neutron.getEnergy() );

  double absorption_cross_section = 
    this->getAbsorptionCrossSection( neutron.getEnergy() );

  double reaction_cdf = absorption_cross_section/total_cross_section;
  
  // Check if absorption occurs
  if( random_number < reaction_cdf )
    neutron.setAsGone();
  else
  {
    boost::unordered_map<NuclearReactionType,
			 Teuchos::RCP<NuclearReaction> >::const_iterator
      nuclear_reaction, nuclear_reaction_end;
    
    nuclear_reaction = d_nuclear_reactions.begin();
    nuclear_reaction_end = d_nuclear_reactions.end();
    
    // Make sure that fission reactions are neglected
    while( nuclear_reaction != nuclear_reaction_end )
    {
      reaction_cdf += 
	nuclear_reaction->second->getCrossSection( neutron.getEnergy() )/
	total_cross_section;

      if( random_number < reaction_cdf )
	break;
      
      ++nuclear_reaction;
    }

    TEST_FOR_EXCEPTION( nuclear_reaction == nuclear_reaction_end,
			std::runtime_error,
			"The nuclear reaction type could not be sampled." );

    nuclear_reaction->second->react( neutron, bank );
  }
}

// Collide with a neutron and survival bias
void Nuclide::collideSurvivalBias( NeutronState& neutron, 
				   ParticleBank& bank) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  double total_cross_section = 
    this->getTotalCrossSection( neutron.getEnergy() );

  double absorption_cross_section = 
    this->getAbsorptionCrossSection( neutron.getEnergy() );

  double scattering_cross_section = 
    total_cross_section - absorption_cross_section;
  
  // Multiply the neutrons weight by the survival probability
  neutron.multiplyWeight( scattering_cross_section/total_cross_section );
  
  double reaction_cdf = 0.0;
  
  boost::unordered_map<NuclearReactionType,
		       Teuchos::RCP<NuclearReaction> >::const_iterator
    nuclear_reaction, nuclear_reaction_end;
  
  nuclear_reaction = d_nuclear_reactions.begin();
  nuclear_reaction_end = d_nuclear_reactions.end();
  
  // Make sure that fission reactions are neglected
  while( nuclear_reaction != nuclear_reaction_end )
  {
    reaction_cdf += 
      nuclear_reaction->second->getCrossSection( neutron.getEnergy() )/
      scattering_cross_section;
    
    if( random_number < reaction_cdf )
      break;
    
    ++nuclear_reaction;
  }
  
  TEST_FOR_EXCEPTION( nuclear_reaction == nuclear_reaction_end,
		      std::runtime_error,
		      "The nuclear reaction type could not be sampled." );
  
  nuclear_reaction->second->react( neutron, bank );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end Nuclide.cpp
//---------------------------------------------------------------------------//
