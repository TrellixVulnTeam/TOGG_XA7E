//
// Copyright (c) 2017 ZJULearning. All rights reserved.
//
// This source code is licensed under the MIT license.
//

#ifndef EFANNA2E_INDEX_H
#define EFANNA2E_INDEX_H

#include <cstddef>
#include <string>
#include <vector>
#include <fstream>
#include "distance.h"
#include "parameters.h"

namespace efanna2e {

class Index {
 public:
  explicit Index(const size_t dimension, const size_t n, Metric metric);


  virtual ~Index();

  virtual void BuildOriginalNSG(size_t n, const float *data, const Parameters &parameters) = 0;
  virtual void Build(size_t n, const float *data, const Parameters &parameters) = 0;
  virtual void BuildGuided(size_t n, const float *data, const Parameters &parameters) = 0;
  virtual void SearchOptimalP(size_t n, const float *data, const Parameters &parameters) = 0;

  virtual void Search(
      const float *query,
      const float *x,
      size_t k,
      const Parameters &parameters,
      unsigned *indices) = 0;

  virtual void SaveNSG(const char *filename) = 0;
  virtual void SaveNSG_TOGG_KDT(const char *filename) = 0;
  virtual void SaveGuided(const char *filename) = 0;

  virtual void Load(const char *filename) = 0;
  virtual void LoadGuided(const char *filename) = 0;

  inline bool HasBuilt() const { return has_built; }

  inline size_t GetDimension() const { return dimension_; };

  inline size_t GetSizeOfDataset() const { return nd_; }

  inline const float *GetDataset() const { return data_; }
 protected:
  const size_t dimension_;
  const float *data_;
  size_t nd_;
  bool has_built;
  Distance* distance_;
  struct Tnode {
    unsigned div_dim;
    std::vector <unsigned> left;
    std::vector <unsigned> right;
    std::vector <unsigned> common;
  };
  std::vector <Tnode> Tn;
};

}

#endif //EFANNA2E_INDEX_H