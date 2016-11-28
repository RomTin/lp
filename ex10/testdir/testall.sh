#!/bin/sh

CMDNAME=`basename $0`

program="./tglc"
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


files="$testdir/test*.tgl"
for file in $files
do
  basefile=`echo "$file" | sed -e "s/^.*\(test.*tgl\)$/\1/"`
  ${testdir}/test.sh -t $testdir $basefile
done
