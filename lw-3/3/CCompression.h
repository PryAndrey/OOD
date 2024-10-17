#pragma once

#include "IStreams.h"
#include <deque>
#include <optional>
#include <vector>

class CompressOutputFileStream : public OutputFileDataStreamDecorator
{
public:
	explicit CompressOutputFileStream(std::unique_ptr<IFileOutputDataStream> stream)
		: OutputFileDataStreamDecorator(std::move(stream))
	{
	}

	void WriteByte(uint8_t data) override
	{
		if (m_buffer == std::nullopt)
		{
			m_buffer = { data, 1 };
			return;
		}
		if (m_buffer->first == data && m_buffer->second < 255)
		{
			m_buffer->second++;
			return;
		}
		m_stream->WriteByte(m_buffer->first);
		m_stream->WriteByte(m_buffer->second);
		m_buffer = { data, 1 };
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* data = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(data[i]);
		}
	}

	void Close() override
	{
		m_stream->WriteByte(m_buffer->first);
		m_stream->WriteByte(m_buffer->second);
		m_stream->Close();
	}

private:
	std::optional<std::pair<uint8_t, uint8_t>> m_buffer = std::nullopt;
};

class DecompressInputFileStream : public InputFileDataStreamDecorator
{
public:
	explicit DecompressInputFileStream(std::unique_ptr<IFileInputDataStream> stream)
		: InputFileDataStreamDecorator(std::move(stream))
	{
	}

	[[nodiscard]] bool IsEOF() const override
	{
		return m_stream->IsEOF() && m_buffer.empty();
	}

	uint8_t ReadByte() override
	{
		if (m_buffer.empty() && !m_stream->IsEOF())
		{
			uint8_t byte = m_stream->ReadByte();
			uint8_t count = m_stream->ReadByte();
			m_buffer.insert(m_buffer.end(), count, byte);
		}
		uint8_t data = m_buffer.front();
		m_buffer.pop_front();
		return data;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
		int bytesCount = 0;
		while (bytesCount < size && !IsEOF())
		{
			buffer[bytesCount++] = ReadByte();
		}
		return bytesCount;
	}

private:
	std::deque<uint8_t> m_buffer;
};

class CompressOutputMemoryStream : public OutputMemoryDataStreamDecorator
{
public:
	explicit CompressOutputMemoryStream(std::unique_ptr<IMemoryOutputDataStream> stream)
		: OutputMemoryDataStreamDecorator(std::move(stream))
	{
	}

	void WriteByte(uint8_t data) override
	{
		if (m_buffer == std::nullopt)
		{
			m_buffer = { data, 1 };
			return;
		}
		if (m_buffer->first == data && m_buffer->second < 255)
		{
			m_buffer->second++;
			return;
		}
		m_stream->WriteByte(m_buffer->first);
		m_stream->WriteByte(m_buffer->second);
		m_buffer = { data, 1 };
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* data = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(data[i]);
		}
	}
	~CompressOutputMemoryStream() override
	{
		m_stream->WriteByte(m_buffer->first);
		m_stream->WriteByte(m_buffer->second);
	}

private:
	std::optional<std::pair<uint8_t, uint8_t>> m_buffer = std::nullopt;
};

class DecompressInputMemoryStream : public InputMemoryDataStreamDecorator
{
public:
	explicit DecompressInputMemoryStream(std::unique_ptr<IMemoryInputDataStream> stream)
		: InputMemoryDataStreamDecorator(std::move(stream))
	{
	}

	[[nodiscard]] bool IsEOF() const override
	{
		return m_stream->IsEOF() && m_buffer.empty();
	}

	uint8_t ReadByte() override
	{
		if (m_buffer.empty() && !m_stream->IsEOF())
		{
			uint8_t byte = m_stream->ReadByte();
			uint8_t count = m_stream->ReadByte();
			m_buffer.insert(m_buffer.end(), count, byte);
		}
		uint8_t data = m_buffer.front();
		m_buffer.pop_front();
		return data;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
		int bytesCount = 0;
		while (bytesCount < size && !IsEOF())
		{
			buffer[bytesCount++] = ReadByte();
		}
		return bytesCount;
	}

private:
	std::deque<uint8_t> m_buffer;
};