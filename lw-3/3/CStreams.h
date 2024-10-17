#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

class FileInputStream : public IFileInputDataStream
{
public:
	explicit FileInputStream(const std::string& fileName)
		: m_file(fileName, std::ios::binary)
	{
		if (!m_file.is_open())
		{
			throw std::ios_base::failure("Failed to open input file: " + fileName);
		}
	}

	bool IsEOF() const override
	{
		std::streambuf* buf = m_file.rdbuf();
		int nextByte = buf->sgetc();
		return nextByte == EOF;
	}

	uint8_t ReadByte() override
	{
		char byte = 0;
		m_file.get(byte);
		if (m_file.fail())
		{
			throw std::ios_base::failure("Error reading byte from input stream.");
		}
		return static_cast<uint8_t>(byte);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		m_file.read(static_cast<char*>(dstBuffer), size);
		if (m_file.bad())
		{
			throw std::ios_base::failure("Error reading block from input stream.");
		}
		return m_file.gcount();
	}

	~FileInputStream() override
	{
		if (m_file.is_open())
		{
			m_file.close();
		}
	}

private:
	std::ifstream m_file;
};

class FileOutputStream : public IFileOutputDataStream
{
public:
	explicit FileOutputStream(const std::string& fileName)
		: m_file(fileName, std::ios::binary)
	{
		if (!m_file.is_open())
		{
			throw std::ios_base::failure("Failed to open output file: " + fileName);
		}
	}

	void WriteByte(uint8_t data) override
	{
		if (m_file.is_open())
		{
			if (!m_file.put(static_cast<char>(data)))
			{
				throw std::ios_base::failure("Error writing byte to output stream.");
			}
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		m_file.write(static_cast<const char*>(srcData), size);
		if (m_file.bad())
		{
			throw std::ios_base::failure("Error writing block to output stream.");
		}
	}

	void Close() override
	{
		if (m_file.is_open())
		{
			m_file.close();
		}
	}

	~FileOutputStream() override
	{
		WriteByte('\0');
		Close();
	}

private:
	std::ofstream m_file;
};


class MemoryInputStream : public IMemoryInputDataStream
{
public:
	explicit MemoryInputStream(const std::string& data)
		: m_stream(data)
	{
	}
	bool IsEOF() const override
	{
		std::streambuf* buf = m_stream.rdbuf();
		int nextByte = buf->sgetc();
		return nextByte == EOF;
	}

	uint8_t ReadByte() override
	{
		char byte = 0;
		m_stream.get(byte);
		if (m_stream.fail())
		{
			throw std::ios_base::failure("Error reading byte from input stream.");
		}
		return static_cast<uint8_t>(byte);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		m_stream.read(static_cast<char*>(dstBuffer), size);
		if (m_stream.bad())
		{
			throw std::ios_base::failure("Error reading block from input stream.");
		}
		return m_stream.gcount();
	}

private:
	//надо вектор
	mutable std::stringstream m_stream;
};

class MemoryOutputStream : public IMemoryOutputDataStream
{
public:
	MemoryOutputStream() = default;

	void WriteByte(uint8_t data) override
	{
		if (!m_stream.put(static_cast<char>(data)))
		{
			throw std::ios_base::failure("Error writing byte to output stream.");
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		m_stream.write(static_cast<const char*>(srcData), size);
		if (m_stream.bad())
		{
			throw std::ios_base::failure("Error writing block to output stream.");
		}
	}

	~MemoryOutputStream() override
	{
		std::cout << m_stream.str();
	}
private:
	std::stringstream m_stream;
};