#include <Rcpp11>
#include <sys/stat.h>

bool fileExists(const std::string& file);

// [[Rcpp::export(fileExists)]]
bool fileExists(const std::string& file) {
  struct stat buf;
  return (stat(file.c_str(), &buf) == 0);
}
