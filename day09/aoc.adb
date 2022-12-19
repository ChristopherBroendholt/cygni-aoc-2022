with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Environment_Variables;
with Ada.Containers.Vectors;

procedure Aoc is 
    
-------------------------------------------
-- TYPES
-------------------------------------------
    type Command is record
        DIR : String(1 .. 1);
        MOVE: Integer range 1 .. 1000;
    end record;

    type Position is record
        X: Integer range -10000 .. 10000 := 0;
        Y: Integer range -10000 .. 10000 := 0;
    end record;


-------------------------------------------
-- PACKAGES
-------------------------------------------
    package Command_Vector is new Ada.Containers.Vectors
        (Index_Type => Natural, Element_Type => Command);

    package Position_Vector is new Ada.Containers.Vectors
        (Index_Type => Natural, Element_Type => Position);

    
-------------------------------------------
-- GLOBALS
-------------------------------------------
    Input: Command_Vector.Vector;
    UniqueTailPositions: Position_Vector.Vector;
    KnotPositions: Position_Vector.Vector;

-------------------------------------------
-- FUNCTIONS
-------------------------------------------

    function Itos (value : Integer) return String is
        begin 
            return Trim(Integer'Image(value), Ada.Strings.Left);
    end Itos;

    function IsInAdjacent (knot1: Position; knot2: Position) return Boolean is
        begin
            if knot1.X = knot2.X and knot1.Y = knot2.Y then
                return True;
            
            elsif knot1.X = knot2.X - 1 then
                if knot1.Y = knot2.Y + 1 or knot1.Y = knot2.Y or knot1.Y = knot2.Y - 1 then
                    return True;
                end if;
            
            elsif knot1.X = knot2.X + 1 then 
                if knot1.Y = knot2.Y + 1 or knot1.Y = knot2.Y or knot1.Y = knot2.Y - 1 then
                    return True;
                end if;
            
            elsif knot1.X = knot2.X and knot1.Y = knot2.Y + 1 then
                return True;
            
            elsif knot1.X = knot2.X and knot1.Y = knot2.Y - 1 then
                return True;
            end if;

        return False;
    end IsInAdjacent;


-------------------------------------------
-- PROCEDURES
-------------------------------------------
    
    procedure ReadFile is 
        File: File_Type;
        Dir: String(1 .. 1);
        Move: Integer;
    begin
        Open (File, In_File, "input.txt");
        while not End_Of_File (File) loop
            declare 
            Line: String := Get_Line(File);

            begin
                Dir := Line (1 .. 1);
                Move := Integer'Value(Line(3 .. Line'Length));
                Input.Append((Dir, Move));

            end;
        end loop;
        Close (File);
    end ReadFile;

    procedure moveKnot (knotIndex : Integer; currCommand: Command; isHead: Boolean) is 

        begin
            if isHead = True then
                if currCommand.DIR = "U" then 
                    KnotPositions(knotIndex).Y := KnotPositions(knotIndex).Y + 1;
                elsif currCommand.DIR = "R" then
                    KnotPositions(knotIndex).X := KnotPositions(knotIndex).X + 1;
                elsif currCommand.DIR = "D" then
                    KnotPositions(knotIndex).Y := KnotPositions(knotIndex).Y - 1;
                elsif currCommand.DIR = "L" then
                    KnotPositions(knotIndex).X := KnotPositions(knotIndex).X - 1;
                end if;
            else
                declare
                    xDiff: Integer := KnotPositions(knotIndex - 1).X - KnotPositions(knotIndex).X;
                    yDiff: Integer := KnotPositions(knotIndex - 1).Y - KnotPositions(knotIndex).Y;

                    xMove: Integer := xDiff;
                    yMove: Integer := yDiff;                    
                begin
                    if IsInAdjacent(KnotPositions(knotIndex - 1), KnotPositions(knotIndex)) = False then 

                        if xDiff = -2 then
                            xMove := -1;
                        elsif xDiff = 2 then
                            xMove := 1;
                        end if;
                        
                        if yDiff = -2 then
                            yMove := -1;
                        elsif yDiff = 2 then
                            yMove := 1;
                        end if;

                        KnotPositions(knotIndex).X := KnotPositions(knotIndex).X + xMove;
                        KnotPositions(knotIndex).Y := KnotPositions(knotIndex).Y + yMove;

                    end if;
                end;
            end if;

    end moveKnot;

    procedure addTailPositionIfUnique (tailPosition: Position) is
      begin
        declare 
          unique: Boolean := true;
        begin

          for pos of UniqueTailPositions loop
            if pos.X = tailPosition.X and pos.Y = tailPosition.Y then
              unique := false;
            end if;
          end loop;

          if unique then
            UniqueTailPositions.Append(tailPosition);
          end if;
        end;

        
    end addTailPositionIfUnique;

    procedure WriteTailPositions is 
    
    begin
      declare
        counter : Integer := 0;  
      begin

        for position of UniqueTailPositions loop
          -- Ada.Text_IO.Put_Line("TAIL POS: " & itos(position.X) & ", " & itos(position.Y));
          counter := counter + 1; 
        end loop;

        Ada.Text_IO.Put_Line("Unique Tailpositions: " & itos(counter));
      end;
    end WriteTailPositions;

    procedure WriteKnotPositions is
    begin
        declare
            counter : Integer := 0;  
        begin

        for position of KnotPositions loop
          Ada.Text_IO.Put_Line("#: " & Itos(counter) & " || " & itos(position.X) & ", " & itos(position.Y));
          counter := counter + 1;
        end loop;
      end;

    end WriteKnotPositions;

    procedure MoveRope (amountOfKnots : Integer) is
        
        begin
            declare
                newPosition : Position := (X => 0, Y => 0);
            begin
                for k in 1 .. amountOfKnots loop
                    KnotPositions.Append(newPosition);
                end loop; 

                for nextCommand of Input loop
                    
                    for I in 1 .. nextCommand.MOVE loop
                        for J in 1 .. amountOfKnots loop
                            if J = 1 then
                                moveKnot(J - 1, nextCommand, True);
                            else
                                moveKnot(J - 1, nextCommand, False);
                            end if;
                        end loop; 

                        addTailPositionIfUnique(KnotPositions(amountOfKnots - 1));
                        
                    end loop;
                end loop;

                
            end;

    end MoveRope;

    begin
        ReadFile;

        if not Ada.Environment_Variables.Exists("part") then
            MoveRope(2);
        elsif Ada.Environment_Variables.Value("part") = "PART1" then
            MoveRope(2);
        elsif Ada.Environment_Variables.Value("part") = "PART2" then
            MoveRope(10);
        else
            Put_Line ("Unknown part " & Ada.Environment_Variables.Value("part"));
        end if;

        WriteTailPositions;

end Aoc;