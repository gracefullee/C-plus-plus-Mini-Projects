#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
  public:
    virtual ~IList () {}  // destructor

    virtual int size () const = 0; 
      // returns the number of elements in the list

    virtual void insert (int position, const T & val) = 0;
      /* Inserts val into the list before the given position,
         shifting all later items one position to the right.
         Inserting before 0 (i.e., position = 0) makes it the 
         new first element.
         Inserting before size() (i.e., position = size()) makes 
         it the new last element.
         Your function should throw an exception if position is
         outside the legal range, which would be 0-size() here. */

    virtual void remove (int position) = 0;
      /* Removes the item from the given position, shifting all
         later items one position to the left.
         Your function should throw an exception if position is
         outside the legal range, which is 0-(size()-1) here. */

    virtual void set (int position, const T & val) = 0;
      /* Overwrites the given position with the given value.
         Does not affect any other positions.  
         Your function should throw an exception if position is
         outside the legal range, which is 0-(size()-1) here. */

    virtual T& get (int position) = 0;
         /* Returns the item at the given position.
            Your function should throw an exception if position is
            outside the legal range. */

    virtual T const & get (int position) const = 0 ;
      /* Returns the item at the given position.
         Your function should throw an exception if position is
         outside the legal range, which is 0-(size()-1) here. */
};

#endif
