/*
 *   This file belongs to the Project ESP-WeatherStation
 *   Copyright (c) 2023 Peter Tißen, Stephan Brüning
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "helper_icons.h"

#include <map>
#include <cstdint>
#include <vector>
#include "logging.h"

const uint8_t *ICONS::getBattery24(int percent)
{
    if (percent >= 93)
        return IMG_battery_full_90_deg_24x24;
    else if (percent >= 79)
        return IMG_battery_6_bar_90deg_24x24;
    else if (percent >= 65)
        return IMG_battery_5_bar_90deg_24x24;
    else if (percent >= 50)
        return IMG_battery_4_bar_90deg_24x24;
    else if (percent >= 36)
        return IMG_battery_3_bar_90deg_24x24;
    else if (percent >= 22)
        return IMG_battery_2_bar_90deg_24x24;
    else if (percent >= 10)
        return IMG_battery_1_bar_90deg_24x24;

    return IMG_battery_0_bar_90deg_24x24;
}

const uint8_t *ICONS::getWifi16(int dbm)
{
    if (dbm == 0)
        return IMG_wifi_off_16x16;
    else if (dbm >= -50)
        return IMG_wifi_3_16x16;
    else if (dbm >= -60)
        return IMG_wifi_2_16x16;
    else if (dbm >= -70)
        return IMG_wifi_1_16x16;

    return IMG_wifi_0_16x16;
}

// https://openweathermap.org/weather-conditions#Weather-Condition-Codes-1
/*
| Group 2xx       | ID    | Main         | Description                        | Icon   |
| --------------- | ----- | ------------ | ---------------------------------- | ------ |
| Thunderstorm    | 200   | Thunderstorm | thunderstorm IMG_with light rain       | 11d    |
| Thunderstorm    | 201   | Thunderstorm | thunderstorm IMG_with rain             | 11d    |
| Thunderstorm    | 202   | Thunderstorm | thunderstorm IMG_with heavy rain       | 11d    |
| Thunderstorm    | 210   | Thunderstorm | light thunderstorm                 | 11d    |
| Thunderstorm    | 211   | Thunderstorm | thunderstorm                       | 11d    |
| Thunderstorm    | 212   | Thunderstorm | heavy thunderstorm                 | 11d    |
| Thunderstorm    | 221   | Thunderstorm | ragged thunderstorm                | 11d    |
| Thunderstorm    | 230   | Thunderstorm | thunderstorm IMG_with light drizzle    | 11d    |
| Thunderstorm    | 231   | Thunderstorm | thunderstorm IMG_with drizzle          | 11d    |
| Thunderstorm    | 232   | Thunderstorm | thunderstorm IMG_with heavy drizzle    | 11d    |

| Group 3xx       | ID    | Main         | Description                        | Icon   |
| --------------- | ----- | ---------    | ---------------------------------  | ------ |
| Drizzle         | 300   | Drizzle      | light intensity drizzle            | 09d    |
| Drizzle         | 301   | Drizzle      | drizzle                            | 09d    |
| Drizzle         | 302   | Drizzle      | heavy intensity drizzle            | 09d    |
| Drizzle         | 310   | Drizzle      | light intensity drizzle rain       | 09d    |
| Drizzle         | 311   | Drizzle      | drizzle rain                       | 09d    |
| Drizzle         | 312   | Drizzle      | heavy intensity drizzle rain       | 09d    |
| Drizzle         | 313   | Drizzle      | shower rain and drizzle            | 09d    |
| Drizzle         | 314   | Drizzle      | heavy shower rain and drizzle      | 09d    |
| Drizzle         | 321   | Drizzle      | shower drizzle                     | 09d    |

| Group 5xx       | ID    | Main         | Description                        | Icon   |
| -----------     | ----  | ------       | ---------------------------------- | ------ |
| Rain            | 500   | Rain         | light rain                         | 10d    |
| Rain            | 501   | Rain         | moderate rain                      | 10d    |
| Rain            | 502   | Rain         | heavy intensity rain               | 10d    |
| Rain            | 503   | Rain         | very heavy rain                    | 10d    |
| Rain            | 504   | Rain         | extreme rain                       | 10d    |
| Rain            | 511   | Rain         | freezing rain                      | 13d    |
| Rain            | 520   | Rain         | light intensity shower rain        | 09d    |
| Rain            | 521   | Rain         | shower rain                        | 09d    |
| Rain            | 522   | Rain         | heavy intensity shower rain        | 09d    |
| Rain            | 531   | Rain         | ragged shower rain                 | 09d    |

| Group 6xx       | ID    | Main         | Description                        | Icon   |
| -----------     | ----  | ------       | ---------------------------------- | ------ |
| Snow            | 600   | Snow         | light snow                         | 13d    |
| Snow            | 601   | Snow         | snow                               | 13d    |
| Snow            | 602   | Snow         | heavy snow                         | 13d    |
| Snow            | 611   | Snow         | sleet                              | 13d    |
| Snow            | 612   | Snow         | light shower sleet                 | 13d    |
| Snow            | 613   | Snow         | shower sleet                       | 13d    |
| Snow            | 615   | Snow         | light rain and snow                | 13d    |
| Snow            | 616   | Snow         | rain and snow                      | 13d    |
| Snow            | 620   | Snow         | light shower snow                  | 13d    |
| Snow            | 621   | Snow         | shower snow                        | 13d    |
| Snow            | 622   | Snow         | heavy shower snow                  | 13d    |

| Group 7xx       | ID    | Main         | Description                        | Icon   |
| -----------     | ----  | --------     | --------------------------------   | ------ |
| Atmosphere      | 701   | Mist         | mist                               | 50d    |
| Atmosphere      | 711   | Smoke        | smoke                              | 50d    |
| Atmosphere      | 721   | Haze         | haze                               | 50d    |
| Atmosphere      | 731   | Dust         | sand/dust whirls                   | 50d    |
| Atmosphere      | 741   | Fog          | fog                                | 50d    |
| Atmosphere      | 751   | Sand         | sand                               | 50d    |
| Atmosphere      | 761   | Dust         | dust                               | 50d    |
| Atmosphere      | 762   | Ash          | volcanic ash                       | 50d    |
| Atmosphere      | 771   | Squall       | squalls                            | 50d    |
| Atmosphere      | 781   | Tornado      | tornado                            | 50d    |

| Group 800       | ID    | Main         | Description                        | Icon    |
| -----------     | ----  | -------      | ---------------------------------  | ------  |
| Clear           | 800   | Clear        | clear sky                          | 01d 01n |

| Group 80x       | ID    | Main         | Description                        | Icon      |
| -----------     | ----  | --------     | --------------------------------   | ------    |
| Clouds          | 801   | Clouds       | few clouds: 11-25%                 | 02d 02n   |
| Clouds          | 802   | Clouds       | scattered clouds: 25-50%           | 03d 03n   |
| Clouds          | 803   | Clouds       | broken clouds: 51-84%              | 04d 04n   |
| Clouds          | 804   | Clouds       | overcast clouds: 85-100%           | 04d 04n   |
**/

