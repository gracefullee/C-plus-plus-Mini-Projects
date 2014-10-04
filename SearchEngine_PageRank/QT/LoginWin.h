//
//  LoginWin.h
//  
//
//  Created by D Bell on 5/7/14.
//
//

#ifndef ____LoginWin__
#define ____LoginWin__

#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <string>
#include <set>
#include <QPlainTextEdit>
#include <QRadioButton>
#include "../WebPage.h"
#include "SearchWin.h"

class SearchWin;

class LoginWin : public QMainWindow
{
    Q_OBJECT
    
public:
    LoginWin (SearchWin *parent = 0);
    ~LoginWin();

private slots:
    void newUser();
    void login();
    void logout();
    
private:
    SearchWin* parent;

    QWidget * centralWidget;
    QLabel * passwordLabel;
    QLabel * userNameLabel;
    QVBoxLayout * wholeLayout;
    QLineEdit * userNameLine;
    QLineEdit * passwordLine;
    QPushButton * loginButton;
    QPushButton * logoutButton;
    QHBoxLayout * buttonsLayout;
    QPushButton * newUserButton;
    QHBoxLayout * userNameLayout;
    QHBoxLayout * passwordLayout;

   std::string userFieldText();
   std::string passwordFieldText();
};
#endif /* defined(____LoginWin__) */
