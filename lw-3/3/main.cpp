#include <iostream>
#include <string>
#include <vector>
#include "IStreams.h"
#include "CStreams.h"
#include "CCompression.h"
#include "СEncryption.h"

void transform(int argc, char** argv) {
	// Обработка аргументов командной строки и создание потоков
	// Пример: --encrypt 3 --compress input.dat output.dat
}

int main(int argc, char** argv) {
	try {
		transform(argc, argv);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}