#!/bin/sh

CMDNAME=`basename $0`

program="./smplc"
testdir=.

# echo $program
# if [ !-e $program ] ; then
#   echo `basename $program` " does not exist !"
#   exit 1
# fi

while getopts t: OPT
do
  case $OPT in
  "t") testdir="$OPTARG" ;;
  *  ) echo "Usage: $CMDNAME [-t TESTDIR]" 1>&2
          exit 1 ;;
  esac
done


files="$testdir/test*.smpl"
for file in $files
do
  basefile=`echo "$file" | sed -e "s/^.*\(test.*smpl\)$/\1/"`
  ${testdir}/test.sh -t $testdir $basefile
done
