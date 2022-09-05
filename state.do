// ***************
// 	state	//
// ***************
gen gdp = 0 // billion RMB
gen unemp = 0 // unemployment rate

// 11 北京市
replace gdp = 14964 if provcd==11&year==2010
replace gdp = 19024.7 if provcd==11&year==2012
replace gdp = 22926 if provcd==11&year==2014
replace gdp = 27041.2 if provcd==11&year==2016
replace gdp = 33106 if provcd==11&year==2018

replace unemp = 1.4 if provcd==11&year==2010
replace unemp = 1.3 if provcd==11&year==2012
replace unemp = 1.3 if provcd==11&year==2014
replace unemp = 1.4	if provcd==11&year==2016
replace unemp = 1.4	if provcd==11&year==2018

// 12 天津市
replace gdp = 6830.8 if provcd==12&year==2010
replace gdp = 9043 if provcd==12&year==2012
replace gdp = 10640.6 if provcd==12&year==2014
replace gdp = 11477.2 if provcd==12&year==2016
replace gdp = 13362.9 if provcd==12&year==2018

replace unemp = 3.6 if provcd==12&year==2010
replace unemp = 3.6 if provcd==12&year==2012
replace unemp = 3.5 if provcd==12&year==2014
replace unemp = 3.5	if provcd==12&year==2016
replace unemp = 3.5	if provcd==12&year==2018

// 13 河北省
replace gdp = 18003.6 if provcd==13&year==2010
replace gdp = 23077.5 if provcd==13&year==2012
replace gdp = 25208.9 if provcd==13&year==2014
replace gdp = 28474.1 if provcd==13&year==2016
replace gdp = 32494.6 if provcd==13&year==2018

replace unemp = 3.9 if provcd==13&year==2010
replace unemp = 3.7 if provcd==13&year==2012
replace unemp = 3.6 if provcd==13&year==2014
replace unemp = 3.7	if provcd==13&year==2016
replace unemp = 3.3	if provcd==13&year==2018

// 14 山西省
replace gdp = 8903.9 if provcd==14&year==2010
replace gdp = 11683.1 if provcd==14&year==2012
replace gdp = 12094.7 if provcd==14&year==2014
replace gdp = 11946.4 if provcd==14&year==2016
replace gdp = 15958.1 if provcd==14&year==2018

replace unemp = 3.6 if provcd==14&year==2010
replace unemp = 3.3 if provcd==14&year==2012
replace unemp = 3.4 if provcd==14&year==2014
replace unemp = 3.5	if provcd==14&year==2016
replace unemp = 3.3	if provcd==14&year==2018

// 15 内蒙古自治区
replace gdp = 8199.9 if provcd==15&year==2010
replace gdp = 10470.1 if provcd==15&year==2012
replace gdp = 10470.1 if provcd==15&year==2014
replace gdp = 13789.3 if provcd==15&year==2016
replace gdp = 16140.8 if provcd==15&year==2018

replace unemp = 3.9 if provcd==15&year==2010
replace unemp = 3.7 if provcd==15&year==2012
replace unemp = 3.6 if provcd==15&year==2014
replace unemp = 3.7	if provcd==15&year==2016
replace unemp = 3.6	if provcd==15&year==2018

// 21 辽宁省
replace gdp = 13896.3 if provcd==21&year==2010
replace gdp = 17848.6 if provcd==21&year==2012
replace gdp = 20025.7 if provcd==21&year==2014
replace gdp = 20392.5 if provcd==21&year==2016
replace gdp = 20392.5 if provcd==21&year==2018

replace unemp = 3.6 if provcd==21&year==2010
replace unemp = 3.6 if provcd==21&year==2012
replace unemp = 3.4 if provcd==21&year==2014
replace unemp = 3.8	if provcd==21&year==2016
replace unemp = 3.9	if provcd==21&year==2018

// 22 吉林省
replace gdp = 6410.5 if provcd==22&year==2010
replace gdp = 8678.0 if provcd==22&year==2012
replace gdp = 9966.5 if provcd==22&year==2014
replace gdp = 10427.0 if provcd==22&year==2016
replace gdp = 11253.8 if provcd==22&year==2018

replace unemp = 3.8 if provcd==22&year==2010
replace unemp = 3.7 if provcd==22&year==2012
replace unemp = 3.4 if provcd==22&year==2014
replace unemp = 3.5	if provcd==22&year==2016
replace unemp = 3.5	if provcd==22&year==2018

