#include "SearchWin.h"
#include "DisplayPageWin.h"
#include <QList>
#include <QMessageBox>
#include <QDockWidget>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "msort.h"
#include "User.h"

using namespace std;

void filter(string &key) {
	for (unsigned int i = 0; i < key.size(); i++) {
		if (ispunct(key[i])) {
			key.erase(key.begin() + i);
		}
		if (isupper(key[i])) {
			key[i] = tolower(key[i]);
		}
	}
}

struct Charge {
	string _name;
	double _charge;
	Charge(string n, double c) :
			_name(n), _charge(c) {
	}
};

struct WebPageComp {
	bool operator()(WebPage*& lhs, WebPage*& rhs) {
		return *lhs < *rhs;
	}
};

struct StrComp {
	bool operator()(Charge*& lhs, Charge*& rhs) {
		string temp1 = lhs->_name;
		string temp2 = rhs->_name;
		filter(temp1);
		filter(temp2);
		return temp1 < temp2;
	}
};

struct AdComp {
	bool operator()(Ad*& lhs, Ad*& rhs) {
		return lhs->bid > rhs->bid;
	}
};

struct PageRankComp {
	bool operator()(WebPage*& lhs, WebPage*& rhs) {
		return lhs->get_PR() > rhs->get_PR();
	}
};

struct RelevanceComp {
    bool operator()(WebPage*& lhs, WebPage*& rhs) {
		return lhs->get_TR() > rhs->get_TR();
    }
};

SearchWin::SearchWin(char* masterFile, char* adFile, char* outFile,
		QWidget *parent) :
		QMainWindow(parent), curr_user(NULL) {
    login = new LoginWin(this);
	outputFile = outFile;
	btnQuit = new QPushButton("&Quit");
	btnAbout = new QPushButton("&About");
	btnSelect = new QPushButton("&Select");
	btnSearch = new QPushButton("&Search");
	upperLayout = new QHBoxLayout;
	lowerLayout = new QHBoxLayout;
	radioLayout = new QHBoxLayout;
	adBtnLayout = new QVBoxLayout;
	totalLayout = new QHBoxLayout;
	searchWordInput = new QLineEdit;
	displaySearchResults = new QListWidget;
	wholeLayout = new QVBoxLayout;
	centralWidget = new QWidget(this);
	alphabetical = new QRadioButton("&alphabetical");
	relevance = new QRadioButton("&relevance");
	user = new QLabel("");

	//only one item can be selected at a time
	displaySearchResults->setSelectionMode(QAbstractItemView::SingleSelection);

	//Add Widgets to UpperLayout
	upperLayout->addWidget(searchWordInput);
	upperLayout->addWidget(btnSearch);

	//Add Widgets to LowerLayout
	lowerLayout->addWidget(btnSelect);
	lowerLayout->addWidget(btnAbout);
	lowerLayout->addWidget(btnQuit);

	//Add Widgets to RadioLayout
	radioLayout->addWidget(alphabetical);
	radioLayout->addWidget(relevance);

	//Add Items to whole layout
    wholeLayout->addWidget(user);
	wholeLayout->addLayout(upperLayout);
	wholeLayout->addLayout(radioLayout);
	wholeLayout->addWidget(displaySearchResults);
	wholeLayout->addLayout(lowerLayout);

	totalLayout->addLayout(wholeLayout);
	totalLayout->addLayout(adBtnLayout);
	//Add wholeLayout to central Widget
	centralWidget->setLayout(totalLayout);

	//Set central widget to be the centralWidget
	this->setCentralWidget(centralWidget);

	connect(btnQuit, SIGNAL(clicked()), this, SLOT(outputCharges()));
	connect(btnSearch, SIGNAL(clicked()), this, SLOT(doSearch()));
	connect(searchWordInput, SIGNAL(returnPressed()), this, SLOT(doSearch()));
	connect(btnSelect, SIGNAL(clicked()), this,
			SLOT(doDisplaySelectedResult()));
	connect(btnAbout, SIGNAL(clicked()), this, SLOT(showAbout()));

	readAdfile(adFile);

	masterList = masterFile;
	std::ifstream fin(masterFile);
	if (fin.fail()) {
		throw std::invalid_argument("File not found");
	}

	//reads in all files
	std::string filename;
	fin >> filename;
	while (!fin.eof()) {
		WebPage* temp = new WebPage(filename);
        //ITERATE THROUGH USERS HERE
		allFiles.push_front(temp);
		links.insert(pair<string,WebPage*> (filename,temp));
		fin >> filename;
	}

	for(deque<WebPage*>::iterator it=allFiles.begin(); it!=allFiles.end(); ++it){
		WebPage* p = (*it);
		Set<string>* pageLinks = p->allLinks();
		for(Set<string>::iterator jt=pageLinks->begin();
				jt!=pageLinks->end(); ++jt){
			p->addOutgoingLink(links[*jt]);
			links[*jt]->addIncomingLink(p);
		}
	}
	
	//gets a set of unique words in any file
	std::deque<WebPage*>::iterator it = allFiles.begin();
	everyWord = (*it)->allWords();
	++it;
	while (it != allFiles.end()) {
		everyWord = everyWord.setUnion((*it)->allWords());
		++it;
	}

	//Maps words to files with hits
	for (Set<std::string>::iterator word = everyWord.begin();
			word != everyWord.end(); ++word) {
		Set<WebPage*> hitFiles;
		WebPage* tempPage;
		for (std::deque<WebPage*>::iterator it = allFiles.begin();
				it != allFiles.end(); ++it) {
			tempPage = *it;
			Set < std::string > wordsFromFile = tempPage->allWords();
			for (Set<std::string>::iterator fileWord = wordsFromFile.begin();
					fileWord != wordsFromFile.end(); ++fileWord) {
				if (*word == *fileWord) {
					hitFiles.insert(tempPage);
				}
			}
		}
		wordToFile.insert(
				std::pair<std::string, Set<WebPage*> >(*word, hitFiles));
	}

	fin.close();
}

