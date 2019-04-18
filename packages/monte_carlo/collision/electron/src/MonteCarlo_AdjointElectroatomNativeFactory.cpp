//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom native factory class definition.
//!
//---------------------------------------------------------------------------//

//// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create an adjoint electroatom core
void AdjointElectroatomNativeFactory::createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const SimulationAdjointElectronProperties& properties,
        std::shared_ptr<const AdjointElectroatomCore>& adjoint_electroatom_core )
{
  std::shared_ptr<const std::vector<double> > critical_line_energies =
    std::make_shared<const std::vector<double> >(
      properties.getCriticalAdjointElectronLineEnergies() );

  // Extract the common energy grid used for this atom
  auto energy_grid = std::make_shared<std::vector<double> >(
    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid() );

  // Construct the hash-based grid searcher for this atom
  std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher = std::make_shared<Utility::StandardHashBasedGridSearcher<std::vector<double>,false> >(
                     energy_grid,
                     properties.getNumberOfAdjointElectronHashGridBins() );

  std::shared_ptr<const ElectroatomicReaction> total_forward_reaction;

  // Create the scattering reactions
  AdjointElectroatomCore::ConstReactionMap scattering_reactions;

  std::string electron_interp =
    raw_adjoint_electroatom_data.getElectronTwoDInterpPolicy();

  std::string electron_grid =
    raw_adjoint_electroatom_data.getElectronTwoDGridPolicy();

  std::vector<std::vector<double> > forward_inelastic_cross_sections;
  std::function<double (const double&)> forward_elastic_xs_evaluator;

  // Create the elastic scattering reaction
  if ( properties.isAdjointElasticModeOn() )
  {
    std::shared_ptr<const AdjointElectroatomicReaction> elastic_reaction;

    if( electron_interp == "Log-Log-Log" )
    {
      if ( electron_grid == "Unit-base Correlated" || electron_grid == "Correlated" )
      {
        ThisType::createElasticElectroatomCore<Utility::LogNudgedLogCosLog,Utility::Correlated>(
                                                  raw_adjoint_electroatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  elastic_reaction,
                                                  scattering_reactions );
      }
      else if( electron_grid == "Unit-base" || electron_grid == "Direct" )
      {
        if( properties.getAdjointCoupledElasticSamplingMode() == MODIFIED_TWO_D_UNION )
        {
          THROW_EXCEPTION( std::runtime_error, "the bivariate grid policy "
                           << Utility::UnitBase<Utility::LogLogLog>::name()
                           << " is not currently supported "
                           << "with a "
                           << properties.getAdjointCoupledElasticSamplingMode()
                           << " coupled elastic sampling mode!" );
        }

        ThisType::createElasticElectroatomCore<Utility::LogNudgedLogCosLog,Utility::Direct>(
                                                  raw_adjoint_electroatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  elastic_reaction,
                                                  scattering_reactions );
      }
    }
    else if( electron_interp == "Lin-Lin-Lin" )
    {
      if ( electron_grid == "Unit-base Correlated" || electron_grid == "Correlated" )
      {
        ThisType::createElasticElectroatomCore<Utility::LinLinLin,Utility::Correlated>(
                                                raw_adjoint_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                elastic_reaction,
                                                scattering_reactions );
      }
      else if( electron_grid == "Unit-base" || electron_grid == "Direct" )
      {
        ThisType::createElasticElectroatomCore<Utility::LinLinLin,Utility::Direct>(
                                                raw_adjoint_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                elastic_reaction,
                                                scattering_reactions );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                        "the bivariate grid policy "
                        << electron_grid <<
                        " is not currently supported!" );
      }
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "the 2D interpolation policy "
                       << electron_interp <<
                       " is not currently supported!" );
    }

    // Set the forward elastic reaction cross section evaluator
    forward_elastic_xs_evaluator = [elastic_reaction](const double& energy ){
      return elastic_reaction->getCrossSection( energy );
    };
  }
  else
  {
    // Set a zero forward elastic reaction cross section evaluator
    forward_elastic_xs_evaluator = [](const double& ){ return 0.0; };
  }

  // Create the bremsstrahlung scattering reaction
  if ( properties.isAdjointBremsstrahlungModeOn() )
  {
    std::vector<double> cross_section =
      raw_adjoint_electroatom_data.getForwardBremsstrahlungElectronCrossSection();

    for( unsigned j = 0; j < raw_adjoint_electroatom_data.getForwardBremsstrahlungElectronCrossSectionThresholdEnergyIndex(); ++j )
    {
      auto it = cross_section.begin();
      it = cross_section.insert(it, 0.0);
    }

    // Make sure the cross section is the right size
    testPostcondition( cross_section.size() == energy_grid->size() );

    forward_inelastic_cross_sections.push_back( cross_section );

    AdjointElectroatomCore::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION];

    if( electron_interp == "Log-Log-Log" )
    {
      if ( electron_grid == "Unit-base Correlated" )
      {
        AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        critical_line_energies,
                        properties.getAdjointElectronEvaluationTolerance() );
      }
      else if( electron_grid == "Correlated" )
      {
        AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LogLogLog,Utility::Correlated>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        critical_line_energies,
                        properties.getAdjointElectronEvaluationTolerance() );
      }
      else if( electron_grid == "Unit-base" )
      {
        AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LogLogLog,Utility::UnitBase>(
                         raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        critical_line_energies,
                        properties.getAdjointElectronEvaluationTolerance() );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                        "the bivariate grid policy "
                        << electron_grid <<
                        " is not currently supported!" );
      }
    }
    else if( electron_interp == "Lin-Lin-Lin" )
    {
      if ( electron_grid == "Unit-base Correlated" )
      {
        AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLin,Utility::UnitBaseCorrelated>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        critical_line_energies,
                        properties.getAdjointElectronEvaluationTolerance() );
      }
      else if( electron_grid == "Correlated" )
      {
        AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLin,Utility::Correlated>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        critical_line_energies,
                        properties.getAdjointElectronEvaluationTolerance() );
      }
      else if( electron_grid == "Unit-base" )
      {
        AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLin,Utility::UnitBase>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        critical_line_energies,
                        properties.getAdjointElectronEvaluationTolerance() );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                        "the bivariate grid policy "
                        << electron_grid <<
                        " is not currently supported!" );
      }
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "the 2D interpolation policy "
                       << electron_interp <<
                       " is not currently supported!" );
    }
  }

  // Create the atomic excitation scattering reaction
  if ( properties.isAdjointAtomicExcitationModeOn() )
  {
    std::vector<double> cross_section =
      raw_adjoint_electroatom_data.getForwardAtomicExcitationElectronCrossSection();

    for( unsigned j = 0; j < raw_adjoint_electroatom_data.getForwardAtomicExcitationElectronCrossSectionThresholdEnergyIndex(); ++j )
    {
      auto it = cross_section.begin();
      it = cross_section.insert(it, 0.0);
    }

    // Make sure the cross section is the right size
    testPostcondition( cross_section.size() == energy_grid->size() );

    forward_inelastic_cross_sections.push_back( cross_section );

    AdjointElectroatomCore::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               raw_adjoint_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               reaction_pointer,
                               critical_line_energies );
  }

  // Create the subshell electroionization reactions
  if ( properties.isAdjointElectroionizationModeOn() )
  {
    std::vector<double> cross_section =
      raw_adjoint_electroatom_data.getForwardElectroionizationElectronCrossSection();

    for( unsigned j = 0; j < raw_adjoint_electroatom_data.getForwardElectroionizationElectronCrossSectionThresholdEnergyIndex(); ++j )
    {
      auto it = cross_section.begin();
      it = cross_section.insert(it, 0.0);
    }

    // Make sure the cross section is the right size
    testPostcondition( cross_section.size() == energy_grid->size() );

    forward_inelastic_cross_sections.push_back( cross_section );

    std::vector<std::shared_ptr<const AdjointElectroatomicReaction> >
        electroionization_reactions;

    if( electron_interp == "Log-Log-Log" )
    {
      if ( electron_grid == "Unit-base Correlated" )
      {
        AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
                                  raw_adjoint_electroatom_data,
                                  energy_grid,
                                  grid_searcher,
                                  electroionization_reactions,
                                  critical_line_energies,
                                  properties.getAdjointElectronEvaluationTolerance() );
      }
      else if( electron_grid == "Correlated" )
      {
        AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LogLogLog,Utility::Correlated>(
                                  raw_adjoint_electroatom_data,
                                  energy_grid,
                                  grid_searcher,
                                  electroionization_reactions,
                                  critical_line_energies,
                                  properties.getAdjointElectronEvaluationTolerance() );
      }
      else if( electron_grid == "Unit-base" )
      {
        AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LogLogLog,Utility::UnitBase>(
                                  raw_adjoint_electroatom_data,
                                  energy_grid,
                                  grid_searcher,
                                  electroionization_reactions,
                                  critical_line_energies,
                                  properties.getAdjointElectronEvaluationTolerance() );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                        "the bivariate grid policy "
                        << electron_grid <<
                        " is not currently supported!" );
      }
    }
    else if( electron_interp == "Lin-Lin-Lin" )
    {
      if ( electron_grid == "Unit-base Correlated" )
      {
        AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LinLinLin,Utility::UnitBaseCorrelated>(
                                  raw_adjoint_electroatom_data,
                                  energy_grid,
                                  grid_searcher,
                                  electroionization_reactions,
                                  critical_line_energies,
                                  properties.getAdjointElectronEvaluationTolerance() );
      }
      else if( electron_grid == "Correlated" )
      {
        AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LinLinLin,Utility::Correlated>(
                                  raw_adjoint_electroatom_data,
                                  energy_grid,
                                  grid_searcher,
                                  electroionization_reactions,
                                  critical_line_energies,
                                  properties.getAdjointElectronEvaluationTolerance() );
      }
      else if( electron_grid == "Unit-base" )
      {
        AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LinLinLin,Utility::UnitBase>(
                                  raw_adjoint_electroatom_data,
                                  energy_grid,
                                  grid_searcher,
                                  electroionization_reactions,
                                  critical_line_energies,
                                  properties.getAdjointElectronEvaluationTolerance() );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                        "the bivariate grid policy "
                        << electron_grid <<
                        " is not currently supported!" );
      }
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "the 2D interpolation policy "
                       << electron_interp <<
                       " is not currently supported!" );
    }

    for( size_t i = 0; i < electroionization_reactions.size(); ++i )
    {
      scattering_reactions[electroionization_reactions[i]->getReactionType()] =
        electroionization_reactions[i];
    }
  }

  // Create the total forward reaction
  AdjointElectroatomicReactionNativeFactory::createTotalForwardReaction(
      forward_inelastic_cross_sections,
      energy_grid,
      grid_searcher,
      forward_elastic_xs_evaluator,
      total_forward_reaction );

  // Create the electroatom core
  adjoint_electroatom_core.reset(
    new AdjointElectroatomCore( energy_grid,
                                grid_searcher,
                                critical_line_energies,
                                total_forward_reaction,
                                scattering_reactions,
                                AdjointElectroatomCore::ConstReactionMap(),
                                AdjointElectroatomCore::ConstLineEnergyReactionMap(),
                                false,
                                Utility::LogLog() ) );
}

// Create a adjoint electroatom
void AdjointElectroatomNativeFactory::createAdjointElectroatom(
                    const Data::AdjointElectronPhotonRelaxationDataContainer&
                        raw_adjoint_electroatom_data,
                    const std::string& adjoint_electroatom_name,
                    const double atomic_weight,
                    const SimulationAdjointElectronProperties& properties,
                    std::shared_ptr<const AdjointElectroatom>& adjoint_electroatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );

  std::shared_ptr<const AdjointElectroatomCore> core;

  ThisType::createAdjointElectroatomCore( raw_adjoint_electroatom_data,
                                          properties,
                                          core);

  // Create the adjoint electroatom
  adjoint_electroatom.reset( new AdjointElectroatom(
                                adjoint_electroatom_name,
                                raw_adjoint_electroatom_data.getAtomicNumber(),
                                atomic_weight,
                                *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
