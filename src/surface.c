#include "tlgr_internal.h"

tlgrSurface* tlgrInitSurface()
{
    return tlgrMalloc(tlgrSurface);
}

tlgrReturn tlgrTerminateSurface(tlgrSurface** surface)
{
    if(!surface || !*surface)
	tlgrReturn(NO_SURFACE);
    tlgrFree(*surface);
    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrSetSurface(tlgrContext* context, tlgrSurface* surface)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);
    if(!surface)
	tlgrReturn(NO_SURFACE);

    if(context->_surface && context->_ownsSurface)
    {
	tlgrFree(context->_surface->_pixels);
	tlgrFree(context->_surface);
    }
    context->_surface     = surface;
    context->_ownsSurface = 0;

    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrSetPixelsSurface(tlgrSurface* surface, void* pixels, int width, int height)
{
    if(!surface)
	tlgrReturn(NO_SURFACE);
    
    surface->_pixels = pixels;

    surface->_size[0] = width;
    surface->_size[1] = height;
    tlgrReturn(SUCCESS);
}

tlgrReturn tlgrInitDefaultSurface(tlgrContext* context)
{
    if(!context)
	tlgrReturn(NO_CONTEXT);
    
    tlgrSurface* surface = context->_surface ? context->_surface : tlgrInitSurface();
    if(!surface)
	tlgrReturn(NO_SURFACE);

    if(context->_size[0] == surface->_size[0] &&
       context->_size[1] == surface->_size[1])
	tlgrReturn(SUCCESS); // already got a surface, no need to resize

    if(surface->_pixels)
	tlgrFree(surface->_pixels);
    col32* pixels = tlgrMallocArray(col32, context->_size[0] * context->_size[1]);
    tlgrSetPixelsSurface(surface, pixels, context->_size[0], context->_size[1]);

    context->_surface     = surface;
    context->_ownsSurface = 1;

    tlgrReturn(SUCCESS);
}
