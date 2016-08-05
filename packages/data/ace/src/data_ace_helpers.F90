!!---------------------------------------------------------------------------!!
!>
!> @file   data_ace_helpers.F90
!> @author Alex Robinson
!> @brief  Ace table reading procedures
!>
!!---------------------------------------------------------------------------!!

module data_ace_table_helpers

  use iso_c_binding
  use utility_fortran_string_helpers

  implicit none

  private

  public :: read_ace_table_header_line_1
  public :: read_ace_table_header_line_2
  public :: read_ace_table_zaids_and_awrs
  public :: read_ace_table_nxs_array
  public :: read_ace_table_jxs_array
  public :: read_ace_table_xss_array

  contains

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

  end module data_ace_table_helpers

!!---------------------------------------------------------------------------!!
!! end data_ace_table_helpers.F90
!!---------------------------------------------------------------------------!!
