// #include "typedefs.hpp"


namespace knapply { // knapply

template<typename STREAM_T>
i64 count_lines(const std::string& file_path) {
  i64 out = 0;
  
  std::string line;
  STREAM_T in_file;
  in_file.open( file_path.c_str() );
  while (std::getline(in_file, line) ) {
    ++out;
  }
  in_file.close();

  return out;
}




} // knapply