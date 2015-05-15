//---------------------------------------------------------------------------//
//!
//! \file   Utility_MaxwellFissionDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Maxwell Fission distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP
#define UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

//! Maxwell fission distribution class
class MaxwellFissionDistribution : public OneDDistribution,
			   public ParameterListCompatibleObject<MaxwellFissionDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
 
  //! Default Constructor
  MaxwellFissionDistribution( const double incident_energy = 1.0,
		      const double nuclear_temperature = 1.0,
		      const double restriction_energy = 0.0 );

  //! Copy constructor
  MaxwellFissionDistribution( const MaxwellFissionDistribution& dist_instance );

  //! Assignment operator
  MaxwellFissionDistribution& operator=( const MaxwellFissionDistribution& dist_instance );

  //! Destructor
  ~MaxwellFissionDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample() const;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static double sampleAndRecordTrials( unsigned& trials, const double incident_energy, const double nuclear_temperature, const double restriction_energy );

  //! Test if the distribution is continuous
  bool isContinuous() const;

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
  bool isEqual( const MaxwellFissionDistribution& other ) const;

private:

  // Return the normalization constant of the distribution, pass in parameters
  double getNormalizationConstant( const double incident_energy, const double nuclear_temperature, const double restriction_energy ) const;
 
  // The distribution type
  static const OneDDistributionType distribution_type = MAXWELLFISSION_DISTRIBUTION;

  // The incident neutron energy of the distribution
  double d_incident_energy;

  // The nuclear temperature of the distribution
  double d_nuclear_temperature;
  
  // The restriction energy of the distribution
  double d_restriction_energy;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::MaxwellFissionDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::MaxwellFissionDistribution>
{
public:
  static std::string name()
  {
    return "Maxwell Fission Distribution";
  }
  static std::string concreteName( 
				const Utility::MaxwellFissionDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_MaxwellFissionDistribution.hpp
//---------------------------------------------------------------------------//
