//---------------------------------------------------------------------------//
//!
//! \file   OneDDistribution.hpp
//! \author Alex Robinson
//! \brief  One dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ONE_D_DISTRIBUTION_HPP
#define ONE_D_DISTRIBUTION_HPP

namespace FACEMC{

//! The one dimensional probability density function declaration
class OneDDistribution
{

public:

  //! Constructor
  OneDDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~OneDPdf()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double indep_var_value ) const = 0;

  //! Return a random sample from the corresponding CDF
  virtual double sample() = 0;

  //! Return the sampling efficiency from the distribution
  virtual double getSamplingEfficiency() const = 0;

  //! Return the upper bound of the distribution independent variable
  virtual double getUpperBoundOfIndepVar() const = 0;

  //! Return the lower bound of the distribution independent variable
  virtual double getLowerBoundOfIndepVar() const = 0;
};

} // end FACEMC namespace

#endif // end ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end OneDDistribution.hpp
//---------------------------------------------------------------------------//

