#ifndef CENTROID_H_
#define CENTROID_H_

#pragma once

#include "fileutils.h"

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace fileutils;

class Centroid
{
public:
  Centroid(int clusterId, double lat, double longitude)
  {
    this->cluster_id_ = clusterId;
    this->longitude_ = longitude;
    this->latitude_ = lat;
  }

  void AddRecord(CrimeRecord record)
  {
    record.cid = cluster_id_;
    data_.push_back(record);
  }

  bool RemoveRecord(double id)
  {
    int size = data_.size();
    for(int i = 0; i < size; i++)
    {
      if(data_[i].id == id)
      {
        data_.erase(data_.begin() + i);
        return true;
      }
    }
    return false;
  }


public:
  int cluster_id_;
  std::vector<CrimeRecord> data_;
  double longitude_;
  double latitude_;
};

#endif /* CENTROID_H_ */
