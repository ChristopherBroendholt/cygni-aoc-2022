! BUILD: gfortran aoc.f90 -o aoc
! RUN:   aoc

! cls && gfortran aoc.f90 -o aoc && aoc

module str2int_mod
contains 

  elemental subroutine str2int(str,int,stat)
    implicit none
    ! Arguments
    character(len=*),intent(in) :: str
    integer,intent(out)         :: int
    integer,intent(out)         :: stat

    read(str,*,iostat=stat)  int
  end subroutine str2int

end module

program aoc
    implicit none

    type :: instruction
        logical :: noop
        integer :: cycles 
        integer :: register_value
    end type instruction

    character(10) :: line
    character(6) :: part
    integer :: iostat, line_count = 1
    integer :: cycle_index = 1, cycle_sum = 1, signal_strength = 0
    integer :: line_index = 0, new_cycle_index = 1;
    integer :: i = 0, j = 0, h

    character(40), dimension(6) :: screen_lines
    
    Type(instruction) :: new_instruction
    Type(instruction), dimension(500) :: instructions

    do i = 0, 5
        do j = 0, 39
            screen_lines(i)(j:j) = "_"
        end do
    end do

    ! Screen Pixels

    open(10, file="input.txt")
    do
        read(10, '(A)',iostat=iostat) line
            
            if (line(1:4).eq."noop") then
                new_instruction%noop = .TRUE.
                new_instruction%cycles = 1
                new_instruction%register_value = 0
                instructions(line_count) = new_instruction
            
            else if(line(1:4).eq."addx") then
                new_instruction%noop = .FALSE.
                new_instruction%cycles = 2
                Read(line(5: len_trim(line)), '(I10)') new_instruction%register_value
                instructions(line_count) = new_instruction

            endif
            
            ! print *, "NEW INSTRUCTION ", new_instruction%noop, new_instruction%cycles, new_instruction%register_value, line_count

            line_count = line_count + 1

            if (iostat/=0) then
                exit
            endif
    enddo
    close(10)
    
    call get_environment_variable('part', part)
    if (trim(part).eq.'PART1'.or.trim(part).eq.'') then
        print *, "PART 1"
    else if (trim(part).eq.'PART2') then
        print *, "PART 2"
    else
        print *, 'Unknown part '//part
    end if
    
    if (part .eq. "PART1") then
        do i = 1, line_count - 1
            do j = 1, instructions(i)%cycles
                if (cycle_index == 20) then
                    signal_strength = signal_strength + cycle_sum * cycle_index
                    ! print *, (cycle_sum * cycle_index)
                    ! print *, "20: ", signal_strength
                else if (modulo(cycle_index - 20, 40)==0) then
                    signal_strength = signal_strength + cycle_sum * cycle_index
                    ! print *, (cycle_sum * cycle_index)
                    ! print *, "%40: ", signal_strength
                endif

                ! print *, "Cycle: ", cycle_index, cycle_sum, instructions(i)%register_value, instructions(i)%noop
                cycle_index = cycle_index + 1
            
            end do

            cycle_sum = cycle_sum + instructions(i)%register_value
        end do

        ! print *, cycle_sum
        print *, signal_strength
    end if

    if (part .eq. "PART2") then

        do i = 0, 5
            do j = 0, 39
                screen_lines(i)(j:j) = " "
            end do
        end do

        do i = 1, line_count - 1
            ! print *,"INSTRUCTION: ", instructions(i)%cycles, instructions(i)%register_value, cycle_sum, cycle_index, line_index
            do j = 1, instructions(i)%cycles

                if (modulo(cycle_index, 40)==0) then
                    line_index = line_index + 1

                end if

                new_cycle_index = cycle_index - (line_index * 40)
                ! print *, "new ", new_cycle_index, " sum ",  cycle_sum

                if (new_cycle_index == cycle_sum) then
                    screen_lines(line_index)(new_cycle_index:new_cycle_index) = "#"
                end if

                if (new_cycle_index == cycle_sum + 1) then
                    screen_lines(line_index)(new_cycle_index:new_cycle_index) = "#"
                end if

                if (new_cycle_index == cycle_sum + 2) then
                    screen_lines(line_index)(new_cycle_index:new_cycle_index) = "#"
                end if

                cycle_index = cycle_index + 1
            end do
            
            do h = 0, 5
                ! print *, screen_lines(h)
            end do
            cycle_sum = cycle_sum + instructions(i)%register_value
        end do


        do i = 0, 5
            print *, screen_lines(i)
        end do
    end if
end program aoc
