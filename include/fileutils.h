#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/tokenizer.hpp>



using namespace std;

namespace fileutils
{

typedef boost::escaped_list_separator<char> Separator;
typedef boost::tokenizer<Separator> Tokenizer;

struct CrimeRecord
{
  int cid;
  double id;
  double latitude;
  double longitude;
};

std::vector<CrimeRecord> parseCSV(string path_to_file)
{
  ifstream data(path_to_file);
  std::vector<CrimeRecord> records;

  if(data.is_open())
  {

    string line;
    double valid = 0;
    double invalid = 0;
    while(getline(data, line))
    {
      bool bad_line = false;
      std::vector<std::string> tokens;
      Tokenizer tokenizer(line);

      for(Tokenizer::iterator iter = tokenizer.begin();
              iter != tokenizer.end(); ++iter)
      {
        //std::cout << *iter << "\n";
        tokens.push_back(*iter);
      }

      for(int i = 0; i < tokens.size(); i++)
      {
        if(tokens[i].empty())
        {
          bad_line = true;
          break;
        }
      }

      //std::cout << "\n";
      //std::cout << tokens.size() << "\n\n";
      CrimeRecord record;

      if(bad_line == false)
      {
        record.id = stod(tokens[0]);
        record.latitude = stod(tokens[20]);
        record.longitude = stod(tokens[21]);
        records.push_back(record);
        valid++;

      } else
      {
        //std::cout << "Illegal Line During Input. \n";
        invalid++;
      }

    }
    cout << "Percentage of Records Valid: " << valid / (valid + invalid) * 100 << "\n";
    cout << "Total Number of Records Stored: " << records.size() << "\n";

  }

  return records;
}


}
#endif /* FILEUTILS_H_ */
