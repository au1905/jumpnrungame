/*
 * GameOver.h
 *
 *  Created on: 25.07.2017
 *      Author: nopper09
 */

#ifndef SRC_GAMEOVER_H_
#define SRC_GAMEOVER_H_

#include "Object.h"

class GameOver: public Object {
public:
	GameOver(GLuint texturNr);
	virtual ~GameOver();
};

#endif /* SRC_GAMEOVER_H_ */
