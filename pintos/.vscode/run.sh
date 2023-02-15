ROOT=${1}
PROGRAM=${2}
DEBUG=${3:-}
cd $ROOT/src/userprog/build
pintos -v --qemu $DEBUG -- run $PROGRAM