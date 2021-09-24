//
// Created by Marcos on 04/08/2021.
//

#include "Buffer.h"
/**
 * Inicializa a instancia do Buffer definindo o tamanho maximo com o informado.
 * @param maxSize Tamanho maximo do buffer.
 */
Buffer::Buffer(int maxSize) {
    this->maxSize = maxSize;
    this->data = std::vector<char>(maxSize,0x0);
    this->actualSize = 0;
}
/**
 * Inicializa a intancia Buffer definindo o texto da string em seu conteudo e definindo seu tamanho maximo.
 * @param str String a ser alocada.
 * @param maxSize Tamanho maximo do buffer.
 */
Buffer::Buffer(std::string str, int maxSize) {
    this->maxSize = maxSize;
    this->data = std::vector<char>(maxSize);
    std::copy(str.begin(), str.end(), this->data.begin());
    this->actualSize = str.size();
}

std::string Buffer::toString() {
	std::string temp="";
	try{
		temp = std::string(&this->data[0],this->actualSize);
	}catch(const std::exception& e) {
		
	}
	return temp;
}
char* Buffer::getDataAccess() {
    return &data[0];
}

const std::vector<char> &Buffer::getData() const {
    return data;
}

void Buffer::setData(const std::vector<char> &data) {
    Buffer::data = data;
}

int Buffer::getMaxSize() const {
    return maxSize;
}

void Buffer::setMaxSize(int maxSize) {
    Buffer::maxSize = maxSize;
}

int Buffer::getActualSize() const {
    return actualSize;
}

void Buffer::setActualSize(int actualSize) {
    Buffer::actualSize = actualSize;
}

char * Buffer::operator[](int indice) {
    return &this->data[indice];
}
