#include "tlgr-tests.h"

float dummyRequest(float val, void* user)
{
    return val;
}

TEST_TLGR(SetRequest, Setup, 0,
	  {
	      ASSERT(tlgrSetRequest(m_data.context, dummyRequest, 0) == TLGR_SUCCESS);
	  });

TEST_TLGR(SetRange, Setup, 0,
	  {
	      ASSERT(tlgrSetRange(m_data.context, 0, 15.f) == TLGR_SUCCESS);
	  });

TEST_TLGR(SetSize, Setup, 0,
	  {
	      ASSERT(tlgrSetSize(m_data.context, 1024, 768) == TLGR_SUCCESS);
	  });
