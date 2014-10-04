#ifndef OSTREAM_CPP
#define OSTREAM_CPP

#include <iostream>

using namespace std;

std::ostream& operator<<(std::ostream & os, const WebPage& page)
{
	for(unsigned int i=0; i<page.original.size(); i++){
		stringstream p; string word;
		p << page.original[i];
		while(p >> word){
			if(word[0]=='['){
				string alink = word.substr(1,word.find(']')-1);
				if(page.atext.find(alink)!=page.atext.end()){
					os << alink;
				}
				else{
					os << word;
				}
			}
			else{
				os << word;
			}
			os << " ";
		}
		os << endl;
	}
	return os;
}

#endif

