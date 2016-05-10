#include "../SerializadorFeatureFactory.h"
#include "../Headers/SerializadorFeature.h"

iSerializadorFeaturePtr SerializadorFeatureFactory_Nuevo()
{
	return new SerializadorFeature();
}