// Use default Mapping that is provided by weather icons
// https://erikflowers.github.io/weather-icons/api-list.html


const std::map<int, const unsigned char *> ICONS_WEATHER_CONDITION_DAY_160 = {
    {200, IMG_wi_day_thunderstorm_160x160},
    {201, IMG_wi_day_thunderstorm_160x160},
    {202, IMG_wi_day_thunderstorm_160x160},
    {210, IMG_wi_day_lightning_160x160},
    {211, IMG_wi_day_lightning_160x160},
    {212, IMG_wi_day_lightning_160x160},
    {221, IMG_wi_day_lightning_160x160},
    {230, IMG_wi_day_thunderstorm_160x160},
    {231, IMG_wi_day_thunderstorm_160x160},
    {232, IMG_wi_day_thunderstorm_160x160},
    {300, IMG_wi_day_sprinkle_160x160},
    {301, IMG_wi_day_sprinkle_160x160},
    {302, IMG_wi_day_rain_160x160},
    {310, IMG_wi_day_rain_160x160},
    {311, IMG_wi_day_rain_160x160},
    {312, IMG_wi_day_rain_160x160},
    {313, IMG_wi_day_rain_160x160},
    {314, IMG_wi_day_rain_160x160},
    {321, IMG_wi_day_sprinkle_160x160},
    {500, IMG_wi_day_sprinkle_160x160},
    {501, IMG_wi_day_rain_160x160},
    {502, IMG_wi_day_rain_160x160},
    {503, IMG_wi_day_rain_160x160},
    {504, IMG_wi_day_rain_160x160},
    {511, IMG_wi_day_rain_mix_160x160},
    {520, IMG_wi_day_showers_160x160},
    {521, IMG_wi_day_showers_160x160},
    {522, IMG_wi_day_showers_160x160},
    {531, IMG_wi_day_storm_showers_160x160},
    {600, IMG_wi_day_snow_160x160},
    {601, IMG_wi_day_sleet_160x160},
    {602, IMG_wi_day_snow_160x160},
    {611, IMG_wi_day_rain_mix_160x160},
    {612, IMG_wi_day_rain_mix_160x160},
    {615, IMG_wi_day_rain_mix_160x160},
    {616, IMG_wi_day_rain_mix_160x160},
    {620, IMG_wi_day_rain_mix_160x160},
    {621, IMG_wi_day_snow_160x160},
    {622, IMG_wi_day_snow_160x160},
    {701, IMG_wi_day_showers_160x160},
    {711, IMG_wi_smoke_160x160},
    {721, IMG_wi_day_haze_160x160},
    {731, IMG_wi_dust_160x160},
    {741, IMG_wi_day_fog_160x160},
    {761, IMG_wi_dust_160x160},
    {762, IMG_wi_dust_160x160},
    {781, IMG_wi_tornado_160x160},
    {800, IMG_wi_day_sunny_160x160},
    {801, IMG_wi_day_cloudy_gusts_160x160},
    {802, IMG_wi_day_cloudy_gusts_160x160},
    {803, IMG_wi_day_cloudy_gusts_160x160},
    {804, IMG_wi_day_sunny_overcast_160x160},
    {900, IMG_wi_tornado_160x160},
    {902, IMG_wi_hurricane_160x160},
    {903, IMG_wi_snowflake_cold_160x160},
    {904, IMG_wi_hot_160x160},
    {906, IMG_wi_day_hail_160x160},
    {957, IMG_wi_strong_wind_160x160}
};


