//
//  coreVariables.h
//  apngqao
//
//  Created by *p on 4/2/18.
//  Copyright © 2018 *p. All rights reserved.
//

#ifndef coreVariables_h
#define coreVariables_h
#include <boost/filesystem.hpp>
#include <map>
struct coreVariables{
	boost::filesystem::path m_path_Myself;
	boost::filesystem::path m_path_SourceDir;
	boost::filesystem::path m_path_pngquant;
	boost::filesystem::path m_path_apngasm;
	boost::filesystem::path m_path_apngopt;
	boost::filesystem::path m_path_TempRootDir;
	unsigned short m_usDelayFrame;
	unsigned short m_usInitialQuality;
	unsigned int m_uiLogicalCoreNumber;
	unsigned long m_uiMaxResultSize = 10485760;
	std::map<unsigned short, boost::filesystem::path> mapResult;
};

#endif /* coreVariables_h */
