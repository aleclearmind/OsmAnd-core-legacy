#ifndef _OSMAND_TRANSPORT_ROUTING_CONFIGURATION_H
#define _OSMAND_TRANSPORT_ROUTING_CONFIGURATION_H
#include "CommonCollections.h"
#include "boost/dynamic_bitset.hpp"
#include "commonOsmAndCore.h"
#include "openingHoursParser.h"
// #include <algorithm>

class GeneralRouter;
struct TransportRoute;
typedef boost::dynamic_bitset<> dynbitset;

struct TransportRoutingConfiguration {
	const string KEY = "public_transport";
	int32_t zoomToLoadTiles = 15;
	int32_t walkRadius = 1500;
	int32_t walkChangeRadius = 300;
	int32_t maxNumberOfChanges = 2; // replaced with max_num_changes

	int32_t ptLimitResultsByNumber = 50; // pt_limit - limit number of best routes (0 = unlimited)

	double increaseForAlternativesRoutes = 2.0;
	double increaseForAltRoutesWalking = 3.0;

	int combineAltRoutesDiffStops = 120;
	int combineAltRoutesSumDiffStops = 300;

	int32_t maxRouteTime = 60 * 60 * 10;
	int32_t maxRouteDistance = 0;
	int32_t maxRouteIncreaseSpeed = 30;
	SHARED_PTR<GeneralRouter> router;

	float walkSpeed = (float)(3.6 / 3.6);
	float defaultTravelSpeed = (60 / 3.6);

	int32_t defaultStopTime = 0;
	UNORDERED(map)<string, int32_t> stopTimes;

	int32_t defaultBoardingTime = 0;
	UNORDERED(map)<string, int32_t> boardingTimes;

	int32_t defaultChangeTime = 0;
	UNORDERED(map)<string, int32_t> changingTimes;

	bool useSchedule = false;

	int32_t scheduleTimeOfDay = 12 * 60 * 6;
	int32_t scheduleMaxTime = 50 * 6;
	//    int32_t scheduleDayNumber; Unused

	// Drop routes whose opening_hours say they do not run at openingHoursTime. Mirrors
	// TransportRoutingConfiguration.java field for field — java_wrap.cpp copies both across, so
	// the java planner and this one make the same decision. Off by default.
	bool filterByOpeningHours = false;
	int64_t openingHoursTime = 0;  // epoch millis, as java hands it over

	// opening_hours strings repeat across every stop of a route and across an operator's routes,
	// and parsing one is not cheap. Keyed by the string, not the route.
	UNORDERED(map)<string, std::shared_ptr<OpeningHoursParser::OpeningHours>> openingHoursCache;

	MAP_STR_FLOAT speed;
	UNORDERED(map)<string, float> rawTypes;

	TransportRoutingConfiguration();

	TransportRoutingConfiguration(SHARED_PTR<GeneralRouter> prouter,
								  MAP_STR_STR params);

	float getSpeedByRouteType(std::string routeType);
	dynbitset getRawBitset(std::string tg, std::string vl);
	uint getRawType(string &tg, string &vl);

	int32_t getStopTime(const std::string &routeType);
	int32_t getBoardingTime(const std::string &routeType);
	int32_t getChangeTime(const std::string &fromRouteType, const std::string &toRouteType);

	bool isRouteOpen(const SHARED_PTR<TransportRoute> &route);
};

#endif	//_OSMAND_TRANSPORT_ROUTING_CONFIGURATION_H
