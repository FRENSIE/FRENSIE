//---------------------------------------------------------------------------//
// \file   SetOperationFunctor.hpp
// \author Alex Robinson
// \brief  Functor that takes two boolean variables and returns a boolean
//---------------------------------------------------------------------------//

#ifndef SET_OPERATION_FUNCTOR_HPP
#define SET_OPERATION_FUNCTOR_HPP

namespace FACEMC{

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


} // end FACEMC namespace

#endif // end SET_OPERATION_FUNCTOR_HPP

//---------------------------------------------------------------------------//
// end SetOperationFunctor.hpp
//---------------------------------------------------------------------------//


  
