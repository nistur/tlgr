#include "tlgr-tests.h"

#define __W 80
#define __H 40

int pixels[__W*__H];

TEST_TLGR_COMPLETE(InitTerminate, Surface, 0,
		   {
		       tlgrSurface* surface = 0;
		       ASSERT(surface = tlgrInitSurface());
		       ASSERT(tlgrTerminateSurface(&surface) == TLGR_SUCCESS);
		       ASSERT(!surface);
		   });

TEST_TLGR_COMPLETE(SetSurface, Surface, 0,
		   {
		       ASSERT(tlgrSetSurface(m_data.context, m_data.surface) == TLGR_SUCCESS);
		   });

TEST_TLGR_COMPLETE(SetPixels, Surface, 0,
		   {
		       ASSERT(tlgrSetPixelsSurface(m_data.surface, pixels, __W, __H) == TLGR_SUCCESS);
		   });
