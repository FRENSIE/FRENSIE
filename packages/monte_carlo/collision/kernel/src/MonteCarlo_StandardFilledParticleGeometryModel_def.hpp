//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFilledParticleGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The standard filled particle geometry model class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FILLED_PARTICLE_GEOMETRY_MODEL_DEF_HPP
#define MONTE_CARLO_STANDARD_FILLED_PARTICLE_GEOMETRY_MODEL_DEF_HPP

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename Material>
StandardFilledParticleGeometryModel<Material>::StandardFilledParticleGeometryModel()
{ /* ... */ }

// Constructor
template<typename Material>
StandardFilledParticleGeometryModel<Material>::StandardFilledParticleGeometryModel(
                 const std::shared_ptr<const Geometry::Model>& unfilled_model )
  : d_unfilled_model( unfilled_model ),
    d_scattering_center_name_map(),
    d_material_name_map(),
    d_cell_id_material_map()
{
  // Make sure that the unfilled model is valid
  testPrecondition( unfilled_model.get() );
}

// Set the unfilled model
template<typename Material>
void StandardFilledParticleGeometryModel<Material>::setUnfilledModel(
                 const std::shared_ptr<const Geometry::Model>& unfilled_model )
{
  // Make sure that the unfilled model is valid
  testPrecondition( unfilled_model.get() );
  
  d_unfilled_model = unfilled_model;
}

// Load the materials and fill the model
template<typename Material>
void StandardFilledParticleGeometryModel<Material>::loadMaterialsAndFillModel(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&
       atomic_relaxation_model_factory,
       const SimulationProperties& properties,
       const bool verbose_material_construction,
       const MaterialDefinitionDatabase& material_definitions,
       const Geometry::Model::CellIdMatIdMap& cell_id_mat_id_map,
       const Geometry::Model::CellIdDensityMap& cell_id_density_map )
{
  try{
    this->loadScatteringCenters( database_path,
                                 unique_scattering_center_names,
                                 scattering_center_definitions,
                                 atomic_relaxation_model_factory,
                                 properties,
                                 verbose_material_construction,
                                 d_scattering_center_name_map );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not load the requested scattering "
                           "centers!" );

  // Process the loaded scattering centers
  this->processLoadedScatteringCenters( d_scattering_center_name_map );

  // Create each material
  std::unordered_map<std::string,std::vector<Geometry::Model::EntityId> > material_name_cell_ids_map;
  
  Geometry::Model::CellIdMatIdMap::const_iterator
    cell_id_mat_id_it = cell_id_mat_id_map.begin();

  while( cell_id_mat_id_it != cell_id_mat_id_map.end() )
  {
    Geometry::Model::EntityId cell_id =
      cell_id_mat_id_it->first;

    typename MaterialType::MaterialId material_id =
      cell_id_mat_id_it->second;

    double density = cell_id_density_map.find( cell_id )->second.value();

    // Convert the atom density (1/cm^3) to the required units (1/b-cm)
    if( density > 0.0 )
      density *= 1e-24;

    std::string material_name =
      material_definitions.getMaterialName( material_id );

    material_name += "_";

    material_name += Utility::toString( density );

    if( d_material_name_map.find( material_name ) ==
        d_material_name_map.end() )
    {
      std::shared_ptr<const MaterialType>& new_material =
        d_material_name_map[material_name];

      const MaterialDefinitionDatabase::MaterialDefinitionArray&
        material_definition = material_definitions.getDefinition( material_id );

      std::vector<double> scattering_center_fractions( material_definition.size() );
      std::vector<std::string> scattering_center_names( material_definition.size() );

      for( size_t i = 0; i < material_definition.size(); ++i )
      {
        scattering_center_names[i] =
          Utility::get<0>( material_definition[i] );
        
        scattering_center_fractions[i] =
          Utility::get<1>( material_definition[i] );
      }

      new_material.reset( new MaterialType( material_id,
                                            density,
                                            d_scattering_center_name_map,
                                            scattering_center_fractions,
                                            scattering_center_names ) );
    }

    material_name_cell_ids_map[material_name].push_back( cell_id );
        
    ++cell_id_mat_id_it;
  }

  // Fill the geometry
  typename std::unordered_map<std::string,std::shared_ptr<const MaterialType> >::const_iterator
    material_name_it = d_material_name_map.begin();
  
  while( material_name_it != d_material_name_map.end() )
  {
    this->addMaterial( material_name_it->second,
                       material_name_cell_ids_map.find( material_name_it->first )->second );
    
    ++material_name_it;
  }
}

// Add a material to the collision kernel
template<typename Material>
void StandardFilledParticleGeometryModel<Material>::addMaterial(
                       const std::shared_ptr<const MaterialType>& material,
                       const std::vector<Geometry::Model::EntityId>&
                       cells_containing_material )
{
  // Make sure the material pointer is valid
  testPrecondition( material.get() );
  // Make sure the cells are valid
  testPrecondition( cells_containing_material.size() > 0 );

  for( size_t i = 0; i < cells_containing_material.size(); ++i )
  {
    TEST_FOR_EXCEPTION(
                 d_cell_id_material_map.find( cells_containing_material[i] ) !=
                 d_cell_id_material_map.end(),
                 std::logic_error,
                 "cell " << cells_containing_material[i] <<
                 " already has a material assigned!" );

    d_cell_id_material_map[cells_containing_material[i]] = material;
  }
}

