//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FillledPhotonGeometryModel.cpp
//! \author Alex Robinson
//! \brief  The filled photon geometry model class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_FilledPhotonGeometryModel.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"

namespace MonteCarlo{

// Load the scattering centers
void FilledPhotonGeometryModel::loadScatteringCenters(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&
       atomic_relaxation_model_factory,
       const SimulationProperties& properties,
       const bool verbose,                  
       ScatteringCenterNameMap& scattering_center_name_map ) const
{
  PhotoatomFactory photoatom_factory( database_path,
                                      unique_scattering_center_names,
                                      scattering_center_definitions,
                                      atomic_relaxation_model_factory,
                                      properties,
                                      verbose );

  photoatom_factory.createPhotoatomMap( scattering_center_name_map );
}

// Get the macroscopic cross section for a specific reaction
double FilledPhotonGeometryModel::getMacroscopicReactionCrossSection(
                                const PhotonState& photon,
                                const PhotonuclearReactionType reaction ) const
{
  return this->getMacroscopicReactionCrossSection( photon.getCell(),
                                                   photon.getEnergy(),
                                                   reaction );
}

// Get the macroscopic cross section for a specific reaction
double FilledPhotonGeometryModel::getMacroscopicReactionCrossSection(
                         const Geometry::Model::EntityId cell,
                         const double energy,
                         const PhotonuclearReactionType reaction ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
  {
    return this->getMaterial(cell)->getMacroscopicReactionCrossSection(
                                                            energy, reaction );
  }
}

// Get the macroscopic cross section for a specific reaction
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
double FilledPhotonGeometryModel::getMacroscopicReactionCrossSectionQuick(
                                const PhotonState& photon,
                                const PhotonuclearReactionType reaction ) const
{
  return this->getMacroscopicReactionCrossSectionQuick( photon.getCell(),
                                                        photon.getEnergy(),
                                                        reaction );
}

// Get the macroscopic cross section for a specific reaction
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
double FilledPhotonGeometryModel::getMacroscopicReactionCrossSectionQuick(
                         const Geometry::Model::EntityId cell,
                         const double energy,
                         const PhotonuclearReactionType reaction ) const
{
  // Make sure that the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );
  
  return this->getMaterial(cell)->getMacroscopicReactionCrossSection(
                                                            energy, reaction );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledPhotonGeometryModel.cpp
//---------------------------------------------------------------------------//