SearchWin::~SearchWin() {
	cleanButtons();
	delete btnAbout;
	delete btnSelect;
	delete btnSearch;
	delete upperLayout;
	delete lowerLayout;
	delete searchWordInput;
	delete displaySearchResults;
	delete centralWidget;
	delete wholeLayout;
}

void SearchWin::doSearch() {
	int count = displaySearchResults->count();
	for (int i = 0; i <= count; i++) {
		displaySearchResults->takeItem(0);
	}
	std::string selection;
	char temp;
	QString wholeLine = searchWordInput->text();
	std::string stdWholeLine = wholeLine.toStdString();

	std::stringstream ss;
	ss << stdWholeLine;
	ss >> selection;
	temp = ss.peek();
	deque < string > wordsCopy;

	if (selection == "AND") {
		char temp1;
		ss >> temp1; //consume open paren

		std::string allLine;
		getline(ss, allLine);
		ss.str("");
		std::deque < std::string > words = getWords(allLine);
		wordsCopy = words;
		while (!wordsCopy.empty()) {
			keywords.insert(wordsCopy.front());
			wordsCopy.pop_front();
		}

		if (words.size() == 0) {
			displaySearchResults->clear();
			QMessageBox::information(this, tr("No Results"),
					tr("No web pages matched your query"));
		}

		std::deque<std::string>::iterator it = words.begin();
		std::string first = *it;
		std::string next;
		Set<WebPage*> cummulative;
		try {
			cummulative = wordToFile.at(first);
			++it;
			while (it != words.end()) {
				next = *it;
				next = allLower(next);
				Set<WebPage*> nextSet = wordToFile.at(next);
				cummulative = cummulative.setIntersection(nextSet);
				++it;
			}
		} catch (const std::out_of_range &oor) {
			displaySearchResults->clear();
			QMessageBox::information(this, tr("No Results"),
					tr("No web pages matched your query"));
		}

		Set<WebPage*> PRPageSet = cummulative;
		for (Set<WebPage*>::iterator it = cummulative.begin();
				it != cummulative.end(); ++it) {
			Set<WebPage*> outLinks = (*it)->allOutgoingLinks();
			for (Set<WebPage*>::iterator it2 = outLinks.begin();
					it2 != outLinks.end(); ++it2) {
				PRPageSet.insert(*it2);
			}
			Set<WebPage*> inLinks = (*it)->allIncomingLinks();
			for (Set<WebPage*>::iterator it2 = inLinks.begin();
					it2 != inLinks.end(); ++it2) {
				PRPageSet.insert(*it2);
			}
		}
		
		compute_PageRank(PRPageSet);

		std::vector<WebPage*> sorted;
		for (Set<WebPage*>::iterator it = cummulative.begin();
				it != cummulative.end(); ++it) {
			sorted.push_back(*it);
		}
		if (alphabetical->isChecked()) {
			WebPageComp alphaComp;
			mergeSort(sorted, alphaComp);
		} else if (relevance->isChecked()) {
			RelevanceComp Rcomp;
			mergeSort(sorted, Rcomp);
		}
		displayOptions(sorted);
	} else if (selection == "OR") {
		char temp1;
		ss >> temp1; //consume open paren

		std::string allLine;
		getline(ss, allLine);
		ss.str("");
		std::deque < std::string > words = getWords(allLine);
		wordsCopy = words;
		while (!wordsCopy.empty()) {
			keywords.insert(wordsCopy.front());
			wordsCopy.pop_front();
		}

		if (words.size() == 0) {
			displaySearchResults->clear();
			QMessageBox::information(this, tr("No Results"),
					tr("No web pages matched your query"));
		}

		std::deque<std::string>::iterator it = words.begin();
		std::string first = *it;
		std::string next;
		Set<WebPage*> cummulative;
		try {
			cummulative = wordToFile.at(first);
			++it;
			while (it != words.end()) {
				next = *it;
				next = allLower(next);
				Set<WebPage*> nextSet = wordToFile.at(next);
				cummulative = cummulative.setUnion(nextSet);
				++it;
			}
		} catch (const std::out_of_range &oor) {
			displaySearchResults->clear();
			QMessageBox::information(this, tr("No Results"),
					tr("No web pages matched your query"));
		}

		Set<WebPage*> PRPageSet = cummulative;
		for (Set<WebPage*>::iterator it = cummulative.begin();
				it != cummulative.end(); ++it) {
			Set<WebPage*> outLinks = (*it)->allOutgoingLinks();
			for (Set<WebPage*>::iterator it2 = outLinks.begin();
					it2 != outLinks.end(); ++it2) {
				PRPageSet.insert(*it2);
			}
			Set<WebPage*> inLinks = (*it)->allIncomingLinks();
			for (Set<WebPage*>::iterator it2 = inLinks.begin();
					it2 != inLinks.end(); ++it2) {
				PRPageSet.insert(*it2);
			}
		}

		compute_PageRank(PRPageSet);

		std::vector<WebPage*> sorted;
		for (Set<WebPage*>::iterator it = cummulative.begin();
				it != cummulative.end(); ++it) {
			sorted.push_back(*it);
		}
		if (alphabetical->isChecked()) {
			WebPageComp alphaComp;
			mergeSort(sorted, alphaComp);
		} else if (relevance->isChecked()) {
			RelevanceComp Rcomp;
			mergeSort(sorted, Rcomp);
		}
		displayOptions(sorted);
	}

	//a new line was entered after one word
	else if ((int) temp == 10 || ss.fail()) {
		selection = allLower(selection);
		ss.str("");
		ss.clear();
		Set<WebPage*> cummulative;
		keywords.insert(selection);

/*	
std::string s = findRoot(selection);
		Set<std::string> rootwords =this-> wordsWithPrefix(s);
		
		Set<std::string>::iterator it = rootwords.begin();
		std::string first = *it;
		std::string next;
		Set<WebPage*> cummulative;
		try {
			cummulative = wordToFile.at(first);
			++it;
			while (it != rootWords.end()) {
				next = *it;
				next = allLower(next);
				Set<WebPage*> nextSet = wordToFile.at(next);
				cummulative = cummulative.setUnion(nextSet);
				++it;
			}
		} catch (const std::out_ofrange &oor) {
			displaySearchResults->clear();
			QMessageBox::information(this, tr("No Results"),
					tr("No web pages matched your query"));
		}
*/
		try {
			cummulative = wordToFile.at(selection);
		} catch (const std::out_of_range &oor) {
			displaySearchResults->clear();
			QMessageBox::information(this, tr("No Results"),
					tr("No web pages matched your query"));
		}


		Set<WebPage*> PRPageSet = cummulative;
		for (Set<WebPage*>::iterator it = cummulative.begin();
				it != cummulative.end(); ++it) {
			Set<WebPage*> outLinks = (*it)->allOutgoingLinks();
			for (Set<WebPage*>::iterator it2 = outLinks.begin();
					it2 != outLinks.end(); ++it2) {
				PRPageSet.insert(*it2);
			}
			Set<WebPage*> inLinks = (*it)->allIncomingLinks();
			for (Set<WebPage*>::iterator it2 = inLinks.begin();
					it2 != inLinks.end(); ++it2) {
				PRPageSet.insert(*it2);
			}
		}

		compute_PageRank(PRPageSet);
        if(curr_user != NULL)
        {
            compute_total_relevance(PRPageSet);
        }
		else
		{
			for(Set<WebPage*>::iterator iter = PRPageSet.begin(); iter != PRPageSet.end(); ++iter)
			{
				(*iter)->set_TR((*iter)->get_PR());
			}
		}

		std::vector<WebPage*> sorted;
		for (Set<WebPage*>::iterator it = cummulative.begin();
				it != cummulative.end(); ++it) {
			sorted.push_back(*it);
		}
		if (alphabetical->isChecked()) {
			WebPageComp alphaComp;
			mergeSort(sorted, alphaComp);
		} else if (relevance->isChecked()) {
			RelevanceComp Rcomp;
			mergeSort(sorted, Rcomp);
		}
		displayOptions(sorted);
	} else {
		ss.clear();
		ss.str("");
		displaySearchResults->clear();
		QMessageBox::information(this, tr("No Results"),
				tr("No web pages matched your query"));
	}
	
	//Get Set for Advertisement
	map<string,double> matchingAds;
	Set<string> companies;
	for (Set<string>::iterator it = keywords.begin(); it != keywords.end();
			++it) {
		if (adSet.find(*it) != adSet.end()) {
			Set<Ad*> match = adSet[*it];
			for (Set<Ad*>::iterator jt = match.begin(); jt != match.end();
					++jt) {
				
				if(companies.find((*jt)->name)!=companies.end()){
					double bid1 = matchingAds[(*jt)->name];
					double bid2 = (*jt)->bid;
					if (bid1 < bid2) {
						matchingAds[(*jt)->name] = bid2;
					}
				}
				else {
					matchingAds.insert(pair<string,double> ((*jt)->name,(*jt)->bid));
					companies.insert((*jt)->name);
				}
			}
		}
	}

	if (matchingAds.size() > 0) {
		createAdButtons(matchingAds);
	}
	else cleanButtons();
	

	keywords.clear();
}

