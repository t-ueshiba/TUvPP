/*
 *  $Id: Allocator++.h,v 1.4 2006-04-19 02:34:37 ueshiba Exp $
 */
#ifndef __TUAllocatorPP_h
#define __TUAllocatorPP_h

#include "TU/List++.h"
#include "TU/Array++.h"

namespace TU
{
/************************************************************************
*  class Allocator<T>							*
************************************************************************/
template <class T>
class Allocator
{
  public:
    class Page : public List<Page>::Node
    {
      public:
	Page(u_int nelements)
	    :_nelements(nelements),
	     _p(new char[sizeof(T)*_nelements])	{}
	~Page()					{delete [] _p;}

	u_int		nelements()	const	{return _nelements;}
	void*		nth(int i)	const	{return _p + sizeof(T)*i;}

      private:
	const u_int	_nelements;	// # of elements in this page.
	char* const	_p;		// memory pool.
    };

    class PageList : public List<Page>
    {
      public:
      	~PageList()					;

	using		List<Page>::begin;
	using		List<Page>::end;
	using		List<Page>::empty;
	using		List<Page>::front;
	using		List<Page>::pop_front;
    };

    class Element : public List<Element>::Node
    {
    };

    class FreeList : public List<Element>
    {
      public:
	void		addPage(Page& page)		;

	using		List<Element>::begin;
	using		List<Element>::end;
	using		List<Element>::empty;
	using		List<Element>::front;
	using		List<Element>::pop_front;
    };

    class Enumerator : public List<Enumerator>::Node
    {
      public:
	Enumerator(const Allocator<T>& allocator)	;
	~Enumerator()					;

	void		head()				;
			operator T*()			{return _p;}
	T*		operator ->()			{return _p;}
	Enumerator&	operator ++()			;
	
      private:
	friend class	Allocator;
	
	void		unmark(const void* p)		;
	
	const Allocator<T>&			_allocator;
	typename List<Page>::ConstIterator	_pageIter;
	u_int					_page, _index, _bit;
	T*					_p;
	Array<Array<u_int> >	_mark;	// marked if not in freeList.
    };

  public:
    Allocator(u_int nelmsPerPage=1024)		{setPageSize(nelmsPerPage);}

    void*		alloc()			;
    void		free(void* p)		;
    void		setPageSize(u_int n)	;

  private:
    friend class	Enumerator;

    PageList		_pageList;
    FreeList		_freeList;
    u_int		_nelmsPerPage;
    List<Enumerator>	_enumeratorList;
};
 
}

#endif	// !__TUAllocatorPP_h
