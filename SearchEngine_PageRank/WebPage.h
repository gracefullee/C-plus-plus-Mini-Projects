// required headers go here
#ifndef WEBPAGE_H
#define WEBPAGE_H

#include "lib/set.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

class WebPage{
  public:
    WebPage ();    // constructor that creates an empty page
    WebPage (std::string filename);
      /* constructor that initializes the page from the given file.
         Should throw an exception if the file does not exist
         or has other problems. */
    ~WebPage ();   // destructor

    Set<std::string> allWords () const;
      /* Returns a set containing all individual words on the web page. */   

    bool operator==(const WebPage& other) const;

    bool operator<(const WebPage& other) const;
		
	void filter (std::string &key);

    friend std::ostream & operator<< (std::ostream & os, const WebPage & page);
      /* Declares an operator we can use to print the web page. */

    Set<WebPage*> allOutgoingLinks () const;
          /* Returns "pointers" to all webpages that this page has links to.
             As discussed above, this could be as a set or via an iterator,
             and it could be as actual pointers, or as strings,
             or possibly other. */

    Set<WebPage*> allIncomingLinks () const;
          /* Returns "pointers" to all webpages that link to this page.
             Same consideration as previous function. */

    std::string filename () const;
          /* Returns the filename from which this page was read. */

    Set<std::string>* allLinks();
    
    Set<std::string> allEmphs();
    
    Set<WebPage*>::iterator beginIncoming();
      
	Set<WebPage*>::iterator endIncoming();
  
	Set<WebPage*>::iterator beginOutgoing();
  	  
	Set<WebPage*>::iterator endOutgoing();
    
    void set_PR (double num);
    
    double get_PR () const;
    
    void set_TR (double num); //must impl
    
    double get_TR () const;
    
    std::vector<std::string> getOriginal() const;
    
    Set<std::string> allAtext() const;

        /* Based on which overall architecture you choose, you may
           also need/want some or all of the following functions. */

    void parse ();
          /* actually parses the content of the filename that was passed
             to the constructor into the object. */

    void addIncomingLink (WebPage* start);
          /* Adds a link from start to the current page
             in the current page's storage. */

    void addOutgoingLink (WebPage* target);
          /* Adds a link from the current page to the target
             in the current page's storage. */

  private:
    bool CheckHeader (std::string &key);
    Set<std::string> words;
    std::vector<std::string> original;
    std::string name;
    Set<WebPage*> outgoingLinks;
    Set<WebPage*> incomingLinks;
    Set<std::string> link;
    Set<std::string> atext;
    Set<std::string> emphSet;
    double PR;
    double total_relevance;
};

#endif
