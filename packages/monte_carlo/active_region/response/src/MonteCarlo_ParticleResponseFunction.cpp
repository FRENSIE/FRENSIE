//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Particle response function base class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Check if the description requires parentheses
bool ParticleResponseFunction::doesDescriptionRequireParentheses() const
{
  return false;
}

// Return a shared ptr of the object
std::shared_ptr<ParticleResponseFunction> ParticleResponseFunction::getShared()
{
  return shared_from_this();
}

// Return a shared ptr of the object (const)
std::shared_ptr<const ParticleResponseFunction> ParticleResponseFunction::getShared() const
{
  return shared_from_this();
}

// Evaluate the response function at the desired phase space point
double ParticleResponseFunction::operator()(
                                          const ParticleState& particle ) const
{
  return this->evaluate( particle );
}

//! The scalar particle response function
class ScalarParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! Default constructor
  ScalarParticleResponseFunction()
    : d_scalar_value( 0.0 )
  { /* ... */ }

  //! Constructor
  ScalarParticleResponseFunction( const double scalar_value )
    : d_scalar_value( scalar_value )
  { /* ... */ }

  //! Destructor
  ~ScalarParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override
  { return d_scalar_value; }

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override
  { return true; }

  //! Get a description of the response function
  std::string description() const final override
  { return Utility::toString( d_scalar_value ); }

private:

  // Serialize the particle response function
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    // Serialize the base class member data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

    // Serialize the local member data
    ar & BOOST_SERIALIZATION_NVP( d_scalar_value );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The scalar value
  double d_scalar_value;
};

//! The combined particle response function
template<typename ArithmeticOperationFunctor>
class CombinedParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! Default constructor
  CombinedParticleResponseFunction()
  { /* ... */ }

  //! Constructor
  CombinedParticleResponseFunction(
                   const std::shared_ptr<const ParticleResponseFunction>& lhs,
                   const std::shared_ptr<const ParticleResponseFunction>& rhs )
    : d_lhs( lhs ),
      d_rhs( rhs )
  { /* ... */ }

  //! Destructor
  virtual ~CombinedParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override
  { return s_op( d_lhs->evaluate( particle ), d_rhs->evaluate( particle ) ); }

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override
  { return d_lhs->isSpatiallyUniform() && d_rhs->isSpatiallyUniform(); }

  //! Get a description of the response function
  std::string description() const final override
  {
    std::string description_string;

    if( d_lhs->doesDescriptionRequireParentheses() )
      description_string += "(";

    description_string += d_lhs->description();

    if( d_lhs->doesDescriptionRequireParentheses() )
      description_string += ")";

    description_string += " ";
    description_string += this->getOpString();
    description_string += " ";

    if( d_rhs->doesDescriptionRequireParentheses() )
      description_string += "(";

    description_string += d_rhs->description();

    if( d_rhs->doesDescriptionRequireParentheses() )
      description_string += ")";

    return description_string;
  }

protected:

  //! Get the operation string
  virtual std::string getOpString() const = 0;

private:

  // Serialize the particle response function
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    // Serialize the base class member data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

    // Serialize the local member data
    ar & BOOST_SERIALIZATION_NVP( d_lhs );
    ar & BOOST_SERIALIZATION_NVP( d_rhs );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The operation function
  static const ArithmeticOperationFunctor s_op;

  // The lhs response function
  std::shared_ptr<const ParticleResponseFunction> d_lhs;

  // The rhs response function
  std::shared_ptr<const ParticleResponseFunction> d_rhs;
};

// Initialize static member data
template<typename ArithmeticOperationFunctor>
const ArithmeticOperationFunctor CombinedParticleResponseFunction<ArithmeticOperationFunctor>::s_op = ArithmeticOperationFunctor();

//! The addition particle response function
class AdditionParticleResponseFunction : public CombinedParticleResponseFunction<std::plus<double> >
{
  // Typedef for the base type
  typedef CombinedParticleResponseFunction<std::plus<double> > BaseType;

public:

  //! Constructors
  using CombinedParticleResponseFunction<std::plus<double> >::CombinedParticleResponseFunction;

  //! Destructor
  ~AdditionParticleResponseFunction()
  { /* ... */ }

protected:

  //! Check if the description requires parentheses
  bool doesDescriptionRequireParentheses() const final override
  { return true; }

  //! Get the operation string
  std::string getOpString() const final override
  { return "+"; }

private:

  // Serialize the particle response function
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//! The subtraction particle response function
class SubtractionParticleResponseFunction : public CombinedParticleResponseFunction<std::minus<double> >
{
  // Typedef for the base type
  typedef CombinedParticleResponseFunction<std::minus<double> > BaseType;

public:

  //! Constructors
  using CombinedParticleResponseFunction<std::minus<double> >::CombinedParticleResponseFunction;

  //! Destructor
  ~SubtractionParticleResponseFunction()
  { /* ... */ }

  protected:

  //! Check if the description requires parentheses
  bool doesDescriptionRequireParentheses() const final override
  { return true; }

