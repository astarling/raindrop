EESchema Schematic File Version 5
LIBS:power
LIBS:74xx
EELAYER 30 0
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
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
$Comp
L power:+3V3 #PWR0101
U 1 1 5D830AB8
P 5850 2475
F 0 "#PWR0101" H 5850 2325 50  0001 C CNN
F 1 "+3V3" H 5865 2648 50  0000 C CNN
F 2 "" H 5850 2475 50  0001 C CNN
F 3 "" H 5850 2475 50  0001 C CNN
	1    5850 2475
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D83ADEE
P 6675 3350
F 0 "#PWR0102" H 6675 3100 50  0001 C CNN
F 1 "GND" H 6680 3177 50  0000 C CNN
F 2 "" H 6675 3350 50  0001 C CNN
F 3 "" H 6675 3350 50  0001 C CNN
	1    6675 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3250 6675 3250
Connection ~ 5850 4150
Connection ~ 5850 2475
Text Label 6350 3950 0    50   ~ 0
RFM_IRQ
$Comp
L power:GND #PWR0103
U 1 1 5D832E59
P 5625 2775
F 0 "#PWR0103" H 5625 2525 50  0001 C CNN
F 1 "GND" H 5630 2602 50  0000 C CNN
F 2 "" H 5625 2775 50  0001 C CNN
F 3 "" H 5625 2775 50  0001 C CNN
	1    5625 2775
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5D831C25
P 5625 2625
F 0 "C1" H 5740 2671 50  0000 L CNN
F 1 "C" H 5740 2580 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5663 2475 50  0001 C CNN
F 3 "~" H 5625 2625 50  0001 C CNN
	1    5625 2625
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2475 5850 3050
Wire Wire Line
	5750 4150 5850 4150
Wire Wire Line
	5850 4150 5950 4150
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5D83A63A
P 6875 3250
F 0 "J1" H 6847 3132 50  0000 R CNN
F 1 "ANT" H 6847 3223 50  0000 R CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 6875 3250 50  0001 C CNN
F 3 "~" H 6875 3250 50  0001 C CNN
	1    6875 3250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5D822D52
P 5850 4150
F 0 "#PWR0104" H 5850 3900 50  0001 C CNN
F 1 "GND" H 5855 3977 50  0000 C CNN
F 2 "" H 5850 4150 50  0001 C CNN
F 3 "" H 5850 4150 50  0001 C CNN
	1    5850 4150
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:RFM95W-868S2 U1
U 1 1 5D82CC67
P 5850 3550
F 0 "U1" H 5500 4000 50  0000 C CNN
F 1 "RFM95W-868S2" H 6225 4025 50  0000 C CNN
F 2 "miceuz-lib:RFM95" H 2550 5200 50  0001 C CNN
F 3 "https://www.hoperf.com/data/upload/portal/20181127/5bfcbea20e9ef.pdf" H 2550 5200 50  0001 C CNN
	1    5850 3550
	1    0    0    -1  
$EndComp
Text Label 5350 3350 2    50   ~ 0
RFM_MOSI
Text Label 5350 3750 2    50   ~ 0
RFM_RST
Wire Wire Line
	5850 2475 5625 2475
Text Label 5350 3450 2    50   ~ 0
RFM_MISO
Text Label 5350 3250 2    50   ~ 0
RFM_SCK
Text Label 5350 3550 2    50   ~ 0
RFM_NSS
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 5D895E52
P 3600 4575
F 0 "J2" H 3518 5092 50  0000 C CNN
F 1 "Conn_01x08" H 3518 5001 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x08_Pitch2.54mm" H 3600 4575 50  0001 C CNN
F 3 "~" H 3600 4575 50  0001 C CNN
	1    3600 4575
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J3
U 1 1 5D893DE2
P 3600 3575
F 0 "J3" H 3680 3567 50  0000 L CNN
F 1 "Conn_01x08" H 3680 3476 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x08_Pitch2.54mm" H 3600 3575 50  0001 C CNN
F 3 "~" H 3600 3575 50  0001 C CNN
	1    3600 3575
	-1   0    0    -1  
$EndComp
Text Label 6350 3450 0    50   ~ 0
DIO5
Text Label 6350 3550 0    50   ~ 0
DIO04
Text Label 6350 3650 0    50   ~ 0
DIO03
Text Label 6350 3750 0    50   ~ 0
DIO02
Text Label 6350 3850 0    50   ~ 0
DIO01
Text Label 6350 3250 0    50   ~ 0
ANT
$Comp
L power:GND #PWR?
U 1 1 5D89C8EE
P 4475 3275
F 0 "#PWR?" H 4475 3025 50  0001 C CNN
F 1 "GND" H 4480 3102 50  0000 C CNN
F 2 "" H 4475 3275 50  0001 C CNN
F 3 "" H 4475 3275 50  0001 C CNN
	1    4475 3275
	1    0    0    -1  
$EndComp
Wire Wire Line
	4475 3275 4350 3275
Text Label 3800 3375 0    50   ~ 0
RFM_MISO
Text Label 3800 3475 0    50   ~ 0
RFM_MOSI
Text Label 3800 3575 0    50   ~ 0
RFM_SCK
Text Label 3800 3675 0    50   ~ 0
RFM_NSS
Text Label 3800 3775 0    50   ~ 0
RFM_RST
Text Label 3800 3875 0    50   ~ 0
DIO5
Wire Wire Line
	3800 3975 4350 3975
Wire Wire Line
	4350 3975 4350 3275
Connection ~ 4350 3275
Wire Wire Line
	4350 3275 3800 3275
Text Label 3800 4275 0    50   ~ 0
DIO02
Text Label 3800 4375 0    50   ~ 0
DIO01
Text Label 3800 4475 0    50   ~ 0
RFM_IRQ
$Comp
L power:+3V3 #PWR?
U 1 1 5D8A2052
P 4350 4575
F 0 "#PWR?" H 4350 4425 50  0001 C CNN
F 1 "+3V3" H 4365 4748 50  0000 C CNN
F 2 "" H 4350 4575 50  0001 C CNN
F 3 "" H 4350 4575 50  0001 C CNN
	1    4350 4575
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4575 3800 4575
Text Label 3800 4675 0    50   ~ 0
DIO04
Text Label 3800 4775 0    50   ~ 0
DIO03
$Comp
L power:GND #PWR?
U 1 1 5D8A248B
P 4350 4875
F 0 "#PWR?" H 4350 4625 50  0001 C CNN
F 1 "GND" H 4355 4702 50  0000 C CNN
F 2 "" H 4350 4875 50  0001 C CNN
F 3 "" H 4350 4875 50  0001 C CNN
	1    4350 4875
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4875 3800 4875
Text Label 3800 4975 0    50   ~ 0
ANT
$EndSCHEMATC
