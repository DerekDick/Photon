#ifndef _MIRROR_H_
#define _MIRROR_H_

#include "Lense.h"

class Mirror : public Lense {
	bool change(std::vector<Photon*>::iterator &target, std::vector<Photon*> &photons);
};

#endif // _MIRROR_H_