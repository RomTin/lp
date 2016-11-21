#!/bin/sh


$2/$1 > $2/$1.result 2>&1
if diff $2/$1.result $1.correct.1 > /dev/null ; then
  echo $1: 成功
elif diff $2/$1.result $1.correct.2 > /dev/null ; then
  echo $1: 成功
else
  echo $1: 失敗
fi
