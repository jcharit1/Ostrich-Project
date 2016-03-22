//in import_export_text.h

#ifndef IMPORT_EXPORT_TEXT    
#define IMPORT_EXPORT_TEXT

#include <vector>
#include <string>

void textImport(int max_row, std::string file_path, std::vector<long double>* data);
void importPara(std::string file_path, std::vector< std::vector<std::string>*>* inputVec);
void textMatrixExport(int max_row, std::string file_path, std::vector<std::vector<long double>* >* data);
  
#endif