// 23 黑龙江省
replace gdp = 8308.3 if provcd==23&year==2010
replace gdp = 11015.8 if provcd==23&year==2012
replace gdp = 12170.8 if provcd==23&year==2014
replace gdp = 11895.0 if provcd==23&year==2016
replace gdp = 12846.5	if provcd==23&year==2018

replace unemp = 4.3 if provcd==23&year==2010
replace unemp = 4.2 if provcd==23&year==2012
replace unemp = 4.5 if provcd==23&year==2014
replace unemp = 4.2	if provcd==23&year==2016
replace unemp = 4.0	if provcd==23&year==2018

// 31	上海市
replace gdp = 17915.4	if provcd==31&year==2010
replace gdp = 21305.6 if provcd==31&year==2012
replace gdp = 25269.8 if provcd==31&year==2014
replace gdp = 29887.0 if provcd==31&year==2016
replace gdp = 36011.8	if provcd==31&year==2018

replace unemp = 4.4 if provcd==31&year==2010
replace unemp = 3.1 if provcd==31&year==2012
replace unemp = 4.1 if provcd==31&year==2014
replace unemp = 4.1	if provcd==31&year==2016
replace unemp = 3.5	if provcd==31&year==2018

// 32 江苏省
replace gdp = 41383.9	if provcd==32&year==2010
replace gdp = 53701.9 if provcd==32&year==2012
replace gdp = 64830.5 if provcd==32&year==2014
replace gdp = 77350.9 if provcd==32&year==2016
replace gdp = 93207.6	if provcd==32&year==2018

replace unemp = 3.2 if provcd==32&year==2010
replace unemp = 3.1 if provcd==32&year==2012
replace unemp = 3.0 if provcd==32&year==2014
replace unemp = 3.0	if provcd==32&year==2016
replace unemp = 3.0	if provcd==32&year==2018

// 33 浙江省
replace gdp = 27399.9	if provcd==33&year==2010
replace gdp = 34382.4 if provcd==33&year==2012
replace gdp = 40023.5 if provcd==33&year==2014
replace gdp = 47254.0 if provcd==33&year==2016
replace gdp = 58002.8	if provcd==33&year==2018

replace unemp = 3.2 if provcd==33&year==2010
replace unemp = 3.0 if provcd==33&year==2012
replace unemp = 3.0 if provcd==33&year==2014
replace unemp = 2.9	if provcd==33&year==2016
replace unemp = 2.6	if provcd==33&year==2018

// 34 安徽省
replace gdp = 13249.8	if provcd==34&year==2010
replace gdp = 18341.7 if provcd==34&year==2012
replace gdp = 22519.7 if provcd==34&year==2014
replace gdp = 26307.7 if provcd==34&year==2016
replace gdp = 34010.9	if provcd==34&year==2018

replace unemp = 3.7 if provcd==34&year==2010
replace unemp = 3.7 if provcd==34&year==2012
replace unemp = 3.2 if provcd==34&year==2014
replace unemp = 3.2	if provcd==34&year==2016
replace unemp = 2.8	if provcd==34&year==2018

// 35 福建省
replace gdp = 15002.5	if provcd==35&year==2010
replace gdp = 20190.7 if provcd==35&year==2012
replace gdp = 24942.1 if provcd==35&year==2014
replace gdp = 29609.4 if provcd==35&year==2016
replace gdp = 38687.8	if provcd==35&year==2018

replace unemp = 3.8 if provcd==35&year==2010
replace unemp = 3.6 if provcd==35&year==2012
replace unemp = 3.5 if provcd==35&year==2014
replace unemp = 3.9	if provcd==35&year==2016
replace unemp = 3.7	if provcd==35&year==2018

// 36 江西省
replace gdp = 9383.2	if provcd==36&year==2010
replace gdp = 12807.7 if provcd==36&year==2012
replace gdp = 15667.8 if provcd==36&year==2014
replace gdp = 18388.6 if provcd==36&year==2016
replace gdp = 22716.5	if provcd==36&year==2018

replace unemp = 3.3 if provcd==36&year==2010
replace unemp = 3.0 if provcd==36&year==2012
replace unemp = 3.3 if provcd==36&year==2014
replace unemp = 3.4	if provcd==36&year==2016
replace unemp = 3.4	if provcd==36&year==2018

