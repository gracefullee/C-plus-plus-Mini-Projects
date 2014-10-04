#ifndef DISPLAYPAGEWIN_H
#define DISPLAYPAGEWIN_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <string>
#include <set>
#include <QListWidgetItem>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QRadioButton>
#include "../WebPage.h"
#include "SearchWin.h"

class DisplayPageWin : public QMainWindow
{
  Q_OBJECT

    public:
  DisplayPageWin(SearchWin* main, WebPage* thisResult, SearchWin *parent = 0);
  ~DisplayPageWin();

  private slots:
  void doDisplaySelectedIncoming();
  void doDisplaySelectedOutgoing();


 private:
  QPushButton * btnSelectIncoming;
  QPushButton * btnSelectOutgoing;
  QHBoxLayout * wholeLayout;
  QVBoxLayout * listLayout;
  QHBoxLayout * radioLayout;
  QPlainTextEdit * searchResultDisplay; //make it read only
  QListWidget * incomingLinksList;
  QListWidget * outgoingLinksList;
  QWidget * centralWidget;
  SearchWin * mainPage;
  QRadioButton * alphabetical;
  QRadioButton * relevance;

};

#endif
