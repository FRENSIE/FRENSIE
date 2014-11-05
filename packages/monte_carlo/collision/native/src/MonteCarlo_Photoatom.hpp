//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photoatom.hpp
//! \author Alex Robinson
//! \brief  The photo atom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_HPP
#define MONTE_CARLO_PHOTOATOM_HPP

// Std Lib Includes
#include <string>

namespace MonteCarlo{

//! The atomic class for photoatomic reactions
class Photoatom
{

public:

  //! Set the photoatomic reaction types that will be considered as absorption
  static void setAbsorptionReactionTypes(
    const Teuchos::Array<PhotoatomicReactionType>& absorption_reaction_types );
  
  //! Add a photoatomic reaction type that will be considered as absorption
  static void addAbsorptionReactionType( 
				      const PhotoatomicReactionType reaction );
					
  //! Constructor (no atomic relaxation)
  Photoatom( const std::string& name,
	     const unsigned atomic_number );

  //! Constructor (with atomic relaxation)
  Photoatom( 
	  const std::string& name,
	  const unsigned atomic_number );

  //! Destructor
  virtual ~Photoatom()
  { /* ... */ }

  //! Return the atom name
  const std::string& getName() const;

  //! Return the atomic number
  const unsigned getAtomicNumber() const;

protected:

  //! Get the reactions that should be treated as absorption
  static const boost::unordered_set<PhotoatomicReactionType>& 
  getAbsorptionReactionTypes();

private:

  // Reactions that should be treated as absorption
  static boost::unordered_set<PhotoatomicReactionType> 
  absorption_reaction_types;

  // The atom name
  std::string d_name;

  // The atomic number of the nuclide
  unsigned d_atomic_number;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Photoatom.hpp
//---------------------------------------------------------------------------//
