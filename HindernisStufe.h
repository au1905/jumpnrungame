/*
 * HindernisStufe.h
 *
 *  Created on: 25.04.2017
 *      Author: nopper03
 */

#ifndef SRC_HINDERNISSTUFE_H_
#define SRC_HINDERNISSTUFE_H_

#include "Hindernisse.h"


class Hindernis_Stufe: public Hindernisse {
public:
	Hindernis_Stufe(double x, double y, double size, GLuint texturNr);
	virtual ~Hindernis_Stufe();

	void collision(double px, double py);
};


#endif /* SRC_HINDERNISSTUFE_H_ */
