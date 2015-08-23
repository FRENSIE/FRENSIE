//---------------------------------------------------------------------------//
//!
//! \file   Utility_MaxwellFissionDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Maxwell Fission distribution class declaration. Modified by Alex
//!         Robison to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP
#define UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>
#include <boost/units/dimensionless_type.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

/*! The unit-aware Maxwell fission distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareMaxwellFissionDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
					    public ParameterListCompatibleObject<UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit> >
{

  // Only allow construction when the independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, energy_dimension );

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

  // The distribution multiplier unit traits typedef
  typedef UnitTraits<typename UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::template GetUnitToPowerType<1,-2>::type>::type> DistMultiplierUnitTraits;

  // The distribution multiplier quantity type
  typedef typename DistMultiplierUnitTraits::template GetQuantityType<double>::type DistMultiplierQuantity;

  // The distribution normalization unit traits typedef
  typedef UnitTraits<typename UnitTraits<typename UnitTraits<DependentUnit>::InverseUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::InverseUnit>::type> DistNormUnitTraits;

  // The distribution normalization quantity type
  typedef typename DistNormUnitTraits::template GetQuantityType<double>::type DistNormQuantity;

public:

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;
 
  //! Default Constructor
  UnitAwareMaxwellFissionDistribution( 
		    const IndepQuantity incident_energy = 
		    QuantityTraits<IndepQuantity>::initializeQuantity( 1.0 ),
		    const IndepQuantity nuclear_temperature = 
		    QuantityTraits<IndepQuantity>::initializeQuantity( 1.0 ),
		    const IndepQuantity restriction_energy = 
		    QuantityTraits<IndepQuantity>::initializeQuantity( 0.0 ) );

  //! Constructor
  template<typename InputIndepQuantityA,
	   typename InputIndepQuantityB,
	   typename InputIndepQuantityC>
  UnitAwareMaxwellFissionDistribution(
				const InputIndepQuantityA incident_energy,
				const InputIndepQuantityB nuclear_temperature,
				const InputIndepQuantityC restriction_energy );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareMaxwellFissionDistribution( const UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareMaxwellFissionDistribution( const UnitAwareMaxwellFissionDistribution<void,void>& unitless_dist_instance );

  //! Assignment operator
  UnitAwareMaxwellFissionDistribution& operator=( const UnitAwareMaxwellFissionDistribution& dist_instance );

  //! Destructor
  ~UnitAwareMaxwellFissionDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample from the distribution and record the number of trials
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
    const IndepQuantity incident_energy,
    const IndepQuantity nuclear_temperature,
    const IndepQuantity restriction_energy,
    unsigned& trials );

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const UnitAwareMaxwellFissionDistribution& other ) const;

private:

  // Calculate the normalization constant of the distribution
  void calculateNormalizationConstant();

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareMaxwellFissionDistribution;
 
  // The distribution type
  static const OneDDistributionType distribution_type = MAXWELLFISSION_DISTRIBUTION;

  // The incident neutron energy of the distribution
  IndepQuantity d_incident_energy;

  // The nuclear temperature of the distribution
  IndepQuantity d_nuclear_temperature;
  
  // The restriction energy of the distribution
  IndepQuantity d_restriction_energy;

  // The distribution multiplier
  DistMultiplierQuantity d_multiplier;

  // The distribution normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The Maxwell fission distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareMaxwellFissionDistribution<void,void> MaxwellFissionDistribution;

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

/*! \brief Type name traits partial specialization for the 
 * Utility::UnitAwareMaxwellFissionDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U,typename V>
class TypeNameTraits<Utility::UnitAwareMaxwellFissionDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Maxwell Fission Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
	    const Utility::UnitAwareMaxwellFissionDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_MaxwellFissionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_MaxwellFissionDistribution.hpp
//---------------------------------------------------------------------------//
