#include "tlgr-tests.h"
#include "tlgr.h"

TEST(InitTerminate, Basic, 0.0f,
     // initialisation
     {
	 m_data.context = 0;
     },
     // cleanup
     {
	 tlgrTerminateContext(&m_data.context);
     },
     // test
     {
	 ASSERT(m_data.context = tlgrInitContext());
	 ASSERT(tlgrTerminateContext(&m_data.context) == TLGR_SUCCESS);
     },
     // data
     {
	 tlgrContext* context;
     }
    );
