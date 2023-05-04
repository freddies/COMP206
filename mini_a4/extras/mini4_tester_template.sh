#!/bin/bash

if [[ ! -f asciidraw.c ]]
then
	echo "Error cannot locate asciidraw.c"
	exit 1
fi

# Modify this to whatever is your compilation statement is (subject to the restrictions in the assignment PDF)
gcc -o asciidraw asciidraw.c -lm
rc=$?

if [[ $rc -ne 0 ]]
then
	echo "There were errors/warnings from gcc. rc = $rc"
	exit $rc
fi

echo " --- test case to draw simple lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,20 25,30
CHAR +
LINE 5,10 10,15
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,20 25,30
CHAR +
LINE 5,10 10,15
DISPLAY
END
ENDOFCMDS


echo " --- test case to draw multiple shapes, switching characters, etc --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 20,20 25,30
CHAR +
CIRCLE 25,25 10
DISPLAY
LINE 10,10 15,20
CHAR %
RECTANGLE 30,45 35,35
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 20,20 25,30
CHAR +
CIRCLE 25,25 10
DISPLAY
LINE 10,10 15,20
CHAR %
RECTANGLE 30,45 35,35
DISPLAY
END
ENDOFCMDS

echo "Please remember to make your own tester script, drawtester.bash and submit THAT and NOT THIS script." > /dev/tty
