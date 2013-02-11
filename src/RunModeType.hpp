#ifndef RUN_MODE_TYPE_HPP
#define RUN_MODE_TYPE_HPP

namespace FAPMC{

//! Rum mode type enumeration
enum RunModeType{
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
extern const char* const RunModeTypeStr[];

} // end namespace FAPMC

#endif // end RUN_MODE_TYPE_HPP

//---------------------------------------------------------------------------//
// end RunModeType.hpp
//---------------------------------------------------------------------------//

  
