//
//  initializer.hpp
//  apngqao
//
//  Created by *p on 4/2/18.
//  Copyright © 2018 *p. All rights reserved.
//

#ifndef initializer_hpp
#define initializer_hpp

#include "headers.hpp"
class initializer{
private:
	coreVariables& CoreData;
public:
	initializer(const char* argv[], coreVariables& CoreDataStruct);
	void setLogicalCoreNumber();
	int integerInputReceiver();
	void setInitialQuality();
	void setFrameDelay();
	void setPath_Myself(const char* argv[]);
	void setPath_SourceDir(const char* argv[]);
	void setPath_pngquant();
	void setPath_apngasm();
	void setPath_apngopt();
	void setPath_TempRootDir();
	void renameSourceFiles();
	void clearTempRootDir();
};
#endif /* initializer_hpp */
