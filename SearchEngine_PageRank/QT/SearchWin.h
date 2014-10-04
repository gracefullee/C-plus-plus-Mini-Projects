#ifndef SEARCHWIN_H
#define SEARCHWIN_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <string>
#include <set>
#include <QLabel>
#include <QListWidgetItem>
#include <QListWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <deque>
#include <map>
#include <vector>
#include <unordered_map>
#include "../WebPage.h"
#include "AdPushButton.h"
#include "User.h"
#include "LoginWin.h"
class LoginWin;

class SearchWin : public QMainWindow
{
  Q_OBJECT

    //    friend class DisplayPageWin;
    public:
  SearchWin(char* masterFile, char* adFile, char* outFile, QWidget *parent = 0);
  ~SearchWin();
  std::map<std::string, User*> users;
  User* curr_user;
  QLabel * user;
  
  std::deque<WebPage*> & getAllFiles();
  
	private slots:
	  void outputCharges();
	  void doDisplaySelectedResult();
	  void showAbout();
	  void doSearch();
	  void readAdfile(char * adFile);
	  void showAd(Ad* adver);
	  void createAdButtons(std::map<std::string,double> &Adver);
	  void generateButtons(std::vector<Ad*> matches);
  
  signals:
  void constructedNewDisplayWin();
  
  
 private:
  void cleanButtons(void);
  bool checkEmphasis(WebPage* page);
  std::string allLower(std::string toChange);
  std::deque<std::string> getWords(std::string restOfLine);
  void displayOptions(std::vector<WebPage*> &setOfResults) const;
  void compute_PageRank (Set<WebPage*> &result);
  void compute_total_relevance(Set<WebPage*> & result);
  std::string findRoot(std::string word);
  Set<std::string> & wordsWithPrefix(std::string & pref);

  std::string masterList;
  
  LoginWin * login;
  QPushButton * btnQuit;
  QPushButton * btnAbout;
  QPushButton * btnSelect;
  QPushButton * btnSearch;
  QHBoxLayout * upperLayout;
  QHBoxLayout * lowerLayout;
  QHBoxLayout * radioLayout;
  QLineEdit * searchWordInput;
  QListWidget * displaySearchResults;
  QVBoxLayout * wholeLayout;
  QVBoxLayout * adBtnLayout;
  QHBoxLayout * totalLayout;
  QDockWidget * dock;
  QPushButton ** adButtons;
  QWidget * centralWidget;
  QRadioButton * alphabetical;
  QRadioButton * relevance;
  char* outputFile;

  Set<std::string> keywords;
  Set<AdPushButton*> setButtons;
  std::unordered_map<std::string, Ad* > setAdsBid;
  std::unordered_map<std::string, Set<Ad*> > adSet;
  std::set<std::string> adKeys;
  std::unordered_map<std::string,double> adCharges;
  std::set<QListWidgetItem*> searchResults;
  std::deque<WebPage*> allFiles;
  std::map<std::string,WebPage*> links;
  Set<std::string> everyWord;
  std::map<std::string, Set<WebPage*> > wordToFile;

};

#endif
