#ifndef __TLGR_TESTS_H__
#define __TLGR_TESTS_H__

#include "tlgr.h"
#include "testsuite/tests.h"

#define TEST_TLGR(x, grp, time, test)			\
    TEST(x, grp, time,					\
	 { m_data.context = tlgrInitContext(); },	\
	 { tlgrTerminateContext(&m_data.context); },	\
	 test,						\
	 { tlgrContext* context; })

#define TEST_TLGR_COMPLETE(x, grp, time, test)				\
    TEST(x, grp, time,							\
	 {								\
	     m_data.context = tlgrInitContext();			\
	     m_data.specs   = tlgrInitSpecs();				\
	     m_data.surface = tlgrInitSurface();			\
	     tlgrSetRequest(m_data.context, exampleRequest, 0);		\
	 },								\
	 {								\
	     tlgrTerminateSpecs(&m_data.specs);				\
	     tlgrTerminateSurface(&m_data.surface);			\
	     tlgrTerminateContext(&m_data.context);			\
	 },								\
	 test,								\
	 { tlgrContext* context; tlgrSurface* surface; tlgrSpecs* specs; })

float exampleRequest(float val, void* user);

#endif/*__TLGR_TESTS_H__*/
