//---------------------------------------------------------------------------//
// \file RunMode.hpp
// \author Alex Robinson
// \brief Run mode enumeration
//---------------------------------------------------------------------------//

#ifndef RUN_MODE_HPP
#define RUN_MODE_HPP

namespace FACEMC{

//! Rum mode type enumeration
enum RunMode{
  NEUTRON_MODE,
  PHOTON_MODE,
  ELECTRON_MODE,
  NEUTRON_PHOTON_MODE,
  PHOTON_ELECTRON_MODE,
  NEUTRON_PHOTON_ELECTRON_MODE,
  ADJOINT_NEUTRON_MODE,
  ADJOINT_PHOTON_MODE,
  ADJOINT_ELECTRON_MODE,
  ADJOINT_NEUTRON_ADJOINT_PHOTON_MODE,
  ADJOINT_PHOTON_ADJOINT_ELECTRON_MODE,
  ADJOINT_NEUTRON_ADJOINT_PHOTON_ADJOINT_ELECTRON_MODE,
  NEUTRON_ADJOINT_NEUTRON_MODE,
  PHOTON_ADJOINT_PHOTON_MODE,
  ELECTRON_ADJOINT_ELECTRON_MODE
};

//! Run mode type string
extern const char* const RunModeStr[];

} // end FACEMC namespace

#endif // end RUN_MODE_HPP

//---------------------------------------------------------------------------//
// end RunMode.hpp
//---------------------------------------------------------------------------//

  
