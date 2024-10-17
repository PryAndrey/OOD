#include "CCompression.h"
#include "CEncryption.h"
#include "CStreams.h"
#include "IStreams.h"
#include <iostream>
#include <string>
#include <vector>

int TransformFile(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cerr << "Command must have: transform [options] <input-file> <output-file>" << std::endl;
		return 1;
	}

	std::string inputFileName = argv[argc - 2];
	std::string outputFileName = argv[argc - 1];

	std::unique_ptr<IFileInputDataStream> inputStream = std::make_unique<FileInputStream>(inputFileName);
	std::unique_ptr<IFileOutputDataStream> outputStream = std::make_unique<FileOutputStream>(outputFileName);

	std::vector<std::pair<std::string, int>> commands;

	for (int i = 1; i < argc - 2; ++i)
	{
		std::string option = argv[i];
		if (option == "--encrypt" || option == "--decrypt")
		{
			try
			{
				if (i + 1 < argc - 2)
				{
					commands.emplace_back(option, std::stoi(argv[++i]));
				}
				else
				{
					std::cerr << "Missing key for --encrypt/decrypt option." << std::endl;
					return 1;
				}
				continue;
			}
			catch (std::invalid_argument& e)
			{
				std::cerr << e.what() << std::endl;
				return 1;
			}
		}
		else if (option == "--compress" || option == "--decompress")
		{
			commands.emplace_back(option, 0);
			continue;
		}
		std::cerr << "Wrong option: " << option << std::endl;
		return 1;
	}
	for (auto it = commands.rbegin(); it != commands.rend(); ++it)
	{
		const auto& [command, key] = *it;
		if (command == "--decrypt")
			inputStream = std::make_unique<DecryptInputFileStream>(std::move(inputStream), key);
		if (command == "--decompress")
			inputStream = std::make_unique<DecompressInputFileStream>(std::move(inputStream));
	}

	for (auto& [command, key] : commands)
	{
		if (command == "--encrypt")
			outputStream = std::make_unique<EncryptOutputFileStream>(std::move(outputStream), key);
		if (command == "--compress")
			outputStream = std::make_unique<CompressOutputFileStream>(std::move(outputStream));
	}

	//	while (!inputStream->IsEOF())
	//	{
	//		uint8_t byte = inputStream->ReadByte();
	//		outputStream->WriteByte(byte);
	//	}

	while (!inputStream->IsEOF())
	{
		std::vector<uint8_t> byteVec(5);
		std::streamsize byteReaded = inputStream->ReadBlock(byteVec.data(), 5);
		outputStream->WriteBlock(byteVec.data(), byteReaded);
	}

	outputStream->Close();

	return 0;
}

int main(int argc, char* argv[])
{
	return TransformFile(argc, argv);

	std::unique_ptr<IMemoryInputDataStream> inputStream = std::make_unique<MemoryInputStream>("hello!");
	std::unique_ptr<IMemoryOutputDataStream> outputStream = std::make_unique<MemoryOutputStream>();

	inputStream = std::make_unique<DecryptInputMemoryStream>(std::move(inputStream), 10);
	inputStream = std::make_unique<DecompressInputMemoryStream>(std::move(inputStream));

	outputStream = std::make_unique<EncryptOutputMemoryStream>(std::move(outputStream), 10);
	outputStream = std::make_unique<CompressOutputMemoryStream>(std::move(outputStream));

	while (!inputStream->IsEOF())
	{
		std::vector<uint8_t> byteVec(100);
		std::streamsize byteReaded = inputStream->ReadBlock(byteVec.data(), 100);
		outputStream->WriteBlock(byteVec.data(), byteReaded);
	}
}