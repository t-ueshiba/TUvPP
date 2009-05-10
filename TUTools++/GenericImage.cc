/*
 *  $BJ?@.(B14-19$BG/!JFH!K;:6H5;=QAm9g8&5f=j(B $BCx:n8"=jM-(B
 *  
 *  $BAO:n<T!'?"<G=SIW(B
 *
 *  $BK\%W%m%0%i%`$O!JFH!K;:6H5;=QAm9g8&5f=j$N?&0w$G$"$k?"<G=SIW$,AO:n$7!$(B
 *  $B!JFH!K;:6H5;=QAm9g8&5f=j$,Cx:n8"$r=jM-$9$kHkL)>pJs$G$9!%Cx:n8"=jM-(B
 *  $B<T$K$h$k5v2D$J$7$KK\%W%m%0%i%`$r;HMQ!$J#@=!$2~JQ!$Bh;0<T$X3+<($9$k(B
 *  $BEy$N9T0Y$r6X;_$7$^$9!%(B
 *  
 *  $B$3$N%W%m%0%i%`$K$h$C$F@8$8$k$$$+$J$kB;32$KBP$7$F$b!$Cx:n8"=jM-<T$*(B
 *  $B$h$SAO:n<T$O@UG$$rIi$$$^$;$s!#(B
 *
 *  Copyright 2002-2007.
 *  National Institute of Advanced Industrial Science and Technology (AIST)
 *
 *  Creator: Toshio UESHIBA
 *
 *  [AIST Confidential and all rights reserved.]
 *  This program is confidential. Any using, copying, changing or
 *  giving any information concerning with this program to others
 *  without permission by the copyright holder are strictly prohibited.
 *
 *  [No Warranty.]
 *  The copyright holder or the creator are not responsible for any
 *  damages caused by using this program.
 *  
 *  $Id: GenericImage.cc,v 1.5 2009-05-10 23:33:22 ueshiba Exp $
 */
#include "TU/Image++.h"

namespace TU
{
/************************************************************************
*  class GenericImage							*
************************************************************************/
//! $BF~NO%9%H%j!<%`$+$i2hA|$N2hAG%G!<%?$rFI$_9~$`!%(B
/*!
  \param in	$BF~NO%9%H%j!<%`(B
  \return	in$B$G;XDj$7$?F~NO%9%H%j!<%`(B
*/
std::istream&
GenericImage::restoreData(std::istream& in)
{
    for (int v = 0; v < height(); )
  	if (!(*this)[v++].restore(in))
	    break;
    return in;
}

//! $B=PNO%9%H%j!<%`$K2hA|$N2hAG%G!<%?$r=q$-=P$9!%(B
/*!
  \param out	$B=PNO%9%H%j!<%`(B
  \return	out$B$G;XDj$7$?=PNO%9%H%j!<%`(B
*/
std::ostream&
GenericImage::saveData(std::ostream& out) const
{
    for (int v = 0; v < height(); )
	if (!(*this)[v++].save(out))
	    break;
    return out;
}

u_int
GenericImage::_width() const
{
    return (ncol()*8) / type2depth(_type);
}

u_int
GenericImage::_height() const
{
    return nrow();
}

ImageBase::Type
GenericImage::_defaultType() const
{
    return type();
}

void
GenericImage::_resize(u_int h, u_int w, ImageBase::Type type)
{
    _type = type;
    w = (type2depth(_type)*w - 1)/8 + 1;
    Array2<Array<u_char> >::resize(h, w);
}

}
