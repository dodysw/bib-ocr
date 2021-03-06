#ifndef BO_EXTRACTOR_H_
#define BO_EXTRACTOR_H_

#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

#include "block_separator.h"
#include "number_reader.h"
#include "result.h"
#include "color_replacer.h"
#include "logger.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace bib_ocr {

class Extractor {
 public:
  explicit Extractor(const std::string& filename);
  explicit Extractor(const std::string& filename, const cv::Scalar black_start, const cv::Scalar black_stop, const cv::Scalar white_start, const cv::Scalar white_end);
  ~Extractor();

  int Extract();
  std::vector<Result> GetNumbers() const { return numbers_; };

 private:
  void ExtractNumbers(const std::vector<std::pair<cv::Mat, cv::Mat> >& blocks);
  void AddResult(const std::vector<Result>& results);

  std::string filename_;
  cv::Mat image_;
  std::vector<Result> numbers_;
};

}

#endif  // BO_EXTRACTOR_H_
