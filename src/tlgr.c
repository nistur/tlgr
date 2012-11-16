#include "tlgr_internal.h"

tlgrReturn tlgrClearContext(tlgrContext* context)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);
    context->_request = 0;
    context->_user    = 0;
    // sensible default range is [0,1]
    context->_range[0] = 0.f;
    context->_range[1] = 1.f;
    // sensible default output size is 640x480
    context->_size[0] = 640;
    context->_size[1] = 480;
    if(context->_ownsSurface)
	tlgrTerminateSurface(&context->_surface);
    context->_surface = 0;
    tlgrReturn(SUCCESS);
}

tlgrContext* tlgrInitContext()
{
    tlgrContext* context = tlgrMalloc(tlgrContext);
    if(tlgrClearContext(context) != TLGR_SUCCESS)
	tlgrTerminateContext(&context);
    return context;
}

tlgrReturn tlgrTerminateContext(tlgrContext** context)
{
    if(*context == 0)
	tlgrReturn(NO_CONTEXT);

    tlgrFree(*context);
    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrSetRequest(tlgrContext* context, tlgrRequest request, void* user)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);

    context->_request = request;
    context->_user    = user;
    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrSetRange(tlgrContext* context, float min, float max)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);

    context->_range[0] = min;
    context->_range[1] = max;

    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrSetSize(tlgrContext* context, int width, int height)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);

    context->_size[0] = width;
    context->_size[1] = height;
    if(!context->_surface || context->_ownsSurface)
	tlgrInitDefaultSurface(context);

    tlgrReturn(SUCCESS);
}

col32 tlgrColour(char r, char g, char b, char a)
{
    col32 rtn;
    rtn.r = r; rtn.g = g; rtn.b = b; rtn.a = a;
    return rtn;
}

tlgrReturn tlgrSetPixel(tlgrContext* context, int x, int y, col32 colour)
{
    col32* image = (col32*)context->_surface->_pixels;
    image[x + (y *context->_surface->_size[0])] = colour;
    tlgrReturn(SUCCESS);
}

#define PAD 10

tlgrReturn tlgrRender(tlgrContext* context)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);

    // first thing, we probably should try to get the values
    if(!context->_request)
	tlgrReturn(NO_REQUEST);
    if(!context->_surface)
	tlgrInitDefaultSurface(context);

    //memset(context->_pixels, 0, sizeof(col32) * size);
    int numSteps = MAX(context->_size[0] - PAD,1);
    float step = (context->_range[1] - context->_range[0]) / (float)numSteps;
    float x;
    float* vals = tlgrMallocArray(float, numSteps);
    float* pVal = vals;
    float min = 0;
    float max = 0;
    for(x=context->_range[0]; x<context->_range[1]; x+=step)
    {
	*pVal = context->_request(x, context->_user);
	min = MIN(*pVal, min);
	max = MAX(*pVal, max);
	pVal++;
    }

    int _x, _y;
    col32 black = tlgrColour(0, 0, 0, 255);
    for(_x = PAD/2; _x < context->_size[0] - PAD/2; ++_x)
	tlgrSetPixel(context, _x, context->_size[1] - (PAD), black);
    for(_y = PAD/2; _y < context->_size[1] - PAD/2; ++_y)
	tlgrSetPixel(context, PAD, _y, black);

    float range = max - min;
    int pxRange = context->_size[1] - ( PAD * 2);
    float mul = (float)pxRange / range;
    
    for(_x=0; _x<numSteps; ++_x)
    {
	float val = vals[_x];
	val *= mul;
	val = (float)context->_size[1] - val - PAD+1;
	tlgrSetPixel(context, PAD+_x, (int)val , black);
    }

    tlgrFree(vals);
	

    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrGetPixels(tlgrContext* context, void** pixels)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);
    if(!context->_surface)
	tlgrReturn(NO_SURFACE)
    *pixels = context->_surface->_pixels;

    tlgrReturn(SUCCESS);
}

const char* tlgrError()
{
    return g_tlgrErrors[g_tlgrError];
}

void* _tlgrMallocInternal(int size)
{
    void* data = malloc(size);
    memset(data, 0, size);
    return data;
}