void SearchWin::doDisplaySelectedResult() {
	QList<QListWidgetItem*> selected = displaySearchResults->selectedItems();
	QList<QListWidgetItem*>::iterator it;

	for (it = selected.begin(); it != selected.end(); ++it) {
		if ((*it)->isSelected() == true) {
			for (std::deque<WebPage*>::iterator jt = allFiles.begin();
					jt != allFiles.end(); ++jt) {
				if ((*jt)->filename() == (*it)->text().toStdString()) {
					emit constructedNewDisplayWin();
					DisplayPageWin* nextWindow = new DisplayPageWin(this, *jt,
							this);
					nextWindow->setWindowTitle((*it)->text());
					nextWindow->show();
					break;
				}
			}
		}
	}
}

void SearchWin::showAbout() {
	QMessageBox::information(this, tr("About"),
			tr("David, Elif and Yoo Jin's Search Engine"));
}

std::string SearchWin::allLower(std::string toChange) {
	for (unsigned int i = 0; i < toChange.size(); i++) {
		if (std::isupper(toChange.at(i)) && std::isalnum(toChange.at(i))) {
			toChange.at(i) = std::tolower(toChange.at(i));
		}
	}
	return toChange;
}

std::deque<std::string> SearchWin::getWords(std::string restOfLine) {
	int alnum = 0;
	int other = 1;
	int state = other;
	char temp;
	std::string tempStr;
	std::stringstream ss;
	std::deque < std::string > allWords;

	for (unsigned int i = 0; i < restOfLine.size(); i++) {
		temp = restOfLine.at(i);
		if (state == other) {
			if (std::isalnum(temp)) {
				state = alnum;
				if (std::isalpha(temp) && std::isupper(temp)) {
					temp = std::tolower(temp);
				}
				ss << temp;
			}
		} else {
			if (std::isalnum(temp)) {
				if (std::isalpha(temp) && std::isupper(temp)) {
					temp = std::tolower(temp);
				}
				ss << temp;
			} else {
				state = other;
				tempStr = ss.str();
				allWords.push_front(tempStr);

				ss.str("");
			}
		}
		temp = restOfLine.at(i);
	}
	return allWords;
}

