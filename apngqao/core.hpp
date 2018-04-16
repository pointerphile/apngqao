//
//  core.hpp
//  apngqao
//
//  Created by *p on 4/2/18.
//  Copyright © 2018 *p. All rights reserved.
//

#ifndef core_hpp
#define core_hpp

#include "headers.hpp"
class core {
private:
	boost::filesystem::path m_pathTempName;
	boost::filesystem::path m_pathTempDir;
	boost::filesystem::path m_pathTempAPNG;
	unsigned short m_usQuality;
	coreVariables& CoreData;
public:
	core(coreVariables& CoreDataStruct, unsigned short usQuality);
	void setTempName();
	void setPath_tempDir();
	void setPath_tempAPNG();
	void makeTempDir();
	void runApp_pngquant();
	void runApp_apngasm();
	void runApp_apngopt();
	void recordResult();
	unsigned long getAPNGSize();
	void release();
	void cleanTemp();
	void run();
};
#endif /* core_hpp */