const std::map<int, const unsigned char *> ICONS_WEATHER_CONDITION_NIGHT_160 = {
    {200, IMG_wi_night_alt_thunderstorm_160x160},
    {201, IMG_wi_night_alt_thunderstorm_160x160},
    {202, IMG_wi_night_alt_thunderstorm_160x160},
    {210, IMG_wi_night_alt_lightning_160x160},
    {211, IMG_wi_night_alt_lightning_160x160},
    {212, IMG_wi_night_alt_lightning_160x160},
    {221, IMG_wi_night_alt_lightning_160x160},
    {230, IMG_wi_night_alt_thunderstorm_160x160},
    {231, IMG_wi_night_alt_thunderstorm_160x160},
    {232, IMG_wi_night_alt_thunderstorm_160x160},
    {300, IMG_wi_night_alt_sprinkle_160x160},
    {301, IMG_wi_night_alt_sprinkle_160x160},
    {302, IMG_wi_night_alt_rain_160x160},
    {310, IMG_wi_night_alt_rain_160x160},
    {311, IMG_wi_night_alt_rain_160x160},
    {312, IMG_wi_night_alt_rain_160x160},
    {313, IMG_wi_night_alt_rain_160x160},
    {314, IMG_wi_night_alt_rain_160x160},
    {321, IMG_wi_night_alt_sprinkle_160x160},
    {500, IMG_wi_night_alt_sprinkle_160x160},
    {501, IMG_wi_night_alt_rain_160x160},
    {502, IMG_wi_night_alt_rain_160x160},
    {503, IMG_wi_night_alt_rain_160x160},
    {504, IMG_wi_night_alt_rain_160x160},
    {511, IMG_wi_night_alt_rain_mix_160x160},
    {520, IMG_wi_night_alt_showers_160x160},
    {521, IMG_wi_night_alt_showers_160x160},
    {522, IMG_wi_night_alt_showers_160x160},
    {531, IMG_wi_night_alt_storm_showers_160x160},
    {600, IMG_wi_night_alt_snow_160x160},
    {601, IMG_wi_night_alt_sleet_160x160},
    {602, IMG_wi_night_alt_snow_160x160},
    {611, IMG_wi_night_alt_rain_mix_160x160},
    {612, IMG_wi_night_alt_rain_mix_160x160},
    {615, IMG_wi_night_alt_rain_mix_160x160},
    {616, IMG_wi_night_alt_rain_mix_160x160},
    {620, IMG_wi_night_alt_rain_mix_160x160},
    {621, IMG_wi_night_alt_snow_160x160},
    {622, IMG_wi_night_alt_snow_160x160},
    {701, IMG_wi_night_alt_showers_160x160},
    {711, IMG_wi_smoke_160x160},
    {721, IMG_wi_day_haze_160x160},
    {731, IMG_wi_dust_160x160},
    {741, IMG_wi_night_fog_160x160},
    {761, IMG_wi_dust_160x160},
    {762, IMG_wi_dust_160x160},
    {781, IMG_wi_tornado_160x160},
    {800, IMG_wi_night_clear_160x160},
    {801, IMG_wi_night_alt_cloudy_gusts_160x160},
    {802, IMG_wi_night_alt_cloudy_gusts_160x160},
    {803, IMG_wi_night_alt_cloudy_gusts_160x160},
    {804, IMG_wi_night_alt_cloudy_160x160},
    {900, IMG_wi_tornado_160x160},
    {902, IMG_wi_hurricane_160x160},
    {903, IMG_wi_snowflake_cold_160x160},
    {904, IMG_wi_hot_160x160},
    {906, IMG_wi_night_alt_hail_160x160},
    {957, IMG_wi_strong_wind_160x160}
};

