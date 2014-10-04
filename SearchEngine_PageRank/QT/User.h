//
//  User.h
//  
//
//  Created by D Bell on 5/7/14.
//
//

#ifndef ____User__
#define ____User__

#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include "../WebPage.h"

class User
{
public:
    std::string user_name;
    std::string password;
    
    User()
    {
        
    }

    User(std::string user, std::string pass) : user_name(user), password(pass)
    {

    }
    
    User(std::deque<WebPage*> & allFiles)
    {
        for(std::deque<WebPage*>::iterator iter = allFiles.begin(); iter != allFiles.end(); ++iter)
        {
            relevance_chart[*iter] = 0;
        }
    }
    
    ~User()
    {
        
    }
    
    int get_relevance(WebPage* pg)
    {
        return relevance_chart[pg];
    }
    
    void increment_rel(WebPage* pg)
    {
        relevance_chart[pg] += 1;
    }
    
    void decrement_rel(WebPage* pg)
    {
        relevance_chart[pg] -= 1;
    }
    
private:
    std::map<WebPage*, int> relevance_chart;
    
};

#endif /* defined(____User__) */
