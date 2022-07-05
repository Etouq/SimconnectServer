#ifndef __DATA_HANDLERS_HPP__
#define __DATA_HANDLERS_HPP__

#include "AirspeedHandler/AirspeedHandler.hpp"
#include "AltitudeHandler/AltitudeHandler.hpp"
#include "ApInfoHandler/ApInfoHandler.hpp"
#include "AttitudeHandler/AttitudeHandler.hpp"
#include "BottombarHandler/BottombarHandler.hpp"
#include "HsiBrgHandler/HsiBrgHandler.hpp"
#include "HsiHandler/HsiHandler.hpp"
#include "MiscHandler/MiscHandler.hpp"
#include "NavInfoHandler/NavInfoHandler.hpp"
#include "RadioHandler/RadioHandler.hpp"
#include "WindInfoHandler/WindInfoHandler.hpp"
#include "AircraftHandler/AircraftHandler.hpp"
#include "EngineHandler/EngineHandler.hpp"


using airspeed::AirspeedHandler;
using altitude::AltitudeHandler;
using apinfo::ApInfoHandler;
using attitude::AttitudeHandler;
using bottombar::BottombarHandler;
using hsi::HsiHandler;
using hsibrg::HsiBrgHandler;
using misc::MiscHandler;
using navinfo::NavInfoHandler;
using radio::RadioHandler;
using windinfo::WindInfoHandler;

using handler::aircraft::AircraftHandler;
using handler::engine::EngineHandler;

#endif  // __DATA_HANDLERS_HPP__