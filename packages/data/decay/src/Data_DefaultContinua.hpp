//---------------------------------------------------------------------------//
//!
//! \file   Data_DefaultContinua.cpp
//! \author CJ Solomon
//! \brief  Default Coninua
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DEFAULT_CONTINUA_HPP
#define DATA_DEFAULT_CONTINUA_HPP

#include<map>

#include<boost/assign.hpp>

#include "Data_ENDFConsts.hpp"
#include "Data_Histogram.hpp"

namespace data {

class DefaultContinua {
public:
  static void SetDefaultContinuum(const int& pt, const Histogram& continuum);

  static Histogram GetDefaultContinuum(const int& pt);

protected:
  DefaultContinua();

private:
  static std::map<int,Histogram> m_default_continua;
};

} // end namespace data

#endif // DATA_DEFAULT_CONTINUA_HPP

//---------------------------------------------------------------------------//
// end Data_DefaultContinua.hpp
//---------------------------------------------------------------------------//
