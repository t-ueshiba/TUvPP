/*
 *  $Id$  
 */
#include "TU/v/Bitmap.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class Bitmap								*
************************************************************************/
Bitmap::Bitmap(const Colormap& colormap, const u_char data[])
    :_display(colormap.display()),
     _bitmap(XCreateBitmapFromData(_display, DefaultRootWindow(_display),
				   (const char*)data+2, data[0], data[1]))
{
}

Bitmap::~Bitmap()
{
    XFreePixmap(_display, _bitmap);
}

}
}
