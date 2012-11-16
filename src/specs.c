#include "tlgr_internal.h"

tlgrSpecs* tlgrInitSpecs()
{
    return tlgrMalloc(tlgrSpecs);
}

tlgrReturn tlgrTerminateSpecs(tlgrSpecs** specs)
{
    if(!specs || !*specs)
	tlgrReturn(NO_SPECS);

    tlgrFree(*specs);
    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrSetSpec(tlgrContext* context, tlgrSpecs* specs)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);
    if(!specs)
	tlgrReturn(NO_SPECS);

    memcpy(&context->_specs, specs, sizeof(tlgrSpecs));

    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrSetColDepthSpec(tlgrSpecs* specs, tlgrColourDepth depth)
{
    if(!specs)
	tlgrReturn(NO_SPECS);
    specs->_depth = depth;
    specs->_dirty = 1;
    tlgrReturn(SUCCESS);
}
