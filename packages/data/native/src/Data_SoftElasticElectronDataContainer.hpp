//---------------------------------------------------------------------------//
//!
//! \file   Data_SoftElasticElectronDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native soft elastic electron data container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SOFT_ELASTIC_ELECTRON_DATA_CONTAINER_HPP
#define DATA_SOFT_ELASTIC_ELECTRON_DATA_CONTAINER_HPP

// Std Lib Includes
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_StandardArchivableObject.hpp"
#include "Utility_StandardSerializableObject.hpp"

namespace Data{

/*! The soft elastic electron data container
 * \details Linear-linear interpolation should be used for all data.
 */
class SoftElasticElectronDataContainer : public Utility::StandardArchivableObject<SoftElasticElectronDataContainer,false>, public Utility::StandardSerializableObject<SoftElasticElectronDataContainer,false>
{

public:

  //! Constructor (from saved archive)
  SoftElasticElectronDataContainer( 
		  const std::string& archive_name,
                  const Utility::ArchivableObject::ArchiveType archive_type =
		  Utility::ArchivableObject::XML_ARCHIVE );

  //! Destructor
  virtual ~SoftElasticElectronDataContainer()
  { /* ... */ }

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the elastic cutoff angle cosine
  double getCutoffAngleCosine() const;

  //! Return the elastic angular energy grid
  const std::set<double>& getElasticAngularEnergyGrid() const;

  //! Return the number of discrete angles for an angular energy bin
  unsigned getNumberOfDiscreteAngles( const unsigned angular_energy_bin ) const;

  //! Return the soft elastic discrete angles for an angular energy bin
  const std::vector<double>& getSoftElasticDiscreteAngles(
					       const unsigned angular_energy_bin ) const;

  //! Return the soft elastic weights for an angular energy bin
  const std::vector<double>& getSoftElasticWeights(
					       const unsigned angular_energy_bin ) const;

  //! Return the electron energy grid
  const std::vector<double>& getElectronEnergyGrid() const;

  //! Return the Moment Preserving (MP) soft elastic electron cross section
  const std::vector<double>& 
  getMomentPreservingSoftElasticCrossSection() const;

  //! Return the MP soft elastic cross section threshold energy bin index
  unsigned 
  getMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex() const;

protected:

  //! Default constructor
  SoftElasticElectronDataContainer()
  { /* ... */ }

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );
  
  //! Set the elastic cutoff angle cosine
  void setCutoffAngleCosine( const double cutoff_angle_cosine );


  //! Set the elastic angular energy grid
  void setElasticAngularEnergyGrid( 
            const std::set<double>& angular_energy_grid );

  //! Set the number of discrete angles for an angular energy bin
  void setNumberOfDiscreteAngles( 
             const unsigned angular_energy_bin,
             const unsigned number_of_discrete_angles );

  //! Set the soft elastic discrete angles for an angular energy bin
  void setSoftElasticDiscreteAngles(
		     const unsigned angular_energy_bin,
		     const std::vector<double>& soft_elastic_discrete_angles );

  //! Set the soft elastic weights for an angular energy bin
  void setSoftElasticWeights( 
			 const unsigned angular_energy_bin,
			 const std::vector<double>& soft_elastic_weights );
  
  //! Set the photon energy grid
  void setElectronEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the soft elastic electron cross section using Moment Preserving (MP) theory
  void setMomentPreservingSoftElasticCrossSection(
			 const std::vector<double>& soft_elastic_cross_section );

  //! Set the MP soft elastic cross section threshold energy bin index
  void setMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index );

  
private:

  // Test if a value is less than or equal to zero
  static bool isValueLessThanOrEqualToZero( const double value );

  // Test if a value is less than zero
  static bool isValueLessThanZero( const double value );

  // Test if a value is greater than one
  static bool isValueGreaterThanOne( const double value );

  // Test if a value is less than minus one
  static bool isValueLessThanMinusOne( const double value );

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;
  
  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atomic number
  unsigned d_atomic_number;

  // The elastic cutoff angle cosine
  double d_cutoff_angle_cosine;

  // The elastic angular energy grid (MeV)
  std::set<double> d_angular_energy_grid;

  // The number of discrete angles for angular energy bin
  std::map<unsigned,unsigned> d_number_of_discrete_angles;

  // The soft elastic discrete angles
  std::map<unsigned,std::vector<double> > d_soft_elastic_discrete_angles;

  // The soft elastic weights
  std::map<unsigned,std::vector<double> > d_soft_elastic_weights;

  // The electron energy grid (MeV)
  std::vector<double> d_electron_energy_grid;

  // The Moment Preserving soft elastic electron cross section (b)
  std::vector<double> d_moment_preserving_soft_elastic_cross_section;

  // The Moment Preserving soft elastic electron cross section threshold energy index
  unsigned d_moment_preserving_soft_elastic_cross_section_threshold_index;

};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_SoftElasticElectronDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_SOFT_ELASTIC_ELECTRON_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_SoftElasticElectronDataContainer.hpp
//---------------------------------------------------------------------------//

