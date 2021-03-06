#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>

#include "logger.h"
#include "extractor.h"

using namespace bib_ocr;

int main(int argc, char **argv) {
  //Log::file("foo.log");
  srand(time(0));
  if (argc <= 1) {
    printf("At least one image or dataset path is required!\n");

    return EXIT_FAILURE;
  }

  if (argc == 2) {
    if (!(strlen(argv[1]) > 4 && !strcmp(argv[1] + strlen(argv[1]) - 4, ".jpg"))) {
      // read
      FILE *f = fopen(argv[1], "r+");
      if (f == NULL) {
        printf("Config file does not exist.\n");
        return EXIT_FAILURE;
      }

      char filename[255];
      int bsh, bss, bsv, beh, bes, bev, wsh, wss, wsv, weh, wes, wev;
      int c;

      Log::info("Dataset file %s", argv[1]);

      while ((c = fscanf(f, "%s %d %d %d %d %d %d %d %d %d %d %d %d", filename,
            &bsh, &bss, &bsv, &beh, &bes, &bev, &wsh, &wss, &wsv, &weh, &wes, &wev)) > 0) {
        if (filename[0] == '#')
          continue;

        std::unique_ptr<Extractor> extractor;
        if (c == 1) {
          extractor = std::unique_ptr<Extractor>(new Extractor(filename));
        } else {
          extractor = std::unique_ptr<Extractor>(new Extractor(filename,
                cv::Scalar(bsh, bss, bsv),
                cv::Scalar(beh, bes, bev),
                cv::Scalar(wsh, wss, wsv),
                cv::Scalar(weh, wes, wev)));
        }

        extractor->Extract();

        std::vector<Result> numbers = extractor->GetNumbers();
        sort(numbers.begin(), numbers.end(), [] (Result& a, Result& b) {
          int sa = std::to_string(a.number()).size(), sb = std::to_string(b.number()).size();
          if (sa == sb) return a.probability() > b.probability();
            return sa > sb;
        });
        for (auto result : numbers)
          printf("---------------------------------------------------(%d %d)\n", result.number(), result.probability());

        Log::info("File %s processed", filename);
      }

      fclose(f);
      return EXIT_SUCCESS;
    }
  }

  for (int i = 1; i < argc; i++) {
    std::unique_ptr<Extractor> extractor(new Extractor(argv[i]));
    extractor->Extract();

    std::vector<Result> numbers = extractor->GetNumbers();
    sort(numbers.begin(), numbers.end(), [] (Result& a, Result& b) {
        int sa = std::to_string(a.number()).size(), sb = std::to_string(b.number()).size();
        if (sa == sb) return a.probability() > b.probability();
        return sa > sb;
        });
    for (auto result : numbers)
      printf("---------------------------------------------------(%d %d)\n", result.number(), result.probability());
    printf("\n");

    Log::info("File %s processed", argv[i]);
  }

  return EXIT_SUCCESS;
}
