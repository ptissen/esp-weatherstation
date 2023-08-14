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

 #include "displayhandler.h"
 
#include <Arduino.h>
#include <math.h>
#include "config/config.h"
#include "version/version.h"
#include "locale/locale_de.h"

#include "../lib/GxEPD2/GxEPD2_display_selection_new_style.h"

#include "globalvar.h"
#include "helper.h"
#include "helper_conversions.h"
#include "helper_fonts.h"
#include "helper_icons.h"
#include "locale/locale_de.h"
#include "logging.h"

#define UNUSED(x) (void)(x)

void DisplayHandler::ini() {
    logI.println("\n------------ DISPLAY ------------");
    
    if (m_isInit)
        return;

    display.init(115200, true, 2, false);
    display.setRotation(0);
    display.setTextSize(1);
    display.setTextWrap(false);
    display.setTextColor(GxEPD_BLACK);
    display.setFullWindow();
    m_isInit = true;
    delay(20);
}

void DisplayHandler::off(){
    delay(1);
    display.powerOff();
    delay(10);
    m_isInit = false;
}

void DisplayHandler::drawError(ERROR_t err) {

    logD.println("  Begin draw error");
    const uint8_t *bitmap = IMG_bug_solid_256x256;
    char str[20] = "";

    switch (err)
    {
        case ERR_BATTERY:   
            bitmap = IMG_battery_0_bar_256x256; 
            strncpy ( str, TXT_ERROR_BATTERY_LOW, sizeof(str) );
            break;
        case ERR_WIFI:      
            bitmap = IMG_wifi_off_256x256;
            strncpy ( str, TXT_ERROR_WIFI, sizeof(str) );
            break;
        case ERR_API:       
            bitmap = IMG_wi_cloud_down_256x256;
            strncpy ( str, TXT_ERROR_API, sizeof(str) );
            break;
        case ERR_TIME:      
            bitmap = IMG_wi_time_4_256x256;
            strncpy ( str, TXT_ERROR_TIME, sizeof(str) );
            break;
        case ERR_SYSTEM:    
            bitmap = IMG_bug_solid_256x256;
            strncpy ( str, TXT_ERROR_SYSTEM, sizeof(str) );
            break;
        default:
            bitmap = IMG_bug_solid_256x256;
            strncpy ( str, TXT_ERROR_UNKNOWN, sizeof(str) );
    }
    logD.print("  Display error txt: ");
    logD.println(str);

    /**
     * Calculate spacing for center alignment
     * DISPLAY  : 480
     * TXT_SP   : 16
     * FONT     : 26 pt = 35 px
     * IMG      : 256 
    */
    const int16_t c_txtsp = 36;
    const int16_t c_font = 36;
    const int16_t c_img = 256;
    const int16_t c_sp = (DISP_HEIGHT - c_img - c_txtsp - c_font) / 2;
    const int16_t y_img = c_sp;
    const int16_t y_txt = c_sp + c_img + c_txtsp;

    ini();
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
        display.setFont(&FONT_32px);
        drawText(DISP_WIDTH / 2, y_txt, str, ALIGN_CB);

        display.drawInvertedBitmap(DISP_WIDTH / 2 - 256 / 2, y_img,
                                    bitmap, 256, 256, GxEPD_BLACK);
        display.display();
        delay(15000);
    }
    while (display.nextPage());
    off();
    logD.println("  Draw error finished");
}