void SearchWin::displayOptions(std::vector<WebPage*> &setOfResults) const {
	std::vector<WebPage*>::iterator it;
	for (it = setOfResults.begin(); it != setOfResults.end(); ++it) {
		QString searchResult((*it)->filename().c_str());
		QListWidgetItem* temp = new QListWidgetItem(searchResult);
		displaySearchResults->addItem(temp);
	}
}


std::deque<WebPage*> & SearchWin::getAllFiles() {
	return allFiles;
}

void SearchWin::compute_PageRank(Set<WebPage*> &result) {
	
	//EDITED: CARRIES HIGHER PR FOR PAGE WHERE KEYWORDS ARE BOLD/ITALIC/HEADER
	double alpha = 0.15;
	double N = result.size();

	for (Set<WebPage*>::iterator it = result.begin(); it != result.end();
			++it) {
		(*it)->set_PR(1/N);
	}
	
	//for each iteration
	for (int i = 0; i < 30; i++) {
		//make a map of temp PR values - initialized to zero each iteration
		std::map<WebPage*, double> PRList;
		for (Set<WebPage*>::iterator it = result.begin(); it != result.end(); ++it) {
			PRList.insert(pair<WebPage*, double>(*it, 0));
		}

		//loop through all webPages
		for (Set<WebPage*>::iterator it = result.begin(); it != result.end(); ++it) {
			//get the subset of its outgoing links within the expanded results list
			Set<WebPage*> expandedOutLinks = ((*it)->allOutgoingLinks()).setIntersection(result);
			//if it's a sink node, distribute its PR among all pages
			if (expandedOutLinks.size() == 0) {
				for (Set<WebPage*>::iterator jt = result.begin();
						jt != result.end(); ++jt) {
					PRList[*jt] += ((*it)->get_PR()) / N;
				}
			}
			else {
				int countEmph = 0;	
				for (Set<WebPage*>::iterator jt = result.begin(); jt != result.end(); ++jt) {
					if(checkEmphasis(*jt)){
						countEmph++;
					}
				}
				//distribute a (1-a) fraction of PR to all its outgoing links
				//MODIFIED: (1-a) fraction is distributed so that pages with emphasis
				//carry DOUBLE the weight/probability compared to the ones without emphasis				
				for (Set<WebPage*>::iterator jt = expandedOutLinks.begin();
						jt != expandedOutLinks.end(); ++jt) {
					if(checkEmphasis(*jt))
						PRList[*jt] += ((1.5*(1 - alpha)) * ((*it)->get_PR()))/(expandedOutLinks.size()+countEmph);
					else{
						PRList[*jt] += ((1 - alpha) * ((*it)->get_PR()))/(expandedOutLinks.size()+countEmph);
					}
				}
				//distribute the remaining (a) fraction to every page not including itself
				//MODIFIED: remaining (a) fraction is distributed so that pages with emphasis
				//carry DOUBLE the weight/probability compared to the ones without emphasis
				for (Set<WebPage*>::iterator jt = result.begin(); jt != result.end(); ++jt) {
					if((*jt)!=(*it)){
						if(checkEmphasis(*jt))
							PRList[*jt] += ((1.5*alpha) * ((*it)->get_PR())) / (result.size()+(countEmph));
						else{
							PRList[*jt] += (alpha * ((*it)->get_PR()) / (result.size()+(countEmph)));
						}
					}
				}
			}
		}
		//set the actual value of PR to be the recently summed temp value
		for (Set<WebPage*>::iterator it = result.begin(); it != result.end();
				++it) {
			(*it)->set_PR(PRList[*it]);
		}
		
		PRList.clear();
	}

}

