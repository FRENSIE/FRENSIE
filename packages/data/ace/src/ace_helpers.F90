!!---------------------------------------------------------------------------!!
!>
!> @file   ace_helpers.F90
!> @author Alex Robinson
!> @brief  Ace table reading procedures
!>
!!---------------------------------------------------------------------------!!

module ace_table_helpers

  use iso_c_binding
!  use Utility_FortranStringHelpers

  implicit none

  private

  public :: ace_library_exists
  public :: ace_library_is_readable
  public :: ace_library_open
  public :: open_ace_library
  public :: close_ace_library
  public :: locate_ace_table
  public :: read_ace_table_header_line_1
  public :: read_ace_table_header_line_2
  public :: read_ace_table_zaids_and_awrs
  public :: read_ace_table_nxs_array
  public :: read_ace_table_jxs_array
  public :: read_ace_table_xss_array

  contains

    !> Convert a C string to a FORTRAN string
    !> \details Both the C string and FORTRAN string must have the same size.
    subroutine convert_c_string_to_fortran( c_string, fortran_string, &
         string_size )
      use iso_c_binding
      
      integer(c_int), intent(in), value :: string_size
      character(kind=c_char,len=1), dimension(string_size), intent(in) :: &
           c_string
      character(string_size), intent(out) :: fortran_string

      integer(c_int) :: i
      
      do i=1, string_size
         fortran_string(i:i) = c_string(i)
      end do

    end subroutine convert_c_string_to_fortran

    !> Convert a FORTRAN string to a C string
    !> \details Both the C string and FORTRAN string must have the same size.
    subroutine convert_fortran_string_to_c( fortran_string, c_string, &
         string_size )
      use iso_c_binding

      integer(c_int), intent(in), value :: string_size
      character(string_size), intent(in) :: fortran_string
      character(kind=c_char,len=1), dimension(string_size), intent(out) :: &
           c_string

      integer(c_int) :: i

      do i=1, string_size
         c_string(i) = fortran_string(i:i)
      end do

    end subroutine convert_fortran_string_to_c

    !> Test if the file name exists
    !> \details The size variable should neglect the null character.
    integer(c_int) function ace_library_exists( file_name, file_name_size ) &
         bind(c, name='aceLibraryExists')
      use iso_c_binding
!      use Utility_FortranStringHelpers

      integer(c_int), intent(in), value :: file_name_size
      character(kind=c_char,len=1), dimension(file_name_size), intent(in) :: &
           file_name

      character(file_name_size) :: file_name_fortran
      logical                   :: file_exists
      integer(c_int)            :: file_existence_verified ! return value

      ! Convert the file name character array to a fortran character array
      call convert_c_string_to_fortran( file_name, file_name_fortran, &
           file_name_size )

      ! Check if the file exists
      inquire(file=file_name_fortran, exist=file_exists)

      if(file_exists) then
         file_existence_verified = 1
      else
         file_existence_verified = 0
      end if

    end function ace_library_exists

    !> Test if the file is readable
    integer(c_int) function ace_library_is_readable( file_name, &
         file_name_size ) bind(c, name='aceLibraryIsReadable')
      use iso_c_binding
!      use Utility_FortranStringHelpers

      integer(c_int), intent(in), value :: file_name_size
      character(kind=c_char,len=1), dimension(file_name_size), intent(in) :: &
           file_name

      character(file_name_size) :: file_name_fortran
      character(7)              :: read_message
      integer(c_int)            :: file_is_readable ! return value

      ! Convert the file name character array to a fortran character array
      call convert_c_string_to_fortran( file_name, file_name_fortran, &
           file_name_size )

      inquire(file=file_name_fortran, read=read_message)

      if(read_message(1:3) == 'NO') then
         file_is_readable = 0
      else
         file_is_readable = 1
      end if

    end function ace_library_is_readable

    !> Check if an ACE library file is open
    integer(c_int) function ace_library_open( file_id ) & 
         bind(c, name='aceLibraryOpen')
      use iso_c_binding
      
      integer(c_int), intent(in), value :: file_id

      logical        :: file_open
      integer(c_int) :: file_open_verified ! return value
      
      ! Check if a file is open
      inquire(file_id, opened=file_open)

      if(file_open) then
         file_open_verified = 1
      else
         file_open_verified = 0
      end if

    end function ace_library_open

    !> Open the ACE library file
    !> \details Once the ace library has been opened, it will persist in this
    !> module (unit=1) until it is closed.
    subroutine open_ace_library( file_name, file_name_size, file_id ) &
         bind(c, name='openAceLibrary')
      use iso_c_binding
