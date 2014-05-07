//---------------------------------------------------------------------------//
//!
//! \file   Nuclide.cpp
//! \author Alex Robinson
//! \brief  The nuclide class declaration
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "Nuclide.hpp"
#include "NuclearReactionFactory.hpp"

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
		       raw_nuclide_data.extractTotalAbsorptionCrossSection() ),
    d_elastic_scattering_reaction( NULL ),
    d_nuclear_reactions( 0 )
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
  reaction_factory.createElasticReaction( d_elastic_scattering_reaction );

  // Create all of the non-elastic reactions
  reaction_factory.createNonElasticReactions( d_nuclear_reactions );

  // Calculate the total absorption cross section
  
  // Calculate the total cross section
}


} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end Nuclide.cpp
//---------------------------------------------------------------------------//
