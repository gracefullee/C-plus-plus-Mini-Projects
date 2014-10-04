#include "DisplayPageWin.h"
#include <sstream>
#include <deque>
#include <QLabel>

DisplayPageWin::DisplayPageWin(SearchWin* main, WebPage* thisResult, 
			       SearchWin *parent) : QMainWindow(parent)
{
  if(parent->curr_user != NULL)
  {
  	parent->curr_user->increment_rel(thisResult);
  }
  btnSelectIncoming = new QPushButton("&Select");
  btnSelectOutgoing = new QPushButton("&Select");
  wholeLayout = new QHBoxLayout;
  listLayout = new QVBoxLayout;
  radioLayout = new QHBoxLayout;
  searchResultDisplay = new QPlainTextEdit;
  incomingLinksList = new QListWidget;
  outgoingLinksList = new QListWidget;
  centralWidget = new QWidget;
  alphabetical = new QRadioButton("&alphabetical");
  relevance = new QRadioButton("&relevance");

  //Make the webPage display read only 
  searchResultDisplay->setReadOnly(true);

  //Fill RadioLayout
  radioLayout->addWidget(alphabetical);
  radioLayout->addWidget(relevance);

  //Fill list vbox with lists and buttons and labels
  QString temp("incoming");
  QLabel* incoming = new QLabel(temp);
  listLayout->addWidget(incoming);
  listLayout->addWidget(incomingLinksList);
  listLayout->addWidget(btnSelectIncoming);
  temp = "outgoing";
  QLabel* outgoing = new QLabel(temp);
  listLayout->addWidget(outgoing);
  listLayout->addWidget(outgoingLinksList);
  listLayout->addWidget(btnSelectOutgoing);
  listLayout->addLayout(radioLayout);

  //build HBoxLayout
  wholeLayout->addWidget(searchResultDisplay);
  wholeLayout->addLayout(listLayout);
 
  //set layout for central widget
  centralWidget->setLayout(wholeLayout);

  //set central widget as the central widget
  this->setCentralWidget(centralWidget);

  //connect Select buttons
  connect(btnSelectIncoming, SIGNAL(clicked()), this, 
	  SLOT(doDisplaySelectedIncoming()));
  connect(btnSelectOutgoing, SIGNAL(clicked()), this,
	  SLOT(doDisplaySelectedOutgoing()));
  connect(main, SIGNAL(constructedNewDisplayWin()), this, SLOT(close()));

  //Display the Web Page contents
  std::stringstream ss;
  ss << *thisResult;
  std::string stdPageText = ss.str();

  //take out brackets and links from the display text
  for(std::string::iterator it=stdPageText.begin(); it!=stdPageText.end(); 
      it++)
    {
      if(*it == '[')
	{
	  stdPageText.erase(it);
	}
      else if (*it == ']')
	{
	  stdPageText.erase(it);
	  //if the character immediately after close bracket is an open paren
	  //then it denotes a link and should not be displayed
	  
	  if(*it == '(')
	    {
	      while(*it != ')')
		{
		  stdPageText.erase(it);
		}
	      //now remove the close paren
	      stdPageText.erase(it);
	    }

	}
    }
  
  //Display the web page
  QString pageText(stdPageText.c_str());
  searchResultDisplay->setPlainText(pageText);

  //Display incoming links
  Set<WebPage*>::iterator it;
  for(it=thisResult->beginIncoming(); it!=thisResult->endIncoming(); ++it)
    {
      QString incomingLink((*it)->filename().c_str());
      QListWidgetItem* temp = new QListWidgetItem(incomingLink);
      incomingLinksList->addItem(temp);
    }
  
  //Display outgoing links
  for(it=thisResult->beginOutgoing(); it!=thisResult->endOutgoing(); ++it)
    {
      QString outgoingLink((*it)->filename().c_str());
      QListWidgetItem* temp = new QListWidgetItem(outgoingLink);
      outgoingLinksList->addItem(temp);
    }

  mainPage = main;
}

DisplayPageWin::~DisplayPageWin()
{
  delete btnSelectIncoming;
  delete btnSelectOutgoing;
  delete wholeLayout;
  delete listLayout;
  delete searchResultDisplay;
  delete incomingLinksList;
  delete outgoingLinksList;
  delete centralWidget;
}

void DisplayPageWin::doDisplaySelectedIncoming()
{
  QList<QListWidgetItem*> selected = incomingLinksList->selectedItems();
  QList<QListWidgetItem*>::iterator it;
  for(it=selected.begin(); it!=selected.end(); ++it)
    {
      if((*it)->isSelected() == true)
	{
	  std::deque<WebPage*>::iterator jt;
	  for(jt=mainPage->getAllFiles().begin(); 
	      jt!=mainPage->getAllFiles().end(); ++jt)
	    {
	      if((*jt)->filename() == (*it)->text().toStdString())
		{
		  DisplayPageWin* nextWindow = new DisplayPageWin(mainPage,
								  *jt, mainPage);
		  nextWindow->setWindowTitle((*it)->text());
		  nextWindow->show();
		  this->close();
		  break;
		}
	    }
	}
    }
}

void DisplayPageWin::doDisplaySelectedOutgoing()
{
  QList<QListWidgetItem*> selected = outgoingLinksList->selectedItems();
  QList<QListWidgetItem*>::iterator it;
  for(it=selected.begin(); it!=selected.end(); ++it)
    {
      if((*it)->isSelected() == true)
	{
	  for(std::deque<WebPage*>::iterator jt=mainPage->getAllFiles().begin(); 
	      jt!=mainPage->getAllFiles().end(); ++jt)
	    {
	      if((*jt)->filename() == (*it)->text().toStdString())
		{
		  DisplayPageWin* nextWindow = new DisplayPageWin(mainPage, 
								  *jt, mainPage);
		  nextWindow->setWindowTitle((*it)->text());
		  nextWindow->show();
		  this->close();
		  break;
		}
	    }
	}
    }
}
