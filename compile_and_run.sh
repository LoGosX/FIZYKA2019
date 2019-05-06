SCRIPT=`realpath $0`
SCRIPTPATH=`dirname $SCRIPT`
cmake --build ${SCRIPTPATH}/build --config Release
${SCRIPTPATH}/build/Release/FIZYKA2019