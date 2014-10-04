#ifndef SET_H
#define SET_H

#include <stdexcept>
#include <cstdlib>
#include <set>

template <class T>
class Set : public std::set<T> {
 public: 
  Set<T> setIntersection (const Set<T> & other) const;
  /* Returns the intersection of the current set with other.
         That is, returns the set of all items that are both in this
         and in other. */

  Set<T> setUnion (const Set<T> & other) const;
  /* Returns the union of the current set with other.
         That is, returns the set of all items that are in this set
         or in other (or both).
         The resulting set should not contain duplicates. */
};

template <class T>
Set<T> Set<T>::setIntersection(const Set<T> & other) const
{
  Set<T> result;
  
  for(typename std::set<T>::iterator it=std::set<T>::begin();
      it!=std::set<T>::end(); ++it)
    {
      for(typename std::set<T>::iterator jt=other.begin(); jt!=other.end();
	  ++jt)
	{
	  if(*it == *jt)
	    {
	      result.insert(*it);
	    }
	}
    }
  return result;
}

template <class T>
Set<T> Set<T>::setUnion(const Set<T> & other) const
{
  Set<T> result;
  for(typename std::set<T>::iterator it=other.begin(); it!=other.end(); ++it)
    {
      result.insert(*it);
    }
  for(typename std::set<T>::iterator it=std::set<T>::begin();
      it!=std::set<T>::end(); ++it)
    {
      result.insert(*it);
    }
  return result;
}

#endif
