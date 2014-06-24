//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayData.hpp
//! \author CJ Solomon
//! \brief  Decay Data
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_DATA_HPP
#define DATA_DECAY_DATA_HPP

#include <cmath>
#include <vector>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>

namespace data {

class DecayData {
public:
  DecayData();

  DecayData(unsigned int z, unsigned int a, unsigned int s=0);

  void SetZ(unsigned int z);
  void SetA(unsigned int a);
  void SetS(unsigned int s);

  void SetHalfLife(double hl, double hl_err=0.0);

  void InsertDecayData(unsigned int dsza, unsigned int rtyp, double br, double br_err=0.0);

  unsigned int GetZ() const;
  unsigned int GetA() const;
  unsigned int GetS() const;

  double GetHalfLife() const;
  double GetHalfLifeErr() const;
  double GetDecayConst() const;
  double GetDecayConstErr() const;

  unsigned int GetNumber() const;
  double GetBranchingRatio(unsigned int n) const;
  double GetBranchingRatioErr(unsigned int n) const;
  unsigned int GetDaughter(unsigned int n) const;
  unsigned int GetDecayType(unsigned int n) const;
  unsigned int GetPrimaryDecayType(unsigned int n) const;

private:
  unsigned int m_z, m_a, m_s;
  double m_half_life;
  double m_half_life_err;
  double m_decay_const;
  double m_decay_const_err;

  struct DecayDataStruct {
    double m_branching_ratio;
    double m_branching_ratio_err;
    unsigned int m_daughter;
    unsigned int m_decay_type;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
      using namespace boost::serialization;
      ar & make_nvp("branching_ratio", m_branching_ratio);
      ar & make_nvp("branching_ratio_err", m_branching_ratio_err);
      ar & make_nvp("daughter", m_daughter);
      ar & make_nvp("decay_type", m_decay_type);
    };
  };

  std::vector<DecayDataStruct> m_decay_data;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    using namespace boost::serialization;
    
    ar & make_nvp("z",m_z);
    ar & make_nvp("a",m_a);
    ar & make_nvp("s",m_s);
    ar & make_nvp("half_life", m_half_life);
    ar & make_nvp("half_life_err", m_half_life_err);
    ar & make_nvp("decay_const", m_decay_const);
    ar & make_nvp("decay_const_err", m_decay_const_err);
    ar & make_nvp("decay_data",m_decay_data);
  } 
};

} // Ends namespace data

#endif // DATA_DECAY_DATA_HPP

//---------------------------------------------------------------------------//
// end Data_DecayData.hpp
//---------------------------------------------------------------------------//
