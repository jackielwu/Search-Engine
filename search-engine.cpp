
#include <string.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "search-engine.h"

SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
	//FILE *fp;
	//fp = fopen("word.txt","r");
	switch(dictionaryType) {
		case ArrayDictionaryType:
			_wordToURLList = new ArrayDictionary();
			break;
		case HashDictionaryType:
			_wordToURLList = new HashDictionary();
			break;
		case AVLDictionaryType:
			_wordToURLList = new AVLDictionary();
			break;
		case BinarySearchDictionaryType:
			_wordToURLList = new BinarySearchDictionary();
			break;
	}
  // Create dictionary of the indicated type
	//char **word= new char*[100];
	printf("load word\n");
	std::fstream fs("word.txt",std::fstream::in);
	if(fs.is_open()) {
		while(!fs.eof()) {
			std::string line;
			std::getline(fs,line);
			char *tokens = strdup(line.c_str());
			printf("%s\n",tokens);
			char *word = strtok(tokens," ");
			char *index = strtok(NULL," ");
			URLRecordList *list = new URLRecordList();
			URLRecordList *e = list;
			while(index!=NULL) {
				e->_index = atoi(index);
				printf("%d ",e->_index);
				URLRecordList *n = new URLRecordList();
				e->_next = n;
				e=e->_next;
				index = strtok(NULL," ");
			}
			_wordToURLList->addRecord((const char *)word, (URLRecordList *)list);
			printf("\n");
		}
		fs.close();
		printf("loaded word\n");
	}
	
	
  // Populate dictionary and sort it if necessary
  /*if(fp!=NULL) {
  	while(!feof(fp))
  	{
  		URLRecordList *num = new URLRecordList();
  		URLRecordList *e=num;
  		int i=0;
  		//char line[5000];
  		//fgets(line,4999,fp);
  		//fscanf(fp,"%s", word[i++]);
  		
  		char c;
  		do {
  			//fscanf(fp,"%d%c",&e->_urlRecordIndex,&c);
  			URLRecordList *n = new URLRecordList();
  			e->_next=n;
  			e=e->_next;
  		} while(c!='\n');
  		_wordToURLList->addRecord((const char*)word,(URLRecordList *)num);
  	}
  	fclose(fp);
  }*/
  urlArray=new URLRecord[500];
  /*fp=fopen("url.txt","r");
  if(fp!=NULL) {
  	while(!feof(fp))
  	{
  		int d;
  		int i=0;
  		URLRecord *e = new URLRecord;
  		fscanf(fp,"%d ",&d);
  		fgets(e->_url,500,fp);
  		fgets(e->_description,600,fp);
  		std::string s(e->_url);
  		s.erase(s.length()-1,1);
  		e->_url=strdup(s.c_str());
  		std::string s1(e->_description);
  		s1.erase(s1.length()-1,1);
  		e->_description=strdup(s1.c_str());
  		
  		urlArray[i++]=*e;
  	}
  	fclose(fp);
  }*/
}

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
  if (strcmp(documentRequested, "/")==0) {
    // Send initial form
    fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
    fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
    fprintf(fout, "<H2>\n");
    fprintf(fout, "<FORM ACTION=\"search\">\n");
    fprintf(fout, "Search:\n");
    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
    fprintf(fout, "</H2>\n");
    fprintf(fout, "</FORM></CENTER>\n");
    return;
  }
	timespec start,stop;
	long timeelapsed=0;
	clock_gettime(CLOCK_REALTIME,&start);
  // TODO: The words to search in "documentRequested" are in the form
  // /search?word=a+b+c
  // search = "this is the search"
  // documentRequested= "/search?word=this+is+the+search"
  // You need to separate the words before search
  // Search the words in the dictionary and find the URLs that
  // are common for al the words. Then print the URLs and descriptions
  // in HTML. Make the output look nicer.

  // Here the URLs printed are hardwired
  
  int nurls=0;
	
	std::string s(documentRequested);
	s.erase(0,13);
	//printf("%s\n",s.c_str());
	ReplaceStringInPlace(s,std::string("+"),std::string(" "));
	//printf("%s\n",s.c_str());
  const char * words = s.c_str();
	char *token = strtok((char *)words," ");
	char *word[10];
	int i=0;
	while(token != NULL) {
		word[i] = token;
		token = strtok(NULL," ");
		i++;
	}
	const char *urls[500];
	const char *description[500];
	URLRecordList *data[10];
	for(int j=0;j<i;i++) {
		data[j]=(URLRecordList *)_wordToURLList->findRecord(word[j]);
	}
	if(i==1) {
		URLRecordList *e = data[0];
		while(e!=NULL) {
			urls[nurls]=strdup(urlArray[e->_index]._url);
			description[nurls]=strdup(urlArray[e->_index]._description);
			nurls++;
			e=e->_next;
		}
	}
	/*else {
		bool intersect =false;
		URLRecordList *e = data[0];
		int index = e->_index;
		while(e!=NULL) {
			for(int j=1;j<i;j++) {
				if(!findURL(data[j],index)) {
					intersect = false;
					break;
				}
				else {
					intersect = true;
				}
			}
			e=e->_next;
			index=e->_index;
		}
		if(intersect) {
			
		}

	}*/
	
	
	
  /*const char * urls[] = {
    "http://www.cs.purdue.edu",
    "http://www.cs.purdue.edu/homes/cs251"
  };
  
  const char * description[] = {
    "Computer Science Department. Purdue University.",
    "CS251 Data Structures"
  };*/

	clock_gettime(CLOCK_REALTIME,&stop);
	timeelapsed = stop.tv_nsec - start.tv_nsec;
	

  fprintf( stderr, "Search for words: \"%s\"\n", words);

  fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
  fprintf( fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
  fprintf( fout, "<H2> <Center>Search Results for \"%s\"</H2>\n", words );
  fprintf( fout, "<H3> <Center>Time Elasped: %ldns</Center></H3>\n", timeelapsed );

  for ( int i = 0; i < nurls; i++ ) {
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, urls[i], urls[i] );
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
  }

  // Add search form at the end
  fprintf(fout, "<HR><H2>\n");
  fprintf(fout, "<FORM ACTION=\"search\">\n");
  fprintf(fout, "Search:\n");
  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
  fprintf(fout, "</H2>\n");
  fprintf(fout, "</FORM>\n");
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | avl | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }

  // Get port
  int port;
  sscanf( argv[1], "%d", &port);

  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
  }
  else if (!strcmp(dictType, "avl")) {
    dictionaryType = AVLDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }
  
  SearchEngine httpd(port, dictionaryType);
  
  httpd.run();

  return 0;
}
bool SearchEngine::findURL(URLRecordList *list, int index) {
	URLRecordList *e=list;
	while(e!=NULL) {
		if(e->_index == index) {
			return true;
		}
		e=e->_next;
	}
	return false;
}

void SearchEngine::ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}
