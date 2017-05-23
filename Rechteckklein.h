


#ifndef SRC_RECHTECKKLEIN_H_
#define SRC_RECHTECKKLEIN_H_

#include <GL/glu.h>
#include "Hindernisse.h"

class Rechteckklein: public Hindernisse {
public:
	Rechteckklein(double x, double y, double size, GLuint texturNr);
	virtual ~Rechteckklein();
};

#endif /* SRC_RECHTECKKLEIN_H_ */
