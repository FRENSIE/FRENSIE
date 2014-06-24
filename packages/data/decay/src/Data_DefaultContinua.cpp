//---------------------------------------------------------------------------//
//!
//! \file   Data_DefaultContinua.cpp
//! \author CJ Solomon
//! \brief  Default Coninua
//!
//---------------------------------------------------------------------------//

#include "Data_DefaultContinua.hpp"

namespace data {

std::map<int,Histogram> DefaultContinua::m_default_continua = boost::assign::map_list_of
  ( endf::decay::BREMS,    Histogram(0.0,20.0,1000) )
  ( endf::decay::GAMMA,    Histogram(0.0,20.0,1000) )
  ( endf::decay::BETAM,    Histogram(0.0,20.0,1000) )
  ( endf::decay::BETAP,    Histogram(0.0,20.0,1000) )
  ( endf::decay::ALPHA,    Histogram(0.0,20.0,1000) )
  ( endf::decay::NEUTRON,  Histogram(1e-10,100,1000,true))
  ( endf::decay::PROTON,   Histogram(0.0,20.0,1000) )
  ( endf::decay::ELECTRON, Histogram(0.0,20.0,1000) )
  ( endf::decay::XRAY,     Histogram(0.0,20.0,1000) );

void DefaultContinua::SetDefaultContinuum(const int& pt, const Histogram& continuum) {
  m_default_continua[pt] = continuum;
}

Histogram DefaultContinua::GetDefaultContinuum(const int& pt) {
  return m_default_continua.at(pt);
}

} // End namespace data

//---------------------------------------------------------------------------//
// end Data_DefaultContinua.cpp
//---------------------------------------------------------------------------//
