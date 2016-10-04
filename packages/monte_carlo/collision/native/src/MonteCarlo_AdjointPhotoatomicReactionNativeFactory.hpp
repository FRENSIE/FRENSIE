// Return the adjoint photon energy grid for a max energy
std::vector<double>
AdjointElectronPhotonRelaxationDataContainer::getAdjointPhotonEnergyGrid(
                                                const double max_energy ) const
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > d_min_photon_energy );
  testPrecondition( max_energy <= d_max_photon_energy );

  std::vector<double> condensed_energy_grid;
  
  if( max_energy > d_adjoint_photon_energy_grid.front() &&
      max_energy < d_adjoint_photon_energy_grid.back() )
  {
    std::vector<double>::const_iterator lower_bound_index_it = 
      Utility::Search::binaryLowerBoundIndex(
                                          d_adjoint_photon_energy_grid.begin(),
                                          d_adjoint_photon_energy_grid.end(),
                                          max_energy );

    std::vector<double>::const_iterator upper_bound_index_it =
      lower_bound_index_it;
    ++upper_bound_index_it;

    condensed_energy_grid.assign( d_adjoint_photon_energy_grid.begin(),
                                  upper_bound_index_it );

    condensed_energy_grid.push_back( max_energy );
  }
  else if( max_energy == d_adjoint_photon_energy_grid.back() )
    condensed_energy_grid = d_adjoint_photon_energy_grid;

  return condensed_energy_grid;
}

// Return the adjoint Waller-Hartree (WH) incoh. photon cs for the max erg
std::vector<double>
AdjointElectronPhotonRelaxationDataContainer::getAdjointWallerHartreeIncoherentCrossSection(
                                                const double max_energy ) const
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > d_min_photon_energy );
  testPrecondition( max_energy <= d_max_photon_energy );

  std::vector<double> condensed_cross_section;

  for( unsigned i = 0; i < d_adjoint_photon_energy_grid.size(); ++i )
  {
    const std::vector<double>& max_energy_grid =
      d_adjoint_waller_hartree_incoherent_max_energy_grid[i];

    const std::vector<double>& cross_section =
      d_adjoint_waller_hartree_incoherent_max_energy_grid[i];

    if( max_energy_grid.front() <= max_energy )
    {
      unsigned index =
        Utility::Search::binaryLowerBoundIndex( max_energy_grid.begin(),
                                                max_energy_grid.end(),
                                                max_energy );

      condensed_cross_section.push_back(
                      Utility::LinLin::interpolate( max_energy_grid[index],
                                                    max_energy_grid[index+1],
                                                    max_energy,
                                                    cross_section[index],
                                                    cross_section[index+1] ) );
    }
    else
      condensed_cross_section.push_back( 0.0 );
  }

  // Check that the last cross section value (corresponding to max energy)
  // is zero
  if( condensed_cross_section.back() != 0.0 )
    condensed_cross_section.back() == 0.0;

  return condensed_cross_section;
}

// Return the subshell adjoint IA incoh. photon cs for the max energy
std::vector<double> AdjointElectronPhotonRelaxationDataContainer::getAdjointImpulseApproxSubshellIncoherentCrossSection(
                                                const unsigned subshell,
                                                const double max_energy ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );
  // Make sure the max energy is valid
  testPrecondition( max_energy > d_min_photon_energy );
  testPrecondition( max_energy <= d_max_photon_energy );

  std::vector<double> condensed_cross_section;

  // Get the subshell cross section
  const std::vector<std::vector<double> >& subshell_max_energy_grids =
    d_adjoint_impulse_approx_subshell_incoherent_max_energy_grid.find( subshell )->second;

  const std::vector<std::vector<double> >& subshell_cross_sections =
    d_adjoint_impulse_approx_subshell_incoherent_cross_section.find( subshell )->second;

  // Get the binding energy for this cross section
  const double binding_energy = this->getSubshellBindingEnergy( subshell );

  if( max_energy_grid.front() <= max_energy )
  {
    unsigned index =
      Utility::Search::binaryLowerBoundIndex( max_energy_grid.begin(),
                                              max_energy_grid.end(),
                                              max_energy );
    
    condensed_cross_section.push_back(
                      Utility::LinLin::interpolate( max_energy_grid[index],
                                                    max_energy_grid[index+1],
                                                    max_energy,
                                                    cross_section[index],
                                                    cross_section[index+1] ) );
  }
  else
  {
    condensed_cross_section.push_back( 0.0 );
  }

  // Check that the last cross section value (corresponding to max energy)
  // is zero
  if( condensed_cross_section.back() != 0.0 )
    condensed_cross_section.back() == 0.0;

  return condensed_cross_section;
}
