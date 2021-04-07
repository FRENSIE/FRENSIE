//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDFFissionYieldsFileHandler.cpp
//! \author Alex Bennett
//! \brief  An ENDF file handler class definition for fission yields.
//!
//---------------------------------------------------------------------------//

// FRENSIE Include
#include "Data_ENDFFissionYieldsFileHandler.hpp"
#include "Utility_FortranFileHelperWrappers.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Data_ENDFFissionYieldsHelperWrappers.hpp"

namespace Data{

// Constructor
ENDFFissionYieldsFileHandler::ENDFFissionYieldsFileHandler( const std::string& file_name,
                                                            const int zaid_name )
   : d_file_id( 1 ),
     d_zaid( 0 ),
     d_number_energies_independent(),
     d_energies_independent(),
     d_number_data_sets_independent(),
     d_yield_zaid_independent(),
     d_yield_meta_state_independent(),
     d_yield_independent(),
     d_yield_std_independent(),
     d_number_energies_cumulative(),
     d_energies_cumulative(),
     d_number_data_sets_cumulative(),
     d_yield_zaid_cumulative(),
     d_yield_meta_state_cumulative(),
     d_yield_cumulative(),
     d_yield_std_cumulative()
{
   openENDFFile( file_name );
   readENDFFile( zaid_name );
}

// Destructor
ENDFFissionYieldsFileHandler::~ENDFFissionYieldsFileHandler()
{}

// Open an ENDF Fission Yields Library
void ENDFFissionYieldsFileHandler::openENDFFile( const std::string& file_name)
{
   // Test to make sure no file is open with the desired ID.
   testPrecondition( !fileIsOpenUsingFortran( d_file_id ) );

   // Check that the desired file exists.
   bool endf_file_exists = (bool)fileExistsUsingFortran( file_name.c_str(), file_name.size() );

   TEST_FOR_EXCEPTION( !endf_file_exists, std::runtime_error,
                       "Fatal Error: ENDF file " + file_name + " does not exist." );

    // Check that the desired file is readable.
    bool endf_file_is_readable = (bool)fileIsReadableUsingFortran( file_name.c_str(), file_name.size() );

    TEST_FOR_EXCEPTION( !endf_file_is_readable, std::runtime_error,
                        "Fatal Error: ENDF file " + file_name + " is not readable." );

    // Open the file
    openFileUsingFortran( file_name.c_str(), file_name.size(), d_file_id );

    // Test to make sure the file is open.
    testPostcondition( fileIsOpenUsingFortran( d_file_id ) );
}

// Read the ENDF Table
void ENDFFissionYieldsFileHandler::readENDFFile( const int zaid_name)
{
    // Skip the upper header block
    skipEndfFissionYieldsFirstHeader( d_file_id );

    // The Independent Yields are given first.
    // Read the header block
    readEndfFissionYieldsHeader( d_file_id, &d_zaid , &d_number_energies_independent );

    d_number_data_sets_independent.resize( d_number_energies_independent );
    d_energies_independent.resize( d_number_energies_independent );
    d_yield_zaid_independent.resize( d_number_energies_independent );
    d_yield_meta_state_independent.resize( d_number_energies_independent );
    d_yield_independent.resize( d_number_energies_independent );
    d_yield_std_independent.resize( d_number_energies_independent );

    // Test that the correct ZAID was read.
    {
       bool expected_zaid = ( zaid_name == d_zaid );

       if( ! expected_zaid )
       {

           expected_zaid = ( (zaid_name - 1000000) == d_zaid );

           if( ! expected_zaid)
           {
                std::stringstream ss;

                ss << "Warning: Expected ZAID: " << zaid_name
                   << " Found ZAID: " << d_zaid << "The wrong ENDF"
                   << " file was given."
                   << std::endl;

            //    TEST_FOR_EXCEPTION( !expected_zaid, std::runtime_error, ss.str() );
           }
       }
    }

    // Loop through the number of energie tables given.
    for(int i = 0; i < d_number_energies_independent; ++i)
    {

        // Read the data header.
        readEndfFissionYieldsDataHeader( d_file_id, &d_number_data_sets_independent[i], &d_energies_independent[i] );

        d_yield_zaid_independent[i].resize( d_number_data_sets_independent[i] );
        d_yield_meta_state_independent[i].resize( d_number_data_sets_independent[i] );
        d_yield_independent[i].resize( d_number_data_sets_independent[i] );
        d_yield_std_independent[i].resize( d_number_data_sets_independent[i] );

        // Read the data.
        readEndfFissionYieldsData( d_file_id,
                                  &d_number_data_sets_independent[i],
                                  d_yield_zaid_independent[i].data(),
                                  d_yield_meta_state_independent[i].data(),
                                  d_yield_independent[i].data(),
                                  d_yield_std_independent[i].data() );

        // Converts ZAID into SZAIDS
        for(int j = 0; j < d_yield_zaid_independent[i].size(); ++j)
        {
             d_yield_zaid_independent[i][j] = d_yield_zaid_independent[i][j] + 1000000 * d_yield_meta_state_independent[i][j];
        }

        // Remove zero yield entries
        filterZeroYields(d_yield_zaid_independent[i],
                         d_yield_meta_state_independent[i],
                         d_yield_independent[i],
                         d_yield_std_independent[i] );

    }

    // The Cumulative Yields are given second.
    // Read the header block
    readEndfFissionYieldsHeader( d_file_id, &d_zaid , &d_number_energies_cumulative );

    d_number_data_sets_cumulative.resize( d_number_energies_cumulative );
    d_energies_cumulative.resize( d_number_energies_cumulative );
    d_yield_zaid_cumulative.resize( d_number_energies_cumulative );
    d_yield_meta_state_cumulative.resize( d_number_energies_cumulative );
    d_yield_cumulative.resize( d_number_energies_cumulative );
    d_yield_std_cumulative.resize( d_number_energies_cumulative );

    // Loop through the number of energie tables given.
    for(int i = 0; i < d_number_energies_cumulative; ++i)
    {
        // Read the data header.
        readEndfFissionYieldsDataHeader( d_file_id, &d_number_data_sets_cumulative[i], &d_energies_cumulative[i] );

        d_yield_zaid_cumulative[i].resize( d_number_data_sets_cumulative[i] );
        d_yield_meta_state_cumulative[i].resize( d_number_data_sets_cumulative[i] );
        d_yield_cumulative[i].resize( d_number_data_sets_cumulative[i] );
        d_yield_std_cumulative[i].resize( d_number_data_sets_cumulative[i] );

        // Read the data.
        readEndfFissionYieldsData( d_file_id,
                                  &d_number_data_sets_cumulative[i],
                                  d_yield_zaid_cumulative[i].data(),
                                  d_yield_meta_state_cumulative[i].data(),
                                  d_yield_cumulative[i].data(),
                                  d_yield_std_cumulative[i].data() );

        // Converts ZAID into SZAIDS
        for(int j = 0; j < d_yield_zaid_cumulative[i].size(); ++j)
        {
             d_yield_zaid_cumulative[i][j] = d_yield_zaid_cumulative[i][j] + 1000000 * d_yield_meta_state_cumulative[i][j];
        }

        // Remove zero yield entries
        filterZeroYields(d_yield_zaid_cumulative[i],
                         d_yield_meta_state_cumulative[i],
                         d_yield_cumulative[i],
                         d_yield_std_cumulative[i] );


    }

    // Close the file
    closeFileUsingFortran( d_file_id );

}

// Get the ZAID
int ENDFFissionYieldsFileHandler::getZaid() const
{
   return d_zaid;
}

// Get the energies for the independent yields
Utility::ArrayView<const double> ENDFFissionYieldsFileHandler::getEnergyIndependentYields() const
{
  return Utility::arrayViewOfConst(d_energies_independent);
}

// Get the ZAID of the fission products for the independent yields
Utility::ArrayView<const std::vector<int> >
ENDFFissionYieldsFileHandler::getZaidFissionProductsIndependentYields() const
{
  return Utility::arrayViewOfConst(d_yield_zaid_independent);
}

// Get the Meta State of the fission products for the independent yields
Utility::ArrayView<const std::vector<int> >
ENDFFissionYieldsFileHandler::getMetaStateFissionProductsIndependentYields() const
{
  return Utility::arrayViewOfConst(d_yield_meta_state_independent);
}

// Get the yields of the fission products for the independent yields
Utility::ArrayView<const std::vector<double> >
ENDFFissionYieldsFileHandler::getYieldFissionProductsIndependentYields() const
{
  return Utility::arrayViewOfConst(d_yield_independent);
}

// Get the standard deviation for the yields of the fission products for the independent yields
Utility::ArrayView<const std::vector<double> >
ENDFFissionYieldsFileHandler::getStdYieldFissionProductsIndependentYields() const
{
  return Utility::arrayViewOfConst(d_yield_std_independent);
}

// Get the energies for the cumulative yields
Utility::ArrayView<const double> ENDFFissionYieldsFileHandler::getEnergyCumulativeYields() const
{
  return Utility::arrayViewOfConst(d_energies_cumulative);
}

// Get the ZAID of the fission products for the cumulative yields
Utility::ArrayView<const std::vector<int> >
ENDFFissionYieldsFileHandler::getZaidFissionProductsCumulativeYields() const
{
  return Utility::arrayViewOfConst(d_yield_zaid_cumulative);
}

// Get the Meta State of the fission products for the cumulative yields
Utility::ArrayView<const std::vector<int> >
ENDFFissionYieldsFileHandler::getMetaStateFissionProductsCumulativeYields() const
{
  return Utility::arrayViewOfConst(d_yield_meta_state_cumulative);
}

// Get the yields of the fission products for the cumulative yields
Utility::ArrayView<const std::vector<double> >
ENDFFissionYieldsFileHandler::getYieldFissionProductsCumulativeYields() const
{
  return Utility::arrayViewOfConst(d_yield_cumulative);
}

// Get the standard deviation for the yields of the fission products for the cumulative yields
Utility::ArrayView<const std::vector<double> >
ENDFFissionYieldsFileHandler::getStdYieldFissionProductsCumulativeYields() const
{
  return Utility::arrayViewOfConst(d_yield_std_cumulative);
}

// Filter out the zero yield entries
void ENDFFissionYieldsFileHandler::filterZeroYields( std::vector<int>& zaid,
                                                     std::vector<int>& meta_state,
                                                     std::vector<double>& yield,
                                                     std::vector<double>& yield_std )
{
     // Test Precondition
     testPrecondition(zaid.size() == meta_state.size());
     testPrecondition(zaid.size() == yield.size());
     testPrecondition(zaid.size() == yield_std.size());

     std::vector<int>::iterator zaid_it, meta_state_it;
     std::vector<double>::iterator yield_it, yield_std_it;

     zaid_it = zaid.begin();
     meta_state_it = meta_state.begin();
     yield_it = yield.begin();
     yield_std_it = yield_std.begin();

     while( zaid_it != zaid.end() )
     {

          if( *yield_it == 0.0 )
          {
               zaid_it = zaid.erase( zaid_it );
               meta_state_it = meta_state.erase( meta_state_it );
               yield_it = yield.erase( yield_it );
               yield_std_it = yield_std.erase( yield_std_it );
          }
          else
          {
               ++zaid_it;
               ++meta_state_it;
               ++yield_it;
               ++yield_std_it;
          }
    }
}


} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ENDFFissionYieldsFileHandler.cpp
//---------------------------------------------------------------------------//
