#pragma once

#include "IStreams.h"
#include <algorithm>
#include <memory>
#include <random>

std::vector<uint8_t> GenerateSubstitutionTable(int key) {
	std::vector<uint8_t> table(256);
	std::iota(table.begin(), table.end(), 0);
	std::mt19937 generator(key);
	std::shuffle(table.begin(), table.end(), generator);
	return table;
}

std::vector<uint8_t> GenerateInverseSubstitutionTable(const std::vector<uint8_t>& table) {
	std::vector<uint8_t> inverseTable(256);
	for (size_t i = 0; i < table.size(); ++i) {
		inverseTable[table[i]] = static_cast<uint8_t>(i);
	}
	return inverseTable;
}


class EncryptOutputFileStream : public OutputFileDataStreamDecorator
{
public:
	EncryptOutputFileStream(std::unique_ptr<IFileOutputDataStream> stream, int key)
		: OutputFileDataStreamDecorator(std::move(stream)), m_table(GenerateSubstitutionTable(key)) {}

	void WriteByte(uint8_t data) override {
		m_stream->WriteByte(m_table[data]);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override {
		const uint8_t* data = static_cast<const uint8_t*>(srcData);
		std::vector<uint8_t> encryptedData(size);
		for (std::streamsize i = 0; i < size; ++i) {
			encryptedData[i] = m_table[data[i]];
		}
		m_stream->WriteBlock(encryptedData.data(), size);
	}

	void Close() override {
		m_stream->Close();
	}

private:
	std::vector<uint8_t> m_table;
};

class DecryptInputFileStream : public InputFileDataStreamDecorator
{
public:
	DecryptInputFileStream(std::unique_ptr<IFileInputDataStream> stream, int key)
		: InputFileDataStreamDecorator(std::move(stream)), m_inverseTable(GenerateInverseSubstitutionTable(GenerateSubstitutionTable(key))) {}

	[[nodiscard]] bool IsEOF() const override {
		return m_stream->IsEOF();
	}

	uint8_t ReadByte() override {
		uint8_t encryptedByte = m_stream->ReadByte();
		return m_inverseTable[encryptedByte];
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override {
		uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
		std::streamsize bytesRead = m_stream->ReadBlock(buffer, size);
		for (std::streamsize i = 0; i < bytesRead; ++i) {
			buffer[i] = m_inverseTable[buffer[i]];
		}
		return bytesRead;
	}

private:
	std::vector<uint8_t> m_inverseTable;
};


class EncryptOutputMemoryStream : public OutputMemoryDataStreamDecorator
{
public:
	EncryptOutputMemoryStream(std::unique_ptr<IMemoryOutputDataStream> stream, int key)
		: OutputMemoryDataStreamDecorator(std::move(stream)), m_table(GenerateSubstitutionTable(key)) {};

	void WriteByte(uint8_t data) override {
		m_stream->WriteByte(m_table[data]);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override {
		const uint8_t* data = static_cast<const uint8_t*>(srcData);
		std::vector<uint8_t> encryptedData(size);
		for (std::streamsize i = 0; i < size; ++i) {
			encryptedData[i] = m_table[data[i]];
		}
		m_stream->WriteBlock(encryptedData.data(), size);
	}

private:
	std::vector<uint8_t> m_table;
};

class DecryptInputMemoryStream : public InputMemoryDataStreamDecorator
{
public:
	DecryptInputMemoryStream(std::unique_ptr<IMemoryInputDataStream> stream, int key)
		: InputMemoryDataStreamDecorator(std::move(stream)), m_inverseTable(GenerateInverseSubstitutionTable(GenerateSubstitutionTable(key))) {}

	[[nodiscard]] bool IsEOF() const override {
		return m_stream->IsEOF();
	}

	uint8_t ReadByte() override {
		uint8_t encryptedByte = m_stream->ReadByte();
		return m_inverseTable[encryptedByte];
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override {
		uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
		std::streamsize bytesRead = m_stream->ReadBlock(buffer, size);
		for (std::streamsize i = 0; i < bytesRead; ++i) {
			buffer[i] = m_inverseTable[buffer[i]];
		}
		return bytesRead;
	}

private:
	std::vector<uint8_t> m_inverseTable;
};