void DisplayHandler::drawStatusBar() {
    // Print1Version
    logI.println("  print StatusBar");
    display.setFont(&FONT_8px);
    display.setCursor(200, 200);

    const int16_t sp = 2;
    const int16_t spl = 4;
    const int16_t spll = 16;

    int16_t pos = DISP_WIDTH - sp;

    // --- Version ---
    drawText(pos, DISP_HEIGHT - sp, VERSION_INFO, ALIGN_RB);
    pos -= getTextWidth(VERSION_INFO) + spl + 12;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 12, IMG_code_branch_solid_12x12, 12, 12, GxEPD_BLACK);
    pos -= spll;

    // --- BATTERY ---
    String txt = String(GL_BAT_PERCENTAGE) + "% (" + String( round(100.0 * GL_BAT_VOLTAGE) / 100.0, 2 ) + "v)";
    drawText(pos, DISP_HEIGHT - 1 - 2, txt, ALIGN_RB);
    pos -= getTextWidth(txt) + spl + 24;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 17,
                                ICONS::getBattery24(GL_BAT_PERCENTAGE), 24, 24, GxEPD_BLACK);
    pos -= spll;

    // --- WiFi ---
    int16_t dbm = GL_WIFI_DBM;
    txt = String(TEXT_getWiFidesc(dbm));

    if (dbm != 0)
    {
        txt += " (" + String(dbm) + "dBm)";
    }
    drawText(pos, DISP_HEIGHT - 1 - 2, txt, ALIGN_RB);
    pos -= getTextWidth(txt) + spl + 16;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 13, ICONS::getWifi16(dbm),
                                16, 16, GxEPD_BLACK);
    pos -= spll;

    //  --- Last Refresh ---
    char t[20] = "";
    strftime(t, 20, "%d.%m.%Y %H:%M", GL_TIME_LASTUPDATE);
    drawText(pos, DISP_HEIGHT - 1 - 2, t, ALIGN_RB);
    pos -= getTextWidth(t) + 12 + spl;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 12, IMG_sync_12x12, 12, 12, GxEPD_BLACK);
    pos -= spll;

    // City
    drawText(pos, DISP_HEIGHT - 1 - 2, OWM_CITY_STRING, ALIGN_RB);
    pos -= getTextWidth(OWM_CITY_STRING) + 12 + spl;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 12, IMG_place_black_24dp_12x12, 12, 12, GxEPD_BLACK);
    pos -= spll;

    // status
    if (!GL_STATUS.isEmpty())
    {
        drawText(pos, DISP_HEIGHT - 1 - 2, GL_STATUS, ALIGN_RB);
        pos -= getTextWidth(GL_STATUS) + 24 + spl;
        display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 18, IMG_error_icon_24x24,
                                    24, 24, GxEPD_BLACK);
    }

}

void DisplayHandler::drawWeatherCurrent(const OpenWeatherMap::owm_current_weather_t &owm) {
    int16_t id = owm.weather.id;
    bool isNight = String(owm.weather.icon).endsWith("n");
    String dataStr = String(round(owm.main.temp),0);
    String unitStr = TXT_UNITS_TEMP;
    String feelStr =  String(TEXT_FEELS_LIKE) + ' '
                        + String(round(owm.main.feels_like),0)
                        + String(TXT_UNITS_TEMP);

    
    display.drawInvertedBitmap(0, 0, 
                                ICONS::getWeather160(id,isNight),
                                160, 160, GxEPD_BLACK);
    display.setFont(&FONT_64px);
    drawText(160 + 100, 90 , dataStr, ALIGN_RB);
    display.setFont(&FONT_24px);
    drawText(160 + 105, 95 - 64 + 24 , unitStr, ALIGN_LB);
    display.setFont(&FONT_16px);
    drawText(160 + 80,  120, feelStr, ALIGN_CB);
}

