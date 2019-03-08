mkdir -p ../../qt-test-build && cd ../../qt-test-build
qmake ../build/test/qt-test.pro
make
./qt-test