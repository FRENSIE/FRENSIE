//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayDataContainer.hpp
//! \author Alex Robinson
//! \brief  The decay data container class declaration (based on DecayFile.hpp
//!         written by CJ Solomon)
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_DATA_CONTAINER_HPP
#define DATA_DECAY_DATA_CONTAINER_HPP

// Std Lib Includes
#include <map>
#include <set>

// FRENSIE Includes
#include "Data_DecayNuclide.hpp"
#include "Utility_StandardArchivableObject.hpp"
#include "Utility_StandardSerializableObject.hpp"

namespace Data{

//! The decay data container
class DecayDataContainer : public Utility::StandardArchivableObject<DecayDataContainer,false>, public Utility::StandardSerializableObject<DecayDataContainer,false>
{

public:
  
  //! Constructor (from saved archive)
  DecayDataContainer(
		  const std::string& archive_name,
                  const Utility::ArchivableObject::ArchiveType archive_type =
		  Utility::ArchivableObject::XML_ARCHIVE );

  //! Destructor
  virtual ~DecayDataContainer()
  { /* ... */ }

  //! Return the nuclide szaids
  std::set<unsigned> getNuclideIdentifiers() const;

  //! Return the desired decay nuclide
  const DecayNuclide& getDecayNuclide( const unsigned szaid ) const;

  //! Return the daughters of a nuclide
  std::set<unsigned> getNuclideDaughters( const unsigned szaid ) const;

  //! Construct unit decay chain at the desired time
  std::map<unsigned, double> constructUnitDecayChain(
				   const unsigned szaid,
				   const double time,
		                   std::vector<double> parent_decay_constants =
				   std::vector<double>() ) const;

protected:

  //! Default constructor
  DecayDataContainer()
  { /* ... */ }

  //! Add a decay nuclide
  void addDecayNuclide( const unsigned szaid,
			const DecayNuclide& nuclide );

private:

  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned int version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The decay nuclides
  typedef std::map<unsigned,DecayNuclide> DecayNuclideMap;
  DecayNuclideMap d_decay_nuclides;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_DecayDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_DECAY_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_DecayDataContainer.hpp
//---------------------------------------------------------------------------//
