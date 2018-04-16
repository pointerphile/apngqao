//
//  core.cpp
//  apngqao
//
//  Created by *p on 4/2/18.
//  Copyright © 2018 *p. All rights reserved.
//

#include "core.hpp"
core::core(coreVariables& CoreDataStruct, unsigned short usQuality) : CoreData(CoreDataStruct) {
	m_usQuality = usQuality;
}
void core::setTempName(){
	auto rawTime = std::chrono::system_clock::now();
	auto ctimeNow = std::chrono::system_clock::to_time_t(rawTime);
	std::ostringstream time2string;
	time2string << std::put_time(std::localtime(&ctimeNow), "%Y%m%d%H%M%S") << "-Q" << m_usQuality;
	m_pathTempName = time2string.str();
}
void core::setPath_tempDir(){
	m_pathTempDir = CoreData.m_path_TempRootDir;
	m_pathTempDir /= m_pathTempName;
}
void core::setPath_tempAPNG(){
	m_pathTempAPNG = m_pathTempDir;
	m_pathTempAPNG += ".png";
}
void core::makeTempDir(){
	boost::filesystem::create_directory(m_pathTempDir);
	boost::filesystem::directory_iterator cursor(CoreData.m_path_SourceDir);
	if(boost::filesystem::is_directory(CoreData.m_path_SourceDir)){
		for (auto& reader : cursor) {
			if((reader.path().extension()) == ".png"){
				boost::filesystem::path path_TempImage = m_pathTempDir;
				path_TempImage /= reader.path().filename();
				boost::filesystem::copy(reader.path(), path_TempImage);
			}
		}
	}
}
void core::runApp_pngquant(){
	boost::filesystem::directory_iterator cursor(m_pathTempDir);
	for (auto& reader : cursor) {
		boost::filesystem::path command = CoreData.m_path_pngquant;
		command += " --force --ext=.png --speed=1 --quality=";
		command += std::to_string(m_usQuality);
		command += " ";
		command += reader.path();
		
		boost::process::child run(command.string());
		run.wait();
	}
}
void core::runApp_apngasm(){
	boost::filesystem::path command = CoreData.m_path_apngasm;
	command += " -o ";
	command += m_pathTempAPNG;
	command += " ";
	command += m_pathTempDir;
	command /= "*.png";
	command += " -F -d ";
	command += std::to_string(CoreData.m_usDelayFrame);

	boost::process::child run(command.string());
	run.wait();
}
void core::runApp_apngopt(){
	boost::filesystem::path command = CoreData.m_path_apngopt;
	command += " -i30 ";
	command += m_pathTempAPNG;
	command += " ";
	command += m_pathTempAPNG;
	
	boost::process::child run(command.string());
	run.wait();
}
unsigned long core::getAPNGSize(){
	unsigned long result;
	result = boost::filesystem::file_size(m_pathTempAPNG);
	return result;
}
void core::recordResult(){
	if(getAPNGSize() < CoreData.m_uiMaxResultSize){
		CoreData.mapResult.insert(std::make_pair(m_usQuality, m_pathTempAPNG));
	}
}
void core::release(){
	boost::filesystem::path path_Output = CoreData.m_path_Myself;
	path_Output /= m_pathTempAPNG.filename();
	boost::filesystem::copy(m_pathTempAPNG, path_Output);
}
void core::cleanTemp(){
	boost::filesystem::remove_all(m_pathTempDir);
	//boost::filesystem::remove(m_pathTempAPNG);
}
void core::run(){
	if(m_usQuality <= 100){
		setTempName();
		setPath_tempDir();
		setPath_tempAPNG();
		makeTempDir();
		runApp_pngquant();
		runApp_apngasm();
		runApp_apngopt();
	}
}
