//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayData.cpp
//! \author CJ Solomon
//! \brief  Decay Data
//!
//---------------------------------------------------------------------------//

#include "Data_DecayData.hpp"

namespace data {

DecayData::DecayData() {
  m_z = 0; m_a = 0; m_z = 0;
  m_half_life=0.0; m_half_life_err=0.0;
  m_decay_const=0.0; m_decay_const_err=0.0;
}

DecayData::DecayData(unsigned int z, unsigned int a, unsigned int s) {
  m_z = z; m_a = a; m_s = s;
  m_half_life=0.0; m_half_life_err=0.0;
  m_decay_const=0.0; m_decay_const_err=0.0;
}

void DecayData::SetZ(unsigned int z) {
  m_z = z;
}

void DecayData::SetA(unsigned int a) {
  m_a = a;
}

void DecayData::SetS(unsigned int s) {
  m_s = s;
}

void DecayData::SetHalfLife(double hl, double hl_err) {
  m_half_life = hl;
  m_half_life_err = hl_err;
  m_decay_const = std::log(2.0)/m_half_life;
  m_decay_const_err = std::sqrt( std::pow( std::log(2.0)/std::pow(m_half_life,2), 2 ) * std::pow(m_half_life_err,2) );
}

void DecayData::InsertDecayData(unsigned int dsza, unsigned int rtyp, double br, double br_err) {
  DecayDataStruct dd;
  dd.m_daughter = dsza;
  dd.m_decay_type = rtyp;
  dd.m_branching_ratio = br;
  dd.m_branching_ratio_err = br_err;

  m_decay_data.push_back(dd);
}

unsigned int DecayData::GetZ() const {
  return m_z;
}

unsigned int DecayData::GetA() const {
  return m_a;
}

unsigned int DecayData::GetS() const {
  return m_s;
}

double DecayData::GetHalfLife() const {
  return m_half_life;
}

double DecayData::GetHalfLifeErr() const {
  return m_half_life_err;
}

double DecayData::GetDecayConst() const {
  return m_decay_const;
}

double DecayData::GetDecayConstErr() const {
  return m_decay_const_err;
}

unsigned int DecayData::GetNumber() const { 
  return m_decay_data.size();
}

double DecayData::GetBranchingRatio(unsigned int n) const {
  return m_decay_data.at(n).m_branching_ratio;
}

double DecayData::GetBranchingRatioErr(unsigned int n) const {
  return m_decay_data.at(n).m_branching_ratio_err;
}

unsigned int DecayData::GetDaughter(unsigned int n) const {
  return m_decay_data.at(n).m_daughter;
}

unsigned int DecayData::GetDecayType(unsigned int n) const {
  return m_decay_data.at(n).m_decay_type;
}

unsigned int DecayData::GetPrimaryDecayType(unsigned int n) const {
  unsigned int dt = m_decay_data.at(n).m_decay_type;
  while( dt / 10 > 0 ) {
    dt /= 10;
  }
  return dt;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_DecayData.cpp
//---------------------------------------------------------------------------//
