//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution.hpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DELTA_DISTRIBUTION_HPP
#define UTILITY_DELTA_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

//! Delta distribution class
class DeltaDistribution : public OneDDistribution,
			  public ParameterListCompatibleObject<DeltaDistribution>
{

private:
  
  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default Constructor
  DeltaDistribution();
  
  //! Constructor
  DeltaDistribution( const double location );

  //! Copy constructor
  DeltaDistribution( const DeltaDistribution& dist_instance );

  //! Assignment operator
  DeltaDistribution& operator=( const DeltaDistribution& dist_instance );

  //! Destructor
  ~DeltaDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the corresponding CDF
  double sample() const;

  //! Return a random sample from the corresponding CDF and record the number of trials
  double sampleAndRecordTrials( unsigned& trials ) const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;
  
  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const DeltaDistribution& other ) const;

private:

  // The distribution type
  static const OneDDistributionType distribution_type = DELTA_DISTRIBUTION;

  // The location of the delta distribution
  double d_location;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::DeltaDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::DeltaDistribution>
{
public:
  static std::string name()
  {
    return "Delta Distribution";
  }
  static std::string concreteName( const Utility::DeltaDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_DELTA_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_DeltaDistribution.hpp
//---------------------------------------------------------------------------//
