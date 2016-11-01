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


for file in test[0-9] test[0-9][0-9]
do
  if [ -f $file ] ; then
    ${testdir}/test.sh -t $testdir $file
  fi
done