void SearchWin::compute_total_relevance(Set<WebPage*> & result)
{
    int N = result.size();
    for(Set<WebPage*>::iterator iter = result.begin(); iter != result.end(); ++iter)
    {
        double tr = (*iter)->get_PR() + static_cast<double>(curr_user->get_relevance(*iter))/N;
        (*iter)->set_TR(tr);
    }
}

void SearchWin::readAdfile(char* adFile) {
	int num;
	ifstream ifile(adFile);
	ifile >> num;
	ifile.ignore(80, '\n');
	for (int i = 0; i < num; i++) {
		double bid;
		string name, keyword, line, temp;
		stringstream l;
		getline(ifile, line);
		l << line;
		l >> keyword;
		filter(keyword);
		l >> bid;
		while (l >> temp) {
			name.append(temp);
			if (l)
				name.append(" ");
		}
		Ad *newAd = new Ad(name, bid);
		if (adCharges.find(name) == adCharges.end())
			adCharges.insert(pair<string, double>(name, 0));
		if (adSet.find(keyword) == adSet.end()) {
			Set<Ad*> adSubset;
			adSubset.insert(newAd);
			adSet.insert(pair<string, Set<Ad*> >(keyword, adSubset));
		} else {
			adSet[keyword].insert(newAd);
		}
	}
}

