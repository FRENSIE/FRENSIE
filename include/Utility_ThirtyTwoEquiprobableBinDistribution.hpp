//---------------------------------------------------------------------------//
//!
//! \file   Utility_ThirtyTwoEquiprobableBinDistribution.hpp
//! \author Alex Robinson
//! \brief  Thirty-two equiprobable bin distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP
#define UTILITY_THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_XMLCompatibleObject.hpp"

namespace Utility{

//! The 32 equiprobable bin distribution class
  class ThirtyTwoEquiprobableBinDistribution : public OneDDistribution,
	       public XMLCompatibleObject<ThirtyTwoEquiprobableBinDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  ThirtyTwoEquiprobableBinDistribution();

  //! Constructor
  ThirtyTwoEquiprobableBinDistribution( 
				 const Teuchos::Array<double>& bin_boundaries);

  //! Copy constructor
  ThirtyTwoEquiprobableBinDistribution(
		   const ThirtyTwoEquiprobableBinDistribution& dist_instance );

  //! Assignment operator
  ThirtyTwoEquiprobableBinDistribution& operator=(
		   const ThirtyTwoEquiprobableBinDistribution& dist_instance );

  //! Destructor
  ~ThirtyTwoEquiprobableBinDistribution()
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
  bool isEqual( const ThirtyTwoEquiprobableBinDistribution& other ) const;

private:

  // The disribution type
  static const OneDDistributionType distribution_type = 
    THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION;

  // The distribution
  Teuchos::Array<double> d_bin_boundaries;
};
  
} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the 
 * Utility::ThirtyTwoEquiprobableBinDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::ThirtyTwoEquiprobableBinDistribution>
{
public:
  static std::string name()
  {
    return "32 Equiprobable Bin Distribution";
  }
  static std::string concreteName( 
		const Utility::ThirtyTwoEquiprobableBinDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_32EquiprobableBinDistribution.hpp
//---------------------------------------------------------------------------//
