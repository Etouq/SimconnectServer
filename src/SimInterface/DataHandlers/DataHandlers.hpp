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
#include "AircraftHandlers/JetHandler/JetHandler.hpp"
#include "AircraftHandlers/PropHandler/PropHandler.hpp"
#include "AircraftHandlers/TurbopropHandler/TurbopropHandler.hpp"


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

using aircraft::base::AircraftHandler;
using aircraft::jet::JetHandler;
using aircraft::prop::PropHandler;
using aircraft::turboprop::TurbopropHandler;

#endif  // __DATA_HANDLERS_HPP__