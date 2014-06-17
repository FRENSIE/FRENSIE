//---------------------------------------------------------------------------//
//!
//! \file   Data_MCNPConsts.cpp
//! \author CJ Solomon
//! \brief  MCNP Constants
//!
//---------------------------------------------------------------------------//

#ifndef DATA_MCNP_CONSTS_HPP
#define DATA_MCNP_CONSTS_HPP

#include <map>
#include <string>
#include <boost/bimap.hpp>
#include <boost/assign.hpp>

#include "Data_ENDFConsts.hpp"

namespace data {

namespace mcnp {

enum ParticleType {
  NEUTRON=1,
  PHOTON=2,
  BREMS=-2,
  ELECTRON=3,
  POSITRON=8,
  PROTON=9,
  ALPHA=34
};

typedef boost::bimap<int, std::string> mcnp_ParticleType_bimap;

static const mcnp_ParticleType_bimap particles = boost::assign::list_of< mcnp_ParticleType_bimap::relation>
  (NEUTRON, "n")
  (PHOTON,  "p")
  (BREMS,   "brems")
  (ELECTRON, "e")
  (POSITRON, "f")
  (PROTON, "h")
  (ALPHA, "a");

} // end namespace mcnp

typedef std::map<endf::decay::DecayTyp,mcnp::ParticleType> endfdecay_mcnp_map;

static const endfdecay_mcnp_map endfdecay2mcnp = boost::assign::map_list_of
  (endf::decay::BREMS     , mcnp::BREMS)
  (endf::decay::GAMMA     , mcnp::PHOTON)
  (endf::decay::BETAM     , mcnp::ELECTRON)
  (endf::decay::BETAP     , mcnp::POSITRON)
  (endf::decay::ALPHA     , mcnp::ALPHA)
  (endf::decay::NEUTRON   , mcnp::NEUTRON)
  (endf::decay::PROTON    , mcnp::PROTON)
  (endf::decay::ELECTRON  , mcnp::ELECTRON)
  (endf::decay::XRAY      , mcnp::PHOTON);

} // end namespace data

#endif // DATA_MCNP_CONSTS_HPP

//---------------------------------------------------------------------------//
// end Data_MCNPConsts.cpp
//---------------------------------------------------------------------------//
