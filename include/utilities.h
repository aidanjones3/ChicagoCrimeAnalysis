#ifndef UTILITIES_H_
#define UTILITIES_H_

#pragma once

#include "fileutils.h"
#include "Centroid.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace FileUtils;

void writeToFile(std::vector<Centroid> centroids, std::string output_file_path)
{
  ofstream file;
  file.open(output_file_path);

  if(file.is_open())
  {
    for(int i = 0; i < centroids.size(); i++)
    {
      //TODO
      file.precision(11);
      file << centroids[i].clusterId << " ";
      file << centroids[i].latitude << " ";
      file << centroids[i].longitude << " ";
      file << std::endl;
    }
    file.close();
  }
  else
  {
    std::cout << "Can't Write to Output File.";
  }
}

#endif /* UTILITIES_H_ */
