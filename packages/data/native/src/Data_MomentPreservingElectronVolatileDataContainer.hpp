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
                          const boost::filesystem::path& file_name_with_path );

  // Add the setter member functions to the public interface
  using MomentPreservingElectronDataContainer::setAtomicNumber;
  using MomentPreservingElectronDataContainer::setCutoffAngleCosine;
  using MomentPreservingElectronDataContainer::setElasticAngularEnergyGrid;
  using MomentPreservingElectronDataContainer::setNumberOfDiscreteAngles;
  using MomentPreservingElectronDataContainer::setMomentPreservingDiscreteAngles;
  using MomentPreservingElectronDataContainer::setMomentPreservingWeights;
};

} // end Data namespace

#endif // end DATA_MOMENT_PRESERVING_ELECTRON_VOLATILE_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

