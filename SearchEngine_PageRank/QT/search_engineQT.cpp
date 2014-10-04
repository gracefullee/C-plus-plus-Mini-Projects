#include <QApplication>
#include <QObject>
#include "SearchWin.h"
#include "DisplayPageWin.h"
#include <fstream>
#include <stdexcept>
#include <deque>
#include "../WebPage.h"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  if(argc != 4)
      throw std::invalid_argument("Usage: ./QT input_index_filename.txt ad_filename.txt output_filename.txt");

  SearchWin* window = new SearchWin(argv[1], argv[2], argv[3]);

  //this will be the button to quit the application, but I have to plug in the right button name in
  //the right place
  //QObject::connect(button3, SIGNAL(clicked()), &app, SLOT(quit()));
  window->setWindowTitle("CSCI 104 Search Engine");
  window->show();
  
  return app.exec();
}
