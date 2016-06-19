#ifndef _LENSERGB_H_
#define _LENSERGB_H_

#include "Lense.h"

class LenseRGB : public Lense {
	bool change(std::vector<Photon*>::iterator &target, std::vector<Photon*> &photons);
};

#endif // _LENSERGB_H_