const std::map<int, const unsigned char *> ICONS_WEATHER_CONDITION_160 = {
    {200, IMG_wi_thunderstorm_160x160},
    {201, IMG_wi_thunderstorm_160x160},
    {202, IMG_wi_thunderstorm_160x160},
    {210, IMG_wi_lightning_160x160},
    {211, IMG_wi_lightning_160x160},
    {212, IMG_wi_lightning_160x160},
    {221, IMG_wi_lightning_160x160},
    {230, IMG_wi_thunderstorm_160x160},
    {231, IMG_wi_thunderstorm_160x160},
    {232, IMG_wi_thunderstorm_160x160},
    {300, IMG_wi_sprinkle_160x160},
    {301, IMG_wi_sprinkle_160x160},
    {302, IMG_wi_rain_160x160},
    {310, IMG_wi_rain_mix_160x160},
    {311, IMG_wi_rain_160x160},
    {312, IMG_wi_rain_160x160},
    {313, IMG_wi_showers_160x160},
    {314, IMG_wi_rain_160x160},
    {321, IMG_wi_sprinkle_160x160},
    {500, IMG_wi_sprinkle_160x160},
    {501, IMG_wi_rain_160x160},
    {502, IMG_wi_rain_160x160},
    {503, IMG_wi_rain_160x160},
    {504, IMG_wi_rain_160x160},
    {511, IMG_wi_rain_mix_160x160},
    {520, IMG_wi_showers_160x160},
    {521, IMG_wi_showers_160x160},
    {522, IMG_wi_showers_160x160},
    {531, IMG_wi_storm_showers_160x160},
    {600, IMG_wi_snow_160x160},
    {601, IMG_wi_snow_160x160},
    {602, IMG_wi_sleet_160x160},
    {611, IMG_wi_rain_mix_160x160},
    {612, IMG_wi_rain_mix_160x160},
    {615, IMG_wi_rain_mix_160x160},
    {616, IMG_wi_rain_mix_160x160},
    {620, IMG_wi_rain_mix_160x160},
    {621, IMG_wi_snow_160x160},
    {622, IMG_wi_snow_160x160},
    {701, IMG_wi_showers_160x160},
    {711, IMG_wi_smoke_160x160},
    {721, IMG_wi_day_haze_160x160},
    {731, IMG_wi_dust_160x160},
    {741, IMG_wi_fog_160x160},
    {761, IMG_wi_dust_160x160},
    {762, IMG_wi_dust_160x160},
    {771, IMG_wi_cloudy_gusts_160x160},
    {781, IMG_wi_tornado_160x160},
    {800, IMG_wi_day_sunny_160x160},
    {801, IMG_wi_cloudy_gusts_160x160},
    {802, IMG_wi_cloudy_gusts_160x160},
    {803, IMG_wi_cloudy_gusts_160x160},
    {804, IMG_wi_cloudy_160x160},
    {900, IMG_wi_tornado_160x160},
    {901, IMG_wi_storm_showers_160x160},
    {902, IMG_wi_hurricane_160x160},
    {903, IMG_wi_snowflake_cold_160x160},
    {904, IMG_wi_hot_160x160},
    {905, IMG_wi_windy_160x160},
    {906, IMG_wi_hail_160x160},
    {957, IMG_wi_strong_wind_160x160}
};


