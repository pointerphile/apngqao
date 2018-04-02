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
public:
	void checkInputIsInteger();
	void setInitialQuality();
	void setFrameDelay();
	void setSelfPath();
	void setPath_pngquant();
	void setPath_apngasm();
	void setPath_apngopt();
}
#endif /* initializer_hpp */
