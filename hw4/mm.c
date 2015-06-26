#include "mm.h"
static Header base;
static Header *freep = NULL;

Header *morecore(size_t nu)
{
	char *cp = NULL;
	Header *up;
	if(nu<NALLOC)
		nu=NALLOC;
	cp=(char *)sbrk(nu * sizeof(Header));
	if(cp == (char*)-1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	myfree((void *)(up+1));
	return freep;	
}
void* mymalloc(size_t size){
	Header *p,*prevp;
	unsigned nunits;
	nunits = (size + sizeof(Header)-1)/sizeof(Header)+1;
	if((prevp = freep)==NULL)
	{
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
	{
		if(p->s.size >= nunits)
		{
			if(p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else
			{
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if(p == freep)
			if((p = morecore(nunits)) == NULL)
				return NULL;
	} 
}
void* myrealloc(void* ptr,size_t size)
{
	if(ptr == NULL)
	{
		return mymalloc(sizeof(size));
	}
	if(size == 0)
	{
		myfree(ptr);
		return NULL;
	}
	Header *p = (Header *)ptr - 1;
	size_t n = (p->s.size-1)*sizeof(Header);
	void *temp = mymalloc(size);
	if(n < size)
		memcpy(temp,ptr,size);
	else
		memcpy(temp,ptr,size);
	myfree(ptr);
	return temp;
}
void* mycalloc(size_t nmemb,size_t size)
{
	void *ptr = mymalloc(nmemb * size);
	memset(ptr,0,nmemb * size);
	return ptr;
}
void myfree(void* ptr)
{
	Header *bp,*p;
	bp = (Header *)ptr - 1;
	for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
	{
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;
	}
	if(bp + bp->s.size == p->s.ptr)
	{
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}
	else
		bp->s.ptr = p->s.ptr;
	if(p + p->s.size == bp)
	{
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}
	else
		p->s.ptr = bp;
	freep = p;
}