// Get the material contained in a cell
template<typename Material>
auto StandardFilledParticleGeometryModel<Material>::getMaterial(
                         const Geometry::Model::EntityId cell ) const
  -> const std::shared_ptr<const MaterialType>&
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );

  TEST_FOR_EXCEPTION( this->isCellVoid( cell ),
                      std::runtime_error,
                      "Cell " << cell << " is void!" );
  
  return d_cell_id_material_map.find( cell )->second;
}

// Process loaded scattering centers
template<typename Material>
void StandardFilledParticleGeometryModel<Material>::processLoadedScatteringCenters(
                                               const ScatteringCenterNameMap& )
{ /* ... */ }

// Check if the entire model is void
template<typename Material>
bool StandardFilledParticleGeometryModel<Material>::isVoid() const
{
  return d_cell_id_material_map.empty();
}

// Check if a cell is void
template<typename Material>
bool StandardFilledParticleGeometryModel<Material>::isCellVoid(
                         const Geometry::Model::EntityId cell ) const
{
  return d_cell_id_material_map.find( cell ) == d_cell_id_material_map.end();
}

// Check if a cell is a termination cell
template<typename Material>
bool StandardFilledParticleGeometryModel<Material>::isTerminationCell(
                         const Geometry::Model::EntityId cell ) const
{
  return d_unfilled_model->isTerminationCell( cell );
}

// Get the total macroscopic cross section of a material
template<typename Material>
double StandardFilledParticleGeometryModel<Material>::getMacroscopicTotalCrossSection(
                                           const ParticleStateType& particle ) const
{
  return this->getMacroscopicTotalCrossSection( particle.getCell(),
                                                particle.getEnergy() );
}

// Get the total macroscopic cross section of a material
template<typename Material>
inline double StandardFilledParticleGeometryModel<Material>::getMacroscopicTotalCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
    return this->getMaterial(cell)->getMacroscopicTotalCrossSection( energy );
}

// Get the total macroscopic cross section of a material
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardFilledParticleGeometryModel<Material>::getMacroscopicTotalCrossSectionQuick(
                                           const ParticleStateType& particle ) const
{
  return this->getMacroscopicTotalCrossSectionQuick( particle.getCell(),
                                                     particle.getEnergy() );
}

// Get the total macroscopic cross section of a material
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
inline double StandardFilledParticleGeometryModel<Material>::getMacroscopicTotalCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );

  return this->getMaterial( cell )->getMacroscopicTotalCrossSection( energy );
}

// Get the total forward macroscopic cross section of a material
/*! \details When a distance must be converted to an optical path length only
 * use the macroscopic cross section returned from this method.
 */
template<typename Material>
double StandardFilledParticleGeometryModel<Material>::getMacroscopicTotalForwardCrossSection(
                                           const ParticleStateType& particle ) const
{
  return this->getMacroscopicTotalForwardCrossSection( particle.getCell(),
                                                       particle.getEnergy() );
}

// Get the total forward macroscopic cross section of a material
template<typename Material>
inline double StandardFilledParticleGeometryModel<Material>::getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
    return this->getMaterial(cell)->getMacroscopicTotalCrossSection( energy );
}

// Get the total forward macroscopic cross section of a material
/*! \details When a distance must be converted to an optical path length only
 * use the macroscopic cross section returned from this method. Before calling 
 * this method you must first check if the cell is void. Calling this method 
 * with a void cell is not allowed.
 */
template<typename Material>
double StandardFilledParticleGeometryModel<Material>::getMacroscopicTotalForwardCrossSectionQuick(
                                           const ParticleStateType& particle ) const
{
  return this->getMacroscopicTotalForwardCrossSectionQuick( particle.getCell(),
                                                            particle.getEnergy() );
}

// Get the total forward macroscopic cross section of a material
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
inline double StandardFilledParticleGeometryModel<Material>::getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );
  
  return this->getMaterial( cell )->getMacroscopicTotalCrossSection( energy );
}

// Get the macroscopic reaction cross section for a specific reaction
template<typename Material>
double StandardFilledParticleGeometryModel<Material>::getMacroscopicReactionCrossSection(
                                        const ParticleStateType& particle,
                                        const ReactionEnumType reaction ) const
{
  return this->getMacroscopicReactionCrossSection( particle.getCell(),
                                                   particle.getEnergy(),
                                                   reaction );
}

// Get the macroscopic reaction cross section for a specific reaction
template<typename Material>
double StandardFilledParticleGeometryModel<Material>::getMacroscopicReactionCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy,
                                const ReactionEnumType reaction ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
  {
    return this->getMaterial( cell )->getMacroscopicReactionCrossSection(
                                                            energy, reaction );
  }
}

// Get the macroscopic reaction cross section for a specific reaction
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardFilledParticleGeometryModel<Material>::getMacroscopicReactionCrossSectionQuick(
                                        const ParticleStateType& particle,
                                        const ReactionEnumType reaction ) const
{
  return this->getMacroscopicReactionCrossSectionQuick( particle.getCell(),
                                                        particle.getEnergy(),
                                                        reaction );
}

// Get the macroscopic reaction cross section for a specific reaction
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardFilledParticleGeometryModel<Material>::getMacroscopicReactionCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy,
                                const ReactionEnumType reaction ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );
  
  return this->getMaterial( cell )->getMacroscopicReactionCrossSection(
                                                            energy, reaction );
}

// Get the unfilled model
template<typename Material>
const Geometry::Model& StandardFilledParticleGeometryModel<Material>::getUnfilledModel() const
{
  return *d_unfilled_model;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_FILLED_PARTICLE_GEOMETRY_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFilledParticleGeometryModel.hpp
//---------------------------------------------------------------------------//
