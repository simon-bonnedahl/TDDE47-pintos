ROOT=${1}
EXAMPLES=$ROOT/src/examples
FILE1=${2}
FILE2=${3:-null}
FILE3=${4:-null}
FILE4=${5:-null}
FILE5=${6:-null}
FILE6=${7:-null}


cd $ROOT/src/userprog/build
echo $FILE1
if [ -e $EXAMPLES/$FILE1 ]
then 
    pintos -v --qemu -p../../examples/$FILE1 -a $FILE1 -- -q
fi
if [ -e $EXAMPLES/$FILE2 ]
then 
    pintos -v --qemu -p ../../examples/$FILE2 -a $FILE2 -- -q
fi
if [ -e $EXAMPLES/$FILE3 ]
then 
    pintos -v --qemu -p ../../examples/$FILE3 -a $FILE3 -- -q
fi
if [ -e $EXAMPLES/$FILE4 ]
then 
    pintos -v --qemu -p ../../examples/$FILE4 -a $FILE4 -- -q
fi
if [ -e $EXAMPLES/$FILE5 ]
then 
    pintos -v --qemu -p ../../examples/$FILE5 -a $FILE5 -- -q
fi
if [ -e $EXAMPLES/$FILE6 ]
then 
    pintos -v ---qemu -p ../../examples/$FILE6 -a $FILE6 -- -q
fi