//---------------------------------------------------------------------------//
//!
//! \file   Utility_WattDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Watt distribution class declaration. Modified by Alex Robinson
//!         to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WATT_DISTRIBUTION_HPP
#define UTILITY_WATT_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! Watt distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareWattDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
				  public ParameterListCompatibleObject<UnitAwareWattDistribution<IndependentUnit,DependentUnit> >
{

  // Only allow construction when the independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, energy_dimension );

private:

  // The distribution multiplier quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DistMultiplierQuantity;

  // The distribution normalization quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistMultiplierQuantity>
  typedef QuantityTraits<DistMultiplierQuantity> DMQT;

public:

  //! The distribution type
  typedef UnitAwareWattDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Constructor
  template<typename InputIndepQuantityA = IndepQuantity,
	   typename InputIndepQuantityB = IndepQuantity,
	   typename InputInverseIndepQuantity = InverseIndepQuantity,
	   typename InputIndepQuantityC = IndepQuantity>
  UnitAwareWattDistribution( const InputIndepQuantityA incident_energy =
                             QuantityTraits<InputIndepQuantityA>::one(),
                             const InputIndepQuantityB a_parameter =
                             QuantityTraits<InputIndepQuantityB>::one(),
                             const InputInverseIndepQuantity b_parameter =
                             QuantityTraits<InputInverseIndepQuantity>::one(),
                             const InputIndepQuantityC restriction_energy =
                             QuantityTraits<InputIndepQuantityC>::zero(),
			    const double constant_multiplier = 1.0 );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareWattDistribution( const UnitAwareWattDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareWattDistribution fromUnitlessDistribution( const UnitAwareWattDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareWattDistribution& operator=( const UnitAwareWattDistribution& dist_instance );

  //! Destructor
  ~UnitAwareWattDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Return a sample from the distribution
  IndepQuantity sample() const;

  //! Return a sample from the distribution
  static IndepQuantity sample( const IndepQuantity incident_energy,
			       const IndepQuantity a_parameter,
			       const InverseIndepQuantity b_parameter,
			       const IndepQuantity restriction_energy );

  //! Return a random sample from the distribution and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
    const IndepQuantity incident_energy,
    const IndepQuantity a_parameter,
    const InverseIndepQuantity b_parameter,
    const IndepQuantity restriction_energy,
    DistributionTraits::Counter& trials );

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
  bool isEqual( const UnitAwareWattDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareWattDistribution( const UnitAwareWattDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  // Calculate the normalization constant of the distribution
  void calculateNormalizationConstant();

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareWattDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = WATT_DISTRIBUTION;

  // The incident neutron energy of the distribution
  IndepQuantity d_incident_energy;

  // The a_parameter of the distribution
  IndepQuantity d_a_parameter;

  // The b_parameter of the distribution
  InverseIndepQuantity d_b_parameter;

  // The restriction energy of the distribution
  IndepQuantity d_restriction_energy;

  // The distribution multiplier
  DistMultiplierQuantity d_multiplier;

  // The distribution normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The Watt distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareWattDistribution<void,void> WattDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::WattDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::WattDistribution>
{
public:
  static std::string name()
  {
    return "Watt Distribution";
  }
  static std::string concreteName(
				const Utility::WattDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareWattDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U,typename V>
class TypeNameTraits<Utility::UnitAwareWattDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Watt Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
		      const Utility::UnitAwareWattDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_WattDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_WATT_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_WattDistribution.hpp
//---------------------------------------------------------------------------//
