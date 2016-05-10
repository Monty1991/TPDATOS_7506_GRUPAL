#include "../FeatureFactory.h"
#include "../Headers/Feature.h"

iFeaturePtr FeatureFactory_Nuevo(uValue valor, eValueType tipo)
{
	return new Feature(valor, tipo);
}
