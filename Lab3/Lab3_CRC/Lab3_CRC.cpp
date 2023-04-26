#include<iostream>
#include<fstream> 

const int BLOCK_SIZE = 8;

void CalculateChecksum(char* res, const char* data, uint32_t length) {
	uint32_t crc = 0xFFFFFFFF;
	uint32_t polynomial = 0xEDB88320;

	for (uint32_t i = 0; i < length; ++i) {
		crc ^= data[i];
		for (int j = 0; j < 8; ++j) {
			crc = (crc >> 1) ^ ((crc & 1) * polynomial);
		}
	}
	crc ^= 0xFFFFFFFF;

	snprintf(res, BLOCK_SIZE, "%08X", crc);
}

void main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Error: Dll path not specified.\n";
		return;
	}

	std::ifstream infile(argv[1], std::ios::binary);

	if (!infile.is_open()) {
		std::cerr << "Error: Could not open DLL file.\n";
		return;
	}

	infile.seekg(0, std::ios::end);
	uint32_t fileSize = infile.tellg();
	infile.seekg(0, std::ios::beg);

	char* fileData = new char[fileSize];
	infile.read(fileData, fileSize);
	infile.close();

	char calculatedChecksum[BLOCK_SIZE];
	CalculateChecksum(calculatedChecksum, fileData, fileSize);

	std::ofstream outfile(argv[1], std::ios::binary | std::ios::app);

	if (!outfile.is_open()) {
		std::cerr << "Error: Could not open DLL file.\n";
		return;
	}

	outfile.write(calculatedChecksum, BLOCK_SIZE);
	outfile.close();
}