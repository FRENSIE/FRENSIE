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
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The scalar particle response function
class ScalarParticleResponseFunction : public ParticleResponseFunction
{

public:

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

private:

  // The scalar valu
  double d_scalar_value;
};

//! The combined particle response function
template<typename ArithmeticOperationFunctor>
class CombinedParticleResponseFunction
{

public:

  //! Constructor
  CombinedParticleResponseFunction(
                   const std::shared_ptr<const ParticleResponseFunction>& lhs,
                   const std::shared_ptr<const ParticleResponseFunction>& rhs,
                   const ArithmeticOperationFunctor& op )
    : d_lhs( lhs ), d_rhs( rhs ), d_op( op )
  { /* ... */ }

  //! Destructor
  ~CombinedParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override
  { return d_op( d_lhs->evaluate( particle ), d_rhs->evaluate( particle ) ); }

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override
  { return d_lhs->isSpatiallyUniform() && d_rhs->isSpatiallyUniform(); }

private:

  // The lhs response function
  std::shared_ptr<const ParticleResponseFunction> d_lhs;

  // The rhs response function
  std::shared_ptr<const ParticleResponseFunction> d_rhs;

  // The operation functor
  ArithmeticOperationFunctor d_op;
};

// Create a new response function from the addition of two response functions
std::shared_ptr<const ParticleResponseFunction> operator+(
                   const std::shared_ptr<const ParticleResponseFunction>& lhs,
                   const std::shared_ptr<const ParticleResponseFunction>& rhs )
{
  // Make sure that both response function pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<CombinedParticleResponseFunction<std::plus<double> > >( lhs, rhs, std::plus<double>() );
}

// Create a new response function from the subtraction of two response functions
std::shared_ptr<const ParticleResponseFunction> operator-(
                   const std::shared_ptr<const ParticleResponseFunction>& lhs,
                   const std::shared_ptr<const ParticleResponseFunction>& rhs )
{
  // Make sure that both response function pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<CombinedParticleResponseFunction<std::minus<double> > >( lhs, rhs, std::minus<double>() );
}

// Create a new response function from the multiplication of two response functions
std::shared_ptr<const ParticleResponseFunction> operator*(
                   const std::shared_ptr<const ParticleResponseFunction>& lhs,
                   const std::shared_ptr<const ParticleResponseFunction>& rhs )
{
  // Make sure that both response function pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );
  
  return std::make_shared<CombinedParticleResponseFunction<std::multiplies<double> > >( lhs, rhs, std::multiplies<double>() );
}

// Create a new response function from the multiplication of a scalar and a response function
std::shared_ptr<const ParticleResponseFunction> operator*(
                   const double lhs,
                   const std::shared_ptr<const ParticleResponseFunction>& rhs )
{
  // Make sure that the scalar value is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( lhs ) );
  // Make sure that the response function pointer is valid
  testPrecondition( rhs.get() );

  return std::make_shared<CombinedParticleResponseFunction<std::multiplies<double> > >( std::make_shared<ScalarParticleResponseFunction>( lhs ), rhs, std::multiplies<double>() );
}

// Create a new response function from the multiplication of a response function and a scalar
std::shared_ptr<const ParticleResponseFunction> operator*(
                    const std::shared_ptr<const ParticleResponseFunction>& lhs,
                    const double rhs )
{
  // Make sure that the response function pointer is valid
  testPrecondition( lhs.get() );
  // Make sure that the scalar value is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( rhs ) );

  return std::make_shared<CombinedParticleResponseFunction<std::multiplies<double> > >( lhs, std::make_shared<ScalarParticleResponseFunction>( rhs ), std::multiplies<double>() );
}

// Create a new response function from the division of two response functions
std::shared_ptr<const ParticleResponseFunction> operator/(
                   const std::shared_ptr<const ParticleResponseFunction>& lhs,
                   const std::shared_ptr<const ParticleResponseFunction>& rhs )
{
  // Make sure that both response function pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<CombinedParticleResponseFunction<std::divides<double> > >( lhs, rhs, std::divides<double>() );
}

// Create a new response function from the division of a scalar and a response function
std::shared_ptr<const ParticleResponseFunction> operator/(
                   const double lhs,
                   const std::shared_ptr<const ParticleResponseFunction>& rhs )
{
  // Make sure that the scalar value is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( lhs ) );
  // Make sure that the response function pointer is valid
  testPrecondition( rhs.get() );

  return std::make_shared<CombinedParticleResponseFunction<std::divides<double> > >( std::make_shared<ScalarParticleResponseFunction>( lhs ), rhs, std::divides<double>() );
}

// Create a new response function from the division of a response function and a scalar
std::shared_ptr<const ParticleResponseFunction> operator/(
                    const std::shared_ptr<const ParticleResponseFunction>& lhs,
                    const double rhs )
{
  // Make sure that the response function pointer is valid
  testPrecondition( lhs.get() );
  // Make sure that the scalar value is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( rhs ) );

  return std::make_shared<CombinedParticleResponseFunction<std::divides<double> > >( lhs, std::make_shared<ScalarParticleResponseFunction>( rhs ), std::divides<double>() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
