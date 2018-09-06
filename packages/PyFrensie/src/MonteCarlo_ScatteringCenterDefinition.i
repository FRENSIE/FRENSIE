//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScatteringCenterDefinition.i
//! \author Luke Kersting
//! \brief  The ScatteringCenterDefinition class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_ScatteringCenterDefinition.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"

using namespace MonteCarlo;
%}

//---------------------------------------------------------------------------//
// Add ScatteringCenterDefinition support
//---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::ScatteringCenterDefinition);

%include "MonteCarlo_ScatteringCenterDefinition.hpp"

// Add some useful methods to the ScatteringCenterDefinition class
%extend MonteCarlo::ScatteringCenterDefinition
{
  // Get the atomic weight of the PhotoatomicDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getPhotoatomicDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getPhotoatomicDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight of the AdjointPhotoatomicDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getAdjointPhotoatomicDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getAdjointPhotoatomicDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight of the ElectroatomicDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getElectroatomicDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getElectroatomicDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight of the AdjointElectroatomicDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getAdjointElectroatomicDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getAdjointElectroatomicDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight ratio of the NuclearDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getNuclearDataAtomicWeightRatio() const
  {
    double atomic_weight_ratio;
    $self->getNuclearDataProperties(&atomic_weight_ratio);
    return atomic_weight_ratio;
  }

  // Get the atomic weight ratio of the AdjointNuclearDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getAdjointNuclearDataAtomicWeightRatio() const
  {
    double atomic_weight_ratio;
    $self->getAdjointNuclearDataProperties(&atomic_weight_ratio);
    return atomic_weight_ratio;
  }

  // Get the atomic weight of the PhotonuclearDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getPhotonuclearDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getPhotonuclearDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight of the AdjointPhotonuclearDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getAdjointPhotonuclearDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getAdjointPhotonuclearDataProperties(&atomic_weight);
    return atomic_weight;
  }

};

//---------------------------------------------------------------------------//
// Add ScatteringCenterDefinitionDatabase support
//---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::ScatteringCenterDefinitionDatabase);

%include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"


// //---------------------------------------------------------------------------//
// // end MonteCarlo_ScatteringCenterDefinition.i
// //---------------------------------------------------------------------------//
