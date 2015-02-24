//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolynomialDistribution.hpp
//! \author Alex Robinson
//! \brief  Polynomial distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POLYNOMIAL_DISTRIBUTION_HPP
#define UTILITY_POLYNOMIAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

//! Polynomial distribution class
class PolynomialDistribution : public OneDDistribution,
			       public ParameterListCompatibleObject<PolynomialDistribution>
{

private:

  // Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  PolynomialDistribution();

  //! Constructor ( sum_(i=0)^(N-1) c_i*x^i : x in (a,b) )
  PolynomialDistribution( const Teuchos::Array<double>& coefficients,
			  const double min_indep_limit,
			  const double max_indep_limit );

  //! Copy constructor
  PolynomialDistribution( const PolynomialDistribution& dist_instance );

  //! Assignment operator
  PolynomialDistribution& operator=( 
				 const PolynomialDistribution& dist_instance );

  //! Destructor
  ~PolynomialDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a random sample from the distribution
  double sample() const;

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const PolynomialDistribution& other ) const;

private:

  // Initialize the distribution
  void initializeDistribution( const double min_indep_limit,
			       const double max_indep_limit );

  // Test if the distribution can be used for sampling (each term must be a
  // positive function
  bool isValidSamplingDistribution();

  // The distribution type
  static const OneDDistributionType distribution_type = 
    POLYNOMIAL_DISTRIBUTION;

  // The polynomial coefficients
  Teuchos::Array<double> d_coefficients;
  
  // The sampling cdf for the probability mixing technique
  Teuchos::Array<double> d_term_sampling_cdf;

  // The min and max indep limits to the powers of each term of the series + 1
  // first = a^(i+1), second = b^(i+1)
  Teuchos::Array<Pair<double,double> > d_indep_limits_to_series_powers_p1;

  // The normalization constant
  double d_norm_constant;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::PolynomialDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::PolynomialDistribution>
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Polynomial Distribution";

    return iss.str();
  }
  static std::string concreteName( 
			      const Utility::PolynomialDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_POLYNOMIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PolynomialDistribution.hpp
//---------------------------------------------------------------------------//
