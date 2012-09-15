/*
 *  平成14-19年（独）産業技術総合研究所 著作権所有
 *  
 *  創作者：植芝俊夫
 *
 *  本プログラムは（独）産業技術総合研究所の職員である植芝俊夫が創作し，
 *  （独）産業技術総合研究所が著作権を所有する秘密情報です．著作権所有
 *  者による許可なしに本プログラムを使用，複製，改変，第三者へ開示する
 *  等の行為を禁止します．
 *  
 *  このプログラムによって生じるいかなる損害に対しても，著作権所有者お
 *  よび創作者は責任を負いません。
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
 *  $Id: Menu.h,v 1.1 2012-09-15 05:00:49 ueshiba Exp $  
 */
#ifndef __TUvMenu_h
#define __TUvMenu_h

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class Menu							*
************************************************************************/
class Menu : public Cmd
{
  public:
    class Item : public Cmd
    {
      public:
	Item(Menu& parentMenu, const MenuDef& menuItem)			;
	virtual			~Item()					;
	
	virtual const Widget&	widget()			const	;

	virtual void	callback(CmdId id, CmdVal val)			;
	virtual CmdVal	getValue()				const	;
	virtual void	setValue(CmdVal val)				;

      private:
	const Widget	_widget;	// smeLineObject or smeBSBObject

	static u_int	_nitems;
    };

  public:
    Menu(Object& parentObject, const MenuDef menu[])			;
    Menu(Object& parentObject, const MenuDef menu[],
	 const char* name, ::Widget parentWidget)			;
    virtual			~Menu()					;
	    
    virtual const Widget&	widget()			const	;

  private:
    const Widget		_widget;	// simpleMenuWidget
};

/************************************************************************
*  class ChoiceMenu							*
************************************************************************/
class ChoiceMenu : public Menu
{
  public:
    ChoiceMenu(Object& parentObject, const MenuDef menu[])		;
    ChoiceMenu(Object& parentObject, const MenuDef menu[],
	       const char* name, ::Widget widget)			;
    virtual		~ChoiceMenu()					;
	    
    virtual void	callback(CmdId id, CmdVal val)			;
    virtual CmdVal	getValue()				const	;
    virtual void	setValue(CmdVal val)				;
};

}
}
#endif	// !__TUvMenu_h