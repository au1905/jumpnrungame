/*
 * HindernisTreppe.h
 *
 *  Created on: 09.05.2017
 *      Author: nopper03
 */

#ifndef SRC_HINDERNISTREPPE_H_
#define SRC_HINDERNISTREPPE_H_

#include "Hindernisse.h"

class HindernisTreppe: public Hindernisse {
public:
	HindernisTreppe(double x, double y, double size, GLuint texturNr);
	virtual ~HindernisTreppe();

};

#endif /* SRC_HINDERNISTREPPE_H_ */
