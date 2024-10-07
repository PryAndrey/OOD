#pragma once
#include <random>
#include <algorithm>

class EncryptingOutputStream : public IOutputDataStream {
private:
	IOutputDataStream& wrappedStream;
	std::vector<uint8_t> substitutionTable;

public:
	EncryptingOutputStream(IOutputDataStream& stream, uint32_t key)
		: wrappedStream(stream) {

		// Генерация таблицы подстановки
		substitutionTable.resize(256);
		for (uint8_t i = 0; i < 256; ++i) {
			substitutionTable[i] = i;
		}

		// Перемешивание таблицы
		std::mt19937 rng(key);
		std::shuffle(substitutionTable.begin(), substitutionTable.end(), rng);
	}

	void WriteByte(uint8_t data) override {
		wrappedStream.WriteByte(substitutionTable[data]);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override {
		const uint8_t* data = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i) {
			WriteByte(data[i]);
		}
	}

	void Close() override {
		wrappedStream.Close();
	}
};

class DecryptingInputStream : public IInputDataStream {
private:
	IInputDataStream& wrappedStream;
	std::vector<uint8_t> inverseSubstitutionTable;

public:
	DecryptingInputStream(IInputDataStream& stream, const std::vector<uint8_t>& substitutionTable)
		: wrappedStream(stream), inverseSubstitutionTable(256) {

		// Генерация обратной таблицы подстановки
		for (uint8_t i = 0; i < 256; ++i) {
			inverseSubstitutionTable[substitutionTable[i]] = i;
		}
	}

	bool IsEOF() const override {
		return wrappedStream.IsEOF();
	}

	uint8_t ReadByte() override {
		uint8_t encryptedByte = wrappedStream.ReadByte();
		return inverseSubstitutionTable[encryptedByte];
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override {
		for (std::streamsize i = 0; i < size; ++i) {
			static_cast<uint8_t*>(dstBuffer)[i] = ReadByte();
		}
		return size;
	}
};