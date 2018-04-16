//
//  initializer.cpp
//  apngqao
//
//  Created by *p on 4/2/18.
//  Copyright © 2018 *p. All rights reserved.
//

#include "initializer.hpp"
initializer::initializer(const char* argv[], coreVariables& CoreDataStruct) : CoreData(CoreDataStruct) {
	setLogicalCoreNumber();
	setFrameDelay();
	setInitialQuality();
	setPath_Myself(argv);
	setPath_pngquant();
	setPath_apngasm();
	setPath_apngopt();
	setPath_TempRootDir();
	setPath_SourceDir(argv);
	renameSourceFiles();
	clearTempRootDir();
}
void initializer::setLogicalCoreNumber(){
	CoreData.m_uiLogicalCoreNumber = std::thread::hardware_concurrency();
}
int initializer::integerInputReceiver(){
	unsigned short usResult = 0;
	bool isValidInput = false;
	while(isValidInput == false){
		std::cin >> usResult;
		if(std::cin.fail()){
			std::cin.clear();
			std::cin.ignore();
			std::cout << "입력은 정수만 받습니다. : ";
		}
		else{
			isValidInput = true;
		}
	}
	return usResult;
}
void initializer::setInitialQuality(){
	unsigned short usResult = 0;
	bool isInputValid = false;
	while(isInputValid == false){
		std::cout << "Animated PNG의 품질을 입력하세요." << std::endl;
		std::cout << "0을 입력하면 "<< CoreData.m_uiMaxResultSize
		<< " Byte 보다 작은 Animated PNG를 만드는 걸 도와드립니다." << std::endl;
		std::cout << "Animated PNG의 품질을 입력하세요.(0~100)" << std::endl;
		usResult = integerInputReceiver();
		if(usResult > 100){
			std::cout << "범위는 0~100임 : " << std::endl;;
		}
		else{
			isInputValid = true;
		}
	}
	CoreData.m_usInitialQuality = usResult;
}
void initializer::setFrameDelay(){
	unsigned short usResult = 0;
	bool isInputValid = false;
	while(isInputValid == false){
		std::cout << "Animated PNG의 FPS를 입력하세요. : ";
		usResult = integerInputReceiver();
		if(usResult > 0){
			isInputValid = true;
		}
		else{
			std::cout << "FPS는 1보다 작을 수 없습니다." << std::endl;;
		}
	}
	usResult = std::round(1000.0f / usResult);
	CoreData.m_usDelayFrame = usResult;
}
void initializer::setPath_Myself(const char* argv[]){
	CoreData.m_path_Myself = argv[0];
	CoreData.m_path_Myself = CoreData.m_path_Myself.remove_filename();
}
void initializer::setPath_SourceDir(const char* argv[]){
	CoreData.m_path_SourceDir = argv[1];
}
void initializer::setPath_pngquant(){
	CoreData.m_path_pngquant = CoreData.m_path_Myself;
	CoreData.m_path_pngquant /= "pngquant";
}
void initializer::setPath_apngasm(){
	CoreData.m_path_apngasm = CoreData.m_path_Myself;
	CoreData.m_path_apngasm /= "apngasm";
}
void initializer::setPath_apngopt(){
	CoreData.m_path_apngopt = CoreData.m_path_Myself;
	CoreData.m_path_apngopt /= "apngopt";
}
void initializer::setPath_TempRootDir(){
	CoreData.m_path_TempRootDir = CoreData.m_path_Myself;
	CoreData.m_path_TempRootDir /= "temp";
}
void initializer::renameSourceFiles(){
	boost::filesystem::directory_iterator cursor(CoreData.m_path_SourceDir);
	unsigned int uiCounter = 0;
	if(boost::filesystem::is_directory(CoreData.m_path_SourceDir)){
		for (auto& reader : cursor) {
			if((reader.path().extension()) == ".png"){
				boost::filesystem::path path_changedName = CoreData.m_path_SourceDir;
				std::stringstream nameFormat;
				nameFormat << std::setw(4) << std::setfill('0') << uiCounter;
				path_changedName /= nameFormat.str();
				path_changedName += ".png";
				boost::filesystem::rename(reader.path(), path_changedName);
				uiCounter++;
			}
		}
	}
}
void initializer::clearTempRootDir(){
	if(boost::filesystem::exists(CoreData.m_path_TempRootDir) == true){
		boost::filesystem::remove_all(CoreData.m_path_TempRootDir);
	}
	boost::filesystem::create_directory(CoreData.m_path_TempRootDir);
}
