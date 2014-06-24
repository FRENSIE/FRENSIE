//---------------------------------------------------------------------------//
//!
//! \file   Data_Histogram.hpp
//! \author CJ Solomon
//! \brief  Histogram
//!
//---------------------------------------------------------------------------//

#ifndef DATA_HISTOGRAM_HPP
#define DATA_HISTOGRAM_HPP

#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include <boost/serialization/nvp.hpp>

namespace data {

class Histogram {
public:
  Histogram();
  //! Construct a Histogram from a lower bound, an upper bound, and the number of bins and initialize to zero
  Histogram(const double&, const double& ,const int&, bool islog=false);
  //! Construct a Histogram from a lower bound, an upper bound, and the number of bins and initialize to value
  Histogram(const double&, const double&, const int&, const double&, bool islog=false);
  //! Construct a Histogram from a vector of doubles and initialize to zero
  Histogram(const std::vector<double>&);
  //! Construct a Histogram from a vector of doubles and initialize values to given value
  Histogram(const std::vector<double>&, const double&);
  //! Construct a Histogram from a vector of doubles and initialize values and errors to given values
  Histogram(const std::vector<double>&, const double&, const double&);
  //! Construct a Histogram from a vector of doubles and initialize values to another vector of doubles and errors to zero 
  Histogram(const std::vector<double>&, const std::vector<double>&);
  //! Construct a Histogram from a vector of doubles and initialize values and errors to other vectors of doubles
  Histogram(const std::vector<double>&, const std::vector<double>&, const std::vector<double>&);

  //! Return minimum value
  double MinBin() const;

  //! Return bin upper value
  double Bin(const int& b) const;

  //! Normalize the histogram
  void Normalize();
  
  //! Print the Histogram to console output
  // NEED TO COMPLETE
  // friend std::ostream& operator<<(std::ostream& os, Histogram& hist);

  //! Set the Histogram value by bin and value
  void Set(const int&, const double&);

  //! Set the Histogram value by number (interpreted to bin) and value
  void Set(const double&, const double&);
  
  //! Set the Histogram value and error by bin and values
  void Set(const int&, const double&, const double&);
  
  //! Set the Histogram value and error by number (interpreted to bin) and values
  void Set(const double&, const double&, const double&);
  
  //! Set the Histogram error by bin and values
  void SetErr(const int&, const double&);
  
  //! Set the Histogram error by number (interpreted to bin) and values
  void SetErr(const double&, const double&);

  //! Return the length of the histogram
  unsigned int Size() const;
  
  //! Get the Histogram value by bin
  double Get(const int&) const;
  
  //! Get the Histogram value by number (interpreted to bin)
  double Get(const double&) const;
  
  //! Get the Histogram error by bin
  double GetErr(const int&) const;
  
  //! Get the Histogram error by number (interpreted to bin)
  double GetErr(const double&) const;

  //! Convert histogram for different set of bins to this set of bins and add to current
  void Convert(const Histogram& h);

  //! Clear all entries in the Histogram
  void Clear();

  //! Return the bins of the Histogram
  std::vector<double> GetBins(bool with_min=false) const;

  //! Return the bin centers of the Histogram
  std::vector<double> GetBinCenters() const;

  double Sum() const;

  //! Overloaded operators
  Histogram& operator*=(const double&);
  Histogram& operator/=(const double&);
  Histogram& operator+=(const Histogram&);
  Histogram& operator-=(const Histogram&);

protected:
  //! given a value find the corresponding bin of the Histogram
  int Search(const double&) const;

private:
  enum SpecialBin {
    UNDER = -1,
    OVER = -2
  };

  double m_uflow;
  double m_oflow;
  double m_uflow_err;
  double m_oflow_err;

  void Check(const std::vector<double>&); //! ensure monotonically increasing bin values

  std::vector<double> bins; //! vector of bin values 0 = -MAX FLOAT, 1 = lower Histogram bound
  std::vector<double> values; //! vector of Histogram values 0 = underflow
  std::vector<double> errors; //! vector of Histogram errors 0 = underflow

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("bins",bins);
    ar & make_nvp("values",values);
    ar & make_nvp("errors",errors);
  };
};

const Histogram operator*(const double&, const Histogram&);
const Histogram operator*(const Histogram&, const double&);
const Histogram operator/(const Histogram&, const double&);
const Histogram operator+(const Histogram&, const Histogram&);
const Histogram operator-(const Histogram&, const Histogram&);

} // end namespace data

#endif // DATA_HISTOGRAM_HPP

//---------------------------------------------------------------------------//
// end Data_Histogram.hpp
//---------------------------------------------------------------------------//
