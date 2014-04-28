#include "FileControl.h"

const bool FileControl::readFile(std::string **buf, std::size_t &size){
	std::ifstream file;
	*buf = 0;
	size = 0;

	file.open(this->name, std::ios::in | std::ios::binary);
	if (!file.is_open()){
		std::cout << "file open fail" << std::endl;
		return false;
	}
	else{
		file.unsetf(std::ios::skipws);
		file.seekg(0, std::ios::end);
		size = file.tellg();
		file.clear();
		file.seekg(0, std::ios::beg);
	}
	*buf = new std::string[size];
	if (!(*buf)){
		std::cout << "buffer memory allocate error" << std::endl;
		file.close();
		return false;
	}
	file.unsetf(std::ios::skipws);
	file.read((char*)*buf, size);
	file.close();
	return true;
}

const bool FileControl::writeFile(std::string *buf, std::size_t &size){
	std::ofstream file;
	std::string::iterator iter = find(this->name.begin(), this->name.end(), '.');
	this->name.erase(iter, this->name.end());
	this->name.append(".tsu");

	file.open(name, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!file.is_open()){
		std::cout << "file oper error" << std::endl;
		return false;
	}
	file.write((char*)buf, size);
	file.close();
	return true;
}