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


shift `expr $OPTIND - 1`

if [ "$testdir" != "." ] ; then
  cp $testdir/$1 .
fi

./strlist $1 > $1.result 2>&1
if diff $1.result $testdir/$1.correct > /dev/null; then
  echo $1: 成功
else
  echo $1: 失敗
fi

if [ "$testdir" != "." ] ; then
  rm $1
fi
