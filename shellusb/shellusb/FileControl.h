
#ifndef _FILECONTROL_H_
#include <iostream>
#include <string>
#include <fstream>

class FileControl{
private:
	std::string name;
public:
	explicit FileControl(std::string _name):name(_name){}
	~FileControl(){}
	const bool readFile(std::string **buf, std::size_t &size);
	const bool writeFile(std::string *buf, std::size_t &size);
};

#endif