  //! Get the operation string
  std::string getOpString() const final override
  { return "-"; }

private:

  // Serialize the particle response function
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//! The multiplication particle response function
class MultiplicationParticleResponseFunction : public CombinedParticleResponseFunction<std::multiplies<double> >
{
  // Typedef for the base type
  typedef CombinedParticleResponseFunction<std::multiplies<double> > BaseType;

public:

  //! Constructor
  using CombinedParticleResponseFunction<std::multiplies<double> >::CombinedParticleResponseFunction;

  //! Destructor
  ~MultiplicationParticleResponseFunction()
  { /* ... */ }

protected:

  //! Check if the description requires parentheses
  bool doesDescriptionRequireParentheses() const final override
  { return false; }

  //! Get the operation string
  std::string getOpString() const final override
  { return "*"; }

private:

  // Serialize the particle response function
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//! The division particle response function
class DivisionParticleResponseFunction : public CombinedParticleResponseFunction<std::divides<double> >
{
  // Typedef for the base type
  typedef CombinedParticleResponseFunction<std::divides<double> > BaseType;

public:

  //! Constructor
  using CombinedParticleResponseFunction<std::divides<double> >::CombinedParticleResponseFunction;

  //! Destructor
  ~DivisionParticleResponseFunction()
  { /* ... */ }

protected:

  //! Check if the description requires parentheses
  bool doesDescriptionRequireParentheses() const final override
  { return true; }

  //! Get the operation string
  std::string getOpString() const final override
  { return "/"; }

private:

  // Serialize the particle response function
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ScalarParticleResponseFunction, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS1_VERSION( CombinedParticleResponseFunction, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_VERSION( AdditionParticleResponseFunction, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_VERSION( SubtractionParticleResponseFunction, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_VERSION( MultiplicationParticleResponseFunction, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_VERSION( DivisionParticleResponseFunction, MonteCarlo, 0 );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ScalarParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS1( CombinedParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdditionParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SubtractionParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MultiplicationParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( DivisionParticleResponseFunction, MonteCarlo );

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ScalarParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( AdditionParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( SubtractionParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( MultiplicationParticleResponseFunction, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( DivisionParticleResponseFunction, MonteCarlo );

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ParticleResponseFunction  );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ScalarParticleResponseFunction );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::AdditionParticleResponseFunction );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SubtractionParticleResponseFunction );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::MultiplicationParticleResponseFunction );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DivisionParticleResponseFunction );

// Create a new response function from the addition of two response functions
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator+(
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
{
  // Make sure that both response function pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<MonteCarlo::AdditionParticleResponseFunction>( lhs, rhs );
}

// Create a new response function from the subtraction of two response functions
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator-(
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
{
  // Make sure that both response function pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<MonteCarlo::SubtractionParticleResponseFunction>( lhs, rhs );
}

// Create a new response function from the multiplication of two response functions
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator*(
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
{
  // Make sure that both response function pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<MonteCarlo::MultiplicationParticleResponseFunction>( lhs, rhs );
}

// Create a new response function from the multiplication of a scalar and a response function
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator*(
       const double lhs,
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
{
  // Make sure that the scalar value is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( lhs ) );
  // Make sure that the response function pointer is valid
  testPrecondition( rhs.get() );

  return std::make_shared<MonteCarlo::MultiplicationParticleResponseFunction>( std::make_shared<MonteCarlo::ScalarParticleResponseFunction>( lhs ), rhs );
}

// Create a new response function from the multiplication of a response function and a scalar
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator*(
        const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
        const double rhs )
{
  // Make sure that the response function pointer is valid
  testPrecondition( lhs.get() );
  // Make sure that the scalar value is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( rhs ) );

  return std::make_shared<MonteCarlo::MultiplicationParticleResponseFunction>( lhs, std::make_shared<MonteCarlo::ScalarParticleResponseFunction>( rhs ) );
}

// Create a new response function from the division of two response functions
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator/(
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
{
  // Make sure that both response function pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<MonteCarlo::DivisionParticleResponseFunction>( lhs, rhs );
}

// Create a new response function from the division of a scalar and a response function
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator/(
       const double lhs,
       const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs )
{
  // Make sure that the scalar value is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( lhs ) );
  // Make sure that the response function pointer is valid
  testPrecondition( rhs.get() );

  return std::make_shared<MonteCarlo::DivisionParticleResponseFunction>( std::make_shared<MonteCarlo::ScalarParticleResponseFunction>( lhs ), rhs );
}

// Create a new response function from the division of a response function and a scalar
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator/(
        const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
        const double rhs )
{
  // Make sure that the response function pointer is valid
  testPrecondition( lhs.get() );
  // Make sure that the scalar value is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( rhs ) );

  return std::make_shared<MonteCarlo::DivisionParticleResponseFunction>( lhs, std::make_shared<MonteCarlo::ScalarParticleResponseFunction>( rhs ) );
}

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
