//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.cpp
//! \author Alex Robinson
//! \brief  Particle source definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleSource::ParticleSource()
  : d_model( new Geometry::InfiniteMediumModel( Geometry::ModuleTraits::invalid_internal_cell_handle ) ),
    d_navigator( d_model->createNavigatorAdvanced() )
{ /* ... */ }

// Embed the source in the desired model
void ParticleSource::embedInModel(
                          const std::shared_ptr<const Geometry::Model>& model )
{
  // Make sure that the model is valid
  testPrecondition( model.get() );

  d_model = model;

  d_navigator.reset( model->createNavigatorAdvanced() );
}

// Print a standard summary of the source data
void ParticleSource::printStandardSummary(
                                   const std::string& source_type,
                                   const ModuleTraits::InternalCounter trials,
                                   const ModuleTraits::InternalCounter samples,
                                   const double efficiency,
                                   std::ostream& os ) const
{
  os << "Source " << this->getId() << " Summary..." << "\n"
     << "\tType: " << source_type << "\n"
     << "\tNumber of (position) trials: " << trials << "\n"
     << "\tNumber of samples: " << samples << "\n"
     << "\tSampling efficiency: " << efficiency << std::endl;
}

// Print a standard summary of the source starting cells
void ParticleSource::printStandardStaringCellSummary(
           std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells,
           std::ostream& os ) const
{
  os << "Source " << this->getId() << " Starting Cells: ";

  std::set<Geometry::ModuleTraits::InternalCellHandle>::const_iterator cell_it,
    cell_end;
  cell_it = starting_cells.begin();
  cell_end = starting_cells.end();

  while( cell_it != cell_end )
  {
    os << *cell_it << " ";

    ++cell_it;
  }

  os << std::endl;
}

// Print a standard summary of the dimension data
void ParticleSource::printStandardDimensionSummary(
                                const std::string& dimension_distribution_type,
                                const PhaseSpaceDimension dimension,
                                const ModuleTraits::InternalCounter trials,
                                const ModuleTraits::InternalCounter samples,
                                const double efficiency,
                                std::ostream& os ) const
{
  os << "Source " << this->getId() << " "
     << dimension << " Sampling Summary..."
     << "\n"
     << "\tDistribution Type: " << dimension_distribution_type << "\n"
     << "\tNumber of trials: " << trials << "\n"
     << "\tNumber of samples: " << samples << "\n"
     << "\tSampling efficiency: " << efficiency << std::endl;
}

// Get the model that this source is embeded in
const Geometry::Model& ParticleSource::getModel() const
{
  return *d_model;
}

// Get the navigator for the model that this source is embedded in
const Geometry::Navigator& ParticleSource::getModelNavigator() const
 {
  return *d_navigator;
}

// Embed a particle in model
/*! \details The particle's current position must be inside of the provided
 * cell.
 */
void MonteCarlo::embedParticleInModel(
                   ParticleState& particle,
                   const Geometry::ModelTraits::InternalCellHandle cell ) const
{
  particle.embedInModel( d_model, cell );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.cpp
//---------------------------------------------------------------------------//
