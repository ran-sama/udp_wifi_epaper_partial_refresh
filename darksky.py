#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import requests, time, socket
from requests.exceptions import ReadTimeout, ConnectionError

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

baseURL = 'https://api.darksky.net/forecast/'
api = 'YOUR_API_KEY'
coordinates = '35.8765,139.5134'
metrics = 'units=ca'
ignore = 'exclude=daily,hourly,flags'
url = baseURL + api + "/" + coordinates + "?" + metrics + "&" + ignore

def main():
    try:
        print('Starting server, use <Ctrl-C> to stop')
        while True:
            try:
                r = requests.get(url)
                j = r.json()
                summary = str(j['currently']['summary'])
                temperature = str(j['currently']['temperature'])
                humidity = str(int(j['currently']['humidity'] * 100))
                pressure = str(j['currently']['pressure'])
                windSpeed = str(int(j['currently']['windSpeed']))
                precipProbability = str(int(j['currently']['precipProbability'] * 100))
                visibility = str(j['currently']['visibility'])
                cloudCover = str(int(j['currently']['cloudCover'] * 100))
                uvIndex =  str(j['currently']['uvIndex'])
                ozone =  str(int(j['currently']['ozone'] ))
                line1 = summary
                line2 = "$" + temperature + " Celsius"
                line3 = "$" + humidity + "% rel. Hum."
                line4 = "$" +  pressure + " hPa"
                line5 = "$" + windSpeed + " km/h Wind"
                line6 = "$" + "UV:" + uvIndex + " / O3:" + ozone
                line7 = "$" + precipProbability + "% Rain prob."
                line8 = "$" + visibility + " km View"
                line9 = "$" + cloudCover + "% Clouds"
                replyString =  line1 + line2 + line3 + line4 + line5 + line6 + line7 + line8 + line9
                print(replyString)
                sock.sendto(replyString.encode(), ("10.0.0.21", 8888))
            except (ReadTimeout, ConnectionError):
                print("A request failed")
                pass
            time.sleep(120)
    except KeyboardInterrupt:
        print(' received, shutting down server')

if __name__ == '__main__':
    main()
