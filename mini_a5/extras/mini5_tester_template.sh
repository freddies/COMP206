#!/bin/bash

if [[ ! -f pimapp.c ]]
then
	echo "could not locate pimapp.c - cannot proceed!!"
	exit 1
fi

echo gcc -o pimapp pimapp.c
gcc -o pimapp pimapp.c

if [[ ! -f pimapp  ]]
then
	echo "The executable pimapp was not built, - cannot proceed!!"
	exit 1
fi

echo ''
echo '[[[ Usage Error - file not passed ]]]'
echo ./pimapp
./pimapp
rc=$?
echo rc=$rc
echo ''


echo ''
echo '[[[ Unable to write a file ]]]'
echo './pimapp /nosuch/dbfile <<ECMDS
I,123456789,S,John Doe,Science,2022
END
ECMDS
'
./pimapp /nosuch/dbfile <<ECMDS
I,123456789,S,John Doe,Science,2022
END
ECMDS
rc=$?
echo rc=$rc
echo ''

echo ''
echo '[[[ Inserts ]]]'
echo './pimapp dbfile1 <<ECMDS
I,123456789,S,John Doe,Science,2022
I,123456899,P,Jane Doe,Arts,2010,Y
LIST
END
ECMDS
'
./pimapp dbfile1 <<ECMDS
I,123456789,S,John Doe,Science,2022
I,123456899,P,Jane Doe,Arts,2010,Y
LIST
END
ECMDS
rc=$?
echo rc=$rc
echo "contents of dbfile ..."
cat dbfile1
echo ''

echo ''
echo '[[[ Deletes ]]]'
echo './pimapp $PWD/dbfile2 <<ECMDS
I,123456789,S,John Doe,Science,2022
I,123456799,P,Jane Doe,Computer Science,2020,N
D,123456799
LIST
END
ECMDS
'
./pimapp $PWD/dbfile2 <<ECMDS
I,123456789,S,John Doe,Science,2022
I,123456799,P,Jane Doe,Computer Science,2020,N
D,123456799
LIST
END
ECMDS
rc=$?
echo rc=$rc
echo "contents of dbfile ..."
cat dbfile2
echo ''

# be careful what you delete !!
rm dbfile1 dbfile2

exit 0
