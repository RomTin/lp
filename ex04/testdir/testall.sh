#!/bin/sh

CMDNAME=`basename $0`

testdir=.

while getopts t: OPT
do
  case $OPT in
  "t") testdir="$OPTARG" ;;
  *  ) echo "Usage: $CMDNAME [-t TESTDIR]" 1>&2
          exit 1 ;;
  esac
done


files="$testdir/test*.in"
for file in $files
do
  basefile=`echo "$file" | sed -e "s/^.*\(test.*in\)$/\1/"`
  ${testdir}/test.sh -t $testdir $basefile
done