const std::map<int, const unsigned char *> ICONS_WEATHER_CONDITION_DAY_64 = {
    {200, IMG_wi_day_thunderstorm_64x64},
    {201, IMG_wi_day_thunderstorm_64x64},
    {202, IMG_wi_day_thunderstorm_64x64},
    {210, IMG_wi_day_lightning_64x64},
    {211, IMG_wi_day_lightning_64x64},
    {212, IMG_wi_day_lightning_64x64},
    {221, IMG_wi_day_lightning_64x64},
    {230, IMG_wi_day_thunderstorm_64x64},
    {231, IMG_wi_day_thunderstorm_64x64},
    {232, IMG_wi_day_thunderstorm_64x64},
    {300, IMG_wi_day_sprinkle_64x64},
    {301, IMG_wi_day_sprinkle_64x64},
    {302, IMG_wi_day_rain_64x64},
    {310, IMG_wi_day_rain_64x64},
    {311, IMG_wi_day_rain_64x64},
    {312, IMG_wi_day_rain_64x64},
    {313, IMG_wi_day_rain_64x64},
    {314, IMG_wi_day_rain_64x64},
    {321, IMG_wi_day_sprinkle_64x64},
    {500, IMG_wi_day_sprinkle_64x64},
    {501, IMG_wi_day_rain_64x64},
    {502, IMG_wi_day_rain_64x64},
    {503, IMG_wi_day_rain_64x64},
    {504, IMG_wi_day_rain_64x64},
    {511, IMG_wi_day_rain_mix_64x64},
    {520, IMG_wi_day_showers_64x64},
    {521, IMG_wi_day_showers_64x64},
    {522, IMG_wi_day_showers_64x64},
    {531, IMG_wi_day_storm_showers_64x64},
    {600, IMG_wi_day_snow_64x64},
    {601, IMG_wi_day_sleet_64x64},
    {602, IMG_wi_day_snow_64x64},
    {611, IMG_wi_day_rain_mix_64x64},
    {612, IMG_wi_day_rain_mix_64x64},
    {615, IMG_wi_day_rain_mix_64x64},
    {616, IMG_wi_day_rain_mix_64x64},
    {620, IMG_wi_day_rain_mix_64x64},
    {621, IMG_wi_day_snow_64x64},
    {622, IMG_wi_day_snow_64x64},
    {701, IMG_wi_day_showers_64x64},
    {711, IMG_wi_smoke_64x64},
    {721, IMG_wi_day_haze_64x64},
    {731, IMG_wi_dust_64x64},
    {741, IMG_wi_day_fog_64x64},
    {761, IMG_wi_dust_64x64},
    {762, IMG_wi_dust_64x64},
    {781, IMG_wi_tornado_64x64},
    {800, IMG_wi_day_sunny_64x64},
    {801, IMG_wi_day_cloudy_gusts_64x64},
    {802, IMG_wi_day_cloudy_gusts_64x64},
    {803, IMG_wi_day_cloudy_gusts_64x64},
    {804, IMG_wi_day_sunny_overcast_64x64},
    {900, IMG_wi_tornado_64x64},
    {902, IMG_wi_hurricane_64x64},
    {903, IMG_wi_snowflake_cold_64x64},
    {904, IMG_wi_hot_64x64},
    {906, IMG_wi_day_hail_64x64},
    {957, IMG_wi_strong_wind_64x64}
};

