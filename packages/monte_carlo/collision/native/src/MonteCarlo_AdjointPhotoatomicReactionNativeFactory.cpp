//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomicReactionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatomic reaction native data factor definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReactioNativeFactory.hpp"
#include "MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"


namespace MonteCarlo{

// Create the union energy grid with the desired max energy
void AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                      const Data::AdjointElectronPhotonRelaxationDataContainer&
                      raw_adjoint_photoatom_data,
                      Teuchos::ArrayRCP<double>& energy_grid,
                      const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().front() );
  testPrecondition( max_energy <= raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().back() );

  if( max_energy < raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().back() )
  {
    // Find the bin that contains the max energy
    std::vector<double>::const_iterator lower_bound =
      Utility::Search::binaryLowerBound(
               raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().begin(),
               raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().end(),
               max_energy );

    energy_grid.assign( raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().begin(),
                        lower_bound + 1 );

    energy_grid.push_back( max_energy );
  }
  else if( max_energy == raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().back() )
  {
    energy_grid.assign( raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().begin(),
                        raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid().end() );
  }
  // else: throw exception?
}

// Create the incoherent adjoint photoatomic reaction(s)
void AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
       const Data::AdjointElectronPhotonRelaxationDataContainer&
       raw_adjoint_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::Array<std::shared_ptr<AdjointPhotoatomicReaction> >&
       incoherent_adjoint_reactions,
       const IncoherentAdjointModelType incoherent_adjoint_model,
       const std::vector<double>& critical_line_energies )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_photoatom_data.getPhotonEnergyGrid().size() >=
                    energy_grid.size() );
  testPrecondition( raw_adjoint_photoatom_data.getPhotonEnergyGrid().back() >=
                    energy_grid.back() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  std::string model_name =
    convertIncoherentAdjointModelTypeToString( incoherent_adjoint_model );

  // Use Waller-Hartree data
  if( model_name.find( "Impulse" ) >= model_name.size() )
  {
    incoherent_adjoint_reactions.resize( 1 );

    // Extract the cross section and slice based on max energy
    Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>
      two_d_cross_section( raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid(),
                           raw_adjoint_photoatom_data.getAdjointWallerHartreeIncoherentMaxEnergyGrid(),
                           raw_adjoint_photoatom_data.getAdjointWallerHartreeIncoherentCrossSection() );

    Teuchos::ArrayRCP<double> cross_section;
    
    ThisType::reduceTwoDCrossSection( two_d_cross_section,
                                      energy_grid,
                                      cross_section );
                                          
    // Create the scattering distribution
    std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>
      distribution;

    IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                                                    raw_adjoint_photoatom_data,
                                                    distribution,
                                                    incoherent_adjoint_model,
                                                    energy_grid.back() );

    // Create the incoherent adjoint reaction
    std::shared_ptr<IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >
      incoherent_adjoint_reaction(
               new IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false>(
                                                              energy_grid,
                                                              cross_section,
                                                              0u,
                                                              grid_searcher,
                                                              distribution ) );

    // Assign the critical line energies
    if( critical_line_energies.size() > 0 )
    {
      incoherent_adjoint_reaction->setCriticalLineEnergies(
                                                      critical_line_energies );
    }

    incoherent_adjoint_reactions[0] = incoherent_adjoint_reaction;
  }
  // Create the subshell reactions using the impulse approx.
  else
  {
    incoherent_reactions.clear();

    std::shared_ptr<IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >
      subshell_incoherent_adjoint_reaction;

    std::set<unsigned>::const_iterator subshell_it =
      raw_adjoint_photoatom_data.getSubshells().begin();

    while( subshell_it != raw_adjoint_photoatom_data.getSubshells().end() )
    {
      // Extract the cross section and slice based on max energy
      Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin>
      two_d_cross_section( raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid(),
                           raw_adjoint_photoatom_data.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell_it ),
                           raw_adjoint_photoatom_data.getAdjointImpulseApproxSubshellIncoherentCrossSection( *subshell_it ) );

      Teuchos::ArrayRCP<double> cross_section;
    
      ThisType::reduceTwoDCrossSection( two_d_cross_section,
                                        energy_grid,
                                        cross_section );

      // Create the subshell incoherent distribution
      std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>
        distribution;
      
      IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                                                    raw_adjoint_photoatom_data,
                                                    distribution,
                                                    incoherent_adjoint_model,
                                                    energy_grid.back(),
                                                    *subshell_it );

      // Create the subshell incoherent adjoint reaction
      subshell_incoherent_adjoint_reaction.reset(
       new SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,false>(
                                                                energy_grid,
                                                                cross_section,
                                                                0u,
                                                                grid_searcher,
                                                                distribution );
       // Assign the critical line energies
       if( critical_line_energies.size() > 0 )
       {
         subshell_incoherent_adjoint_reaction->setCriticalLineEnergies(
                                                      critical_line_energies );
       }

       incoherent_adjoint_reactions.push_back(
                                        subshell_incoherent_adjoint_reaction );

       ++subshell_it;
    }
  }
}

