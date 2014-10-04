#include <set>
#include <fstream>
#include <string>
#include <iostream>

void crawlPages(std::set<std::string>& startFiles,
		std::set<std::string>& finalList, std::ostream& fout);
void DFS(std::set<std::string>& listSoFar, std::string nextFile,
	 std::ostream& fout);

int main(int argc, char* argv[])
{
  if(argc != 3)
    {
      std::cout << "Input only the name of the input file followed"
		<<" by the name of the output file" << std::endl;
      return 1;
    }
  
  std::ifstream fin(argv[1]);
  if(fin.fail())
    {
      std::cout << "No input file of the given name" << std::endl;
    }

  std::set<std::string> initialFiles;
  std::string filename;

  while(1)
    {
      fin >> filename;
      if(fin.fail())
	{
	  break;
	}
      initialFiles.insert(filename);
    }
  fin.close();

  std::set<std::string> finalList;
  std::ofstream fout(argv[2]);
  crawlPages(initialFiles, finalList, fout);
  
  fout.close();

  return 0;
}

void crawlPages(std::set<std::string>& startFiles, 
		std::set<std::string>& endFiles, std::ostream& fout)
{
  for(std::set<std::string>::iterator it=startFiles.begin();
      it!=startFiles.end(); ++it)
    {
      std::ifstream filesearch(it->c_str());
      if(filesearch.fail())
	{
	  std::cout << "Invalid filename found" << std::endl;
	  continue;
	}
      else if(endFiles.find(*it) == endFiles.end())
	{
	  DFS(endFiles, *it, fout);
	}
    }
}
	   
  
void DFS(std::set<std::string>& listSoFar, std::string nextFile,
	 std::ostream& fout)
{
  std::ifstream fin(nextFile.c_str());
  if(fin.fail())
    {
      std::cout << "Invalid filename found: " << nextFile << std::endl;
      return;
    }
  listSoFar.insert(nextFile);
  fout << nextFile << std::endl;
  char tempChar;
  std::string outgoingLink;
  while(1)
    {
      tempChar = fin.get();
      if(fin.fail())
	{
	  fin.close();
	  return;
	}
      if(tempChar == '(')
	{
	  getline(fin, outgoingLink, ')');
	  if(listSoFar.find(outgoingLink) == listSoFar.end())
	    {
	      DFS(listSoFar, outgoingLink, fout);
	    }
	}
    }
}
