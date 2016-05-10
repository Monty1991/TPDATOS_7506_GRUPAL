#include "../HidratadorFeatureFactory.h"
#include "../Headers/HidratadorFeature.h"

iHidratadorFeaturePtr HidratadorFeatureFactory_Nuevo()
{
	return new HidratadorFeature();
}
