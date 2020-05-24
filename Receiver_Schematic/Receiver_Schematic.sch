EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Adafruit_HUZZAH_ESP8266_breakout A?
U 1 1 5CC056D0
P 4200 3800
F 0 "A?" H 4200 2914 50  0000 C CNN
F 1 "Adafruit_HUZZAH_ESP8266_breakout" H 4200 2823 50  0000 C CNN
F 2 "" H 4400 4400 50  0001 C CNN
F 3 "https://www.adafruit.com/product/2471" H 4500 4500 50  0001 C CNN
	1    4200 3800
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Optical:BPW21 D?
U 1 1 5CC0578A
P 5250 3600
F 0 "D?" H 5200 3895 50  0000 C CNN
F 1 "BPW21" H 5200 3804 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-5-2_Window" H 5250 3775 50  0001 C CNN
F 3 "http://techwww.in.tu-clausthal.de/site/Dokumentation/Dioden/Fotodioden/BPW21-Fotodiode.pdf" H 5200 3600 50  0001 C CNN
	1    5250 3600
	1    0    0    -1  
$EndComp
$Comp
L Comparator:LM393 U?
U 1 1 5CC05832
P 5900 3700
F 0 "U?" H 5900 3333 50  0000 C CNN
F 1 "LM393" H 5900 3424 50  0000 C CNN
F 2 "" H 5900 3700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393-n.pdf" H 5900 3700 50  0001 C CNN
	1    5900 3700
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5CC0598A
P 5450 3300
F 0 "R?" H 5520 3346 50  0000 L CNN
F 1 "R" H 5520 3255 50  0000 L CNN
F 2 "" V 5380 3300 50  0001 C CNN
F 3 "~" H 5450 3300 50  0001 C CNN
	1    5450 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3700 6200 2750
Wire Wire Line
	6200 2750 3350 2750
Wire Wire Line
	3350 2750 3350 4200
Wire Wire Line
	3350 4200 3600 4200
$Comp
L Device:R_POT RV?
U 1 1 5CC05B9F
P 5450 4050
F 0 "RV?" H 5380 4096 50  0000 R CNN
F 1 "R_POT" H 5380 4005 50  0000 R CNN
F 2 "" H 5450 4050 50  0001 C CNN
F 3 "~" H 5450 4050 50  0001 C CNN
	1    5450 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5CC05C34
P 5450 3000
F 0 "#PWR?" H 5450 2850 50  0001 C CNN
F 1 "+5V" H 5465 3173 50  0000 C CNN
F 2 "" H 5450 3000 50  0001 C CNN
F 3 "" H 5450 3000 50  0001 C CNN
	1    5450 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC05CA6
P 5450 4400
F 0 "#PWR?" H 5450 4150 50  0001 C CNN
F 1 "GND" H 5455 4227 50  0000 C CNN
F 2 "" H 5450 4400 50  0001 C CNN
F 3 "" H 5450 4400 50  0001 C CNN
	1    5450 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3000 5450 3150
Wire Wire Line
	5450 3450 5450 3600
Wire Wire Line
	5450 3600 5600 3600
Wire Wire Line
	5450 3600 5350 3600
Connection ~ 5450 3600
Wire Wire Line
	5450 4200 5450 4300
Wire Wire Line
	5050 3600 5050 4300
Wire Wire Line
	5050 4300 5450 4300
Connection ~ 5450 4300
Wire Wire Line
	5450 4300 5450 4350
Wire Wire Line
	5450 3900 5450 3800
Wire Wire Line
	5450 3800 5600 3800
Wire Wire Line
	4300 4600 4900 4600
Wire Wire Line
	4900 4600 4900 4350
Wire Wire Line
	4900 4350 5450 4350
Connection ~ 5450 4350
Wire Wire Line
	5450 4350 5450 4400
$Comp
L power:+3.3V #PWR?
U 1 1 5CC06032
P 4800 3000
F 0 "#PWR?" H 4800 2850 50  0001 C CNN
F 1 "+3.3V" H 4815 3173 50  0000 C CNN
F 2 "" H 4800 3000 50  0001 C CNN
F 3 "" H 4800 3000 50  0001 C CNN
	1    4800 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 3000 4800 3000
$EndSCHEMATC
