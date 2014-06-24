//---------------------------------------------------------------------------//
//!
//! \file   Data_WattSpectrum.hpp
//! \author CJ Solomon
//! \brief  Watt Spectrum
//!
//---------------------------------------------------------------------------//

#ifndef DATA_WATT_SPECTRUM_HPP
#define DATA_WATT_SPECTRUM_HPP

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Data_ProbDistFunc.hpp"

namespace data {

class WattSpectrum : public ProbDistFunc {
public:
  WattSpectrum() {};
  WattSpectrum(double a, double b);

  double pdf(double x);
  double cdf(double x);

private:
  double m_a;
  double m_b;
  double m_norm;

  // boost serialization stuff
  friend class boost::serialization::access;
  template< class Archive >
  void serialize( Archive& ar, const unsigned int version ) {
    ar & boost::serialization::make_nvp("a",m_a);
    ar & boost::serialization::make_nvp("b",m_b);
    ar & boost::serialization::make_nvp("norm",m_norm);
  }

};

} // end namespace data

// namespace boost { namespace serialization {
// 
// using namespace isc;
// 
// template<class Archive>
// inline void save_construct_data(Archive& ar, const WattSpectrum* t, const unsigned int version) {
//   ar << make_nvp("a",t->m_a);
//   ar << make_nvp("b",t->m_b);
// }
// 
// template<class Archive>
// inline void load_construct_data(Archive& ar, WattSpectrum* t, const unsigned int version) {
//   double a,b;
//   ar >> make_nvp("a",a);
//   ar >> make_nvp("b",b);
// 
//   ::new(t)WattSpectrum(a,b));
// }
// 
// }} // end namespace boost::serialization

#endif // DATA_WATT_SPECTRUM_HPP

//---------------------------------------------------------------------------//
// end Data_WattSpectrum.hpp
//---------------------------------------------------------------------------//
