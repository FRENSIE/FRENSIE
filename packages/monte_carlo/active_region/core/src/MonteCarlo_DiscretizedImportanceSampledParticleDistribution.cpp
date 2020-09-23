//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DiscretizedImportanceSampledParticleDistribution.cpp
//! \author Philip Britt
//! \brief  Discretized Importance Sampled Particle distribution class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DiscretizedImportanceSampledParticleDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "MonteCarlo_PhaseSpacePoint.hpp"

namespace MonteCarlo{

  // Constructor (without specifics of which mesh elements are to be considered source)
  DiscretizedImportanceSampledParticleDistribution::DiscretizedImportanceSampledParticleDistribution( const std::string& name,
                                                                                                      const std::shared_ptr<const Utility::Mesh>& mesh,
                                                                                                      const std::vector<double>& energy_bin_bounds,
                                                                                                      const std::shared_ptr<const Utility::PQLAQuadrature>& direction_discretization)
  :ParticleDistribution(name),
   d_mesh(mesh),
   d_direction_discretization(direction_discretization),
   d_energy_discretization_boundaries(energy_bin_bounds),
  { 
    this->initializeIntegratorPoint();
  }

  // Constructor (with specifics of which mesh elements are to be considered source)
  DiscretizedImportanceSampledParticleDistribution::DiscretizedImportanceSampledParticleDistribution(const std::string& name,
                                                   const std::shared_ptr<const Utility::Mesh>& mesh,
                                                   const std::vector<Utility::Mesh::ElementHandle>& mesh_source_elements,
                                                   const std::vector<double>& energy_bin_bounds,
                                                   const std::shared_ptr<const Utility::PQLAQuadrature>& direction_discretization)
  :ParticleDistribution(name),
   d_mesh(mesh),
   d_mesh_space_histogram_conversion_vector(mesh_source_elements),
   d_direction_discretization(direction_discretization),
   d_energy_discretization_boundaries(energy_bin_bounds)
  { 
    this->initializeIntegratorPoint();
  } 

  void DiscretizedImportanceSampledParticleDistribution::setEnergyDistribution( const std::shared_ptr<PhaseSpaceDimensionDistribution>& dimension_distribution)
  {
    // Make sure this is an energy distribution being set
    testPrecondition(dimension_distribution->getDimension() == PhaseSpaceDimension::ENERGY_DIMENSION);
    // This class assumes all independent distributions for simplicity
    testPrecondition(dimension_distribution->isIndependent());

    d_actual_energy_distribution = dimension_distribution;

    this->initializeIntegratedDistributions();
  }

  std::string DiscretizedImportanceSampledParticleDistribution::getDimensionDistributionTypeName( const PhaseSpaceDimension dimension ) const
  {

  }

  bool DiscretizedImportanceSampledParticleDistribution::isSpatiallyUniform() const
  {

  }
  
  bool DiscretizedImportanceSampledParticleDistribution::isDirectionallyUniform() const
  {

  }

  void DiscretizedImportanceSampledParticleDistribution::initializeDimensionCounters( DiscretizedImportanceSampledParticleDistribution::DimensionCounterMap& trials ) const
  {

  }

  double DiscretizedImportanceSampledParticleDistribution::evaluate( const ParticleState& particle ) const
  {

  }

  void DiscretizedImportanceSampledParticleDistribution::sample( ParticleState& particle ) const
  {

  }

  void DiscretizedImportanceSampledParticleDistribution::sampleAndRecordTrials( ParticleState& particle,
                                                                                DiscretizedImportanceSampledParticleDistribution::DimensionCounterMap& trials ) const
  {

  }

  void DiscretizedImportanceSampledParticleDistribution::sampleWithDimensionValue( ParticleState& particle,
                                                                                   const PhaseSpaceDimension dimension,
                                                                                   const double dimension_value ) const
  {

  }

