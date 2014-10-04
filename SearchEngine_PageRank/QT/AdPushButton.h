#ifndef ADPUSHBUTTON_H
#define ADPUSHBUTON_H

#include <QPushButton>
#include <string>

class Ad{
public:
	Ad(std::string n, double b): name(n), bid(b) {};
	bool operator==(const Ad& rhs) { return (this->name == rhs.name); }
	bool operator<(const Ad& rhs) { return (this->name < rhs.name);	}
	std::string name;
	double bid;
};

class AdPushButton : public QPushButton
{
	Q_OBJECT
	
	public:
		AdPushButton(Ad* ad, QWidget *parent = 0); 
		virtual ~AdPushButton();
	public slots:
		void triggerPush();
	signals:
		void ClickedWithArgument(Ad*);
	private: 
		Ad* _ad;
};

#endif
