//
//  main.cpp
//  apngqao
//
//  Created by *p on 4/2/18.
//  Copyright © 2018 *p. All rights reserved.
//

#include "initializer.hpp"
#include "core.hpp"
coreVariables CoreData;
void wakeUpWorker(unsigned short usImageQuality);
void binarySearch(unsigned short &usQualityMax, unsigned short &usQualityMin);
void release();
int main(int argc, const char * argv[]) {
	
	initializer CoreInitializer(argv, CoreData);
	
	unsigned short usRangeMax = 100;
	unsigned short usRangeMin = 1;
	
	if(CoreData.m_usInitialQuality != 0){
		core Worker(CoreData, CoreData.m_usInitialQuality);
		Worker.run();
		Worker.release();
		Worker.cleanTemp();
	}
	else{
		binarySearch(usRangeMax, usRangeMin);
		std::cout << "Quality " << usRangeMin << " ~ " << usRangeMax
		<< ", 범위 " << usRangeMax - usRangeMin + 1 <<" 의 Animated PNG 제작중..." << std::endl;
	}
	
	unsigned short numberOfWorker = usRangeMax - usRangeMin + 1;
	
	std::thread thread_handle[numberOfWorker];
	for(unsigned short cursor = 0; cursor < numberOfWorker; cursor++){
		unsigned short usQuality = usRangeMin;
		usQuality = usQuality + cursor;
		std::cout << "Quality " << usQuality << " 제작중..." << std::endl;
		thread_handle[cursor] = std::thread(wakeUpWorker, usQuality);
	}
	for(unsigned short cursor = 0; cursor < numberOfWorker; cursor++){
		thread_handle[cursor].join();
	}
	
	release();
	
	return 0;
}

void binarySearch(unsigned short& QualityMax, unsigned short& QualityMin){
	unsigned short& usRangeMax = QualityMax;
	unsigned short& usRangeMin = QualityMin;
	
	unsigned short usDeltaRange = usRangeMax - usRangeMin + 1;
	unsigned short cursor = 0;
	unsigned long ulResultSize = 0;
	
	std::cout << "논리 코어 개수 : " << CoreData.m_uiLogicalCoreNumber << std::endl;
	
	while(usDeltaRange > (CoreData.m_uiLogicalCoreNumber + 1)){
		usDeltaRange = usRangeMax - usRangeMin + 1;
		std::cout << "Range : " << usRangeMin << " ~ " << usRangeMax << std::endl;
		//std::cout << "delta of range is : " << usDeltaRange << std::endl;
		cursor = usRangeMin + (usDeltaRange/2);
		
		std::cout << "Quality " << cursor << " 제작중..." << std::endl;
		core Worker(CoreData, cursor);
		Worker.run();
		Worker.cleanTemp();
		ulResultSize = Worker.getAPNGSize();
		
		std::cout << "Quality " << cursor << " : " << ulResultSize << " Byte"<< std::endl;
		
		if(ulResultSize > CoreData.m_uiMaxResultSize){
			usRangeMax = cursor-1;
		}
		else if(ulResultSize == CoreData.m_uiMaxResultSize){
			usRangeMax = cursor-1;
		}
		else if(ulResultSize < CoreData.m_uiMaxResultSize){
			usRangeMin = cursor+1;
		}
		usDeltaRange = usRangeMax - usRangeMin + 1;
	}
}

void wakeUpWorker(unsigned short usImageQuality){
	core Worker(CoreData, usImageQuality);
	Worker.run();
	Worker.recordResult();
}
void release(){
	boost::filesystem::path path_Output = CoreData.m_path_Myself;
	std::map<unsigned short, boost::filesystem::path>::iterator cursor;
	cursor = CoreData.mapResult.end();
	cursor--;
	boost::filesystem::path pathTempAPNG = cursor->second;
	path_Output /= pathTempAPNG.filename();
	
	boost::filesystem::copy(pathTempAPNG, path_Output);
}
