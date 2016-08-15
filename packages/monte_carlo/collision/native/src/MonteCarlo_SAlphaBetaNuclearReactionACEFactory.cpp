//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclearReactionACEFactory.cpp
//! \author Eli Moll
//! \brief  S(alpha,beta) nuclear reaction factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SAlphaBetaNuclearReactionACEFactory.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace MonteCarlo{

// Constructor
SAlphaBetaNuclearReactionACEFactory::SAlphaBetaNuclearReactionACEFactory( 
	 const std::string& table_name,
	 const double atomic_weight_ratio,
	 const double temperature,
	 const Teuchos::ArrayRCP<const double>& energy_grid,
	 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
	 const Data::XSSSabDataExtractor& sab_nuclide_data ) :
	   NuclearReactionACEFactory( table_name,
	                              atomic_weight_ratio,
	                              temperature,
	                              energy_grid,
	                              raw_nuclide_data )
{
  // Create the scattering distribution factory
  SAlphaBetaNuclearScatteringDistributionACEFactory 
    scattering_dist_factory( table_name,
			                       atomic_weight_ratio,
			                       raw_nuclide_data,
			                       sab_nuclide_data );
	
  // Create a map of the reaction types and the corresponding cross section
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
    reaction_cross_section;
  setSAlphaBetaCrossSectionMap( sab_nuclide_data,
                                      reaction_cross_section );
	
	// Create a map of the reaction types and the upper energy limits
	boost::unordered_map<NuclearReactionType, double> upper_energy_limits;
	setSAlphaBetaUpperEnergyLimitMap( sab_nuclide_data,
	                                        upper_energy_limits );
	
	// Initialize the S(alpha,beta) reactions
	initializeSAlphaBetaReactions( temperature,
	                               sab_nuclide_data.extractInelasticEnergyGrid(),
	                               reaction_cross_section,
	                               scattering_dist_factory );
}

// Update the reaction threshold map with the new reactions
void SAlphaBetaNuclearReactionACEFactory::setSAlphaBetaCrossSectionMap( 
  const Data::XSSSabDataExtractor& sab_nuclide_data,
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
    reaction_cross_section )
{
  // Inelastic cross-section
  NuclearReactionType reaction_type = convertUnsignedToNuclearReactionType( 1004u );
  reaction_cross_section[reaction_type] = 
    sab_nuclide_data.extractInelasticCrossSection();
  
  // Elastic cross-section
  if( sab_nuclide_data.hasElasticScatteringCrossSectionData() )
  {
    reaction_cross_section[convertUnsignedToNuclearReactionType( 1002u )] = 
      sab_nuclide_data.extractElasticCrossSection();
  }
}

// Update the reaction upper threshold index map
void SAlphaBetaNuclearReactionACEFactory::setSAlphaBetaUpperEnergyLimitMap( 
       const Data::XSSSabDataExtractor& sab_nuclide_data,
       boost::unordered_map<NuclearReactionType, double> upper_energy_limits )
{
  // Inelastic upper energy limit
  upper_energy_limits[convertUnsignedToNuclearReactionType( 1004u )] =
    sab_nuclide_data.extractInelasticEnergyGrid().back();
    
  // Elastic upper energy limit
  if( sab_nuclide_data.hasElasticScatteringCrossSectionData() )
  {
    upper_energy_limits[convertUnsignedToNuclearReactionType( 1002u )] =
      sab_nuclide_data.extractElasticEnergyGrid().back();
  }
}

// Initialize the S(alpha,beta) reactions
void SAlphaBetaNuclearReactionACEFactory::initializeSAlphaBetaReactions(  
    const double temperature,
    Teuchos::ArrayView<const double> sab_energy_grid,
    boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
      reaction_cross_section,
    const SAlphaBetaNuclearScatteringDistributionACEFactory& 
      scattering_dist_factory )
{
  // Create the S(alpha,beta) reactions
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >::const_iterator
    reaction_xs, reaction_xs_end;

  reaction_xs = reaction_cross_section.begin();
  reaction_xs_end = reaction_cross_section.end();

  NuclearReactionType reaction_type;

  Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > 
    scattering_distribution;
 
  while( reaction_xs != reaction_xs_end )
  {
    reaction_type = reaction_xs->first;
  
    Teuchos::RCP<NuclearReaction>& reaction =
      d_scattering_reactions[reaction_type];
      
    scattering_dist_factory.createSAlphaBetaScatteringDistributions(
      reaction_type,
      scattering_distribution );
      
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( sab_energy_grid );
    
    Teuchos::ArrayRCP<double> cross_section;
    cross_section.deepCopy( reaction_cross_section[reaction_type] );
      
    reaction.reset( new NeutronScatteringReaction(
      reaction_type,
      temperature,
      0.0,
      0u,
      0u,
      energy_grid,
      cross_section,
      scattering_distribution ) );
    
    ++reaction_xs;
  }
  
  // Adjust the threshold energy index for the existing scattering reactions
  reaction_xs = reaction_cross_section.begin();
  reaction_xs_end = reaction_cross_section.end();
  
  while( reaction_xs != reaction_xs_end )
  {
    reaction_type = reaction_xs->first;
    
    if( reaction_type == MonteCarlo::SALPHABETA_N__N_INELASTIC_REACTION )
    {
      unsigned index;
      
      Utility::Search::binaryUpperBoundIndex( d_energy_grid.begin(),
                                              d_energy_grid.end(),
                                              sab_energy_grid.back() );
    
      d_scattering_reactions[MonteCarlo::N__N_INELASTIC_REACTION]->updateThresholdEnergyIndex( index );
    }
    else if( reaction_type == MonteCarlo::SALPHABETA_N__N_ELASTIC_REACTION )
    {
      unsigned index;
      
      Utility::Search::binaryUpperBoundIndex( d_energy_grid.begin(),
                                              d_energy_grid.end(),
                                              sab_energy_grid.back() );
    
      d_scattering_reactions[MonteCarlo::N__N_ELASTIC_REACTION]->updateThresholdEnergyIndex( index );
    }
    
  }  
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
