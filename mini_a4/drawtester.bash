#!/bin/bash

#Freddie Liu, 260551011, freddie.liu@mail.mcgill.ca

if [[ ! -f asciidraw.c ]]
then
	echo "Error cannot locate asciidraw.c"
	exit 1
fi

# Modify this to whatever is your compilation statement is (subject to the restrictions in the assignment PDF)
# please use gcc -o asciidraw asciidraw.c -lm to exe due to math.h library
gcc -o asciidraw asciidraw.c -lm
rc=$?

if [[ $rc -ne 0 ]]
then
	echo "There were errors/warnings from gcc. rc = $rc"
	exit $rc
fi

echo " --- case1: draw lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
LINE 20,10 40,25
CHAR =
LINE 15,20 35,10
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
LINE 20,10 40,25
CHAR =
LINE 15,20 35,10
DISPLAY
END
ENDOFCMDS

echo " --- case2: draw rectangles --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
RECTANGLE 5,20 25,0
CHAR &
RECTANGLE 3,4 5,3
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
RECTANGLE 5,20 25,0
CHAR &
RECTANGLE 3,4 5,3
DISPLAY
END
ENDOFCMDS

echo " --- case3: draw circles --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
CIRCLE 25,25 15
CHAR #
CIRCLE 15,20 5
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
CIRCLE 25,25 15
CHAR #
CIRCLE 15,20 5
DISPLAY
END
ENDOFCMDS

echo " --- case4: invalid commands --- "
echo '
./asciidraw <<ENDOFCMDS
CIRCLE 30,30 5
CHAR %
GRID 50 50
REC 10,40 30,20
GRID 30 30
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
CIRCLE 30,30 5
CHAR %
GRID 50 50
REC 10,40 30,20
GRID 30 30
DISPLAY
END
ENDOFCMDS

echo " --- case5: tatucating shapes --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
RECTANGLE 30,40 60,20
CIRCLE 30,40 20
LINE 40,15 70,35
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
RECTANGLE 30,40 60,20
CIRCLE 30,40 20
LINE 40,35 70,15
DISPLAY
END
ENDOFCMDS

echo " --- case6: special cases --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
CIRCLE 30,40 1
LINE 40,35 20,35
LINE 25,20 25,40
LINE 30,40 30,40
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
CIRCLE 30,40 1
LINE 40,35 20,35
LINE 25,20 25,40
LINE 30,40 30,40
DISPLAY
END
ENDOFCMDS

echo " --- case7: art --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
CHAR @
CIRCLE 40,40 15
CIRCLE 10,40 15
CIRCLE 40,10 15
CIRCLE 10,10 15
CHAR &
LINE 40,40 10,10
LINE 10,40 40,10
CHAR +
RECTANGLE 10,30 30,10
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
CHAR @
CIRCLE 40,40 15
CIRCLE 10,40 15
CIRCLE 40,10 15
CIRCLE 10,10 15
CHAR &
LINE 40,40 10,10
LINE 10,40 40,10
CHAR +
RECTANGLE 10,30 30,10
DISPLAY
END
ENDOFCMDS

echo " --- case7: display verification  --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
DISPLAY
RECTANGLE 0,50 30,0
CHAR !
CIRCLE 40,25 10
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
DISPLAY
RECTANGLE 0,50 30,0
CHAR !
CIRCLE 40,25 10
DISPLAY
END
ENDOFCMDS

echo " --- case8: lines' continuity  --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
LINE 10,50 11,0
LINE 5,5 30,10
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
LINE 10,50 15,0
LINE 5,5 30,10
DISPLAY
END
ENDOFCMDS

echo " --- case9: reverse line's input  --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
LINE 35,40 15,5
DISPLAY
CHAR &
LINE 15,5 35,40 
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
LINE 35,40 15,5
DISPLAY
CHAR &
LINE 15,5 35,40
DISPLAY
END
ENDOFCMDS

echo " --- case10: combination --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
CIRCLE 20,20 10
CHAR ~
RECTANGLE 15,40 30,20
DISPLAY
LINE 30,10 60,20
CHAR %
RECTANGLE 30,55 45,35
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
CIRCLE 20,20 10
CHAR ~
RECTANGLE 15,40 30,20
DISPLAY
LINE 30,10 60,20
CHAR %
RECTANGLE 30,55 45,35
DISPLAY
END
ENDOFCMDS

echo "THE END OF THE TESTER." > /dev/tty
