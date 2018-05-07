#include <QtTest>
#include "tst_test.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Test tc;

    return QTest::qExec(&tc, argc, argv);
}
