//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.hpp
//! \author Alex Robinson
//! \brief  Uniform distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIFORM_DISTRIBUTION_HPP
#define UTILITY_UNIFORM_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Uniform distribution class
class UniformDistribution : public OneDDistribution,
			    public ParameterListCompatibleObject<UniformDistribution>
{

private:
  
  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  UniformDistribution();
 
  //! Constructor
  UniformDistribution( const double min_independent_value, 
		       const double max_independent_value,
		       const double dependent_value );

  //! Copy constructor
  UniformDistribution( const UniformDistribution& dist_instance );

  //! Assignment operator
  UniformDistribution& operator=( const UniformDistribution& dist_instance );
  
  //! Destructor
  ~UniformDistribution()
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
  bool isEqual( const UniformDistribution& other ) const;

private:

  // The distribution type
  static const OneDDistributionType distribution_type = UNIFORM_DISTRIBUTION;

  // The min independent value
  double d_min_independent_value;
  
  // The max independent value
  double d_max_independent_value;

  // The uniform distribution dependent value
  double d_dependent_value;

  // The uniform distribution PDF value
  double d_pdf_value;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::UniformDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::UniformDistribution>
{
public:
  static std::string name()
  {
    return "Uniform Distribution";
  }
  static std::string concreteName( 
			     const Utility::UniformDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace 

#endif // end UTILITY_UNIFORM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution.hpp
//---------------------------------------------------------------------------//
