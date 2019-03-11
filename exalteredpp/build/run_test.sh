mkdir -p ../../qt-test-build && cd ../../qt-test-build
qmake ../exalteredpp/build/test/qt-test.pro 
make
./qt-test