//---------------------------------------------------------------------------//
//!
//! \file   Data_SoftElasticElectronVolatileDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native soft elastic electron volatile data container class
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SOFT_ELASTIC_ELECTRON_VOLATILE_DATA_CONTAINER_HPP
#define DATA_SOFT_ELASTIC_ELECTRON_VOLATILE_DATA_CONTAINER_HPP

// FRENSIE Includes
#include "Data_SoftElasticElectronDataContainer.hpp"

namespace Data{

//! The soft elastic electron volatile data container
class SoftElasticElectronVolatileDataContainer : public SoftElasticElectronDataContainer
{

public:

  //! Default constructor
  SoftElasticElectronVolatileDataContainer();

  //! Constructor (from saved archive)
  SoftElasticElectronVolatileDataContainer(
		   const std::string& archive_name,
		   const Utility::ArchivableObject::ArchiveType archive_type );

  // Add the setter member functions to the public interface
  using SoftElasticElectronDataContainer::setAtomicNumber;
  using SoftElasticElectronDataContainer::setCutoffAngleCosine;
  using SoftElasticElectronDataContainer::setElasticAngularEnergyGrid;
  using SoftElasticElectronDataContainer::setNumberOfDiscreteAngles;
  using SoftElasticElectronDataContainer::setSoftElasticDiscreteAngles;
  using SoftElasticElectronDataContainer::setSoftElasticWeights;
  using SoftElasticElectronDataContainer::setElectronEnergyGrid;
  using SoftElasticElectronDataContainer::setMomentPreservingSoftElasticCrossSection;
  using SoftElasticElectronDataContainer::setMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex;

  // Add the export member function to the public interface
  using SoftElasticElectronDataContainer::exportData;

  // Add the packDataInString member function to the public interface
  using SoftElasticElectronDataContainer::packDataInString;
};

} // end Data namespace

#endif // end DATA_SOFT_ELASTIC_ELECTRON_VOLATILE_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_SoftElasticElectronVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

