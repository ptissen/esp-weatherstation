/* Unit conversion functions for esp32-weather-epd.
 * Copyright (C) 2023  Luke Marzen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "helper_conversions.h"
#include "logging.h"
#include <cmath>

int CONVERT_WIND_msToBeaufort(float speed) {
    if (speed < 0.3)        return 0;
    else if (speed < 1.6)   return 1;
    else if (speed < 3.4)   return 2;
    else if (speed < 5.5)   return 3;
    else if (speed < 8.0)   return 4;
    else if (speed < 10.8)  return 5;
    else if (speed < 13.9)  return 6;
    else if (speed < 17.2)  return 7;
    else if (speed < 20.8)  return 8;
    else if (speed < 24.5)  return 9;
    else if (speed < 28.5)  return 10;
    else if (speed < 32.7)  return 11;
    else return 12;
}

bool contains(const std::vector<int>& vec, int value) {
    for (const auto& x : vec) {
    if (x == value) {
        return true;
    }
    }
    return false;
}

int CONVERT_WEATHER_multipleConditionsToOne(const std::vector<int>& vec){
    const std::vector<int> sortedVector = {
    800,  // wi_day_sunny_196x196
    801,  // wi_day_cloudy_gusts_196x196
    802,  // wi_day_cloudy_gusts_196x196
    803,  // wi_day_cloudy_gusts_196x196
    804,  // wi_day_sunny_overcast_196x196
    300,  // wi_day_sprinkle_196x196
    301,  // wi_day_sprinkle_196x196
    302,  // wi_day_rain_196x196
    310,  // wi_day_rain_196x196
    311,  // wi_day_rain_196x196
    312,  // wi_day_rain_196x196
    313,  // wi_day_rain_196x196
    314,  // wi_day_rain_196x196
    321,  // wi_day_sprinkle_196x196
    500,  // wi_day_sprinkle_196x196
    501,  // wi_day_rain_196x196
    502,  // wi_day_rain_196x196
    503,  // wi_day_rain_196x196
    504,  // wi_day_rain_196x196
    511,  // wi_day_rain_mix_196x196
    520,  // wi_day_showers_196x196
    521,  // wi_day_showers_196x196
    522,  // wi_day_showers_196x196
    531,  // wi_day_storm_showers_196x196
    600,  // wi_day_snow_196x196
    601,  // wi_day_sleet_196x196
    602,  // wi_day_snow_196x196
    611,  // wi_day_rain_mix_196x196
    612,  // wi_day_rain_mix_196x196
    615,  // wi_day_rain_mix_196x196
    616,  // wi_day_rain_mix_196x196
    620,  // wi_day_rain_mix_196x196
    621,  // wi_day_snow_196x196
    622,  // wi_day_snow_196x196
    701,  // wi_day_showers_196x196
    200,  // wi_day_thunderstorm_196x196
    201,  // wi_day_thunderstorm_196x196
    202,  // wi_day_thunderstorm_196x196
    210,  // wi_day_lightning_196x196
    211,  // wi_day_lightning_196x196
    212,  // wi_day_lightning_196x196
    221,  // wi_day_lightning_196x196
    230,  // wi_day_thunderstorm_196x196
    231,  // wi_day_thunderstorm_196x196
    232,  // wi_day_thunderstorm_196x196
    711,  // wi_smoke_196x196
    721,  // wi_day_haze_196x196
    731,  // wi_dust_196x196
    741,  // wi_day_fog_196x196
    761,  // wi_dust_196x196
    762,  // wi_dust_196x196
    781,  // wi_tornado_196x196
    957,  // wi_strong_wind_196x196
    906,  // wi_day_hail_196x196
    904,  // wi_hot_196x196
    903,  // wi_snowflake_cold_196x196
    902,  // wi_hurricane_196x196
    900   // wi_tornado_196x196
    };
  
    for (int i = sortedVector.size() - 1; i >= 0; i--) {
        if (contains(vec, sortedVector[i])) {
            return sortedVector[i];
        }
    }

    for (int i = 0; i <= vec.size(); i++) {
        logW.print("Icon not valid: " + String(vec.at(i)));
    }

    return -1;
}