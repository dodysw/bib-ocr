#ifndef BO_EXTRACTOR_H_
#define BO_EXTRACTOR_H_

#include <string>
#include <vector>
#include <cstdio>

#include "block_separator.h"
#include "number_reader.h"
#include "result.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace bib_ocr {

class Extractor {
 public:
  explicit Extractor(const std::string& filename);
  ~Extractor();

  int Extract();
  std::vector<Result> GetNumbers() const { return numbers_; };

 private:
  void ExtractNumbers(const std::vector<cv::Mat>& blocks);
  void AddResult(const Result& result);

  std::string filename_;
  cv::Mat image_;
  std::vector<Result> numbers_;
};

}

#endif  // BO_EXTRACTOR_H_
