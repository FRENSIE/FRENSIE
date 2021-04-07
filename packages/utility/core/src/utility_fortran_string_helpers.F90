!!---------------------------------------------------------------------------!!
!>
!> @file   utility_fortran_string_helpers.F90
!> @author Alex Robinson, Alex Bennett
!> @brief  Fortran String Helpers
!>
!!---------------------------------------------------------------------------!!

module utility_fortran_string_helpers

  use iso_c_binding

  implicit none

  private

  public :: convert_c_string_to_fortran
  public :: convert_fortran_string_to_c

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

  end module utility_fortran_string_helpers

!!---------------------------------------------------------------------------!!
!! end utility_fortran_string_helpers.F90
!!---------------------------------------------------------------------------!!
