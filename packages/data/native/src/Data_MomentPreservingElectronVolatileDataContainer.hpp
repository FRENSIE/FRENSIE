//---------------------------------------------------------------------------//
//!
//! \file   Data_MomentPreservingElectronVolatileDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native moment preserving elastic electron volatile data container class
//!
//---------------------------------------------------------------------------//

#ifndef DATA_MOMENT_PRESERVING_ELECTRON_VOLATILE_DATA_CONTAINER_HPP
#define DATA_MOMENT_PRESERVING_ELECTRON_VOLATILE_DATA_CONTAINER_HPP

// FRENSIE Includes
#include "Data_MomentPreservingElectronDataContainer.hpp"

namespace Data{

//! The moment preserving elastic electron volatile data container
class MomentPreservingElectronVolatileDataContainer : public MomentPreservingElectronDataContainer
{

public:

  //! Default constructor
  MomentPreservingElectronVolatileDataContainer();

  //! Constructor (from saved archive)
  MomentPreservingElectronVolatileDataContainer(
		   const std::string& archive_name,
		   const Utility::ArchivableObject::ArchiveType archive_type );

  // Add the setter member functions to the public interface
  using MomentPreservingElectronDataContainer::setAtomicNumber;
  using MomentPreservingElectronDataContainer::setCutoffAngleCosine;
  using MomentPreservingElectronDataContainer::setElasticAngularEnergyGrid;
  using MomentPreservingElectronDataContainer::setNumberOfDiscreteAngles;
  using MomentPreservingElectronDataContainer::setMomentPreservingDiscreteAngles;
  using MomentPreservingElectronDataContainer::setMomentPreservingWeights;
/*
  using MomentPreservingElectronDataContainer::setElectronEnergyGrid;
  using MomentPreservingElectronDataContainer::setMomentPreservingMomentPreservingCrossSection;
  using MomentPreservingElectronDataContainer::setMomentPreservingMomentPreservingCrossSectionThresholdEnergyIndex;
*/
  // Add the export member function to the public interface
  using MomentPreservingElectronDataContainer::exportData;

  // Add the packDataInString member function to the public interface
  using MomentPreservingElectronDataContainer::packDataInString;
};

} // end Data namespace

#endif // end DATA_MOMENT_PRESERVING_ELECTRON_VOLATILE_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

