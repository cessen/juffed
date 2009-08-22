#!/bin/sh

REVISION=`LC_ALL=C svn info | grep Revision | cut -d" " -f2-`
VERSION=`cat version`".$REVISION"
DIR="juffed-${VERSION}"

mkdir $DIR

svn co http://juffed.svn.sourceforge.net/svnroot/juffed/trunk $DIR
cat CMakeLists.txt | sed -r "s/DEV 1/DEV 0/" > $DIR/CMakeLists.txt
echo $VERSION > $DIR/version

rm -rf $DIR/win32/
find $DIR -name ".svn" -exec rm -rf '{}' ';'

tar -czf "juffed_${VERSION}.tar.gz" $DIR
tar -cjf "juffed_${VERSION}.tar.bz2" $DIR
7z a "juffed_${VERSION}.7z" $DIR