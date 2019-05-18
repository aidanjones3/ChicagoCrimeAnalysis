#ifndef UTILITIES_H_
#define UTILITIES_H_

#pragma once

#include "fileutils.h"
#include "centroid.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace fileutils;

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
      file << centroids[i].cluster_id_ << " ";
      file << centroids[i].latitude_ << " ";
      file << centroids[i].longitude_ << " ";
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
