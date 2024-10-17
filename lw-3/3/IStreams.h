#pragma once

#include <fstream>
#include <memory>
#include <string>

class IInputDataStream
{
public:
	[[nodiscard]] virtual bool IsEOF() const = 0;
	virtual uint8_t ReadByte() = 0;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;
	virtual ~IInputDataStream() = default;
};
class IOutputDataStream
{
public:
	// close для output
	virtual void WriteByte(uint8_t data) = 0;
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;
	virtual ~IOutputDataStream() = default;
};

class IFileInputDataStream : public IInputDataStream
{
};
class IFileOutputDataStream : public IOutputDataStream
{
public:
	virtual void Close() = 0;
};

class IMemoryInputDataStream : public IInputDataStream
{
};
class IMemoryOutputDataStream : public IOutputDataStream
{
};

class InputFileDataStreamDecorator : public IFileInputDataStream
{
public:
	explicit InputFileDataStreamDecorator(std::unique_ptr<IFileInputDataStream> stream)
		: m_stream(std::move(stream))
	{
	}

protected:
	std::unique_ptr<IFileInputDataStream> m_stream;
};

//перенсти общий функционал
class OutputFileDataStreamDecorator : public IFileOutputDataStream
{
public:
	explicit OutputFileDataStreamDecorator(std::unique_ptr<IFileOutputDataStream> stream)
		: m_stream(std::move(stream))
	{
	}

protected:
	std::unique_ptr<IFileOutputDataStream> m_stream;
};

class InputMemoryDataStreamDecorator : public IMemoryInputDataStream
{
public:
	explicit InputMemoryDataStreamDecorator(std::unique_ptr<IMemoryInputDataStream> stream)
		: m_stream(std::move(stream))
	{
	}

protected:
	std::unique_ptr<IMemoryInputDataStream> m_stream;
};
class OutputMemoryDataStreamDecorator : public IMemoryOutputDataStream
{
public:
	explicit OutputMemoryDataStreamDecorator(std::unique_ptr<IMemoryOutputDataStream> stream)
		: m_stream(std::move(stream))
	{
	}

protected:
	std::unique_ptr<IMemoryOutputDataStream> m_stream;
};