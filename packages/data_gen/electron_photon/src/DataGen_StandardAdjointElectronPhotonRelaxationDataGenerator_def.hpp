//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointAdjointElectronPhotonRelaxationDataGenerator_def.hpp
//! \author Luke Kersting
//! \brief  The standard adjoint electron-photon-relaxation data generator template def
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_DEF_HPP
#define DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_DEF_HPP

namespace DataGen{

// Create the cross section on the union energy grid
/*! \detials The functor should take the incoming adjoint energy (double) as its
 *  argument and return the adjoint cross section. 
 */
template <typename Functor>
void StandardAdjointElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   Functor& adjoint_cross_section_functor,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const
{
   std::vector<double> raw_cross_section( union_energy_grid.size() );

   std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();

   unsigned index = 0u;

   while( energy_grid_pt != union_energy_grid.end() )
   {
     raw_cross_section[index] =
       adjoint_cross_section_functor( *energy_grid_pt );

     ++energy_grid_pt;
     ++index;
   }

   std::vector<double>::iterator start =
     std::find_if( raw_cross_section.begin(),
         	  raw_cross_section.end(),
         	  notEqualZero );

   cross_section.assign( start, raw_cross_section.end() );

   threshold_index = std::distance( raw_cross_section.begin(), start );
}

// Update the cross section on the union energy grid
/*! \detials The functor should take the incoming adjoint energy (double) as its
 *  argument and return the adjoint cross section. The old union energy grid and
 *  cross section values should only contain energy grid points that are in the union energy grid
 */
template <typename Functor>
void StandardAdjointElectronPhotonRelaxationDataGenerator::updateCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::list<double>& old_union_energy_grid,
   const std::vector<double>& old_cross_section,
   Functor& adjoint_cross_section_functor,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const
{
  std::vector<double> raw_cross_section( union_energy_grid.size() );

  std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();
  std::list<double>::const_iterator old_energy_grid_pt =
    old_union_energy_grid.begin();

  unsigned index = 0u;
  unsigned old_index = 0u;

  while( energy_grid_pt != union_energy_grid.end() )
  {
    if ( *energy_grid_pt == *old_energy_grid_pt )
    {
      raw_cross_section[index] = old_cross_section[old_index];
   
      ++old_energy_grid_pt;
      ++old_index;
    }
    else
    {
      raw_cross_section[index] =
        adjoint_cross_section_functor( *energy_grid_pt );
    }

    ++energy_grid_pt;
    ++index;
  }

  std::vector<double>::iterator start =
    std::find_if( raw_cross_section.begin(),
		  raw_cross_section.end(),
		  notEqualZero );

  cross_section.assign( start, raw_cross_section.end() );

  threshold_index = std::distance( raw_cross_section.begin(), start );
}

// Set the electroionization data on union energy grid
template<typename Functor>
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionzationData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const std::list<double>& old_union_energy_grid,
    const std::vector<double>& old_cross_section,
    const std::list<double>& union_energy_grid,
    const Functor& grid_function,
    const std::shared_ptr<ElectroionizationEvaluator>& cs_evaluator,
    const std::vector<double>& electron_energy_grid,
    const unsigned subshell ) const
{
  std::vector<double> cross_section;
  unsigned threshold;

  // Update cross sections on the union energy grid
  this->updateCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      old_union_energy_grid,
      old_cross_section,  
      grid_function,
      cross_section,
      threshold );

  // Set the cross section for the subshell
  data_container.setAdjointElectroionizationCrossSection(
    subshell,
    cross_section );

  // Set the threshold energy index for the subshell
  data_container.setAdjointElectroionizationCrossSectionThresholdEnergyIndex(
    subshell,
    threshold );

  double binding_energy = data_container.getSubshellBindingEnergy( subshell );

  /* The energy to outgoing energy nudge value for the should be set slighty
    * higher for the distribution_grid_generator than for the electroionization
    * cross section evaluator. This will ensure that there are no pdf values of
    * zero in the distribution.
    */
  std::shared_ptr<DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin> >
    distribution_grid_generator(
      new AdjointElectronDistributionGenerator<Utility::LinLinLin>(
          this->getMaxElectronEnergy(),
          binding_energy*2.0,
          binding_energy + 2e-7,
          d_adjoint_electroionization_grid_convergence_tol,
          d_adjoint_electroionization_absolute_diff_tol,
          d_adjoint_electroionization_distance_tol ) );

  for ( unsigned i = 0; i < cross_section.size(); ++i )
  {
    std::vector<double> energy_grid, pdf;
    unsigned energy_index = i + threshold;

    distribution_grid_generator->generateAndEvaluateDistribution<ElectroionizationReaction>(
      energy_grid,
      pdf,
      cs_evaluator,
      d_adjoint_electroionization_evaluation_tol,
      electron_energy_grid[energy_index],
      cross_section[i] );

    // Set the adjoint bremsstrahlung scattering distribution
    data_container.setAdjointElectroionizationRecoilEnergyAtIncomingEnergy(
      subshell,
      electron_energy_grid[energy_index],
      energy_grid );

    data_container.setAdjointElectroionizationRecoilPDFAtIncomingEnergy(
      subshell,
      electron_energy_grid[energy_index],
      pdf );
  }
}

// Set the electroionization data on union energy grid
template<typename Functor>
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const std::list<double>& old_union_energy_grid,
    const std::vector<double>& old_cross_section,
    const std::list<double>& union_energy_grid,
    const Functor& grid_function,
    const std::shared_ptr<BremsstrahlungEvaluator>& cs_evaluator,
    const std::vector<double>& electron_energy_grid ) const
{
  std::vector<double> cross_section;
  unsigned threshold;
  this->updateCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      old_union_energy_grid,
      old_cross_section,  
      grid_function,
      cross_section,
      threshold );

  data_container.setAdjointBremsstrahlungElectronCrossSection( cross_section );
  data_container.setAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex( threshold );

  /* The energy to outgoing energy nudge value for the should be set slighty
   * higher for the distribution_grid_generator than for the bremsstrahlung
   * cross section evaluator. This will ensure that there are no pdf values of
   * zero in the distribution.
   */
  std::shared_ptr<DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin> >
    distribution_grid_generator(
      new AdjointElectronDistributionGenerator<Utility::LinLinLin>(
          this->getMaxElectronEnergy(),
          d_adjoint_bremsstrahlung_max_energy_nudge_value,
          2.0*d_adjoint_bremsstrahlung_energy_to_outgoing_energy_nudge_value,
          d_adjoint_bremsstrahlung_grid_convergence_tol,
          d_adjoint_bremsstrahlung_absolute_diff_tol,
          d_adjoint_bremsstrahlung_distance_tol ) );

  for ( unsigned i = 0; i < cross_section.size(); ++i )
  {
    std::vector<double> energy_grid, pdf;
    unsigned energy_index = i + threshold;

    distribution_grid_generator->generateAndEvaluateDistribution<BremsstrahlungReaction>(
      energy_grid,
      pdf,
      cs_evaluator,
      d_adjoint_bremsstrahlung_evaluation_tol,
      electron_energy_grid[energy_index],
      cross_section[i] );

    // Set the adjoint bremsstrahlung scattering distribution
    data_container.setAdjointElectronBremsstrahlungEnergyAtIncomingEnergy(
      electron_energy_grid[energy_index],
      energy_grid );

    data_container.setAdjointElectronBremsstrahlungPDFAtIncomingEnergy(
      electron_energy_grid[energy_index],
      pdf );

  }
}

} // end DataGen namespace

#endif // end DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator_def.hpp
//---------------------------------------------------------------------------//
