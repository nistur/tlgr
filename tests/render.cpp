#include "tlgr-tests.h"

float exampleRequest(float val, void* data)
{
    return val * val;
}

TEST_TLGR_COMPLETE(Render, Render, 0,
		   {
		       ASSERT(tlgrRender(m_data.context) == TLGR_SUCCESS);
		   });

TEST_TLGR_COMPLETE(GetPixels, Render, 0,
		   {
		       void* pixels = 0;
		       ASSERT(tlgrRender(m_data.context) == TLGR_SUCCESS);
		       ASSERT(tlgrGetPixels(m_data.context, &pixels) == TLGR_SUCCESS);
		       ASSERT(pixels);
		   });
