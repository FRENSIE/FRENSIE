//---------------------------------------------------------------------------//
//!
//! \file   Data_ProbDistFunc.hpp
//! \author CJ Solomon
//! \brief  Probability Distribution Function
//!
//---------------------------------------------------------------------------//

#ifndef DATA_PROB_DIST_FUNC_HPP
#define DATA_PROB_DIST_FUNC_HPP

namespace data {

class ProbDistFunc {
public:
  ProbDistFunc() {};

  virtual double pdf(double x) = 0;
  virtual double cdf(double x) = 0;
};

} // end namespace data

#endif // DATA_PROB_DIST_FUNC_HPP

//---------------------------------------------------------------------------//
// end Data_ProbDistFunc.hpp
//---------------------------------------------------------------------------//