const std::map<int, const unsigned char *> ICONS_WEATHER_CONDITION_NIGHT_64 = {
    {200, IMG_wi_night_alt_thunderstorm_64x64},
    {201, IMG_wi_night_alt_thunderstorm_64x64},
    {202, IMG_wi_night_alt_thunderstorm_64x64},
    {210, IMG_wi_night_alt_lightning_64x64},
    {211, IMG_wi_night_alt_lightning_64x64},
    {212, IMG_wi_night_alt_lightning_64x64},
    {221, IMG_wi_night_alt_lightning_64x64},
    {230, IMG_wi_night_alt_thunderstorm_64x64},
    {231, IMG_wi_night_alt_thunderstorm_64x64},
    {232, IMG_wi_night_alt_thunderstorm_64x64},
    {300, IMG_wi_night_alt_sprinkle_64x64},
    {301, IMG_wi_night_alt_sprinkle_64x64},
    {302, IMG_wi_night_alt_rain_64x64},
    {310, IMG_wi_night_alt_rain_64x64},
    {311, IMG_wi_night_alt_rain_64x64},
    {312, IMG_wi_night_alt_rain_64x64},
    {313, IMG_wi_night_alt_rain_64x64},
    {314, IMG_wi_night_alt_rain_64x64},
    {321, IMG_wi_night_alt_sprinkle_64x64},
    {500, IMG_wi_night_alt_sprinkle_64x64},
    {501, IMG_wi_night_alt_rain_64x64},
    {502, IMG_wi_night_alt_rain_64x64},
    {503, IMG_wi_night_alt_rain_64x64},
    {504, IMG_wi_night_alt_rain_64x64},
    {511, IMG_wi_night_alt_rain_mix_64x64},
    {520, IMG_wi_night_alt_showers_64x64},
    {521, IMG_wi_night_alt_showers_64x64},
    {522, IMG_wi_night_alt_showers_64x64},
    {531, IMG_wi_night_alt_storm_showers_64x64},
    {600, IMG_wi_night_alt_snow_64x64},
    {601, IMG_wi_night_alt_sleet_64x64},
    {602, IMG_wi_night_alt_snow_64x64},
    {611, IMG_wi_night_alt_rain_mix_64x64},
    {612, IMG_wi_night_alt_rain_mix_64x64},
    {615, IMG_wi_night_alt_rain_mix_64x64},
    {616, IMG_wi_night_alt_rain_mix_64x64},
    {620, IMG_wi_night_alt_rain_mix_64x64},
    {621, IMG_wi_night_alt_snow_64x64},
    {622, IMG_wi_night_alt_snow_64x64},
    {701, IMG_wi_night_alt_showers_64x64},
    {711, IMG_wi_smoke_64x64},
    {721, IMG_wi_day_haze_64x64},
    {731, IMG_wi_dust_64x64},
    {741, IMG_wi_night_fog_64x64},
    {761, IMG_wi_dust_64x64},
    {762, IMG_wi_dust_64x64},
    {781, IMG_wi_tornado_64x64},
    {800, IMG_wi_night_clear_64x64},
    {801, IMG_wi_night_alt_cloudy_gusts_64x64},
    {802, IMG_wi_night_alt_cloudy_gusts_64x64},
    {803, IMG_wi_night_alt_cloudy_gusts_64x64},
    {804, IMG_wi_night_alt_cloudy_64x64},
    {900, IMG_wi_tornado_64x64},
    {902, IMG_wi_hurricane_64x64},
    {903, IMG_wi_snowflake_cold_64x64},
    {904, IMG_wi_hot_64x64},
    {906, IMG_wi_night_alt_hail_64x64},
    {957, IMG_wi_strong_wind_64x64}
};