// Create the coherent adjoint photoatomic reaction
void AdjointPhotoatomicReactionNativeFactory::createCoherentReaction(
      const Data::AdjointElectronPhotonRelaxationDataContainer&
      raw_adjoint_photoatom_data,
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      std::shared_ptr<AdjointPhotoatomicReaction>& coherent_adjoint_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_photoatom_data.getPhotonEnergyGrid().size() >=
                    energy_grid.size() );
  testPrecondition( raw_adjoint_photoatom_data.getPhotonEnergyGrid().back() >=
                    energy_grid.back() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Extract the coherent cross section
  Teuchos::ArrayRCP<double> cross_section;

  ThisType::sliceCrossSection( raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid(),
                               raw_adjoint_photoatom_data.getAdjointWallerHartreeCoherentCrossSection(),
                               energy_grid.back(),
                               cross_section );

  // Create the coherent distribution
  std::shared_ptr<const CoherentScatteringDistribution>& coherent_distribution;

  CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution(
                                                    raw_adjoint_photoatom_data,
                                                    coherent_distribution );

  // Create the coherent adjoint reaction
  coherent_adjoint_reaction.reset(
                new CoherentAdjointPhotoatomicReaction<Utility::LinLin,false>(
                                                       energy_grid,
                                                       cross_section,
                                                       0u,
                                                       grid_searcher,
                                                       coherent_distribution );
}

// Create the pair production adjoint photoatomic reaction
void AdjointPhotoatomicReactionNativeFactory::createPairProductionReaction(
      const Data::AdjointElectronPhotonRelaxationDataContainer&
      raw_adjoint_photoatom_data,
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      std::shared_ptr<AdjointPhotoatomicReaction>&
      pair_production_adjoint_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_photoatom_data.getPhotonEnergyGrid().size() >=
                    energy_grid.size() );
  testPrecondition( raw_adjoint_photoatom_data.getPhotonEnergyGrid().back() >=
                    energy_grid.back() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Create the energy distribution
  std::shared_ptr<const LineEnergyAdjointPhotonScatteringDistribution>
    pair_production_distribution;

  double cross_section;

  LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createPairProductionDistribution(
                                                  raw_adjoint_photoatom_data,
                                                  pair_production_distribution,
                                                  cross_section,
                                                  energy_grid.back() );

  // Create the reaction
  pair_production_adjoint_reaction.reset(
                           new LineEnergyAdjointPhotoatomicReaction(
                                  PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION,
                                  cross_section,
                                  pair_production_distribution ) );
}

// Create the triplet production adjoint photoatomic reaction
void AdjointPhotoatomicReactionNativeFactory::createTripletProductionReaction(
      const Data::AdjointElectronPhotonRelaxationDataContainer&
      raw_adjoint_photoatom_data,
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      std::shared_ptr<AdjointPhotoatomicReaction>&
      triplet_production_adjoint_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( raw_adjoint_photoatom_data.getPhotonEnergyGrid().size() >=
                    energy_grid.size() );
  testPrecondition( raw_adjoint_photoatom_data.getPhotonEnergyGrid().back() >=
                    energy_grid.back() );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Create the energy distribution
  std::shared_ptr<const LineEnergyAdjointPhotonScatteringDistribution>
    triplet_production_distribution;

  double cross_section;

  LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createTripletProductionDistribution(
                                                  raw_adjoint_photoatom_data,
                                                  triplet_production_distribution,
                                                  cross_section,
                                                  energy_grid.back() );

  // Create the reaction
  triplet_production_adjoint_reaction.reset(
                     new LineEnergyAdjointPhotoatomicReaction(
                              TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION,
                              cross_section,
                              triplet_production_distribution ) );
}

// Create the forward total reaction (only used to get the cross section)
void AdjointPhotoatomicReactionNativeFactory::createTotalForwardReaction(
      const Data::AdjointElectronPhotonRelaxationDataContainer&
      raw_adjoint_photoatom_data,
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      std::shared_ptr<PhotoatomicReaction>& total_forward_reaction )
{
  // Extract the total forward cross section
  Teuchos::ArrayRCP<double> cross_section;

  ThisType::sliceCrossSection( raw_adjoint_photoatom_data.getAdjointPhotonEnergyGrid(),
                               raw_adjoint_photoatom_data.getWallerHartreeTotalCrossSection(),
                               energy_grid.back(),
                               cross_section );

  // Create the coherent adjoint reaction
  total_forward_reaction.reset(
                new AbsorptionPhotoatomicReaction<Utility::LinLin,false>(
                                                energy_grid,
                                                cross_section,
                                                0u,
                                                grid_searcher,
                                                TOTAL_PHOTOATOMIC_REACTION ) );
}

// Reduce a 2D cross section to a 1D cross section
void AdjointPhotoatomicReactionNativeFactory::reduceTwoDCrossSection(
              const Utility::FullyTabularTwoDDistribution& two_d_cross_section,
              const Teuchos::ArrayRCP<const double> energy_grid,
              Teuchos::ArrayRCP<double> cross_section )
{
  // Make sure the energy grid is valid
  testPrecondition( two_d_cross_section.getUpperBoundOfPrimaryIndepVar() >=
                    energy_grid.back() );
  testPrecondition( two_d_cross_section.getLowerBoundOfPrimaryIndepVar() <=
                    energy_grid.back() );

  // Resize the cross section
  cross_section.resize( energy_grid.size() );

  // Assume that the max energy is the final energy in the grid
  const double max_energy = energy_grid.back();
  
  for( size_t i = 0; i < energy_grid.size(); ++i )
  {
    cross_section[i] =
      two_d_cross_section.evaluate( energy_grid[i], max_energy );
  }
}

// Slice the cross section based on the max energy
void LineEnergyAdjointPhotonScatteringDistributionNativeFactory::sliceCrossSection(
                                 const std::vector<double>& full_energy_grid,
                                 const std::vector<double>& full_cross_section,
                                 const double max_energy,
                                 Teuchos::ArrayRCP<double>& cross_section )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > full_energy_grid.front() );
  testPrecondition( max_energy <= full_energy_grid.back() );

  if( max_energy < full_energy_grid.back() )
  {
    // Find the bin that contains the max energy
    size_t bin_index = Utility::Search::binaryLowerBound(
                                                      full_energy_grid.begin(),
                                                      full_energy_grid.end(),
                                                      max_energy );

    // Determine the cross section value at the max energy
    double cross_section_at_max_energy =
      Utility::LinLin::interpolate( full_energy_grid[bin_index],
                                    full_energy_grid[bin_index+1],
                                    max_energy,
                                    full_cross_section[bin_index],
                                    full_cross_section[bin_index+1] );

    // Create the sliced cross section
    cross_section.assign( full_cross_section.begin(),
                          full_cross_section.begin()+bin_index+1 );

    cross_section.push_back( cross_section_at_max_energy );
  }
  else if( max_energy == full_energy_grid.back() )
  {
    cross_section.assign( full_cross_section.begin(),
                          full_cross_section.end() );
  }
  // else: throw exception?
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
