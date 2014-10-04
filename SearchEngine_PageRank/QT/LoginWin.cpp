//
//  LoginWin.cpp
//  
//
//  Created by D Bell on 5/7/14.
//
//

#include "LoginWin.h"
#include <stdexcept>

LoginWin::LoginWin(SearchWin *parent) : QMainWindow(parent), parent(parent)
{
    centralWidget = new QWidget;
    wholeLayout = new QVBoxLayout();
    this->setCentralWidget(centralWidget);
    centralWidget->setLayout(wholeLayout);
    
    userNameLayout = new QHBoxLayout();
    passwordLayout = new QHBoxLayout();
    wholeLayout->addLayout(userNameLayout);
    wholeLayout->addLayout(passwordLayout);
    
    userNameLabel = new QLabel("User Name:");
    userNameLayout->addWidget(userNameLabel);
    passwordLabel = new QLabel("Password:");
    passwordLayout->addWidget(passwordLabel);
    userNameLine = new QLineEdit();
    userNameLayout->addWidget(userNameLine);
    passwordLine = new QLineEdit();
    passwordLayout->addWidget(passwordLine);
    
    buttonsLayout = new QHBoxLayout();
    loginButton = new QPushButton("Login");
    connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
    buttonsLayout->addWidget(loginButton);
    logoutButton = new QPushButton("Logout");
    connect(logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    buttonsLayout->addWidget(logoutButton);
    newUserButton = new QPushButton("New User");
    connect(newUserButton, SIGNAL(clicked()), this, SLOT(newUser()));
    buttonsLayout->addWidget(newUserButton);
    wholeLayout->addLayout(buttonsLayout);
    this->show();
}

LoginWin::~LoginWin()
{
    delete centralWidget;
   	delete passwordLabel;
    delete userNameLabel;
    delete wholeLayout;
    delete userNameLine;
    delete passwordLine;
    delete loginButton;
    delete logoutButton;
    delete buttonsLayout;
    delete newUserButton;
    delete userNameLayout;
    delete passwordLayout;
}

std::string LoginWin::userFieldText()
{
	QString text = userNameLine->displayText();
	return text.toStdString();
}

std::string LoginWin::passwordFieldText()
{
	QString text = passwordLine->displayText();
	return text.toStdString();
}

void LoginWin::newUser()
{
	std::string user = userFieldText();
    std::string pass = passwordFieldText();
	User* new_user = new User(user, pass);
	(this->parent->users)[user] = new_user;
}

void LoginWin::login()
{
	std::string user = userFieldText();
    std::string pass = passwordFieldText();
	try{
		if(this->parent->users.at(user)->password == pass)
		{
			this->parent->curr_user = (this->parent->users)[user];
			QString str(user.c_str());
			this->parent->user->setText(str);
		}
	}
	catch(std::exception & e)
	{
		QMessageBox::information(this, tr("Login Failure"),
				tr("No User Match Found"));
	}
}

void LoginWin::logout()
{
	this->parent->curr_user = NULL;
	this->parent->user->clear();
}
