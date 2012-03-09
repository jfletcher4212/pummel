// test.h
         
#include <cxxtest/TestSuite.h>
#include "../src/dragitem.h"
#include "../src/markerbox.h"

class ut_dragitem : public CxxTest::TestSuite {
public:
  void test_getState(void)
  {
    int actual;
    int expected = 5;
    DragItem *t = new DragItem();
    
    t->setState(expected);
    actual = t->getState();
    
    TS_ASSERT(actual == expected);
    TS_ASSERT_EQUALS(actual, expected);
  }  
};
