!!---------------------------------------------------------------------------!!
!>
!> @file   string_conversion.F90
!> @author Alex Robinson, Alex Bennett
!> @brief  Tests the string conversions
!>
!!---------------------------------------------------------------------------!!

module string_conversion

  use iso_c_binding
  use utility_fortran_string_helpers

  implicit none

  private

  contains

    !> Tests the string conversions between FORTRAN and C.
    subroutine test_string_conversion(c_string,c_string_size,c_string_out) &
         bind(c, name='testStringConversion')
      use iso_c_binding

      integer(c_int), intent(in), value :: c_string_size
      character(kind=c_char,len=1), dimension(c_string_size), intent(in) :: &
            c_string
      character(kind=c_char,len=1), dimension(c_string_size), intent(inout) :: &
            c_string_out
      character(len=c_string_size) :: fortran_string

      ! Converts C string to Fortran
      call convert_c_string_to_fortran(c_string , fortran_string , &
            c_string_size)

      ! Converts Fortran String to C
      call convert_fortran_string_to_c(fortran_string , c_string_out , &
            c_string_size)

    end subroutine test_string_conversion

  end module string_conversion

!!---------------------------------------------------------------------------!!
!! end string_conversion.F90
!!---------------------------------------------------------------------------!!