  void  DiscretizedImportanceSampledParticleDistribution::sampleWithDimensionValueAndRecordTrials(
                                      ParticleState& particle,
                                      DiscretizedImportanceSampledParticleDistribution::DimensionCounterMap& trials,
                                      const PhaseSpaceDimension dimension,
                                      const double dimension_value ) const
  {

  }
  
  void DiscretizedImportanceSampledParticleDistribution::initializeIntegratedDistributions()
  {
    // Make sure necessary distribution information exists
    testPrecondition(d_mesh && d_direction_discretization && d_actual_energy_distribution)
    
    // The integrator object being used
    std::shared_ptr<Utility::GaussKronrodIntegrator> integrator_ptr = std::make_shared<Utility::GaussKronrodIntegrator>(0.001);

    // Will hold the actual histogram bin values for the histogram being formed
    std::vector<double> energy_bin_values;

    std::function<double(double)> integrand = this->integrationHelper;
    // First find integrated energy PDF
    for(unsigned energy_bin = 0; energy_bin < d_energy_discretization_boundaries.size() - 1; ++energy_bin)
    {
      double result;
      double absolute_error;
      integrator_ptr->integrateAdaptively( integrand ,
                                          d_energy_discretization_boundaries(energy_bin),
                                          d_energy_discretization_boundaries(energy_bin + 1),
                                          result,
                                          absolute_error);
      energy_bin_values.push_back(result);
    }

    // Form actual integrated histogram
    // The histogram bin values
    std::vector<double> bin_values;
    bin_values.resize(d_mesh->getNumberOfElements()*energy_bin_values.size()*d_direction_discretization->getNumberOfTriangles())

    // The way this is constructed, bin boundaries are irrelevant so long as the widths for every bin are equal.
    std::vector<double> bin_boundaries;
    bin_boundaries.resize(bin_values.size()+1);

    // Determine the number of spatial elements being iterated over
    size_t source_mesh_size;
    bool is_conversion_vector_empty = d_mesh_space_histogram_conversion_vector.isEmpty();
    if( !is_conversion_vector_empty)
    {
      source_mesh_size = d_mesh_space_histogram_conversion_vector.size();
    }
    else
    {
      source_mesh_size = d_mesh->getNumberOfElements();
    }

    for(size_t mesh_element = 0; mesh_element < source_mesh_size; ++mesh_element)
    {
      for(size_t energy_element = 0; energy_element < energy_bin_values.size(); ++energy_element)
      {
        for(size_t direction_element = 0; direction_element < d_direction_discretization->getNumberOfTriangles(); ++direction_element)
        {
          size_t index = mesh_element*(energy_bin_values.size()*d_direction_discretization->getNumberOfTriangles())
                        +energy_element*(d_direction_discretization->getNumberOfTriangles());
                        +direction_element;
          size_t actual_mesh_index;
          if(!is_conversion_vector_empty)
          {
            actual_mesh_index = d_mesh_space_histogram_conversion_vector[mesh_element];
          }
          else
          {
            actual_mesh_index = mesh_element;
          }
          bin_values[index] = d_mesh->getElementVolume(actual_mesh_index) * 
                              energy_bin_values[energy_element] * 
                              d_direction_discretization->getTriangleArea(direction_element);
          // Bin widths are just 1.0
          bin_boundaries[index] = static_cast<double> index;
          
        }
      }
    }

    bin_boundaries.push_back(bin_boundaries.back() + 1.0;


  }

  double DiscretizedImportanceSampledParticleDistribution::integrationHelper(double energy)
  {
    d_integrator_point->setEnergyCoordinate(energy);

    return d_actual_energy_distribution->evaluateWithoutCascade( d_integrator_point );
  }

  void DiscretizedImportanceSampledParticleDistribution::initializeIntegratorPoint()
  {
    d_integrator_point = std::make_shared<PhaseSpacePoint>( std::make_shared<Utility::CartesianSpatialCoordinateConversionPolicy>(),
                                                            std::make_shared<Utility::CartesianDirectionalCoordinateConversionPolicy>() );
  }
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DiscretizedImportanceSampledParticleDistribution.cpp
//---------------------------------------------------------------------------//
