mkdir -p ../../qt-build && cd ../../qt-build
qmake ../exalteredpp/build/app/exalteredpp.pro CONFIG+=debug
make

mkdir -p ../qt-test-build && cd ../qt-test-build
qmake ../exalteredpp/build/test/qt-test.pro CONFIG+=debug
make
./qt-test