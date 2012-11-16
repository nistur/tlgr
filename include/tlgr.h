#pragma once
#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

#ifdef TLGR_DYNAMIC
# ifdef WIN32
#  ifdef TLGR_BUILD
#   define TLGR_EXPORT __declspec( dllexport )
#  else
#   define TLGR_EXPORT __declspec( dllimport )
#  endif
# endif
#endif
 
#ifndef TLGR_EXPORT
# define TLGR_EXPORT
#endif

// return type
typedef int tlgrReturn;

typedef int tlgrColourDepth;
// data types
typedef struct _tlgrContext tlgrContext;
typedef struct _tlgrSurface tlgrSurface;
typedef struct _tlgrSpecs   tlgrSpecs;
// callback type
typedef float(*tlgrRequest)(float, void*);

// Error codes
#define TLGR_SUCCESS    0
#define TLGR_NO_CONTEXT 1
#define TLGR_NO_REQUEST 2
#define TLGR_NO_SURFACE 3
#define TLGR_NO_SPECS   4

// surface depts
#define TLGR_RGBA_8888    0
#define TLGR_RGB_888      1

    TLGR_EXPORT tlgrContext* tlgrInitContext     ();
    TLGR_EXPORT tlgrReturn   tlgrTerminateContext(tlgrContext** context);
    TLGR_EXPORT const char*  tlgrError();
    
// library interface    
    TLGR_EXPORT tlgrReturn   tlgrSetRequest(tlgrContext* context, tlgrRequest request, void* user);
    TLGR_EXPORT tlgrReturn   tlgrSetRange(tlgrContext* context, float min, float max);
    TLGR_EXPORT tlgrReturn   tlgrSetSize(tlgrContext* context, int width, int height);
    TLGR_EXPORT tlgrReturn   tlgrRender(tlgrContext* context);
    TLGR_EXPORT tlgrReturn   tlgrGetPixels(tlgrContext* context, void** pixels);
    
// surface extensions
    TLGR_EXPORT tlgrSurface* tlgrInitSurface();
    TLGR_EXPORT tlgrReturn   tlgrTerminateSurface(tlgrSurface** surface);
    TLGR_EXPORT tlgrReturn   tlgrSetSurface(tlgrContext* context, tlgrSurface* surface);
    TLGR_EXPORT tlgrReturn   tlgrSetPixelsSurface(tlgrSurface* surface, void* pixels, int width, int height);
    
// render specs
    TLGR_EXPORT tlgrSpecs*   tlgrInitSpecs();
    TLGR_EXPORT tlgrReturn   tlgrTerminateSpecs(tlgrSpecs** specs);
    TLGR_EXPORT tlgrReturn   tlgrSetSpec(tlgrContext* context, tlgrSpecs* specs);
    TLGR_EXPORT tlgrReturn   tlgrSetColDepthSpec(tlgrSpecs* specs, tlgrColourDepth depth);
    
#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TEMPLATE_H__*/
