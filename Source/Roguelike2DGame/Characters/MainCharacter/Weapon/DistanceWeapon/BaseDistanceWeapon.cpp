
#include "BaseDistanceWeapon.h"



UBaseDistanceWeapon::UBaseDistanceWeapon()
{
	damage = 10;
	rateReload = 1.f;
}


void UBaseDistanceWeapon::SetTimeReload(const float rate)
{
	CHECK_WITH_LOG_WARNING(rate < 0.0f, "Negative value can't set")

	rateReload = rate;
}

float UBaseDistanceWeapon::GetTimeReload()
{
	return rateReload;
}