// 37 山东省
replace gdp = 33922.5	if provcd==37&year==2010
replace gdp = 42957.3 if provcd==37&year==2012
replace gdp = 42957.3 if provcd==37&year==2014
replace gdp = 58762.5 if provcd==37&year==2016
replace gdp = 66648.9	if provcd==37&year==2018

replace unemp = 3.4 if provcd==37&year==2010
replace unemp = 3.3 if provcd==37&year==2012
replace unemp = 3.3 if provcd==37&year==2014
replace unemp = 3.5	if provcd==37&year==2016
replace unemp = 3.4	if provcd==37&year==2018

// 41 河南省
replace gdp = 22655.0	if provcd==41&year==2010
replace gdp = 28961.9 if provcd==41&year==2012
replace gdp = 34574.8 if provcd==41&year==2014
replace gdp = 40249.3 if provcd==41&year==2016
replace gdp = 49935.9	if provcd==41&year==2018

replace unemp = 3.4 if provcd==41&year==2010
replace unemp = 3.1 if provcd==41&year==2012
replace unemp = 3.0 if provcd==41&year==2014
replace unemp = 3.0	if provcd==41&year==2016
replace unemp = 3.0	if provcd==41&year==2018

// 42 湖北省
replace gdp = 16226.9	if provcd==42&year==2010
replace gdp = 22590.9 if provcd==42&year==2012
replace gdp = 28242.1 if provcd==42&year==2014
replace gdp = 33353.0 if provcd==42&year==2016
replace gdp = 42022.0	if provcd==42&year==2018

replace unemp = 4.2 if provcd==42&year==2010
replace unemp = 3.8 if provcd==42&year==2012
replace unemp = 3.1 if provcd==42&year==2014
replace unemp = 2.4	if provcd==42&year==2016
replace unemp = 2.6	if provcd==42&year==2018

// 43 湖南省
replace gdp = 15574.3	if provcd==43&year==2010
replace gdp = 21207.2 if provcd==43&year==2012
replace gdp = 25881.3 if provcd==43&year==2014
replace gdp = 30853.5 if provcd==43&year==2016
replace gdp = 36329.7	if provcd==43&year==2018

replace unemp = 4.2 if provcd==43&year==2010
replace unemp = 4.2 if provcd==43&year==2012
replace unemp = 4.1 if provcd==43&year==2014
replace unemp = 4.2	if provcd==43&year==2016
replace unemp = 3.6	if provcd==43&year==2018

// 44 广东省
replace gdp = 45944.6	if provcd==44&year==2010
replace gdp = 57007.7 if provcd==44&year==2012
replace gdp = 68173.0 if provcd==44&year==2014
replace gdp = 82163.2 if provcd==44&year==2016
replace gdp = 99945.2	if provcd==44&year==2018

replace unemp = 2.5 if provcd==44&year==2010
replace unemp = 2.5 if provcd==44&year==2012
replace unemp = 2.4 if provcd==44&year==2014
replace unemp = 2.5	if provcd==44&year==2016
replace unemp = 2.4	if provcd==44&year==2018

// 45 广西壮族自治区
replace gdp = 8552.4	if provcd==45&year==2010
replace gdp = 11303.6 if provcd==45&year==2012
replace gdp = 13587.8 if provcd==45&year==2014
replace gdp = 16116.6 if provcd==45&year==2016
replace gdp = 19627.8	if provcd==45&year==2018

replace unemp = 3.7 if provcd==45&year==2010
replace unemp = 3.4 if provcd==45&year==2012
replace unemp = 3.2 if provcd==45&year==2014
replace unemp = 2.9	if provcd==45&year==2016
replace unemp = 2.3	if provcd==45&year==2018

// 46 海南省
replace gdp = 2020.5	if provcd==46&year==2010
replace gdp = 2789.4 if provcd==46&year==2012
replace gdp = 3449.0 if provcd==46&year==2014
replace gdp = 4090.2 if provcd==46&year==2016
replace gdp = 4910.7 if provcd==46&year==2018

replace unemp = 3.0 if provcd==46&year==2010
replace unemp = 2.0 if provcd==46&year==2012
replace unemp = 2.3 if provcd==46&year==2014
replace unemp = 2.4	if provcd==46&year==2016
replace unemp = 2.3	if provcd==46&year==2018

