//---------------------------------------------------------------------------//
//!
//! \file   Utility_SetOperationFunctor.hpp
//! \author Alex Robinson
//! \brief  Functor that takes two boolean variables and returns a boolean
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SET_OPERATION_FUNCTOR_HPP
#define UTILITY_SET_OPERATION_FUNCTOR_HPP

namespace Utility{

class SetOperationFunctor
{

public:

  //! Constructor
  SetOperationFunctor()
  { /* ... */ }

  //! Destructor
  ~SetOperationFunctor()
  { /* ... */ }

  //! Function evaluation operator
  virtual bool operator()( const bool first, const bool second ) = 0;
};

class IntersectionFunctor : public SetOperationFunctor
{

public:

  //! Constructor
  IntersectionFunctor()
    : SetOperationFunctor()
  { /* ... */ }

  //! Destructor
  ~IntersectionFunctor()
  { /* ... */ }

  //! Function evaluation operator
  bool operator()( const bool first, const bool second ) { return first && second; }
};

class UnionFunctor : public SetOperationFunctor
{

public:

  //! Constructor
  UnionFunctor()
    : SetOperationFunctor()
  { /* ... */ }

  //! Destructor
  ~UnionFunctor()
  { /* ... */ }

  //! Function evaluation operator
  bool operator()( const bool first, const bool second ) { return first || second; }

};


} // end Utility namespace

#endif // end UTILITY_SET_OPERATION_FUNCTOR_HPP

//---------------------------------------------------------------------------//
// end Utility_SetOperationFunctor.hpp
//---------------------------------------------------------------------------//



