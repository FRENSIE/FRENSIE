//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDFConsts.hpp
//! \author CJ Solomon
//! \brief  ENDF Constants
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDF_CONSTS_HPP
#define DATA_ENDF_CONSTS_HPP

#include <string>
#include <boost/bimap.hpp>
#include <boost/assign.hpp>

namespace data {

namespace endf {

namespace interp {

enum interp_method {
  HISTOGRAM=1,
  LINLIN=2,
  LINLOG=3,
  LOGLIN=4,
  LOGLOG=5
};

} // end namespace interp

namespace decay {

enum DecayTyp {
  BREMS=-1, // augmented for LIBISC
  GAMMA=0,
  BETAM=1,
  BETAP=2,
  IT=3,
  ALPHA=4,
  NEUTRON=5,
  SF=6,
  PROTON=7,
  ELECTRON=8,
  XRAY=9,
  UNKNOWN=10
};

typedef boost::bimap<int, std::string> DecayTyp_bimap;

static const DecayTyp_bimap rtyp = boost::assign::list_of< DecayTyp_bimap::relation>
  (GAMMA, "gamma")
  (BETAM, "beta-")
  (BETAP, "beta+")
  (IT, "IT")
  (ALPHA, "alpha")
  (NEUTRON, "neutron")
  (SF, "SF")
  (PROTON, "proton")
  (UNKNOWN, "unknown");

static const DecayTyp_bimap styp = boost::assign::list_of< DecayTyp_bimap::relation>
  (GAMMA, "gamma")
  (BETAM, "beta-")
  (BETAP, "beta+")
  (ALPHA, "alpha")
  (NEUTRON, "neutron")
  (SF, "SF")
  (PROTON, "proton")
  (ELECTRON, "electron")
  (XRAY, "x-ray");

} // end namespace decay

} // end namespace endf

} // end namespace data

#endif // DATA_ENDF_CONSTS_HPP

//---------------------------------------------------------------------------//
// end Data_ENDFConsts.hpp
//---------------------------------------------------------------------------//
