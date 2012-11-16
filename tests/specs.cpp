#include "tlgr-tests.h"

TEST(InitTerminate, Specs, 0,
     {},
     { tlgrTerminateSpecs(&m_data.specs); },
     {
	 ASSERT(m_data.specs = tlgrInitSpecs());
	 ASSERT(tlgrTerminateSpecs(&m_data.specs) == TLGR_SUCCESS);
	 ASSERT(m_data.specs == 0);
     },
     { tlgrSpecs* specs; });

TEST(Set, Specs, 0,
     { m_data.context = tlgrInitContext(); m_data.specs = tlgrInitSpecs(); },
     { tlgrTerminateSpecs(&m_data.specs); tlgrTerminateContext(&m_data.context); },
     {
	 ASSERT(tlgrSetSpec(m_data.context, m_data.specs) == TLGR_SUCCESS);
     },
     { tlgrContext* context; tlgrSpecs* specs; });

TEST_TLGR_COMPLETE(ColourDepth, Specs, 0,
		   {
		       ASSERT(tlgrSetColDepthSpec(m_data.specs, TLGR_RGBA_8888) == TLGR_SUCCESS);
		       ASSERT(tlgrSetColDepthSpec(m_data.specs, TLGR_RGB_888) == TLGR_SUCCESS);
		   });
