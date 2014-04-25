#include <iostream>
#include <algorithm>
#include <string>
#include "FileControl.h"
int main(){
	FileControl *fc = new FileControl("test.txt");
	std::string *buf=0;
	std::size_t size=0;
	if (fc->readFile( &buf, size)){
		fc->writeFile(buf, size);
	}
	delete fc;
	return 0;
}