void DisplayHandler::drawWeatherInfos(const OpenWeatherMap::owm_current_weather_t &owm, const OpenWeatherMap::owm_air_pollution_t &owm_ap)
{
    const int16_t x0 = 25;
    const int16_t y0 = 160;
    const int16_t dx = 150; // 800 / 5 - 10 = 150 
    const int16_t is = 48;

    #define LOC_MAXLEN 20
    char vSunrise[LOC_MAXLEN]  = "";
    char vSunset[LOC_MAXLEN]   = "";
    char vHumidity[LOC_MAXLEN] = "";
    char vWind[LOC_MAXLEN]     = "";
    char vAQI[LOC_MAXLEN]      = "";

    // Sunrise
    TIME_timeToString(owm.sys.sunrise, vSunrise, 20);

    // Sunset
    TIME_timeToString(owm.sys.sunset, vSunset, 20);

    // Humidity
    snprintf(vHumidity, 20, "%2.0i %%", owm.main.humidity);

    // Wind
    snprintf(vWind, 20, "%1.0f m/s", owm.wind.speed);
    
    // air quality index
    snprintf(vAQI, 20, "%s", TEXT_getAQIdesc(owm_ap.list[0].main.aqi));

    // Icons
    display.drawInvertedBitmap(x0 + dx * 0, y0,
                                IMG_wi_sunrise_48x48,
                                48, 48, GxEPD_BLACK);
    display.drawInvertedBitmap(x0 + dx * 1, y0,
                                IMG_wi_sunset_48x48, 
                                48, 48, GxEPD_BLACK);
    display.drawInvertedBitmap(x0 + dx * 2, y0,
                                IMG_wi_humidity_48x48,
                                48, 48, GxEPD_BLACK);
    display.drawInvertedBitmap(x0 + dx * 3, y0,
                                ICONS::getWindBeaufort48(CONVERT_WIND_msToBeaufort(owm.wind.speed)),
                                48, 48, GxEPD_BLACK);
    display.drawInvertedBitmap(x0 + dx * 4, y0,
                                IMG_wi_humidity_48x48, 
                                48, 48, GxEPD_BLACK);

    // Labels
    display.setFont(&FONT_12px);
    drawText(x0 + dx * 0 + is, y0 + 10 + (48 - 30) /2, TXT_SUNRISE, ALIGN_LB);
    drawText(x0 + dx * 1 + is, y0 + 10 + (48 - 30) /2, TXT_SUNSET, ALIGN_LB);
    drawText(x0 + dx * 2 + is, y0 + 10 + (48 - 30) /2, TXT_HUMIDITY, ALIGN_LB);
    drawText(x0 + dx * 3 + is, y0 + 10 + (48 - 30) /2, TXT_WIND, ALIGN_LB);
    drawText(x0 + dx * 4 + is, y0 + 10 + (48 - 30) /2, TXT_AIR_QUALITY, ALIGN_LB);

    // Value
    display.setFont(&FONT_16px);
    drawText(x0 + dx * 0 + is, y0  + (48 - 30) /2 + 10 + 4 + 16, vSunrise, ALIGN_LB);
    drawText(x0 + dx * 1 + is, y0  + (48 - 30) /2 + 10 + 4 + 16, vSunset, ALIGN_LB);
    drawText(x0 + dx * 2 + is, y0  + (48 - 30) /2 + 10 + 4 + 16, vHumidity, ALIGN_LB);
    drawText(x0 + dx * 3 + is, y0  + (48 - 30) /2 + 10 + 4 + 16, vWind, ALIGN_LB);
    drawText(x0 + dx * 4 + is, y0  + (48 - 30) /2 + 10 + 4 + 16, vAQI, ALIGN_LB);
}

void DisplayHandler::drawForecastDays(const OpenWeatherMap::owm_daily_t &owm) {
    const int16_t x0 = 350;
    const int16_t y0 = 20;
    const int16_t dx = 90;
    const int16_t imSize = 64;

    for (int16_t i = 0; i < 5; ++i)
    {
        int16_t x = x0 + dx * i;
        String day = TIME_timeToWeekday(owm.day[i].dt);
        String tmin = String(owm.day[i].temp_min) + "\xB0";
        String tmax = String(owm.day[i].temp_max) + "\xB0"; 

        display.drawInvertedBitmap(x + (dx - imSize) / 2 , y0 + 20,
                                    ICONS::getWeather64(owm.day[i].id, false),
                                    imSize, imSize, GxEPD_BLACK);
        // Day
        display.setFont(&FONT_24px);
        drawText(x + dx / 2 , y0 + 16,  day, ALIGN_CB);

        // Temperatur
        display.setFont(&FONT_16px);
        drawText(x + dx / 2 + 2, y0 + 40 + imSize, tmax, ALIGN_RB);

        display.setFont(&FONT_12px);
        drawText(x + dx / 2 + 4, y0 + 40 + imSize, tmin, ALIGN_LB);
    }
}