void SearchWin::createAdButtons(map<string,double> &matchingAd) {

	vector<Ad*> sortedAd;
	AdComp comp;
	for (map<string,double>::iterator it = matchingAd.begin(); it != matchingAd.end();
			++it) {
		Ad* newAd = new Ad((*it).first,(*it).second);
		sortedAd.push_back(newAd);
	}

	mergeSort(sortedAd, comp);

	generateButtons(sortedAd);

}

void SearchWin::showAd(Ad* adver) {
	//Charge
	adCharges[adver->name] += adver->bid;
	//Show visited
	stringstream m;
	string message;
	string temp = "You've visited ";
	m << temp << adver->name << ".";
	message = m.str();
	QMessageBox::information(this, QString::fromStdString(adver->name),
			QString::fromStdString(message));
}

void SearchWin::outputCharges() {
	ofstream ofile(outputFile);

	vector<Charge*> Charges;
	for (unordered_map<string, double>::iterator it = adCharges.begin();
			it != adCharges.end(); ++it) {
		Charge* newCharge = new Charge((*it).first, (*it).second);
		Charges.push_back(newCharge);
	}

	StrComp comp;
	mergeSort(Charges, comp);

	for(vector<Charge*>::iterator it = Charges.begin(); it != Charges.end();
			++it) {
		ofile << (*it)->_name << endl;
		ofile << (*it)->_charge << endl;
		ofile << endl;
	}
	ofile.close();

	this->close();

}

