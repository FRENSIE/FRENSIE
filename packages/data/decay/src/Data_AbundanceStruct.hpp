//---------------------------------------------------------------------------//
//!
//! \file   Data_AbundanceStruct.hpp
//! \author CJ Solomon
//! \brief  Abundance Structure 
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ABUNDANCE_STRUCT_HPP
#define DATA_ABUNDANCE_STRUCT_HPP

#include <boost/serialization/nvp.hpp>

namespace data {

struct AbundanceStruct {
  double m_mass;
  double m_abundance;

  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("mass", m_mass);
    ar & make_nvp("abundance", m_abundance);
  };
};

} // end namespace data

#endif // DATA_ABUNDANCE_STRUCT_HPP

//---------------------------------------------------------------------------//
// end Data_AbundanceStruct.hpp
//---------------------------------------------------------------------------//
