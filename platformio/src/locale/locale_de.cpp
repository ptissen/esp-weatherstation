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


#include "locale_de.h"

#include <vector>
#include <Arduino.h>

// --------------------------------------------------------------------------
// --- ERRORS ---
const char *TXT_ERROR_UNKNOWN                   = "ERROR";
const char *TXT_ERROR_BATTERY_LOW               = "Battery low";
const char *TXT_ERROR_WIFI                      = "Wifi unavailable";
const char *TXT_ERROR_API                       = "Weather data unavailable";
const char *TXT_ERROR_TIME                      = "Time Error";
const char *TXT_ERROR_SYSTEM                    = "Internal Error";

// --------------------------------------------------------------------------
// --- TIME ---
const char *TXT_DATETIME_LONG                   = "%a %d %b %Y %T %Z";
const char *TXT_DATE                            = "%d.%m.%y";
const char *TXT_TIME                            = "%T";
const char *TXT_TIME_SHORT                      = "%T";

// --------------------------------------------------------------------------
// --- CURRENT CONDITIONS ---
const char *TXT_SUNRISE                         = "Aufgang";
const char *TXT_SUNSET                          = "Untergang";
const char *TXT_HUMIDITY                        = "Feuchtigkeit";
const char *TXT_WIND                            = "Wind";
const char *TXT_AIR_QUALITY                     = "Luftqualit\xE4t";

// --------------------------------------------------------------------------
// --- WIFI ---
const char *TXT_WIFI_EXCELLENT                  = "Optimal";
const char *TXT_WIFI_VERYGOOD                   = "Sehr Gut";
const char *TXT_WIFI_GOOD                       = "Gut";
const char *TXT_WIFI_FAIR                       = "Ausreichend";
const char *TXT_WIFI_WEAK                       = "Schwach";
const char *TXT_WIFI_NO_CONNECTION              = "Keine Verbindung";

// --------------------------------------------------------------------------
// --- UNITS ---
const char *TXT_UNITS_TEMP                      = "\xB0" "C";
const char *TXT_UNITS_SPEED_METERSPERSECOND     = "m/s";

// --------------------------------------------------------------------------
// --- CALENDAR ---
const char *LC_DAY[7]           = {"Sonntag", "Montag", "Dienstag", "Mittwoch",
                                   "Donnerstag", "Freitag", "Samstag"};
const char *LC_DAY_AB[7]        = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
const char *LC_MONTH[12]        = {"Januar",    "Februar",  "M\xE4rz",  "April",
                                   "Mai",       "Juni",     "Juli",     "August",
                                    "September", "Oktober",  "November", "Dezember"};
const char *LC_MONTH_AB[12]     = {"Jan", "Feb", "M\xE4r", "Apr", "Mai", "Jun",
                                   "Jul", "Aug", "Sep",    "Okt", "Nov", "Dez"};

// --------------------------------------------------------------------------                    
const char *TEXT_FEELS_LIKE                     = "Gef\xfchlt";
const char *TXT_UNKNOWN                         = "Unbekannt";