void DisplayHandler::update(const OpenWeatherMap &owm) {
    ini();
    display.firstPage();
    do {
        drawStatusBar();
        drawWeatherCurrent(owm.m_cwd);
        drawForecastDays(owm.m_daily);
        drawForecastGraph(owm.m_5df);
        drawWeatherInfos(owm.m_cwd, owm.m_ap);
        delay(15000);
    }
    while (display.nextPage());
    off();
}

void DisplayHandler::drawForecastGraph(const OpenWeatherMap::owm_5_days_forecast_t &owm)
{
    const int16_t xMargin = 4;
    const int16_t xLegend = 60;
    const int16_t xSizeMax = DISP_WIDTH - 2 * xMargin - 2 * xLegend;

    const int16_t dataCount = 17;
    const int16_t xDataStep = xSizeMax / (dataCount - 1);
    const int16_t xSize =  xDataStep * (dataCount - 1);
    const int16_t xMissAlign = (xSizeMax - xSize) / 2;

    const int16_t x0 = xMargin;
    const int16_t x1 = x0 + xMissAlign;
    const int16_t x2 = x1 + xLegend;
    const int16_t x3 = x2 + xSize;
    //const int16_t x4 = x3 + xLegend;
    //const int16_t x5 = x4 + xMissAlign;
    //const int16_t x6 = x5 + xMargin;

    const int16_t yMin = 240;
    const int16_t yMax = DISP_HEIGHT - 16;

    const int16_t ySizePxMax = yMax - yMin;
    const int16_t yLegend = 40;   
    const int16_t yCount = 5;
    const int16_t yDataStepPx = (ySizePxMax - yLegend) / yCount; 
    const int16_t ySizePx = yDataStepPx * yCount;
    const int16_t yMissAlign = (ySizePxMax - yLegend - ySizePx) / 2;

    const int16_t y0 = yMin;
    const int16_t y1 = y0 + yMissAlign;
    const int16_t y2 = y1 + ySizePx;
    //const int16_t y3 = y2 + yLegend;
    //const int16_t y4 = y3 + yMissAlign;

    const int16_t xTickSize = 6;

    // Find temp range
    float tMax = owm.list[0].main.temp;
    float tMin = owm.list[0].main.temp;
    for (int16_t i = 1; i < dataCount; ++i)
    {
        tMin = min(tMin, owm.list[i].main.temp);
        tMax = max(tMax, owm.list[i].main.temp);
    }
    logD.println("tMin: "+ String(tMin));
    logD.println("tMax: " + String(tMax));

    int16_t mod = (int16_t)  roundf(tMax) % 5;
    int16_t tempMax = (int16_t)  roundf(tMax) - mod;
    if (mod > 0) {
        tempMax += 5;
    }

    mod = (int16_t)  roundf(tMin) % 5;
    int16_t tempMin = (int16_t)  roundf(tMin) - mod;
//    if (mod > 0) {
//        tempMin -= 5;
//    }
    logD.println("tenmpMax: "+ String(tempMax));
    logD.println("tempMin: " + String(tempMin));

    // Find temp offset
    int16_t tempOffset = tempMin;

    int16_t tempRange = 5 * 5;
    logD.println("TempRang: " + String(tempRange));

    logD.println("tempOffset: " + String(tempOffset));

    // Find tempSkale
    float tempPxPerTemp = (float) ySizePx / (float) tempRange;
    logD.println("tempPxPerTemp: " + String(tempPxPerTemp));

    // Draw X Axis
    display.drawLine(x2, y2    , x3, y2,     GxEPD_BLACK);
    display.drawLine(x2, y2 + 1, x3, y2 + 1, GxEPD_BLACK);

    // Draw Legend x-Achse
    for (int16_t i = 0; i < dataCount; i+=2){
        int16_t tx = x2 + i * xDataStep;
        display.drawLine(tx    , y2, tx    , y2 + xTickSize, GxEPD_BLACK);
        display.drawLine(tx + 1, y2, tx + 1, y2 + xTickSize, GxEPD_BLACK);  

        char t [10] = "";
        TIME_timeToString((time_t) owm.list[i].dt, t, 10);
        display.setFont(&FONT_12px);
        drawText(tx, y2 + xTickSize + 14, t , ALIGN_CB);

        float pxC = round((owm.list[i].main.temp - tempOffset) * tempPxPerTemp);
        display.fillCircle(tx, y2 - pxC, 4, GxEPD_BLACK);

        // Draw temperature text
        String temp = String((int16_t)  roundf(owm.list[i].main.temp)) + "\xB0";

        display.setFont(&FONT_16px);
        if(i == 0)
            drawText(tx, y2 - pxC - 16, temp, ALIGN_LB);
        else if ( i+4 >= dataCount )
            drawText(tx, y2 - pxC - 16, temp, ALIGN_RB);
        else
            drawText(tx, y2 - pxC - 16, temp, ALIGN_CB);
    }

    // Draw Legend y-Achse
    //display.setRotation(3);
    //display.setFont(&FONT_12px);
    //drawText(yLegend + (y1 - y0) / 2, 20, "Temperatur in C", ALIGN_CB);
    //drawText(yLegend + (y1 - y0) / 2, DISP_WIDTH - 4, "Regenwahrscheinlichkeit in %", ALIGN_CB);
    //display.setRotation(0);

    int16_t ty = y2;

    display.setFont(&FONT_12px);
    for (int16_t i = 0; i <= yCount; i++)
    {  
        // Draw dotted x axis
        for (int16_t x = x2
        ; x <= x3; x += 6)
        {
            display.drawPixel(x, ty, GxEPD_BLACK);
        }
        
        // Legend Temp
        String str = String(tempOffset + i * 5) + "\xB0";
        drawText(x1 + xLegend / 2, ty + 6, str, ALIGN_CB);

        // Legend Rain
        //  str = String(i * 20) + "%";
        //  drawText(x3 + xLegend / 2, ty + 6, str, ALIGN_CB);
        
        ty -= yDataStepPx;
    }

    // Draw Temperature    
    int16_t txl,txr;
    for (int16_t i = 1; i < dataCount; ++i)
    {
        float pxL =  round((owm.list[i -1].main.temp - tempOffset) * tempPxPerTemp);
        float pxC =  round((owm.list[i].main.temp - tempOffset) * tempPxPerTemp);

        txr = x2 + i     * xDataStep;
        txl = x2 + (i-1) * xDataStep;

        display.drawLine(txl    , y2 - pxL    , txr    , y2 - pxC    , GxEPD_BLACK);
        display.drawLine(txl    , y2 - pxL + 1, txr    , y2 - pxC + 1, GxEPD_BLACK);
        display.drawLine(txl - 1, y2 - pxL    , txr - 1, y2 - pxC    , GxEPD_BLACK);
    }
}

bool DisplayHandler::isInit() {
    return m_isInit;
}

void DisplayHandler::drawText(int16_t x0, int16_t y0, String text, ALIGN_t align)
{
    int16_t tx, ty;
    uint16_t w, h;
    int16_t x;
    display.getTextBounds(text, x0, y0, &tx, &ty, &w, &h);

    switch (align)
    {
    case ALIGN_LB:
        x = x0;
        break;
    case ALIGN_CB:
        x = x0 - w / 2;
        break;
    case ALIGN_RB:
        x = x0 - w;
        break;
    default:
        x = x0;
        break;
    }
    display.setCursor(x, y0);
    display.print(text);
}

uint16_t DisplayHandler::getTextWidth(String text)
{
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    return w;
}