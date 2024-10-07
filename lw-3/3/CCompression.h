#pragma once

class CompressingOutputStream : public IOutputDataStream {
private:
	IOutputDataStream& wrappedStream;

public:
	CompressingOutputStream(IOutputDataStream& stream)
		: wrappedStream(stream) {}

	void WriteByte(uint8_t data) override {
		// Реализация RLE здесь
	}

	void WriteBlock(const void* srcData, std::streamsize size) override {
		// Реализация RLE здесь
	}

	void Close() override {
		wrappedStream.Close();
	}
};

class DecompressingInputStream : public IInputDataStream {
private:
	IInputDataStream& wrappedStream;

public:
	DecompressingInputStream(IInputDataStream& stream)
		: wrappedStream(stream) {}

	bool IsEOF() const override {
		return wrappedStream.IsEOF();
	}

	uint8_t ReadByte() override {
		// Реализация RLE здесь
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override {
		// Реализация RLE здесь
	}
};