void SearchWin::generateButtons(vector<Ad*> matches) {
	cleanButtons();

	for (vector<Ad*>::iterator it = matches.begin(); it != matches.end();
			++it) {
		AdPushButton *btnAd = new AdPushButton(*it);
		setButtons.insert(btnAd);
		setAdsBid.insert(pair<string, Ad*>((*it)->name, *it));
		adBtnLayout->addWidget(btnAd);
		connect(btnAd, SIGNAL(ClickedWithArgument(Ad*)), this, SLOT(showAd(Ad*)));
	}

}

void SearchWin::cleanButtons(void) {
	for (auto b : setButtons) {
		adBtnLayout->removeWidget(b);
		delete b;
	}
	
	setButtons.clear();
}

bool SearchWin::checkEmphasis(WebPage* page)
{
	Set<string> interSet, EmphasisSet;
	EmphasisSet = page->allEmphs();
	interSet = EmphasisSet.setIntersection(keywords);
	if(EmphasisSet.size()>0)
		return true;
	else{
		return false;
	}
}

std::string SearchWin:: findRoot (std::string word)
{

  map < std::string, std::string > irregular;
  irregular["became"] = "become";
  irregular["blew"] = "blow";
  irregular["broke"] = "break";
  irregular["came"] = "come";
  irregular["ate"] = "eat";
  irregular["fed"] = "feed";
  irregular["fought"] = "fight";
  irregular["found"] = "find";
  irregular["went"] = "go";
  irregular["paid"] = "pay";
  irregular["sold"] = "sell";
  irregular["slept"] = "sleep";
  irregular["ran"] = "run";
  irregular["won"] = "win";
  irregular["wrote"] = "write";

  if (irregular.find (word) != irregular.end ())
    return irregular[word];

  int i = word.length ();

  if (word.length () > 2 && word[i - 1] == 's')
    {

      if (word.substr (i - 3) == "ies")
	{			//eg. puppies to puppy
	word = word.substr(0, i-3);
	i = i-3;
	  word += "y";
	}
      else if ((i > 3 && word.substr (i - 4) == "sses")){
	word = word.substr(0, i-2);
	i = i-2;
}
      else if (word[i - 2] != 's')
	{
	  word = word.substr (0, i - 1);	//to prevent removing s from words such as success
	  --i;
	}
    }
  if (i > 3 && word.substr (i - 2) == "ed" && word[i - 3] != 'e')
    {				//to prevent cutting succeed etc.

      if (word.substr (i - 4, 2) == "bl")
	{			//eg. convert enabled to enable instead of enabl

	  word.erase (i - 1);
	  i--;
	}

      else if (word[i - 3] == 'i')
	{			//eg. bullied
	word = word.substr(0, i-3);
	i = i-3;
	  word += "y";

	}
      else if (word.substr (i - 4, 2) == "iz")
	{			//eg. energized to energize
	  word.erase (i - 1);
	  i--;
	}
      else if (word[i - 3] != 'x' && word[i - 3] != 'w' && word[i - 3] != 'y')
	{
	  word.erase (i - 1);
	  i--;
	}

      else
	word = word.substr(0, i-2);
	i = i-2;
    }

  if (i > 3 && word.substr (i - 3) == "ing"){
	word = word.substr(0, i-3);
	i = i-3;
}
  if (i > 7)
    {
      if (word.substr (i - 7) == "ational")
	{

	word = word.substr(0, i-5);
	i = i-5;
	  word += "e";
	}
      else if (word.substr (i - 7) == "ization")
	{

	word = word.substr(0, i-5);
	i = i-5;
	  word += "e";
	}

    }

  if (i > 6)
    {
      if (word.substr (i - 6) == "tional"){
	word = word.substr(0, i-2);
	i = i-2;
}
      else if (word.substr (i - 6) == "biliti")
	{

	word = word.substr(0, i-6);
	i = i-6;

	  word += "ble";
	}


    }
  if (i > 5)
    {

      if (word.substr (i - 5) == "alism" || word.substr (i - 5) == "alize"
	  || word.substr (i - 5) == "icate")

	{	
	word = word.substr(0, i-3);
	i = i-3;
	}


      else if (word.substr (i - 5) == "ality")
{
	word = word.substr(0, i-3);
	i = i-3;
}
      else if (word.substr (i - 5) == "ivity")
	{

	word = word.substr(0, i-3);
	i = i-3;
	  word += "e";
	}
      else if (word.substr (i - 5) == "ation")
	{

	word = word.substr(0, i-3);
	i = i-3;
	  word += "e";
	}
      else if (word.substr (i - 5) == "ement")
	{

	word = word.substr(0, i-4);
	i = i-4;

	}
    }


  if (i > 4)
    {
      if (word.substr (i - 4) == "izer")
	{
word = word.substr(0, i-4);
	i = i-4;
	}
      else if (word.substr (i - 4) == "ator")
	{
word = word.substr(0, i-2);
	i = i-2;
	  word += "e";
	}
      else if (word.substr (i - 4) == "ness")
	{
word = word.substr(0, i-4);
	i = i-4;
	}
      else if (word.substr (i - 4) == "able")
	{
word = word.substr(0, i-4);
	i = i-4;
	}
      else if (word.substr (i - 4) == "tion")
	{

word = word.substr(0, i-3);
	i = i-3;
	  word += "e";
	}
      else if (word.substr (i - 4) == "ency" || word.substr (i - 4) == "ancy")
	{

word = word.substr(0, i-3);
	i = i-3;
	  word += "e";
	}
      else if (word.substr (i - 4) == "ancy")
	{

word = word.substr(0, i-3);
	i = i-3;
	  word += "e";
	}
      else if (word.substr (i - 4) == "ical")
	{


word = word.substr(0, i-2);
	i = i-2;
	}
    }
  if (i > 3)
    {

      if (word.substr (i - 3) == "ful")
	{


word = word.substr(0, i-3);
	i = i-3;
	}
      else if (word.substr (i - 3) == "ism")
	{

word = word.substr(0, i-3);
	i = i-3;
	}
      else if (word.substr (i - 3) == "ive" || word.substr (i - 3) == "ize")
	{

word = word.substr(0, i-3);
	i = i-3;
	}

      else if (word.substr (i - 3) == "bly")
	{

word = word.substr(0, i-1);
	i--;
	  word += "e";
	}
    }

  if (i > 2)
    {
      if (word.substr (i - 2) == "er")
{
word = word.substr(0, i-2);
	i = i-2;
}

    }


  return word;
}



Set<std::string> & SearchWin::wordsWithPrefix(std::string & pref)
{
	int pref_size = pref.size();
	Set<string>* return_set = new Set<string>();
	for(Set<string>::iterator iter = everyWord.begin(); iter != everyWord.end(); ++iter)
	{
		int wd_size = iter->size();
		if(pref_size > wd_size)
		{
			continue;
		}
		for(int i = 0; i < pref_size; i++)
		{
			if(pref[i] != (*iter)[i])
			{
				continue;
			}
		}		
		return_set->insert(*iter);					
	}
	return *return_set;	
}

