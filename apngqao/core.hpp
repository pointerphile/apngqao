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
	boost::filesystem::path strTempName;
	boost::filesystem::path strTempDirName;
public:
	void setTempName();
	void setTempDirName();
	void runApp_pngquant();
	void runApp_pngadm();
	void runApp_pngopt();
	void release();
	void cleanTemp();
};
#endif /* core_hpp */
