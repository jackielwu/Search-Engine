
#include "minihttpd.h"
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include "array-dictionary.h"
#include "avl-dictionary.h"
#include "bsearch-dictionary.h"
#include "hash-dictionary.h"


// Types of dictionaries used
enum DictionaryType {
  ArrayDictionaryType,
  HashDictionaryType,
  AVLDictionaryType,
  BinarySearchDictionaryType
};

struct URLRecord {
  char * _url;          // URL of the document.
  char * _description;  // First 100 words of the document without tags
  //int _i;
};

struct URLRecordList {
  int _index;     // Index into the URL Array
  URLRecordList * _next;   // Pointer to the next URL Record in the list
};

// Inherits from MiniHTTPD
class SearchEngine : public MiniHTTPD {
  Dictionary * _wordToURLList;
  bool debug;
  void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
  // Add any other member variables you need
  URLRecord **urlArray;
  bool findURL(URLRecordList *list, int index);
 public:
  // Constructor for SearchEngine
  SearchEngine( int port, DictionaryType dictionaryType);

  // Called when a request arrives
  void dispatch( FILE * out, const char * requestLine );

};



