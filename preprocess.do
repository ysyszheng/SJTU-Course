cd "/home/vincent/Documents/Obsidian Vault/Econometrics/data/"

// ***************
//    核心变量	//
// ***************
// 2010年家庭样本编码 | 18年省国标码 | 现住房价值（万元）| 现住房面积（平方米）| 全部家庭纯收入（元）| 家庭总支出（元）| 家庭净资产（元）| 2018年家庭成员人口数 | 您家现住房归谁所有
// fid provcd hp size inc comp asset num belong

use 2018.dta, clear
append using 2016.dta
append using 2014.dta
append using 2012.dta
append using 2010.dta
order fid year

replace hp = hp*10000 // RMB
replace hpm = hpm*10000 // RMB

rm "./main.dta"
save "./main.dta"

use "./main.dta"
do "/home/vincent/Documents/Obsidian Vault/Econometrics/code/renter.do"
do "/home/vincent/Documents/Obsidian Vault/Econometrics/code/state.do"

/* // ***************
//    Renter	//
// ***************
set seed 0001
gen tmp = runiform()
sort tmp

gen treated = belong==0
psmatch2 treated provcd inc num, out(hp) logit ate neighbor(1) common caliper(.05) ties if year=2010 */

// ***************
//    log	//
// ***************
gen lcomp = log(comp+1)
gen lhp = log(hp+1)
gen lhpm = log(hpm)
gen linc = log(inc+1)
gen lsize = log(size+1)
gen lsave = log(save+1)
gen lmort = log(mort+1)
gen ldebt = log(debt+1)
gen lrent = log(rent+1)
gen lgdp = log(gdp)
/* gen lasset = 0
replace lasset = log(1+asset) if asset>=0
replace lasset = -log(1-asset) if asset<0 */

drop if lhp<=0
drop if (lcomp<=5|lcomp>=15)&belong==1
drop if (lcomp<=8|lcomp>=13)&belong==0

label define ownership 1"Owner" 0"Renter" 
label value belong ownership
label var year "year"
label var belong "house ownership"
label var hp "现住房价值（元）"
label var num "家庭成员人口数"

/* egen mis = rowmiss(_all)
drop if mis
drop mis */

bys fid: gen nyear=[_N]
keep if nyear==5
drop nyear

rm "./main.dta"
save "./main.dta"