const std::map<int, const unsigned char *> ICONS_WEATHER_CONDITION_64 = {
    {200, IMG_wi_thunderstorm_64x64},
    {201, IMG_wi_thunderstorm_64x64},
    {202, IMG_wi_thunderstorm_64x64},
    {210, IMG_wi_lightning_64x64},
    {211, IMG_wi_lightning_64x64},
    {212, IMG_wi_lightning_64x64},
    {221, IMG_wi_lightning_64x64},
    {230, IMG_wi_thunderstorm_64x64},
    {231, IMG_wi_thunderstorm_64x64},
    {232, IMG_wi_thunderstorm_64x64},
    {300, IMG_wi_sprinkle_64x64},
    {301, IMG_wi_sprinkle_64x64},
    {302, IMG_wi_rain_64x64},
    {310, IMG_wi_rain_mix_64x64},
    {311, IMG_wi_rain_64x64},
    {312, IMG_wi_rain_64x64},
    {313, IMG_wi_showers_64x64},
    {314, IMG_wi_rain_64x64},
    {321, IMG_wi_sprinkle_64x64},
    {500, IMG_wi_sprinkle_64x64},
    {501, IMG_wi_rain_64x64},
    {502, IMG_wi_rain_64x64},
    {503, IMG_wi_rain_64x64},
    {504, IMG_wi_rain_64x64},
    {511, IMG_wi_rain_mix_64x64},
    {520, IMG_wi_showers_64x64},
    {521, IMG_wi_showers_64x64},
    {522, IMG_wi_showers_64x64},
    {531, IMG_wi_storm_showers_64x64},
    {600, IMG_wi_snow_64x64},
    {601, IMG_wi_snow_64x64},
    {602, IMG_wi_sleet_64x64},
    {611, IMG_wi_rain_mix_64x64},
    {612, IMG_wi_rain_mix_64x64},
    {615, IMG_wi_rain_mix_64x64},
    {616, IMG_wi_rain_mix_64x64},
    {620, IMG_wi_rain_mix_64x64},
    {621, IMG_wi_snow_64x64},
    {622, IMG_wi_snow_64x64},
    {701, IMG_wi_showers_64x64},
    {711, IMG_wi_smoke_64x64},
    {721, IMG_wi_day_haze_64x64},
    {731, IMG_wi_dust_64x64},
    {741, IMG_wi_fog_64x64},
    {761, IMG_wi_dust_64x64},
    {762, IMG_wi_dust_64x64},
    {771, IMG_wi_cloudy_gusts_64x64},
    {781, IMG_wi_tornado_64x64},
    {800, IMG_wi_day_sunny_64x64},
    {801, IMG_wi_cloudy_gusts_64x64},
    {802, IMG_wi_cloudy_gusts_64x64},
    {803, IMG_wi_cloudy_gusts_64x64},
    {804, IMG_wi_cloudy_64x64},
    {900, IMG_wi_tornado_64x64},
    {901, IMG_wi_storm_showers_64x64},
    {902, IMG_wi_hurricane_64x64},
    {903, IMG_wi_snowflake_cold_64x64},
    {904, IMG_wi_hot_64x64},
    {905, IMG_wi_windy_64x64},
    {906, IMG_wi_hail_64x64},
    {957, IMG_wi_strong_wind_64x64}
};

