set -e
set -x

if [ ! -e "tzcode-latest.tar.gz" ]; then
  wget --retr-symlinks 'ftp://ftp.iana.org/tz/tzcode-latest.tar.gz'
fi
if [ ! -e "tzdata-latest.tar.gz" ]; then
  wget --retr-symlinks 'ftp://ftp.iana.org/tz/tzdata-latest.tar.gz'
fi

rm -rf tzdb
mkdir tzdb
pushd tzdb
gzip -dc ../tzcode-latest.tar.gz | tar -xf -
gzip -dc ../tzdata-latest.tar.gz | tar -xf -

make TOPDIR=build install
make zonenames > ../zn.txt
popd
python generate.py tz_db-3.c


