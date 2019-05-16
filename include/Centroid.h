#ifndef CENTROID_H_
#define CENTROID_H_

#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "fileutils.h"

using namespace std;
using namespace FileUtils;

class Centroid
{
public:
  Centroid(int clusterId, double lat, double longitude)
  {
    this->clusterId = clusterId;
    this->longitude = longitude;
    this->latitude = lat;
  }

  void addRecord(CrimeRecord record)
  {
    record.cid = this->clusterId;
    this->data.push_back(record);
  }

  bool removeRecord(double id)
  {
    int size = this->data.size();
    for(int i = 0; i < size; i++)
    {
      if(data[i].id == id)
      {
        data.erase(data.begin() + i);
        return true;
      }
    }
    return false;
  }


public:
  int clusterId;
  std::vector<CrimeRecord> data;
  double longitude;
  double latitude;
};

#endif /* CENTROID_H_ */
