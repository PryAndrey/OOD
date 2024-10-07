#pragma once
#include <fstream>

class FileOutputStream : public IOutputDataStream {
private:
	std::ofstream outFile;

public:
	FileOutputStream(const std::string& filename) {
		outFile.open(filename, std::ios::binary);
		if (!outFile.is_open()) {
			throw std::ios_base::failure("Failed to open output file");
		}
	}

	void WriteByte(uint8_t data) override {
		outFile.put(data);
		if (outFile.fail()) {
			throw std::ios_base::failure("WriteByte failed");
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override {
		outFile.write(static_cast<const char*>(srcData), size);
		if (outFile.fail()) {
			throw std::ios_base::failure("WriteBlock failed");
		}
	}

	void Close() override {
		outFile.close();
	}

	~FileOutputStream() {
		Close();
	}
};

class FileInputStream : public IInputDataStream {
private:
	std::ifstream inFile;

public:
	FileInputStream(const std::string& filename) {
		inFile.open(filename, std::ios::binary);
		if (!inFile.is_open()) {
			throw std::ios_base::failure("Failed to open input file");
		}
	}

	bool IsEOF() const override {
		return inFile.eof();
	}

	uint8_t ReadByte() override {
		char byte;
		inFile.get(byte);
		if (inFile.fail()) {
			throw std::ios_base::failure("ReadByte failed");
		}
		return static_cast<uint8_t>(byte);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override {
		inFile.read(static_cast<char*>(dstBuffer), size);
		return inFile.gcount();
	}

	~FileInputStream() {
		inFile.close();
	}
};