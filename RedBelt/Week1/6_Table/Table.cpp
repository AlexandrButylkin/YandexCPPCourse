#include "test_runer.h"
#include "Table.h"
using namespace std;

// Р РµР°Р»РёР·СѓР№С‚Рµ Р·РґРµСЃСЊ С€Р°Р±Р»РѕРЅРЅС‹Р№ РєР»Р°СЃСЃ Table

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}