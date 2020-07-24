#! /bin/bash
function nl_error {
  echo "gen_setup.sh: $*" >&1
  exit 1
}

[ -n "$1" ] || nl_error "Must specify version number"
version=$1
pkg=icosfit-hwv-$version
destpath=$pkg/usr/share/icosfit/hwv/setup
qdestpath=`echo $destpath | sed -e 's/\\//\\\\\\//g'`
xform="s/^\./$qdestpath/"
echo "version='$version'"
echo "pkg='$pkg'"
echo "destpath='$destpath'"
echo "xform='$xform'"
tar -czf $pkg.tar.gz --xform="$xform" \
  --exclude='*.tar.gz' --exclude=gen_setup.sh \
  .
