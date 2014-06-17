//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayLib.cpp
//! \author CJ Solomon
//! \brief  Decay Library
//!
//---------------------------------------------------------------------------//

#include "Data_DecayLib.hpp"

namespace data {

DecayLib::DecayLib() {}

DecayLib::DecayLib(const DecayFile& df) {
  UnpackString( df.PackString() );
}

void DecayLib::UnpackString( std::string df_packed_string ) {
  std::stringstream ss;

  ss.str(df_packed_string);

  boost::archive::binary_iarchive ar(ss);

  ar & m_decay_data;
}

std::vector<unsigned int> DecayLib::GetSZAs() const {
  std::vector<unsigned int> retval;
  for(std::map<unsigned int, DecayData>::const_iterator it=m_decay_data.begin(); it != m_decay_data.end(); it++) {
    retval.push_back(it->first);
  }
  return retval;
}

DecayData DecayLib::GetDecayData(const unsigned int& sza) const {
  DecayData retval;
  if( m_decay_data.find(sza) != m_decay_data.end() ) {
    retval = m_decay_data.at(sza);
  }
  return retval;
}

std::set<unsigned int> DecayLib::GetAllDaughters(const unsigned int& sza) const {
  std::set<unsigned int> retval;

  for(unsigned int i=0; i<GetDecayData(sza).GetNumber(); i++) {
    unsigned int daughter = m_decay_data.at(sza).GetDaughter(i);
    if( daughter > 0 ) { // filter out 0 daughter values
      retval.insert( daughter );
    }

    if( m_decay_data.find(daughter) != m_decay_data.end() ) {
      std::set<unsigned int> tmp = GetAllDaughters( daughter );
      retval.insert(tmp.begin(), tmp.end());
    }
  }

  return retval;
}

std::map<unsigned int, double> DecayLib::UnitDecay(const unsigned int& sza, const double& t, std::vector<double> p_lambdas) const {
  std::map<unsigned int, double> retval;

  const DecayData dd = GetDecayData(sza);

  std::vector<double> lambdas = p_lambdas;
  double decay_const = dd.GetDecayConst();
  lambdas.push_back( decay_const );

  double sum = 0.0;
  for(unsigned int i=0; i<lambdas.size(); i++) {
    double prod = 1.0;
    for(unsigned int j=0; j<lambdas.size(); j++) {
      if(j!=i) {
        prod *= (lambdas[j] > 0.0 ? lambdas[j] : 1.0)/(lambdas[j]-lambdas[i]);
      }
    }

    sum += (lambdas[i] > 0.0 ? lambdas[i] : 1.0 )*prod*exp(-lambdas[i]*t);
  }

  double value = sum / (decay_const > 0.0 ? decay_const : 1.0 );
  retval[sza] = value > 0.0 ? value : 0.0;

  for(unsigned int i=0; i<dd.GetNumber(); i++) {
    unsigned int daughter = dd.GetDaughter(i);
    if( daughter == 0 ) // filter out SF
      continue;

    std::map<unsigned int,double> dret = UnitDecay(daughter, t, lambdas);
    for(std::map<unsigned int,double>::iterator it=dret.begin(); it!=dret.end(); it++) {
      if( retval.find(it->first) == retval.end() ) {
        retval[it->first] = it->second * dd.GetBranchingRatio(i);
      }
      else {
        retval[it->first] += it->second * dd.GetBranchingRatio(i);
      }
    }
  }

  return retval;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_DecayLib.cpp
//---------------------------------------------------------------------------//