// 50 重庆市
replace gdp = 8065.3 if provcd==50&year==2010
replace gdp = 11595.4 if provcd==50&year==2012
replace gdp = 14623.8 if provcd==50&year==2014
replace gdp = 18023.0 if provcd==50&year==2016
replace gdp = 21588.8 if provcd==50&year==2018

replace unemp = 3.9 if provcd==50&year==2010
replace unemp = 3.3 if provcd==50&year==2012
replace unemp = 3.5 if provcd==50&year==2014
replace unemp = 3.7	if provcd==50&year==2016
replace unemp = 3.0	if provcd==50&year==2018

// 51 四川省
replace gdp = 17224.8 if provcd==51&year==2010
replace gdp = 23922.4 if provcd==51&year==2012
replace gdp = 28891.3 if provcd==51&year==2014
replace gdp = 33138.5 if provcd==51&year==2016
replace gdp = 42902.1 if provcd==51&year==2018

replace unemp = 4.1 if provcd==51&year==2010
replace unemp = 4.0 if provcd==51&year==2012
replace unemp = 4.2 if provcd==51&year==2014
replace unemp = 4.2	if provcd==51&year==2016
replace unemp = 3.5	if provcd==51&year==2018

// 52 贵州省
replace gdp = 4519.0 if provcd==52&year==2010
replace gdp = 6742.2 if provcd==52&year==2012
replace gdp = 9173.1 if provcd==52&year==2014
replace gdp = 11792.4 if provcd==52&year==2016
replace gdp = 15353.2 if provcd==52&year==2018

replace unemp = 3.6 if provcd==52&year==2010
replace unemp = 3.3 if provcd==52&year==2012
replace unemp = 3.3 if provcd==52&year==2014
replace unemp = 3.2	if provcd==52&year==2016
replace unemp = 3.2	if provcd==52&year==2018

// 53 云南省
replace gdp = 7735.3 if provcd==53&year==2010
replace gdp = 11097.4 if provcd==53&year==2012
replace gdp = 14041.7 if provcd==53&year==2014
replace gdp = 16369.0 if provcd==53&year==2016
replace gdp = 20880.6 if provcd==53&year==2018

replace unemp = 4.2 if provcd==53&year==2010
replace unemp = 4.0 if provcd==53&year==2012
replace unemp = 4.0 if provcd==53&year==2014
replace unemp = 3.6	if provcd==53&year==2016
replace unemp = 3.4	if provcd==53&year==2018

// 61 陕西省
replace gdp = 9845.2 if provcd==61&year==2010
replace gdp = 14142.4 if provcd==61&year==2012
replace gdp = 17402.5 if provcd==61&year==2014
replace gdp = 19045.8 if provcd==61&year==2016
replace gdp = 23941.9 if provcd==61&year==2018

replace unemp = 3.9 if provcd==61&year==2010
replace unemp = 3.2 if provcd==61&year==2012
replace unemp = 3.3 if provcd==61&year==2014
replace unemp = 3.3	if provcd==61&year==2016
replace unemp = 3.2	if provcd==61&year==2018

// 62 甘肃省
replace gdp = 3943.7 if provcd==62&year==2010
replace gdp = 5393.1 if provcd==62&year==2012
replace gdp = 6518.4 if provcd==62&year==2014
replace gdp = 6907.9 if provcd==62&year==2016
replace gdp = 8104.1 if provcd==62&year==2018

replace unemp = 3.2 if provcd==62&year==2010
replace unemp = 2.7 if provcd==62&year==2012
replace unemp = 2.2 if provcd==62&year==2014
replace unemp = 2.2	if provcd==62&year==2016
replace unemp = 2.8	if provcd==62&year==2018

// 63 青海省
replace gdp = 1144.2 if provcd==63&year==2010
replace gdp = 1528.5 if provcd==63&year==2012
replace gdp = 1847.7 if provcd==63&year==2014
replace gdp = 2258.2 if provcd==63&year==2016
replace gdp = 2748.0 if provcd==63&year==2018

replace unemp = 3.8 if provcd==63&year==2010
replace unemp = 3.4 if provcd==63&year==2012
replace unemp = 3.2 if provcd==63&year==2014
replace unemp = 3.1	if provcd==63&year==2016
replace unemp = 3.0	if provcd==63&year==2018