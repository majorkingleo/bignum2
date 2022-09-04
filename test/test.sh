#!/usr/bin/env bash

if [ `uname` = 'Interix' ] ; then
	EXT=".exe";
fi

BIGNUM=../../bignum2${EXT}
for i in t* ; do
	if test -d "$i" ; then
		if test -f "$i"/ARGS ; then
			ARG=`cat  "$i"/ARGS`
		else
			ARG=""
		fi

		cd "$i" && $BIGNUM $ARG < INPUT.txt > log 2>/dev/null && res=`diff log RESULT.txt 2>&1` && cd ..
		if ! test -z "$res" ; then
			echo "DIFFER in $i:"
			echo "   $res"
			echo 
			cd ..
		else
			echo "check $i passed "  
#			cd ..
		fi
	fi
done