const uint8_t *ICONS::getWeather160(int id, bool isNight)
{
    if(isNight){
        auto it = ICONS_WEATHER_CONDITION_NIGHT_160.find(id);
        if (it != ICONS_WEATHER_CONDITION_NIGHT_160.end()) {
            return it->second;
        }
        logW.println("Icon not in list " + String(id)); // APi Changed ?
        return IMG_wi_alien_160x160;
    }

    auto it = ICONS_WEATHER_CONDITION_DAY_160.find(id);
    if (it != ICONS_WEATHER_CONDITION_DAY_160.end()) {
        return it->second;
    }
    logW.println("Icon not in list " + String(id)); // APi Changed ?
    return IMG_wi_alien_160x160;

    /*
    auto it = ICONS_WEATHER_CONDITION_160.find(id);
    if (it != ICONS_WEATHER_CONDITION_160.end()) {
        return it->second;
    }*/
    logW.println("Icon not in list " + String(id)); // APi Changed ?
    return IMG_wi_alien_160x160;
};

const uint8_t *ICONS::getWeather64(int id, bool isNight)
{
    /*
    if(isNight){
        auto it = ICONS_WEATHER_CONDITION_NIGHT_64.find(id);
        if (it != ICONS_WEATHER_CONDITION_NIGHT_64.end()) {
            return it->second;
        }
        logW.println("Icon not in list " + String(id)); // APi Changed ?
        return IMG_wi_alien_64x64;
    }*/

    auto it = ICONS_WEATHER_CONDITION_DAY_64.find(id);
    if (it != ICONS_WEATHER_CONDITION_DAY_64.end()) {
        return it->second;
    }

    logW.println("Icon not in list " + String(id)); // APi Changed ?
    return IMG_wi_alien_64x64;

    /*
    auto it = ICONS_WEATHER_CONDITION_64.find(id);
    if (it != ICONS_WEATHER_CONDITION_64.end()) {
        return it->second;
    }
    */
    logW.println("Icon not in list " + String(id)); // APi Changed ?
    return IMG_wi_alien_64x64;
};

const uint8_t *ICONS::getWindBeaufort48(int beaufort)
{
    switch (beaufort)
    {
    case 0:
        return IMG_wi_wind_beaufort_0_48x48;
    case 1:
        return IMG_wi_wind_beaufort_1_48x48;
    case 2:
        return IMG_wi_wind_beaufort_2_48x48;
    case 3:
        return IMG_wi_wind_beaufort_3_48x48;
    case 4:
        return IMG_wi_wind_beaufort_4_48x48;
    case 5:
        return IMG_wi_wind_beaufort_5_48x48;
    case 6:
        return IMG_wi_wind_beaufort_6_48x48;
    case 7:
        return IMG_wi_wind_beaufort_7_48x48;
    case 8:
        return IMG_wi_wind_beaufort_8_48x48;
    case 9:
        return IMG_wi_wind_beaufort_9_48x48;
    case 10:
        return IMG_wi_wind_beaufort_10_48x48;
    case 11:
        return IMG_wi_wind_beaufort_11_48x48;
    case 12:
        return IMG_wi_wind_beaufort_12_48x48;
    }

    logW.println("[ICONS] Beaufort icon not found: " + String(beaufort));
    return IMG_wi_alien_48x48;
};
