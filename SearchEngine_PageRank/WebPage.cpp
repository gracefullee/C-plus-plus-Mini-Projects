#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <cctype>
#include <vector>
#include <stack>
#include <map>
#include "WebPage.h"
#include "ostream.cpp"
#include <cctype>

using namespace std;

WebPage::WebPage()
{

}

WebPage::WebPage(string filename)
{
	ifstream ifile(filename.c_str());
	if(ifile.fail())
		throw invalid_argument ("Please enter a valid filename.");
	name = filename;
	stringstream orig;
	string line, word;
	while(!ifile.eof()){
		getline(ifile,line);
		stringstream orig, n;
		string origLine;
		
		n << line;
		while (n >> word){
			if(word.front()=='['){
				stringstream l;

				l << word << " ";
				while(word.find(']')==std::string::npos){
					n >> word;
					if(word.find(']')==std::string::npos) l << word << " ";
					else{
						l << word;
					}
				}
				word = l.str();
				l.clear();
				string alink = word.substr(1,word.find(']')-1);
				word.erase(0,word.find(']')+1);
				if(word[0]=='('){
					stringstream ln;
					ln << word << " ";
					while(word.find(')')==std::string::npos){
						n >> word;
						if(word.find(')')==std::string::npos) l << word << " ";
						else{
							ln << word;
						}
					}
					word = ln.str();
					string fname = word.substr(1,word.find(')')-1);
					link.insert(fname);
					word.clear();
				}
				else{
					throw invalid_argument ("Invalid Link Format.");
				}
				words.insert(alink);
				orig << alink;
				atext.insert(alink);
			}
			
			//BOLD OR ITALIC
			else if(word.front()=='_' || word.front()=='*')
			{
				char symbol = word.front();
				stringstream e, r;
				string emph, real;
				bool correctFormat = true;
				bool DoubleCheck = false;
				emph = word;
				r << emph;
				if(emph.front()==emph[1]){
					DoubleCheck = true;
					emph.erase(0,2);
				}
				else{
					emph.erase(0,1);
				}
				e << emph;
				while(emph.back()!=symbol)
				{
					n >> emph;
					r << " " << emph;
					e << " " << emph;
					if(n.eof() && emph.back()!=symbol)
						correctFormat = false;
				}
				emph = e.str();
				if(correctFormat==true)
				{
					emph.erase(emph.size()-1,1);
					if(DoubleCheck==true && emph.back()==symbol)
						emph.erase(emph.size()-1,1);
					else if(DoubleCheck==true && emph.back()!=symbol)
						correctFormat=false;
					else if(DoubleCheck==false && emph.back()==symbol)
						correctFormat=false;
					orig << emph;
					filter(emph);
					stringstream w; string word2;
					w << emph;
					while(w >> word2){
						words.insert(word2);
						if(correctFormat==true){
							emphSet.insert(word2);
						}
					}
				}
				else{
					real = r.str();
					orig << real;
					filter(real);
					stringstream w; string word2;
					w << real;
					while(w >> word2){
						words.insert(word2);
					}
				}
			}
			
			//HEADERS
			else if(word.front()=='#')
			{
				bool valid = true;
				while(word.front()=='#')
					word.erase(0,1);
				stringstream h;
				h << word;
				string _word;
				n >> _word;
				h << _word;
				while(!CheckHeader(_word))
				{
					n >> _word;
					if(!CheckHeader(_word))
						h << " " << _word;
				}
				_word = h.str();
				orig << _word;
				filter(_word);
				stringstream w; string word2;
				w << _word;
				while(w >> word2){
					words.insert(word2);
					if(valid==true){
						cout << word2 << endl;
						emphSet.insert(word2);
					}
				}
				
			}
			else{
				orig << word;
				filter(word);
				stringstream w; string word2;
				w << word;
				while(w >> word2){
					words.insert(word2);
				}
			}
			orig << " ";
		}
		origLine = orig.str();
		original.push_back(origLine);
		orig.clear();
	}
	ifile.close();
}

WebPage::~WebPage()
{
	
}

Set<string> WebPage::allWords() const
{
	return words;
}

Set<string>* WebPage::allLinks()
{
	return &link;
}

vector<string> WebPage::getOriginal() const
{
	return original;
}

Set<string> WebPage::allAtext() const
{
	return atext;
}

bool WebPage::operator==(const WebPage& other) const
{
	return (this->name == other.name);
}

bool WebPage::operator<(const WebPage& other) const
{
	return (this->name < other.name);
}

void WebPage::filter(string &key)
{
	for(unsigned int i=0; i<key.size(); i++){
		if(!isalnum(key[i])){
			key[i] = ' ';
		}
		if(isupper(key[i])){
			key[i] = tolower(key[i]);
		}
	}
}

string WebPage::filename() const
{
	return name;
}


Set<WebPage*> WebPage::allOutgoingLinks () const
{
	return outgoingLinks;
}

Set<WebPage*> WebPage::allIncomingLinks () const
{
	return incomingLinks;
}

Set<WebPage*>::iterator WebPage::beginIncoming()
{
  return incomingLinks.begin();
}

Set<WebPage*>::iterator WebPage::endIncoming()
{
  return incomingLinks.end();
}

Set<WebPage*>::iterator WebPage::beginOutgoing()
{
  return outgoingLinks.begin();
}

Set<WebPage*>::iterator WebPage::endOutgoing()
{
  return outgoingLinks.end();
}

void WebPage::addIncomingLink (WebPage* start)
{
	incomingLinks.insert(start);
}

void WebPage::addOutgoingLink (WebPage* target)
{
	outgoingLinks.insert(target);
}

double WebPage::get_PR () const
{
	return PR;
}

void WebPage::set_PR (double num)
{
	PR = num;
}

double WebPage::get_TR () const
{
    return total_relevance;
}

void WebPage::set_TR (double num)
{
    total_relevance = num;
}

bool WebPage::CheckHeader(string &h)
{
	if(h.front()!='#')
		return false;
	bool Check = true;
	for(unsigned int i=0; i<h.size(); i++)
	{
		if(h.front()!=h[i])
			Check = false;
		if(Check==false)
			break;
	}
	return Check;
}

Set<std::string> WebPage::allEmphs()
{
	return emphSet;
}