!      use Utility_FortranStringHelpers

      integer(c_int), intent(in), value :: file_name_size
      character(kind=c_char,len=1), dimension(file_name_size), intent(in) :: &
           file_name
      integer(c_int), intent(in), value :: file_id

      character(file_name_size) :: file_name_fortran

      ! Convert the file name character array to a fortran character array
      call convert_c_string_to_fortran( file_name, file_name_fortran, &
           file_name_size )

      ! Open the file
      open(file_id, file=file_name_fortran, status='old', action='read')

    end subroutine open_ace_library

    !> Close the ACE library file
    !> \details This will free the file unit number (file_id)
    subroutine close_ace_library( file_id ) bind(c, name='closeAceLibrary')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      
      close(file_id)

    end subroutine close_ace_library

    !> Move to the desired table in the ACE library
    !> \detials The indexing for the start line should follow FORTRAN
    !> conventions (start at 1). It is assumed that the desired ACE library
    !> has already been opened
    subroutine locate_ace_table( file_id, table_start_line ) &
         bind(c, name='locateAceTable')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: table_start_line
      
      integer(c_int) :: i

      ! Move to the beginning of the file
      rewind(file_id)

      ! Move to the start line of the desired table
      do i = 1, table_start_line - 1
         read(file_id, fmt=*)
      end do

    end subroutine locate_ace_table

    !> Read the first line of the table header
    !> \detials This function will read the table name, the atomic weight 
    !> ratio, the temperature (MeV), and the date the table was created.
    !> The table name and date arrays must have 10 elements. It is assumed 
    !> that the desired table has already been found in the desired ACE 
    !> library.
    subroutine read_ace_table_header_line_1( file_id, table_name, &
         atomic_weight_ratio, temperature, table_date ) &
         bind(c, name='readAceTableHeaderLine1')
      use iso_c_binding
!      use Utility_FortranStringHelpers

      integer(c_int), intent(in), value :: file_id
      character(kind=c_char,len=1), dimension(10), intent(inout) :: table_name
      real(c_double), intent(inout) :: atomic_weight_ratio
      real(c_double), intent(inout) :: temperature
      character(kind=c_char,len=1), dimension(10), intent(inout) :: table_date

      character(10) :: table_name_fortran
      character(10) :: table_date_fortran

      read(file_id, fmt='(A10,2G12.0,1X,A10)') table_name_fortran, &
           atomic_weight_ratio, temperature, table_date_fortran

      call convert_fortran_string_to_c( table_name_fortran, table_name, 10 )
      call convert_fortran_string_to_c( table_date_fortran, table_date, 10 )

    end subroutine read_ace_table_header_line_1

    !> Read the second line of the table header
    !> \details This function will read the table comment and material id. It
    !> is assumed that the first line of the table has already been read.
    subroutine read_ace_table_header_line_2( file_id, comment, material_id ) &
         bind(c, name='readAceTableHeaderLine2')
      use iso_c_binding
!      use Utility_FortranStringHelpers

      integer(c_int), intent(in), value :: file_id
      character(kind=c_char,len=1), dimension(70), intent(inout) :: comment
      character(kind=c_char,len=1), dimension(10), intent(inout) :: &
           material_id

      character(70)  :: comment_fortran
      character(10)  :: material_id_fortran
      integer(c_int) :: i

      read(file_id, fmt='(A70,A10)') comment_fortran, material_id_fortran

      call convert_fortran_string_to_c( comment_fortran, comment, 70 )
      call convert_fortran_string_to_c( material_id_fortran, material_id, 10 )

    end subroutine read_ace_table_header_line_2

    !> Read the ACE table zaids and atomic weight ratios
    !> \details The zaids and awrs array must have 16 elements. This 
    !> information is only used for S(a,b) tables. This information resides in 
    !> 3rd, 4th, 5th and 6th lines of the table header. It is assumed that the 
    !> first two lines of the table header have been read.
    subroutine read_ace_table_zaids_and_awrs( file_id, zaids, awrs ) &
         bind(c, name='readAceTableZaidsAndAwrs')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(inout) :: zaids(16)
      real(c_double), intent(inout) :: awrs(16)
      
      integer :: i

      read(file_id, fmt='(4(I7,F11.0)/4(I7,F11.0)/4(I7,F11.0)/4(I7,F11.0))') &
           (zaids(i), awrs(i), i=1,16)

    end subroutine read_ace_table_zaids_and_awrs
      
    !> Read the ACE table NXS array
    !> \detials The NXS array must have 16 elements. The array elements reside
    !> in the 7th and 8th lines of the table header. It is assumed that the
    !> first six lines of the table header have been read.
    subroutine read_ace_table_nxs_array( file_id, nxs ) &
         bind(c, name='readAceTableNXSArray')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(inout) :: nxs(16)
      
      read(file_id, '(8I9/8I9)') nxs

    end subroutine read_ace_table_nxs_array
    
    !> Read the ACE table JXS array
    !> \details The JXS array must have 32 elements. The array elements reside
    !> in the 9th, 10th, 11th, and 12th lines of the table header. It is 
    !> assumed that the first eight lines of the table header have been read.
    subroutine read_ace_table_jxs_array( file_id, jxs ) &
         bind(c, name='readAceTableJXSArray')
      use iso_c_binding
      
      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(inout) :: jxs(32)

      read(file_id, '(8I9/8I9/8I9/8I9)') jxs

    end subroutine read_ace_table_jxs_array
    
    !> Read the ace table XSS array
    !> \detials The XSS array must have NXS(1) elements. The array elements 
    !> reside in the table. It is assumed that the entire table header has
    !> been read.
    subroutine read_ace_table_xss_array( file_id, xss, xss_size ) &
         bind(c, name='readAceTableXSSArray')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: xss_size
      real(c_double), dimension(xss_size), intent(inout) :: xss

      read(file_id,'(4G20.0)') xss

    end subroutine read_ace_table_xss_array

  end module ace_table_helpers

!!---------------------------------------------------------------------------!!
!! end ace_table_helpers.F90
!!---------------------------------------------------------------------------!!
